/*
 * Davicom DM9620 USB 2.0 10/100Mbps ethernet devices
 *
 * Peter Korsgaard <jacmet@sunsite.dk>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 * V1.0 - ftp fail fixed
 * V1.1 - model name checking, & ether plug function enhancement [0x4f, 0x20]
 * V1.2 - init tx/rx checksum
 *      - fix dm_write_shared_word(), bug fix
 *      - fix 10 Mbps link at power saving mode fail
 * V1.3 - Support kernel 2.6.31
 * V1.4 - Support eeprom write of ethtool
 *        Support DM9685
 *        Transmit Check Sum Control by Optopn (Source Code Default: Disable)
 *        Recieve Drop Check Sum Error Packet Disable as chip default
 * V1.5 - Support RK2818 (Debug the Register Function)
 * V1.6 - Solve compiler issue for Linux 2.6.35
 * V1.7 - Enable MAC Layer Flow Control and define debug_message for linux version update.
 * V1.8 - Enable PHY Layer Flow Control, clear debug code, setup default phy_id value is 1.
 *        Update dm9620_mdio_read and dm9620_mdio_write.
 *        Fix bug of ethtool eeprom write
 * V1.9 - Fixed "deverr" line 367 error in Linux 2.6.38
 * V2.0 - Fixed "dm9620_set_multicast" function CRC bug.
 * V2.1 - Add 802.3az for dm9621a
 * V2.2 - Add PID=0x1269 support CDC mode.
 * V2.3 - Add PID=0x0269 support CDC mode.
 * V2.41 - Support Linux 3.6.9
 */

//#define DEBUG

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/stddef.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/mii.h>
#include <linux/usb.h>
#include <linux/crc32.h>
#include <linux/usb/usbnet.h>
#include <linux/ctype.h>
#include <linux/skbuff.h>
#include <linux/version.h>

/* Get datasheet: http://www.davicom.com.tw */

/* control requests */
#define DM_READ_REGS	0x00
#define DM_WRITE_REGS	0x01
#define DM_READ_MEMS	0x02
#define DM_WRITE_REG	0x03
#define DM_WRITE_MEMS	0x05
#define DM_WRITE_MEM	0x07

/* registers */
#define DM_NET_CTRL		0x00
#define DM_RX_CTRL		0x05
#define DM_FLOW_CTRL	0x0a
#define DM_SHARED_CTRL	0x0b
#define DM_SHARED_ADDR	0x0c
#define DM_SHARED_DATA	0x0d	/* low + high */
#define DM_EE_PHY_L		0x0d
#define DM_EE_PHY_H		0x0e
#define DM_WAKEUP_CTRL  0x0f
#define DM_PHY_ADDR		0x10	/* 6 bytes */
#define DM_MCAST_ADDR	0x16	/* 8 bytes */
#define DM_GPR_CTRL		0x1e
#define DM_GPR_DATA		0x1f
#define DM_PID      	0x2a
#define DM_XPHY_CTRL	0x2e
#define DM_TX_CRC_CTRL	0x31
#define DM_RX_CRC_CTRL	0x32
#define DM_SMIREG       0x91
#define USB_CTRL		0xf4
#define PHY_SPEC_CFG	20
#define DM_TXRX_M       0x5C

#define MD96XX_EEPROM_MAGIC	0x9620
#define DM_MAX_MCAST		64
#define DM_MCAST_SIZE		8
#define DM_EEPROM_LEN		256
#define DM_TX_OVERHEAD		2	/* 2 byte header */
#define DM_RX_OVERHEAD_9601	7	/* 3 byte header + 4 byte crc tail */
#define DM_RX_OVERHEAD		8	/* 4 byte header + 4 byte crc tail */
#define DM_TIMEOUT			1000
#define DM_MODE9620     	0x80
#define DM_TX_CS_EN			0	/* Transmit Check Sum Control */
#define DM9620_PHY_ID		1	/* Stone add For kernel read phy register */

struct dm96xx_priv {
	int	flag_fail_count;
	u8	mode_9620;
};

#if defined(DEBUG)
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,33)
#define dm9620_print(__dev, format, args...)	netdev_dbg((__dev)->net, format, ##args)
#define dm9620_err(__dev, format, args...)		netdev_err((__dev)->net, format, ##args)
#else	//LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,33)
#define dm9620_print(dev, format, args...)		devdbg(dev, format, ##args)
#define dm9620_err(dev, format, args...)		deverr(dev, format, ##args)
#endif
#else	//!DEBUG
#define dm9620_print(dev, format, args...)		printk(format, ##args)
#define dm9620_err(dev, format, args...)		printk(format, ##args)
#endif

/* Setup ethernet address */
static unsigned param_addr[6];

