/*
 * xmd_rmnet.c
 *
 * Copyright (C) 2007 Google, Inc.
 * Author: Brian Swetland <swetland@google.com>
 *
 * Copyright (C) 2011 Intel Mobile Communications GmbH. All rights reserved.
 * Author: Srinivas M <srinivasaraox.mandadapu@intel.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * RMNET Driver modified by Intel from Google msm_rmnet.c
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/tty.h>
#include <linux/netdevice.h>
#include <linux/poll.h>
#include <linux/crc-ccitt.h>
#include <linux/spinlock.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <asm/uaccess.h>
#include <asm/string.h>
#include <linux/types.h>
#include <linux/compiler.h>
#include <linux/signal.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/etherdevice.h>
#include <linux/ipv6.h>
#include <linux/ip.h>
#include <asm/byteorder.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif

MODULE_LICENSE("GPL");

/**************************DEFINES***************************/
#define RMNET_ETH_HDR_SIZE   14
#define RMNET_MTU_SIZE 1514
#define RMNET_IPV4_VER 0x4
#define RMNET_IPV6_VER 0x6
#define IPV6_HEADER_SZ 40
#define IPV6_PROTO_TYPE 0x08DD
#define N_RMNET 	25
/************************************************************/

/************************STRUCTURES**************************/
struct rmnet_private
{	
	struct net_device_stats stats;
	struct tty_struct *tty;
	struct mutex txrx_mutex_lock;
	struct net_device *dev;
};
/************************************************************/

/**********************GLOBAL VARIABLES**********************/
struct rmnet_private *g_rmnet_private;
/************************************************************/

/*******************FUNCTION DECLARATION*********************/
static int rmnet_init(void);
static void ifx_netif_rx_cb(struct net_device *ptr_dev, const unsigned char *rx_addr, int sz);
/************************************************************/

/*******************FUNCTION DEFINITIONS********************/

/*********************** Line disc driver operations starts *****************************/
static int rmnet_asynctty_open(struct tty_struct *tty)
{		
	
	if (tty->ops->write == NULL)
	{
		return -EOPNOTSUPP;
	}

	if(g_rmnet_private != NULL)
	{
		g_rmnet_private->tty = tty;
		tty->disc_data = g_rmnet_private;
	}	
	
	return 0;
}

static int rmnet_asynctty_ioctl(struct tty_struct *tty, struct file *file,
		unsigned int cmd, unsigned long arg)
{
	return 0;
}

/* May sleep, don't call from interrupt level or with interrupts disabled */
static void rmnet_asynctty_receive(struct tty_struct *tty, const unsigned char *buf,
		char *cflags, int count)
{	
	struct rmnet_private *p = tty->disc_data;
	

	if(p->dev)
	{
		ifx_netif_rx_cb(p->dev, buf, count);
	}
        	
}

static unsigned int rmnet_asynctty_poll(struct tty_struct *tty, struct file *file, poll_table *wait)
{
	
	/* Not implemented */
	return 0;
}

static ssize_t rmnet_asynctty_write(struct tty_struct *tty, struct file *file,
		const unsigned char *buf, size_t count)
{
	
	/* Not implemented */
	return -EAGAIN;
}

/*Line disc info*/
static struct tty_ldisc_ops rmnet_ldisc = {
	.owner  = THIS_MODULE,
	.magic	= TTY_LDISC_MAGIC,
	.name	= "ip_ldisc",
	.open	= rmnet_asynctty_open,
	.write	= rmnet_asynctty_write,
	.ioctl	= rmnet_asynctty_ioctl,
	.poll	= rmnet_asynctty_poll,
	.receive_buf = rmnet_asynctty_receive,
};
/************************ Line disc driver operations ends ******************************/