static int __init dm9620_set_mac(char *str) {
	unsigned char addr[6];
	unsigned int val;
	int idx = 0;
	char *p = str, *end;

	while (*p && idx < 6) {
		val = simple_strtoul(p, &end, 16);
		if (end <= p) {
			break;
		} else {
			addr[idx++] = val;
			p = end;
			if (*p == ':'|| *p == '-') {
				p++;
			} else {
				break;
			}
		}
	}

	if (idx == 6) {
		printk("Setup ethernet address to %pM\n", addr);
		memcpy(param_addr, addr, 6);
	}

	return 1;
}
__setup("ethmac=", dm9620_set_mac);

static int dm_read(struct usbnet *dev, u8 reg, u16 length, void *data)
{
	//dm9620_print(dev, "dm_read() reg=0x%02x length=%d\n", reg, length);
	// usb_control_msg V.S. usb_submit_urb
	// USB_CTRL_SET_TIMEOUT V.S. USB_CTRL_GET_TIMEOUT
	return usb_control_msg(dev->udev,
			usb_rcvctrlpipe(dev->udev, 0),
			DM_READ_REGS,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, reg, data, length, USB_CTRL_SET_TIMEOUT);
}

static int dm_read_reg(struct usbnet *dev, u8 reg, u8 *value)
{
	u16 v[2];
	int ret;

	ret = dm_read(dev, reg, 2, v);
	*value = (u8)(v[0] & 0xff);

	return ret;
}

static int dm_write(struct usbnet *dev, u8 reg, u16 length, void *data)
{
	//dm9620_print(dev, "dm_write() reg=0x%02x, length=%d\n", reg, length);
	return usb_control_msg(dev->udev,
			usb_sndctrlpipe(dev->udev, 0),
			DM_WRITE_REGS,
			USB_DIR_OUT | USB_TYPE_VENDOR |USB_RECIP_DEVICE,
			0, reg, data, length, USB_CTRL_SET_TIMEOUT);
}

static int dm_write_reg(struct usbnet *dev, u8 reg, u8 value)
{
	//dm9620_print(dev , "dm_write_reg() reg=0x%02x, value=0x%02x\n", reg, value);
	return usb_control_msg(dev->udev,
			usb_sndctrlpipe(dev->udev, 0),
			DM_WRITE_REG,
			USB_DIR_OUT | USB_TYPE_VENDOR |USB_RECIP_DEVICE,
			value, reg, NULL, 0, USB_CTRL_SET_TIMEOUT);
}

static void dm_write_async_callback(struct urb *urb)
{
	struct usb_ctrlrequest *req = (struct usb_ctrlrequest *)urb->context;

	if (urb->status < 0)
		printk(KERN_DEBUG "dm_write_async_callback() failed, %d\n", urb->status);

	kfree(req);
	usb_free_urb(urb);
}

static void dm_write_async_helper(struct usbnet *dev, u8 reg, u8 value,
		u16 length, void *data)
{
	struct usb_ctrlrequest *req;
	struct urb *urb;
	int status;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		dm9620_err(dev, "Error allocating URB in dm_write_async_helper!\n");
		return;
	}

	req = kmalloc(sizeof(struct usb_ctrlrequest), GFP_ATOMIC);
	if (!req) {
		dm9620_err(dev, "Failed to allocate memory for control request\n");
		usb_free_urb(urb);
		return;
	}

	req->bRequestType = USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	req->bRequest = length ? DM_WRITE_REGS : DM_WRITE_REG;
	req->wValue = cpu_to_le16(value);
	req->wIndex = cpu_to_le16(reg);
	req->wLength = cpu_to_le16(length);

	usb_fill_control_urb(urb, dev->udev,
			usb_sndctrlpipe(dev->udev, 0),
			(void *)req, data, length,
			dm_write_async_callback, req);

	status = usb_submit_urb(urb, GFP_ATOMIC);
	if (status < 0) {
		dm9620_err(dev, "Submit control message error, %d\n", status);
		kfree(req);
		usb_free_urb(urb);
	}
}

static void dm_write_async(struct usbnet *dev, u8 reg, u16 length, void *data)
{
	//dm9620_print(dev, "dm_write_async() reg=0x%02x length=%d\n", reg, length);
	dm_write_async_helper(dev, reg, 0, length, data);
}

static void dm_write_reg_async(struct usbnet *dev, u8 reg, u8 value)
{
	//dm9620_print(dev, "dm_write_reg_async() reg=0x%02x value=0x%02x\n", reg, value);
	dm_write_async_helper(dev, reg, value, 0, NULL);
}

static int dm_read_shared_word(struct usbnet *dev, int phy, u8 reg, __le16 *value)
{
	u16 v[2];
	int ret, i;

	mutex_lock(&dev->phy_mutex);

	dm_write_reg(dev, DM_SHARED_ADDR, phy ? (reg | 0x40) : reg);
	dm_write_reg(dev, DM_SHARED_CTRL, phy ? 0xc : 0x4);

	for (i = 0; i < DM_TIMEOUT; i++) {
		u8 tmp;

		udelay(1);
		ret = dm_read_reg(dev, DM_SHARED_CTRL, &tmp);
		if (ret < 0)
			goto out;

		/* ready */
		if ((tmp & 1) == 0)
			break;
	}

	if (i == DM_TIMEOUT) {
		dm9620_err(dev, "%s read timed out!\n", phy ? "phy" : "eeprom");
		ret = -EIO;
		goto out;
	}

	dm_write_reg(dev, DM_SHARED_CTRL, 0x0);

	ret = dm_read(dev, DM_SHARED_DATA, 2, v);
	*value = v[0];

#if 0
	dm9620_print(dev, "read shared %d 0x%02x returned 0x%04x, %d\n",
			phy, reg, *value, ret);
#endif

out:
	mutex_unlock(&dev->phy_mutex);
	return ret;
}

static int dm_write_shared_word(struct usbnet *dev, int phy, u8 reg, __le16 value)
{
	int ret, i;

	mutex_lock(&dev->phy_mutex);

	ret = dm_write(dev, DM_SHARED_DATA, 2, &value);
	if (ret < 0)
		goto out;

	dm_write_reg(dev, DM_SHARED_ADDR, phy ? (reg | 0x40) : reg);
	if (!phy)
		dm_write_reg(dev, DM_SHARED_CTRL, 0x10);
	dm_write_reg(dev, DM_SHARED_CTRL, phy ? 0x0a : 0x12);
	dm_write_reg(dev, DM_SHARED_CTRL, 0x10);

	for (i = 0; i < DM_TIMEOUT; i++) {
		u8 tmp;

		udelay(1);
		ret = dm_read_reg(dev, DM_SHARED_CTRL, &tmp);
		if (ret < 0)
			goto out;

		/* ready */
		if ((tmp & 1) == 0)
			break;
	}

	if (i == DM_TIMEOUT) {
		dm9620_err(dev,"%s write timed out!\n", phy ? "phy" : "eeprom");
		ret = -EIO;
		goto out;
	}

	dm_write_reg(dev, DM_SHARED_CTRL, 0x0);

out:
	mutex_unlock(&dev->phy_mutex);
	return ret;
}


static int dm_write_eeprom_word(struct usbnet *dev, int phy, u8 offset, u8 value)
{
	int ret, i;
	u8  reg,dloc,tmp_H,tmp_L;
	__le16 eeword;

	//devwarn(dev, "offset = 0x%x value = 0x%x ", offset, value);

	/* hank: from offset to determin eeprom word register location,reg */
	reg = (offset >> 1) & 0xff;

	/* hank:  high/low byte by odd/even of offset  */
	dloc = (offset & 0x01) ? DM_EE_PHY_H : DM_EE_PHY_L;

	/* retrieve high and low byte from the corresponding reg*/
	ret = dm_read_shared_word(dev, 0, reg, &eeword);
	//devwarn(dev, "reg = 0x%x dloc = 0x%x eeword = 0x%4x", reg, dloc, eeword);

	tmp_H = (eeword & 0xff);
	tmp_L = (eeword >> 8);

	printk("tmp_L = 0x%2x tmp_H = 0x%2x eeword = 0x%4x\n", tmp_L, tmp_H, eeword);
	/* determine new high and low byte */

	if (offset & 0x01)  {
		tmp_L = value;
	} else {
		tmp_H = value;
	}

	//printk("updated new: tmp_L =0x%2x tmp_H =0x%2x\n", tmp_L,tmp_H);

	mutex_lock(&dev->phy_mutex);

	/* hank: write low byte data first to eeprom reg */
	// dm_write(dev, (offset & 0x01)? DM_EE_PHY_H:DM_EE_PHY_L, 1, &value);
	dm_write(dev,DM_EE_PHY_L, 1, &tmp_H);
	/* high byte will be zero */
	//(offset & 0x01)? (value = eeword << 8):(value = eeword >> 8);

	/* write the not modified 8 bits back to its origional high/low byte reg */
	dm_write(dev,DM_EE_PHY_H, 1, &tmp_L);
	if (ret < 0)
		goto out;

	/* hank : write word location to reg 0x0c  */
	ret = dm_write_reg(dev, DM_SHARED_ADDR, reg);

	if (!phy)
		dm_write_reg(dev, DM_SHARED_CTRL, 0x10);
	dm_write_reg(dev, DM_SHARED_CTRL, 0x12);
	dm_write_reg(dev, DM_SHARED_CTRL, 0x10);

	for (i = 0; i < DM_TIMEOUT; i++) {
		u8 tmp;

		udelay(1);
		ret = dm_read_reg(dev, DM_SHARED_CTRL, &tmp);
		if (ret < 0)
			goto out;

		/* ready */
		if ((tmp & 1) == 0)
			break;
	}

	if (i == DM_TIMEOUT) {
		dm9620_err(dev, "%s write timed out!\n", phy ? "phy" : "eeprom");
		ret = -EIO;
		goto out;
	}

	//dm_write_reg(dev, DM_SHARED_CTRL, 0x0);

out:
	mutex_unlock(&dev->phy_mutex);
	return ret;
}

static int dm_read_eeprom_word(struct usbnet *dev, u8 offset, void *value)
{
	return dm_read_shared_word(dev, 0, offset, value);
}