/**************************** Net driver operations starts ******************************/
/* Receive data from TTY and forward it to TCP/IP stack 
    The implementation also handles partial packets.
    Ethernet header is appended to the IP datagram before passing it to TCP/IP stack.
*/
void ifx_netif_rx_cb(struct net_device *dev, const unsigned char *buf, int sz)
{
	struct rmnet_private *p = netdev_priv(dev);
	static struct sk_buff *skb;
	static unsigned short ip_data_in_skb;
	static void *ptr = NULL;
	static unsigned short len = 0; /* IP datagram length */
	int ver = 0;
	unsigned short tempval;
	static int counter;
	
	
	while(sz) {
		if (len == 0) {
#if defined(__BIG_ENDIAN_BITFIELD)
			ver = buf[0] & 0x0F;
#elif defined(__LITTLE_ENDIAN_BITFIELD)
			ver = (buf[0] & 0xF0) >> 4;
#endif
			if (ver == RMNET_IPV4_VER) {
				len = (buf[2]<<8)| buf[3];
			} else if (ver == RMNET_IPV6_VER) {
				len = IPV6_HEADER_SZ + ((buf[4]<<8)| buf[5]);
			} else {
				return;
			}
			if (len + RMNET_ETH_HDR_SIZE > RMNET_MTU_SIZE) {
				ptr = 0;
				sz -= len;
				buf += len;
				len = 0;
				continue;
			} else {
			    len += RMNET_ETH_HDR_SIZE;
				skb = dev_alloc_skb(len + NET_IP_ALIGN);
				if (skb == NULL) {
					/* TODO: We need to handle this case later */
					return;
				}
				skb->dev = dev;
				skb_reserve(skb, NET_IP_ALIGN);
				ptr = skb_put(skb, len);
				/* adding ethernet header */
				{
					char temp[] = {0xB6,0x91,0x24,0xa8,0x14,0x72,0xb6,0x91,0x24,
								   0xa8,0x14,0x72,0x08,0x0};
					struct ethhdr *eth_hdr = (struct ethhdr *) temp;

					if (ver == RMNET_IPV6_VER) {
						eth_hdr->h_proto = htons(IPV6_PROTO_TYPE);
					}

					memcpy((void *)eth_hdr->h_dest,
						   (void*)dev->dev_addr,
						   sizeof(eth_hdr->h_dest));
					memcpy((void *)ptr,
						   (void *)eth_hdr,
						   sizeof(struct ethhdr));
				}
			}
		}

		tempval = (sz < (len - RMNET_ETH_HDR_SIZE - ip_data_in_skb))? sz:(len - RMNET_ETH_HDR_SIZE - ip_data_in_skb);
		memcpy(ptr + RMNET_ETH_HDR_SIZE + ip_data_in_skb, buf, tempval);
		ip_data_in_skb += tempval;			
		sz -= tempval;
		buf += tempval;
		if (ip_data_in_skb < (len - RMNET_ETH_HDR_SIZE)) {
			continue;
		}
		skb->protocol = eth_type_trans(skb, dev);
		p->stats.rx_packets++;
		p->stats.rx_bytes += skb->len;
		netif_rx(skb);
		len = 0;
		ip_data_in_skb = 0;
	}
}

static int rmnet_open(struct net_device *dev)
{
	
	netif_start_queue(dev);
	return 0;
}

static int rmnet_stop(struct net_device *dev)
{
	
	netif_stop_queue(dev);
	return 0;
}