static int dm9620_set_eeprom(struct net_device *net,struct ethtool_eeprom *eeprom, u8 *data)
{
	struct usbnet *dev = netdev_priv(net);

	dm9620_print(dev, "EEPROM: magic = 0x%x offset =0x%x data = 0x%x\n",
			eeprom->magic, eeprom->offset,*data);

	if (eeprom->magic != MD96XX_EEPROM_MAGIC) {
		dm9620_print(dev, "EEPROM: magic value mismatch, magic = 0x%x\n", eeprom->magic);
		return -EINVAL;
	}

	if (dm_write_eeprom_word(dev, 0, eeprom->offset, *data) < 0)
		return -EINVAL;

	return 0;
}

static int dm9620_get_eeprom_len(struct net_device *dev)
{
	return DM_EEPROM_LEN;
}

static int dm9620_get_eeprom(struct net_device *net,
		struct ethtool_eeprom *eeprom, u8 * data)
{
	struct usbnet *dev = netdev_priv(net);
	__le16 *ebuf = (__le16 *) data;
	int i;

	/* access is 16bit */
	if ((eeprom->offset % 2) || (eeprom->len % 2))
		return -EINVAL;

	for (i = 0; i < eeprom->len / 2; i++) {
		if (dm_read_eeprom_word(dev, eeprom->offset / 2 + i, &ebuf[i]) < 0)
			return -EINVAL;
	}

	return 0;
}

static int dm9620_mdio_read(struct net_device *netdev, int phy_id, int loc)
{
	struct usbnet *dev = netdev_priv(netdev);

	__le16 res;

	dm_read_shared_word(dev, phy_id, loc, &res);

	//dm9620_print(dev, "dm9620_mdio_read() phy_id=0x%02x, loc=0x%02x, ret=0x%04x\n",
	//		phy_id, loc, le16_to_cpu(res));
	return le16_to_cpu(res);
}

static void dm9620_mdio_write(struct net_device *netdev, int phy_id, int loc,
		int val)
{
	struct usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);
	int mdio_val;

	//dm9620_print(dev, "dm9620_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
	//		phy_id, loc, val);

	dm_write_shared_word(dev, phy_id, loc, res);
	mdelay(1);
	mdio_val = dm9620_mdio_read(netdev, phy_id, loc);
}

static void dm9620_get_drvinfo(struct net_device *net,
		struct ethtool_drvinfo *info)
{
	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	info->eedump_len = DM_EEPROM_LEN;
}

static u32 dm9620_get_link(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);

	return mii_link_ok(&dev->mii);
}

static int dm9620_ioctl(struct net_device *net, struct ifreq *rq, int cmd)
{
	struct usbnet *dev = netdev_priv(net);

	return generic_mii_ioctl(&dev->mii, if_mii(rq), cmd, NULL);
}


#define DM_LINKEN  (1<<5)
#define DM_MAGICEN (1<<3)
#define DM_LINKST  (1<<2)
#define DM_MAGICST (1<<0)

static void dm9620_get_wol(struct net_device *net, struct ethtool_wolinfo *wolinfo)
{
	struct usbnet *dev = netdev_priv(net);
	u8 opt;

	if (dm_read_reg(dev, DM_WAKEUP_CTRL, &opt) < 0) {
		wolinfo->supported = 0;
		wolinfo->wolopts = 0;
		return;
	}

	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = 0;

	if (opt & DM_LINKEN)
		wolinfo->wolopts |= WAKE_PHY;
	if (opt & DM_MAGICEN)
		wolinfo->wolopts |= WAKE_MAGIC;
}

static int dm9620_set_wol(struct net_device *net, struct ethtool_wolinfo *wolinfo)
{
	struct usbnet *dev = netdev_priv(net);
	u8 opt = 0;

	if (wolinfo->wolopts & WAKE_PHY)
		opt |= DM_LINKEN;
	if (wolinfo->wolopts & WAKE_MAGIC)
		opt |= DM_MAGICEN;

	dm_write_reg(dev, DM_NET_CTRL, 0x48);  // enable WAKEEN

	//dm_write_reg(dev, 0x92, 0x3f); //keep clock on Hank Jun 30

	return dm_write_reg(dev, DM_WAKEUP_CTRL, opt);
}

static struct ethtool_ops dm9620_ethtool_ops = {
	.get_drvinfo	= dm9620_get_drvinfo,
	.get_link		= dm9620_get_link,
	.get_msglevel	= usbnet_get_msglevel,
	.set_msglevel	= usbnet_set_msglevel,
	.get_eeprom_len	= dm9620_get_eeprom_len,
	.get_eeprom		= dm9620_get_eeprom,
	.set_eeprom		= dm9620_set_eeprom,
	.get_settings	= usbnet_get_settings,
	.set_settings	= usbnet_set_settings,
	.nway_reset		= usbnet_nway_reset,
	.get_wol		= dm9620_get_wol,
	.set_wol		= dm9620_set_wol,
};

static void dm9620_set_multicast(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);
	/* We use the 20 byte dev->data for our 8 byte filter buffer
	 * to avoid allocating memory that is tricky to free later */
	u8 *hashes = (u8 *) & dev->data;
	u8 rx_ctl = 0x31;

	memset(hashes, 0x00, DM_MCAST_SIZE);
	hashes[DM_MCAST_SIZE - 1] |= 0x80;	/* broadcast address */

	if (net->flags & IFF_PROMISC) {
		rx_ctl |= 0x02;
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,33)	
	} else if (net->flags & IFF_ALLMULTI ||  netdev_mc_count(net) > DM_MAX_MCAST) {
		rx_ctl |= 0x8;
	} else if (!netdev_mc_empty(net)) {
		struct netdev_hw_addr *ha;

		netdev_for_each_mc_addr(ha, net) {
			u32 crc = crc32_le(~0, ha->addr, ETH_ALEN) & 0x3f;
			hashes[crc>>3] |= 1 << (crc & 0x7);
		}
#else //LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,33)
	} else if (net->flags & IFF_ALLMULTI || net->mc_count > DM_MAX_MCAST) {
		rx_ctl |= 0x08;
	} else if (net->mc_count) {
		struct dev_mc_list *mc_list = net->mc_list;
		int i;

		for (i = 0; i < net->mc_count; i++, mc_list = mc_list->next) {
			u32 crc = crc32_le(~0, mc_list->dmi_addr, ETH_ALEN) & 0x3f;
			hashes[crc>>3] |= 1 << (crc & 0x7);
		}
#endif		
	}

	dm_write_async(dev, DM_MCAST_ADDR, DM_MCAST_SIZE, hashes);
	dm_write_reg_async(dev, DM_RX_CTRL, rx_ctl);
}

static void __dm9620_set_mac_address(struct usbnet *dev)
{
	dm_write_async(dev, DM_PHY_ADDR, ETH_ALEN, dev->net->dev_addr);
}