/* Receive data from TCP/IP stack and forward it to TTY 
    Ethernet header is removed before sending IP datagram to the modem.
    IP Datagram length is appended before the IP packet as per modem requirement.
*/
static int rmnet_xmit(struct sk_buff *skb, struct net_device *dev)
{	
	struct rmnet_private *p;
	
	
	if((skb==NULL)||(dev==NULL))
	{
		return 0;
	}
	
	p = netdev_priv(dev);

	if(p && p->tty)
	{
		//pr_info("Dest MAC Addr = %x %x %x %x %x %x\n", skb->data[0], skb->data[1], skb->data[2], skb->data[3], skb->data[4], skb->data[5]);		    
		//pr_info("Src MAC Addr = %x %x %x %x %x %x\n", skb->data[6], skb->data[7], skb->data[8], skb->data[9], skb->data[10], skb->data[11]);
		//pr_info("Eth Protocol type %x %x \nIP datagram start %x %x %x %x %x %x\n", skb->data[12],skb->data[13],skb->data[14],skb->data[15],skb->data[16],skb->data[17],skb->data[18],skb->data[19]);

		/* 
		IMPORTANT: IP Datagram length is appended in Network byte order, before the IP packet as per modem requirement.
		This will not be required as and when modem starts supporting streaming data for USB HSIC/HS USB.
		*/
		//skb->data[12] =(skb->len - RMNET_ETH_HDR_SIZE) >> 8;
		//skb->data[13]	= (skb->len - RMNET_ETH_HDR_SIZE) & 0xFF ;  

	//	pr_info("\n=================>>>\nlength MSB = %x LSB = %x \nIP datagram start %x %x %x %x %x %x\n\n", skb->data[12],skb->data[13], skb->data[14],skb->data[15],skb->data[16],skb->data[17],skb->data[18],skb->data[19]);

		set_bit(TTY_DO_WRITE_WAKEUP, &(p->tty->flags));	
		// p->tty->ops->write(p->tty, (&skb->data[RMNET_ETH_HDR_SIZE - 2]), ((skb->len+2) - RMNET_ETH_HDR_SIZE));
		p->tty->ops->write(p->tty, (&skb->data[RMNET_ETH_HDR_SIZE]), ((skb->len) - RMNET_ETH_HDR_SIZE));

		p->stats.tx_packets++;
		p->stats.tx_bytes += skb->len;		
	}	

	dev_kfree_skb_irq(skb);
	return NETDEV_TX_OK;
}

static void rmnet_set_multicast_list(struct net_device *dev)
{
	
	/* Not implemented */
}

static struct net_device_stats *rmnet_get_stats(struct net_device *dev)
{	
	struct rmnet_private *p = netdev_priv(dev);
	
	
	return &p->stats;
}

static void rmnet_tx_timeout(struct net_device *dev)
{
	
	/* Not implemented */
}

/* Net device info */
static struct net_device_ops rmnet_ops = {
	.ndo_open = rmnet_open,
	.ndo_stop = rmnet_stop,
	.ndo_start_xmit = rmnet_xmit,
	.ndo_get_stats = rmnet_get_stats,
	.ndo_set_multicast_list = rmnet_set_multicast_list,	
	.ndo_tx_timeout = rmnet_tx_timeout,
};

static void __init rmnet_setup(struct net_device *dev)
{
	
	dev->netdev_ops = &rmnet_ops;
	dev->watchdog_timeo = 20; /* ??? */
	ether_setup(dev);	
	random_ether_addr(dev->dev_addr);
}

static int __init rmnet_init(void)
{		
	int ret;
	struct net_device *dev;
	struct rmnet_private *p;
	

	dev = alloc_netdev(sizeof(struct rmnet_private),
			   "rmnet0", rmnet_setup);

	if (!dev)
		return -ENOMEM;

	p = netdev_priv(dev);
	g_rmnet_private = p;
	p->dev = dev;
	ret = register_netdev(dev);
	
	if (ret < 0) {
		free_netdev(dev);
		return ret;
	}

	return 0;
}
/***************************** Net driver operations ends *******************************/

/***************************** rmnet driver entry/exit **********************************/
static int __init rmnet_async_init(void)
{	
	int err = -EFAULT;
	

	/* 
	    The N_RMNET value should not be used by any other line disc driver in the system.
	    Refer to the list of line disciplines listed in tty.h file.
	    The same value (as N_RMNET) should also be used by application when setting up the line disc association:
		int fdrmnet = open("/dev/ttyACM1",  O_RDWR | O_NOCTTY | O_NONBLOCK);
		int ldisc = N_RMNET;
		ioctl (fdrmnet, TIOCSETD, &ldisc);
	    In some older Linux kernels, dynamically adding new line disc driver is not allowed.
	    In such cases,
	       either an existing line disc number (but not used in the system) can be used, or
	       a new one needs to be added in tty.h and the kernel needs to be rebuild.
	*/
	err = tty_register_ldisc(N_RMNET, &rmnet_ldisc);
	if (err != 0)
	{
	}
	rmnet_init();

	
	return err;
}

static void __exit rmnet_async_cleanup(void)
{
	
	unregister_netdev(g_rmnet_private->dev);	
	if (tty_unregister_ldisc(N_RMNET) != 0) {
	}
}

module_init(rmnet_async_init);
module_exit(rmnet_async_cleanup);
/****************************************************************************************/