static int dm9620_set_mac_address(struct net_device *net, void *p)
{
	struct sockaddr *addr = p;
	struct usbnet *dev = netdev_priv(net);

	printk("dm962x: Set mac addr %pM\n", addr->sa_data);

	if (!is_valid_ether_addr(addr->sa_data)) {
		dev_err(&net->dev, "not setting invalid mac address %pM\n",
				addr->sa_data);
		return -EINVAL;
	}

	memcpy(net->dev_addr, addr->sa_data, net->addr_len);
	__dm9620_set_mac_address(dev);

	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
static const struct net_device_ops vm_netdev_ops= {
	.ndo_open			= usbnet_open,
	.ndo_stop			= usbnet_stop,
	.ndo_start_xmit		= usbnet_start_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_do_ioctl		= dm9620_ioctl,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
	.ndo_set_rx_mode	= dm9620_set_multicast,
#else
	.ndo_set_multicast_list	= dm9620_set_multicast,
#endif
	.ndo_set_mac_address	= dm9620_set_mac_address,
};
#endif

static int dm9620_bind(struct usbnet *dev, struct usb_interface *intf)
{
	const unsigned char *mac_src;
	struct dm96xx_priv* priv;
	u16 pid[2];
	u8 temp;
	u8 tmp;
	int mdio_val, i, ret;

	ret = usbnet_get_endpoints(dev, intf);
	if (ret)
		goto out;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
	dev->net->netdev_ops = &vm_netdev_ops;
	dev->net->ethtool_ops = &dm9620_ethtool_ops;
#else
	dev->net->do_ioctl = dm9620_ioctl;
	dev->net->set_multicast_list = dm9620_set_multicast;
	dev->net->ethtool_ops = &dm9620_ethtool_ops;
#endif
	dev->net->hard_header_len += DM_TX_OVERHEAD;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->rx_urb_size = dev->net->mtu + ETH_HLEN + DM_RX_OVERHEAD+1; // ftp fail fixed

	dev->mii.dev = dev->net;
	dev->mii.mdio_read = dm9620_mdio_read;
	dev->mii.mdio_write = dm9620_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = DM9620_PHY_ID;

	//JJ1
	if ((ret = dm_read_reg(dev, 0x29, &tmp)) >= 0)
		printk("dm962x: dm_read_reg() 0x29 0x%02x\n", tmp);
	else
		printk("dm962x: dm_read_reg() 0x29 fail-func-return %d\n", ret);

	if ((ret = dm_read_reg(dev, 0x28, &tmp)) >= 0)
		printk("dm962x: dm_read_reg() 0x28 0x%02x\n", tmp);
	else
		printk("dm962x: dm_read_reg() 0x28 fail-func-return %d\n", ret);

	if ((ret = dm_read_reg(dev, 0x2b, &tmp)) >= 0)
		printk("dm962x: dm_read_reg() 0x2b 0x%02x\n", tmp);
	else
		printk("dm962x: dm_read_reg() 0x2b fail-func-return %d\n", ret);
	if ((ret = dm_read_reg(dev, 0x2a, &tmp)) >= 0)
		printk("dm962x: dm_read_reg() 0x2a 0x%02x\n", tmp);
	else
		printk("dm962x: dm_read_reg() 0x2a fail-func-return %d\n", ret);

	//JJ3
	if ( (ret = dm_read_reg(dev, 0xF2, &tmp)) >= 0)
		printk("dm962x: dm_read_reg() 0xF2 0x%02x\n", tmp);
	else
		printk("dm962x: dm_read_reg() 0xF2 fail-func-return %d\n", ret);

	printk("dm962x:  [Analysis.2] 0xF2, D[7] %d %s\n", (tmp>>7)&1,
			(tmp&(1<<7)) ? "Err: RX Unexpected condition": "OK" );
	printk("dm962x:  [Analysis.2] 0xF2, D[6] %d %s\n", (tmp>>6)&1,
			(tmp&(1<<6)) ? "Err: Host Suspend condition": "OK" );
	printk("dm962x:  [Analysis.2] 0xF2, D[5] %d %s\n", (tmp>>5)&1,
			(tmp&(1<<5)) ? "EP1: Data Ready": "EP1: Empty" );
	printk("dm962x:  [Analysis.2] 0xF2, D[3] %d %s\n", (tmp>>3)&1,
			(tmp&(1<<3)) ? "Err: Bulk out condition": "OK" );

	printk("dm962x:  [Analysis.2] 0xF2, D[2] %d %s\n", (tmp>>2)&1,
			(tmp&(1<<2)) ? "Err: TX Buffer full": "OK" );
	printk("dm962x:  [Analysis.2] 0xF2, D[1] %d %s\n", (tmp>>1)&1,
			(tmp&(1<<1)) ? "Warn: TX buffer Almost full": "OK" );
	printk("dm962x:  [Analysis.2] 0xF2, D[0] %d %s\n", (tmp>>0)&1,
			(tmp&(1<<0)) ? "Status: TX buffer has pkts": "Status: TX buffer 0 pkts" );

	/* reset */
	dm_write_reg(dev, DM_NET_CTRL, 1);
	udelay(20);

	//Stone add Enable "MAC layer" Flow Control, TX Pause Packet Enable and
	dm_write_reg(dev, DM_FLOW_CTRL, 0x29);

	//Stone add Enable "PHY layer" Flow Control support (phy register 0x04 bit 10)
	temp = dm9620_mdio_read(dev->net, dev->mii.phy_id, 0x04);
	dm9620_mdio_write(dev->net, dev->mii.phy_id, 0x04, temp | 0x400);

	/* Add V1.1, Enable auto link while plug in RJ45, Hank July 20, 2009*/
	dm_write_reg(dev, USB_CTRL, 0x20);

	/* try to using param addr at first */
	if (is_valid_ether_addr(param_addr)) {
		mac_src = "param data";
		memcpy(dev->net->dev_addr, param_addr, 6);
		__dm9620_set_mac_address(dev);

	} else {
		/* try reading the node address from the attached EEPROM */
		mac_src = "eeprom";
		for (i = 0; i < 6; i += 2)
			dm_read_eeprom_word(dev, i / 2, dev->net->dev_addr+i);

		if (is_valid_ether_addr(param_addr)) {
			__dm9620_set_mac_address(dev);

		} else {
			/* try reading from mac */
			mac_src = "chip";
			if (dm_read(dev, DM_PHY_ADDR, ETH_ALEN, dev->net->dev_addr) < 0) {
				printk(KERN_ERR "Error reading MAC address\n");
				ret = -ENODEV;
				goto out;
			}
		}
	}

	if (!is_valid_ether_addr(dev->net->dev_addr)) {
		printk("dm962x: Invalid ethernet MAC address. Please "
				"set using ifconfig\n");
	} else {
		printk("dm962x: ethernet MAC address %pM (%s)\n",
				dev->net->dev_addr, mac_src);
	}

	/* read SMI mode register */
	priv = dev->driver_priv = kmalloc(sizeof(struct dm96xx_priv), GFP_ATOMIC);
	if (!priv) {
		dm9620_err(dev,"Failed to allocate memory for dm96xx_priv\n");
		ret = -ENOMEM;
		goto out;
	}

	/* work-around for 9620 mode */
#if 0
	printk("dm962x: Fixme: work around for 9620 mode\n");
	printk("dm962x: Add tx_fixup() debug...\n");
#endif
	dm_write_reg(dev, DM_MCAST_ADDR, 0);     // clear data bus to 0s
	dm_read_reg(dev, DM_MCAST_ADDR, &temp);  // clear data bus to 0s

	priv->flag_fail_count = 0;

	// Must clear data bus before we can read the 'MODE9620' bit
	ret = dm_read_reg(dev, DM_SMIREG, &temp);
	if (ret < 0) {
		printk(KERN_ERR "dm962x: Error read SMI register\n");
	}
	else priv->mode_9620 = temp & DM_MODE9620;

	printk(KERN_WARNING "dm962x: 9620 Mode = %d\n", priv->mode_9620);

	// Need to check the Chipset version (register 0x5c is 0x02?)
	dm_read_reg(dev, DM_TXRX_M, &temp);
	if (temp == 0x02) {
		dm_read_reg(dev, 0x3f, &temp);
		temp |= 0x80;
		dm_write_reg(dev, 0x3f, temp);
	}

	//Stone add for check Product ID == 0x1269
	ret = dm_read(dev, DM_PID, 2, pid);
	if (pid[0] == 0x1269)
		dm_write_reg(dev, DM_SMIREG, 0xa0);
	if (pid[0] == 0x0269)
		dm_write_reg(dev, DM_SMIREG, 0xa0);

	/* power up phy */
	dm_write_reg(dev, DM_GPR_CTRL, 1);
	dm_write_reg(dev, DM_GPR_DATA, 0);

	/* Init tx/rx checksum */
#if DM_TX_CS_EN
	dm_write_reg(dev, DM_TX_CRC_CTRL, 7);
#endif
	dm_write_reg(dev, DM_RX_CRC_CTRL, 2);

	/* receive broadcast packets */
	dm9620_set_multicast(dev->net);
	dm9620_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);

	/* Hank add, work for comapubility issue (10M Power control) */	

	dm9620_mdio_write(dev->net, dev->mii.phy_id, PHY_SPEC_CFG, 0x800);
	mdio_val = dm9620_mdio_read(dev->net, dev->mii.phy_id, PHY_SPEC_CFG);

	dm9620_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
			ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(&dev->mii);

out:
	return ret;
}

void dm9620_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct dm96xx_priv* priv= dev->driver_priv;
	printk("dm9620_unbind():\n");

	printk("flag_fail_count  %lu\n", (long unsigned int)priv->flag_fail_count);
	kfree(dev->driver_priv); // displayed dev->.. above, then can free dev

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
	printk("rx_length_errors %lu\n",dev->net->stats.rx_length_errors);
	printk("rx_over_errors   %lu\n",dev->net->stats.rx_over_errors  );
	printk("rx_crc_errors    %lu\n",dev->net->stats.rx_crc_errors   );
	printk("rx_frame_errors  %lu\n",dev->net->stats.rx_frame_errors );
	printk("rx_fifo_errors   %lu\n",dev->net->stats.rx_fifo_errors  );
	printk("rx_missed_errors %lu\n",dev->net->stats.rx_missed_errors);	
#else
	printk("rx_length_errors %lu\n",dev->stats.rx_length_errors);
	printk("rx_over_errors   %lu\n",dev->stats.rx_over_errors  );
	printk("rx_crc_errors    %lu\n",dev->stats.rx_crc_errors   );
	printk("rx_frame_errors  %lu\n",dev->stats.rx_frame_errors );
	printk("rx_fifo_errors   %lu\n",dev->stats.rx_fifo_errors  );
	printk("rx_missed_errors %lu\n",dev->stats.rx_missed_errors);	
#endif
}

static int dm9620_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	u8 status;
	int len;
	struct dm96xx_priv *priv = (struct dm96xx_priv *)dev->driver_priv;

	/* 9620 format:
	   b0: rx status
	   b1: packet length (incl crc) low
	   b2: packet length (incl crc) high
	   b3..n-4: packet data
	   bn-3..bn: ethernet crc
	 */

	/* 9620 format:
	   one additional byte then 9620 :
	   rx_flag in the first pos
	 */

	if (unlikely(skb->len < DM_RX_OVERHEAD_9601)) {	// 20090623
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		return 0;
	}

	if (priv->mode_9620) {
		/* mode 9620 */

		if (unlikely(skb->len < DM_RX_OVERHEAD)) {	// 20090623
			dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
			return 0;
		}

		status = skb->data[1];
		len = (skb->data[2] | (skb->data[3] << 8)) - 4;

		if (unlikely(status & 0xbf)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
			if (status & 0x01) dev->net->stats.rx_fifo_errors++;
			if (status & 0x02) dev->net->stats.rx_crc_errors++;
			if (status & 0x04) dev->net->stats.rx_frame_errors++;
			if (status & 0x20) dev->net->stats.rx_missed_errors++;
			if (status & 0x90) dev->net->stats.rx_length_errors++;
#else
			if (status & 0x01) dev->stats.rx_fifo_errors++;
			if (status & 0x02) dev->stats.rx_crc_errors++;
			if (status & 0x04) dev->stats.rx_frame_errors++;
			if (status & 0x20) dev->stats.rx_missed_errors++;
			if (status & 0x90) dev->stats.rx_length_errors++;
#endif
			return 0;
		}

		skb_pull(skb, 4);
		skb_trim(skb, len);

	}
	else { /* mode 9620 (original driver code) */
		status = skb->data[0];
		len = (skb->data[1] | (skb->data[2] << 8)) - 4;

		if (unlikely(status & 0xbf)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
			if (status & 0x01) dev->net->stats.rx_fifo_errors++;
			if (status & 0x02) dev->net->stats.rx_crc_errors++;
			if (status & 0x04) dev->net->stats.rx_frame_errors++;
			if (status & 0x20) dev->net->stats.rx_missed_errors++;
			if (status & 0x90) dev->net->stats.rx_length_errors++;
#else
			if (status & 0x01) dev->stats.rx_fifo_errors++;
			if (status & 0x02) dev->stats.rx_crc_errors++;
			if (status & 0x04) dev->stats.rx_frame_errors++;
			if (status & 0x20) dev->stats.rx_missed_errors++;
			if (status & 0x90) dev->stats.rx_length_errors++;
#endif
			return 0;
		}

		skb_pull(skb, 3);
		skb_trim(skb, len);
	}

	return 1;
}

static struct sk_buff *dm9620_tx_fixup(struct usbnet *dev, struct sk_buff *skb,
		gfp_t flags)
{
	int len;

	/* format:
	   b0: packet length low
	   b1: packet length high
	   b3..n: packet data
	*/

	len = skb->len;

	if (skb_headroom(skb) < DM_TX_OVERHEAD) {
		struct sk_buff *skb2;
		skb2 = skb_copy_expand(skb, DM_TX_OVERHEAD, 0, flags);
		dev_kfree_skb_any(skb);
		skb = skb2;
		if (!skb)
			return NULL;
	}

	__skb_push(skb, DM_TX_OVERHEAD);

	/* usbnet adds padding if length is a multiple of packet size
	   if so, adjust length value in header */
	if ((skb->len % dev->maxpacket) == 0)
		len++;

	skb->data[0] = len;
	skb->data[1] = len >> 8;

	/* hank, recalcute checksum of TCP */

	return skb;
}

static void dm9620_status(struct usbnet *dev, struct urb *urb)
{
	int link;
	u8 *buf;

	/* format:
	   b0: net status
	   b1: tx status 1
	   b2: tx status 2
	   b3: rx status
	   b4: rx overflow
	   b5: rx count
	   b6: tx count
	   b7: gpr
	*/

	if (urb->actual_length < 8)
		return;

	buf = urb->transfer_buffer;

	link = !!(buf[0] & 0x40);
	if (netif_carrier_ok(dev->net) != link) {
		if (link) {
			netif_carrier_on(dev->net);
			usbnet_defer_kevent (dev, EVENT_LINK_RESET);
		} else
			netif_carrier_off(dev->net);
		dm9620_print(dev, "Link Status is: %d\n", link);
	}
}

static int dm9620_link_reset(struct usbnet *dev)
{
	struct ethtool_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);

	/* hank add */
	dm9620_mdio_write(dev->net, dev->mii.phy_id, PHY_SPEC_CFG, 0x800);
	dm9620_print(dev, "link_reset() speed: %d duplex: %d\n",
			ecmd.speed, ecmd.duplex);

	return 0;
}

static const struct driver_info dm9620_info = {
	.description	= "Davicom DM9620 USB Ethernet",
	.flags		= FLAG_ETHER,
	.bind		= dm9620_bind,
	.rx_fixup	= dm9620_rx_fixup,
	.tx_fixup	= dm9620_tx_fixup,
	.status		= dm9620_status,
	.link_reset	= dm9620_link_reset,
	.reset		= dm9620_link_reset,
	.unbind     = dm9620_unbind,
};

static const struct usb_device_id products[] = {
	{
		USB_DEVICE(0x07aa, 0x9601),	/* Corega FEther USB-TXC */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x9601),	/* Davicom USB-100 */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x6688),	/* ZT6688 USB NIC */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x0268),	/* ShanTou ST268 USB NIC */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x8515),	/* ADMtek ADM8515 USB NIC */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a47, 0x9601),	/* Hirose USB-100 */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x9620), /* Davicom 9620 */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x9621), /* Davicom 9621 */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x9622), /* Davicom 9622 */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0fe6, 0x8101), /* Davicom 9601 USB to Fast Ethernet Adapter */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x1269), /* Davicom 9621A CDC */
		.driver_info = (unsigned long)&dm9620_info,
	}, {
		USB_DEVICE(0x0a46, 0x0269), /* Davicom 9620A CDC */
		.driver_info = (unsigned long)&dm9620_info,
	},
	{},			// END
};

MODULE_DEVICE_TABLE(usb, products);

static struct usb_driver dm9620_driver = {
	.name = "dm9620",
	.id_table = products,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
};

static int __init dm9620_init(void)
{
	return usb_register(&dm9620_driver);
}

static void __exit dm9620_exit(void)
{
	usb_deregister(&dm9620_driver);
}

module_init(dm9620_init);
module_exit(dm9620_exit);

MODULE_AUTHOR("Peter Korsgaard <jacmet@sunsite.dk>");
MODULE_DESCRIPTION("Davicom DM9620 USB 2.0 ethernet devices");
MODULE_LICENSE("GPL");

