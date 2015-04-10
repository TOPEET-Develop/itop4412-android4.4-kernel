//iboardtouch.c

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>


#include <linux/timer.h>
#include <linux/sched.h>
struct timer_list timer_s;

/* add by cym 20131212 */
#define TOUCH_MAX_X	4095
#define TOUCH_MAX_Y	4095
/* end add */

//static int swap_xy;
struct usbtouch_usb;
struct usbtouch_device_info 
{
	int min_xc, max_xc;
	int min_yc, max_yc;
	int min_press, max_press;
	int rept_size;


	bool irq_always;

	void (*process_pkt) (struct usbtouch_usb *usbtouch, unsigned char *pkt, int len);

	int  (*get_pkt_len) (unsigned char *pkt, int len);

	int  (*read_data)   (struct usbtouch_usb *usbtouch, unsigned char *pkt);
	int  (*init)        (struct usbtouch_usb *usbtouch);
	void (*exit)	    (struct usbtouch_usb *usbtouch);
};


struct usbtouch_usb 
{
	unsigned char *data;
	dma_addr_t data_dma;
	unsigned char *buffer;
	int buf_len;
	struct urb *irq;
	struct usb_interface *interface;
	struct input_dev *input;
	struct usbtouch_device_info *type;
	char name[128];
	char phys[64];
	void *priv;

	int x, y;
	int touch, press, id;
	int x2, y2;
	int touch2, press2, id2;
	int psum;
	
	int key_input;
};



enum {IBOARD_TOUCH,IBOARD_TOUCH_1,DEVTYPE_IGNORE,};



static const struct usb_device_id usbtouch_devices[] = 
{
{USB_DEVICE(0x12ff, 0x0001), .driver_info = IBOARD_TOUCH},
{USB_DEVICE(0x13ff, 0x0008), .driver_info = IBOARD_TOUCH_1},
{}
};

//1
static int iboardtouch_read_data(struct usbtouch_usb *dev, unsigned char *pkt)//single point
{
		int abs_x = 0;
		int abs_y = 0;
		int intTouch = 0;
		int intTouch_2 = 0;
		int abs_x2 = 0, abs_y2 =0;
		int p_sum = 1;

		abs_x= (256 * (int)pkt[3] + (int)pkt[2] ) ;
		if (abs_x < 0) abs_x = 0;
		abs_y= (256 * (int)pkt[5] + (int)pkt[4] ) ;
		if (abs_y < 0) abs_y = 0;

		if((int)pkt[1] <= 0) intTouch = 0;
		if((int)pkt[1] >= 1) intTouch = 3;
	dev->id = 1;


		dev->x = abs_x;
		dev->y = abs_y;
		dev->touch = intTouch;
		dev->x2 = abs_x2;
		dev->y2 = abs_y2;
		dev->touch2 = intTouch_2;
		dev->psum = p_sum;

		return 1;
}//1





//2
static int iboardtouch_read_data_1(struct usbtouch_usb *dev, unsigned char *pkt)
{
	int abs_x = 0;
	int abs_y = 0;
	int intTouch = 0;
	int intTouch_2 = 0;
	int abs_x2 = 0, abs_y2 =0;
	int p_sum = 0;

	//printk("P2a:%d, %d, %d,X:( %d %d,%d,%d),%d,%d,Y :(%d,%d,%d,%d),%d\n", (int)pkt[0],(int)pkt[1],(int)pkt[2],(int)pkt[3],(int)pkt[4],(int)pkt[5],(int)pkt[6],(int)pkt[7],(int)pkt[8],(int)pkt[9],(int)pkt[10],(int)pkt[11],(int)pkt[12],(int)pkt[13]); 
	     

	if((int)pkt[0] == 1) //single point
	{
		p_sum = 1;
		abs_x= (256 * (int)pkt[3] + (int)pkt[2] ) ;
		if (abs_x < 0) abs_x = 0;
		abs_y= (256 * (int)pkt[5] + (int)pkt[4] ) ;
		if (abs_y < 0) abs_y = 0;

		if((int)pkt[1] <= 0) intTouch = 0;
		if((int)pkt[1] >= 1) intTouch = 3;
	dev->id = 1;


		dev->x = abs_x;
		dev->y = abs_y;
		dev->touch = intTouch;
		dev->x2 = abs_x2;
		dev->y2 = abs_y2;
		dev->touch2 = intTouch_2;
		dev->psum = p_sum;
	}
	else//multi-point
	{
		abs_x= (256 * (int)pkt[4] + (int)pkt[3] ) ;
		if (abs_x < 0) abs_x = 0;
		abs_y= (256 * (int)pkt[6] + (int)pkt[5] ) ;
		if (abs_y < 0) abs_y = 0;
	
		if((int)pkt[1] < 0) intTouch = 0;
		if((int)pkt[1] >= 0) intTouch = (int)pkt[1];
		dev->id = (int)pkt[2];
		
		abs_x2= (256 * (int)pkt[10] + (int)pkt[9] );
		if (abs_x2 < 0) abs_x2 = 0;
		abs_y2= (256 * (int)pkt[12] + (int)pkt[11] );
		if (abs_y2 < 0) abs_y2 = 0;

		if((int)pkt[7] < 0) intTouch_2 = 0;
		if((int)pkt[7] >= 0) intTouch_2 = (int)pkt[7];
		dev->id2 = (int)pkt[8];

		if((int)pkt[13] > 0) p_sum = (int)pkt[13];

		//printk("P3w:%d, X:%d, Y:%d, P2:%d, X2:%d, Y2:%d\n", intTouch,abs_x,abs_y,intTouch_2,abs_x2,abs_y2);


		if(intTouch == 7 || intTouch == 192 ) intTouch = 3;
		if(intTouch == 4 || intTouch == 64 ) intTouch = 2;
		dev->x = abs_x;
		dev->y = abs_y;
		dev->touch = intTouch;
		if(intTouch_2 == 7 || intTouch_2 == 192) intTouch_2 = 3;
		if(intTouch_2 == 4 || intTouch_2 == 64) intTouch_2 = 2;
		dev->x2 = abs_x2;
		dev->y2 = abs_y2;
		dev->touch2 = intTouch_2;
		dev->psum = p_sum;

	}
	return 1;
}//2


static struct usbtouch_device_info usbtouch_dev_info[] = 
{

	[IBOARD_TOUCH] = {
		.min_xc		= 0x0,
		.max_xc		= 0xfff,
		.min_yc		= 0x0,
		.max_yc		= 0xfff,
		.rept_size	= 64,
		.read_data	= iboardtouch_read_data,
	},

	[IBOARD_TOUCH_1] = {
		.min_xc		= 0x0,
		.max_xc		= 0xfff,
		.min_yc		= 0x0,
		.max_yc		= 0xfff,
		.rept_size	= 64,
		.read_data	= iboardtouch_read_data_1,
	},

};


/////////////////////////////////////////////////////////////////
static int X_old = 0;
static int Y_old = 0;
static int  intTouch_old = 0;
static int X2_old = 0;
static int Y2_old = 0;
static int  intTouch2_old = 0;

static int int_counttime = 0;
static int touch_lasthome = 0;
static int x_lasthome = 0;
static int y_lasthome = 0;
static bool is_sendhome = false;
static int touch2_lasthome = 0;
static int x2_lasthome = 0;
static int y2_lasthome = 0;


void  timer_enent(unsigned long data)
{
	int_counttime ++; 
	mod_timer(&timer_s, jiffies + 1*HZ);
}

static void usbtouch_process_pkt(struct usbtouch_usb *usbtouch,
                                 unsigned char *pkt, int len)
{
	int touch_temp = 0;
	int touch_temp2 = 0;

		struct usbtouch_device_info *type = usbtouch->type;

		if (!type->read_data(usbtouch, pkt))
				return;

	//////////////////////////////////////////////////////////single point - KEY_BACK
	if((int)pkt[0] == 1 && (int)pkt[1] == 2) 
	{
		input_report_key(usbtouch->input, BTN_TOUCH, 0);
		input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, 0);
		input_mt_sync(usbtouch->input);

		input_report_key(usbtouch->input, KEY_BACK, 1);
		input_report_key(usbtouch->input, KEY_BACK, 0);
		input_sync(usbtouch->input);
		is_sendhome = true;
		int_counttime = 100;
		return;
	}


	/////////////////////////////////////////////////////////multi-point
	if(3 == usbtouch->touch && 3 != touch_lasthome)
	{
		int_counttime = 0;
		x_lasthome = usbtouch->x;
		y_lasthome = usbtouch->y;
		is_sendhome = false;
	}

	if(3 == usbtouch->touch2 && 3 != touch2_lasthome)
	{
		int_counttime = 0;
		x_lasthome = usbtouch->x;
		y_lasthome = usbtouch->y;
		x2_lasthome = usbtouch->x2;
		y2_lasthome = usbtouch->y2;
	}

	touch_lasthome = usbtouch->touch;
	touch2_lasthome = usbtouch->touch2;
	
	if((3 == usbtouch->touch) && (usbtouch->x - x_lasthome > -30) && (usbtouch->x - x_lasthome < 30) && (usbtouch->y - y_lasthome > -30) && (usbtouch->y - y_lasthome < 30) )
	{
		if (3 != usbtouch->touch2)//
		{
			if (2 == int_counttime)
			{


					input_report_key(usbtouch->input, BTN_TOUCH, 0);
					input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, 0);
					input_mt_sync(usbtouch->input);

					input_report_key(usbtouch->input, KEY_BACK, 1);
					input_report_key(usbtouch->input, KEY_BACK, 0);
					input_sync(usbtouch->input);
				is_sendhome = true;
				int_counttime = 100;
			}
		}
		else
		{
			if((usbtouch->x2 - x2_lasthome > -30) && (usbtouch->x2 - x2_lasthome < 30) && (usbtouch->y2 - y2_lasthome > -30) && (usbtouch->y2 - y2_lasthome < 30))
			{
				if (2 == int_counttime)
				{
					input_report_key(usbtouch->input, BTN_TOUCH, 0);
					input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, 0);
					input_mt_sync(usbtouch->input);

					input_report_key(usbtouch->input, KEY_HOME, 1);
					input_report_key(usbtouch->input, KEY_HOME, 0);
					input_sync(usbtouch->input);
					is_sendhome = true;
					int_counttime = 100;
				}
			}
			else
			{
				int_counttime = 100;
			}
		
		
		}
	}
	else
	{
		int_counttime = 100;
	}


	if (true == is_sendhome) return;



	/////////////////////////////////////////////////////////shortcuts
/*
	if(128 == usbtouch->touch)
	{
		int evlrtb =0;
		int evkey = 0;
		if(1==(int)pkt[10])
		{
			if (30==(int)pkt[5]) evlrtb = KEY_1;
			if (31==(int)pkt[5]) evlrtb = KEY_3;

			if (4==(int)pkt[6]) evkey = KEY_A;
			if (5==(int)pkt[6]) evkey = KEY_B;
			if (6==(int)pkt[6]) evkey = KEY_C;
			if (7==(int)pkt[6]) evkey = KEY_D;
			if (8==(int)pkt[6]) evkey = KEY_E;
			if (9==(int)pkt[6]) evkey = KEY_F;
			if (10==(int)pkt[6]) evkey = KEY_G;
			if (11==(int)pkt[6]) evkey = KEY_H;
			if (12==(int)pkt[6]) evkey = KEY_I;
			if (13==(int)pkt[6]) evkey = KEY_J;
			if (14==(int)pkt[6]) evkey = KEY_K;
			if (15==(int)pkt[6]) evkey = KEY_L;
			if (16==(int)pkt[6]) evkey = KEY_M;
			if (17==(int)pkt[6]) evkey = KEY_N;
			if (18==(int)pkt[6]) evkey = KEY_O;
			if (19==(int)pkt[6]) evkey = KEY_P;
			if (20==(int)pkt[6]) evkey = KEY_Q;
			if (21==(int)pkt[6]) evkey = KEY_R;
			if (22==(int)pkt[6]) evkey = KEY_S;
			if (23==(int)pkt[6]) evkey = KEY_T;
			if (24==(int)pkt[6]) evkey = KEY_U;
			if (25==(int)pkt[6]) evkey = KEY_V;
			if (26==(int)pkt[6]) evkey = KEY_W;
			if (27==(int)pkt[6]) evkey = KEY_X;
			if (28==(int)pkt[6]) evkey = KEY_Y;
			if (29==(int)pkt[6]) evkey = KEY_Z;

			input_report_key(usbtouch->input, BTN_TOUCH, 0);
			input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, 0);
			input_mt_sync(usbtouch->input);

			input_report_key(usbtouch->input, KEY_LEFTSHIFT, 1);
			input_report_key(usbtouch->input, evlrtb, 1);
			input_report_key(usbtouch->input, evlrtb, 0);
			input_report_key(usbtouch->input, evkey, 1);
			input_report_key(usbtouch->input, evkey, 0);
			input_report_key(usbtouch->input, KEY_LEFTSHIFT, 0);
			input_sync(usbtouch->input);
		}

	return ;
	}
*/
///////////////////////////////////////////////////////////////input report


	if((usbtouch->x - X_old > 5)||(usbtouch->x - X_old < -5) || (usbtouch->y - Y_old > 5) || (usbtouch->y - Y_old < -5) ||
	(usbtouch->x2 - X2_old > 5)||(usbtouch->x2 - X2_old < -5) || (usbtouch->y2 - Y2_old > 5) || (usbtouch->y2 - Y2_old < -5)
	|| (usbtouch->touch != intTouch_old) || (usbtouch->touch2 != intTouch2_old) )

	{
		X_old = usbtouch->x;
		Y_old = usbtouch->y;
		intTouch_old = usbtouch->touch;
		X2_old = usbtouch->x2;
		Y2_old = usbtouch->y2;
		intTouch2_old = usbtouch->touch2;

		//printk("P1:%d, id:%d , X:%d, Y:%d ,          id2:%d ,X2:%d, Y2:%d\n", usbtouch->touch,usbtouch->id,usbtouch->x,usbtouch->y,usbtouch->id2,usbtouch->x2,usbtouch->y2);


		if (0 < usbtouch->touch)
		{
			if (3 == usbtouch->touch) 
				touch_temp = 1;
			else
				touch_temp = 0;

			/* add by cym 20131212 */
			usbtouch->y = TOUCH_MAX_Y - usbtouch->y;
			
			printk("x:%d, y:%d\n", usbtouch->x, usbtouch->y);
			/* end add */

			input_report_key(usbtouch->input,ABS_MT_TRACKING_ID, usbtouch->id);
			input_report_key(usbtouch->input, BTN_TOUCH, touch_temp);
			input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, touch_temp);
			input_report_abs(usbtouch->input, ABS_MT_POSITION_X, usbtouch->y);
			input_report_abs(usbtouch->input, ABS_MT_POSITION_Y, usbtouch->x);
			input_mt_sync(usbtouch->input);
		}

		if (0 < usbtouch->touch2) 
		{
			if (3 == usbtouch->touch2) 
				touch_temp2 = 1;
			else
				touch_temp2 = 0;

			/* add by cym 20131212 */
			usbtouch->y2 = TOUCH_MAX_Y - usbtouch->y2;
			
			printk("x2:%d, y2:%d\n", usbtouch->x2, usbtouch->y2);
			/* end add */
			
			input_report_key(usbtouch->input,ABS_MT_TRACKING_ID, usbtouch->id2);
			input_report_key(usbtouch->input, BTN_TOUCH, touch_temp2);
			input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, touch_temp2);
			input_report_abs(usbtouch->input, ABS_MT_POSITION_X, usbtouch->y2);
			input_report_abs(usbtouch->input, ABS_MT_POSITION_Y, usbtouch->x2);
			input_mt_sync(usbtouch->input);
		}

		if(0 == usbtouch->touch && 0 == usbtouch->touch2) 
		{
			input_report_key(usbtouch->input, BTN_TOUCH, 0);
			input_report_abs(usbtouch->input, ABS_MT_TOUCH_MAJOR, 0);
			input_mt_sync(usbtouch->input);
		}
		
		input_sync(usbtouch->input);


	}
}




static void usbtouch_irq(struct urb *urb)
{
	struct usbtouch_usb *usbtouch = urb->context;
	int retval;

	switch (urb->status) {
	case 0:
		break;
	case -ETIME:
		return;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -EPIPE:
		return;
	default:
		goto exit;
	}

	usbtouch->type->process_pkt(usbtouch, usbtouch->data, urb->actual_length);

exit:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval)
		err("%s - usb_submit_urb failed with result: %d",
		    __func__, retval);
}

static int usbtouch_open(struct input_dev *input)
{
	char valsD[8] = {0x10,0x00,0xD0,0x00,0x00,0x00,0x00,0x00};//mt //0xD1 reset
	char valsE[8] = {0x10,0x00,0xE0,0x00,0x00,0x00,0x00,0x00};//mac //0xE0

	struct usbtouch_usb *usbtouch = input_get_drvdata(input);

	usbtouch->irq->dev = interface_to_usbdev(usbtouch->interface);

	if (!usbtouch->type->irq_always) {
		if (usb_submit_urb(usbtouch->irq, GFP_KERNEL))
		  return -EIO;
	}


	usb_control_msg(usbtouch->irq->dev, usb_sndctrlpipe(usbtouch->irq->dev, 0), 0x9, 0x21, 0x310, 0, valsD, 8, 0);///////////mt
	usb_control_msg(usbtouch->irq->dev, usb_sndctrlpipe(usbtouch->irq->dev, 0), 0x1, 0xa1, 0x310, 0, valsD, 8, 0);///////////mt

	usb_control_msg(usbtouch->irq->dev, usb_sndctrlpipe(usbtouch->irq->dev, 0), 0x9, 0x21, 0x310, 0, valsE, 8, 0);///////////mt
	usb_control_msg(usbtouch->irq->dev, usb_sndctrlpipe(usbtouch->irq->dev, 0), 0x1, 0xa1, 0x310, 0, valsE, 8, 0);///////////mt

	return 0;
}

static void usbtouch_close(struct input_dev *input)
{
	struct usbtouch_usb *usbtouch = input_get_drvdata(input);

	if (!usbtouch->type->irq_always)
		usb_kill_urb(usbtouch->irq);
}


static void usbtouch_free_buffers(struct usb_device *udev,
				  struct usbtouch_usb *usbtouch)
{
	usb_free_coherent(udev, usbtouch->type->rept_size,
			  usbtouch->data, usbtouch->data_dma);
	kfree(usbtouch->buffer);
}

static struct usb_endpoint_descriptor *
usbtouch_get_input_endpoint(struct usb_host_interface *interface)
{
	int i;

	for (i = 0; i < interface->desc.bNumEndpoints; i++)
		if (usb_endpoint_dir_in(&interface->endpoint[i].desc))
			return &interface->endpoint[i].desc;

	return NULL;
}

static int usbtouch_probe(struct usb_interface *intf,
			  const struct usb_device_id *id)
{
	struct usbtouch_usb *usbtouch;
	struct input_dev *input_dev;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usbtouch_device_info *type;
	int err = -ENOMEM;

	
	if (id->driver_info == DEVTYPE_IGNORE)/* ignored */
		return -ENODEV;

	endpoint = usbtouch_get_input_endpoint(intf->cur_altsetting);
	if (!endpoint)
		return -ENXIO;

	usbtouch = kzalloc(sizeof(struct usbtouch_usb), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!usbtouch || !input_dev)
		goto out_free;

	type = &usbtouch_dev_info[id->driver_info];
	usbtouch->type = type;
	if (!type->process_pkt)
		type->process_pkt = usbtouch_process_pkt;

	usbtouch->data = usb_alloc_coherent(udev, type->rept_size,
					    GFP_KERNEL, &usbtouch->data_dma);
	if (!usbtouch->data)
		goto out_free;

	if (type->get_pkt_len) {
		usbtouch->buffer = kmalloc(type->rept_size, GFP_KERNEL);
		if (!usbtouch->buffer)
			goto out_free_buffers;
	}

	usbtouch->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!usbtouch->irq) 
	{
		goto out_free_buffers;
	}

	usbtouch->interface = intf;
	usbtouch->input = input_dev;

	if (udev->manufacturer)
		strlcpy(usbtouch->name, udev->manufacturer, sizeof(usbtouch->name));

	if (udev->product) {
		if (udev->manufacturer)
			strlcat(usbtouch->name, " ", sizeof(usbtouch->name));
		strlcat(usbtouch->name, udev->product, sizeof(usbtouch->name));
	}

	if (!strlen(usbtouch->name))
		snprintf(usbtouch->name, sizeof(usbtouch->name),
			"ID: %04x:%04x",
			 le16_to_cpu(udev->descriptor.idVendor),
			 le16_to_cpu(udev->descriptor.idProduct));

	usb_make_path(udev, usbtouch->phys, sizeof(usbtouch->phys));
	strlcat(usbtouch->phys, "/input0", sizeof(usbtouch->phys));

	input_dev->name = usbtouch->name;
	input_dev->phys = usbtouch->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &intf->dev;

	input_set_drvdata(input_dev, usbtouch);

	input_dev->open = usbtouch_open;
	input_dev->close = usbtouch_close;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_dev->keybit[BIT_WORD(KEY_BACK)] = BIT_MASK(KEY_BACK);//
	input_dev->keybit[BIT_WORD(KEY_HOME)] = BIT_MASK(KEY_HOME);//

/*
		input_dev->keybit[BIT_WORD(KEY_LEFTSHIFT)] = BIT_MASK(KEY_LEFTSHIFT);//
		input_dev->keybit[BIT_WORD(KEY_LEFTCTRL)] = BIT_MASK(KEY_LEFTCTRL);//


		set_bit(KEY_A,input_dev->keybit);
		set_bit(KEY_B,input_dev->keybit);
		set_bit(KEY_C,input_dev->keybit);
		set_bit(KEY_D,input_dev->keybit);
		set_bit(KEY_E,input_dev->keybit);
		set_bit(KEY_F,input_dev->keybit);
		set_bit(KEY_G,input_dev->keybit);
		set_bit(KEY_H,input_dev->keybit);
		set_bit(KEY_I,input_dev->keybit);
		set_bit(KEY_J,input_dev->keybit);
		set_bit(KEY_K,input_dev->keybit);
		set_bit(KEY_L,input_dev->keybit);
		set_bit(KEY_M,input_dev->keybit);
		set_bit(KEY_N,input_dev->keybit);
		set_bit(KEY_O,input_dev->keybit);
		set_bit(KEY_P,input_dev->keybit);
		set_bit(KEY_Q,input_dev->keybit);
		set_bit(KEY_R,input_dev->keybit);
		set_bit(KEY_S,input_dev->keybit);
		set_bit(KEY_T,input_dev->keybit);
		set_bit(KEY_U,input_dev->keybit);
		set_bit(KEY_V,input_dev->keybit);
		set_bit(KEY_W,input_dev->keybit);
		set_bit(KEY_X,input_dev->keybit);
		set_bit(KEY_Y,input_dev->keybit);
		set_bit(KEY_Z,input_dev->keybit);
		set_bit(KEY_1,input_dev->keybit);
		set_bit(KEY_2,input_dev->keybit);
		set_bit(KEY_3,input_dev->keybit);
		set_bit(KEY_4,input_dev->keybit);
		set_bit(KEY_5,input_dev->keybit);
*/

	input_set_abs_params(input_dev, ABS_X, type->min_xc, type->max_xc, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, type->min_yc, type->max_yc, 0, 0);
	input_set_abs_params(input_dev,ABS_MT_POSITION_X, type->min_xc, type->max_xc, 0, 0);
	input_set_abs_params(input_dev,ABS_MT_POSITION_Y, type->min_yc, type->max_yc, 0, 0);
	input_set_abs_params(input_dev,ABS_MT_TOUCH_MAJOR, 0, 1, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_WIDTH_MAJOR,0, 1, 0, 0);
	if (type->max_press)
		input_set_abs_params(input_dev, ABS_PRESSURE, type->min_press,
		                     type->max_press, 0, 0);

	if (usb_endpoint_type(endpoint) == USB_ENDPOINT_XFER_INT)
		usb_fill_int_urb(usbtouch->irq, udev,
			 usb_rcvintpipe(udev, endpoint->bEndpointAddress),
			 usbtouch->data, type->rept_size,
			 usbtouch_irq, usbtouch, endpoint->bInterval);
	else
		usb_fill_bulk_urb(usbtouch->irq, udev,
			 usb_rcvbulkpipe(udev, endpoint->bEndpointAddress),
			 usbtouch->data, type->rept_size,
			 usbtouch_irq, usbtouch);

	usbtouch->irq->dev = udev;
	usbtouch->irq->transfer_dma = usbtouch->data_dma;
	usbtouch->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	if (type->init) 
	{
		err = type->init(usbtouch);
		if (err) 
		{
			goto out_free_urb;
		}
	}

	err = input_register_device(usbtouch->input);
	if (err) 
	{
		goto out_do_exit;
	}

	usb_set_intfdata(intf, usbtouch);

	if (usbtouch->type->irq_always) 
	{
		err = usb_submit_urb(usbtouch->irq, GFP_KERNEL);
		if (err) 
		{
			goto out_unregister_input;
		}
	}

	return 0;

out_unregister_input:
	input_unregister_device(input_dev);
	input_dev = NULL;
out_do_exit:
	if (type->exit)
		type->exit(usbtouch);
out_free_urb:
	usb_free_urb(usbtouch->irq);
out_free_buffers:
	usbtouch_free_buffers(udev, usbtouch);
out_free:
	input_free_device(input_dev);
	kfree(usbtouch);
	return err;
}

static void usbtouch_disconnect(struct usb_interface *intf)
{
	struct usbtouch_usb *usbtouch = usb_get_intfdata(intf);

	if (!usbtouch)
		return;

	usb_set_intfdata(intf, NULL);
	
	input_unregister_device(usbtouch->input);
	usb_free_urb(usbtouch->irq);
	if (usbtouch->type->exit)
		usbtouch->type->exit(usbtouch);
	usbtouch_free_buffers(interface_to_usbdev(intf), usbtouch);
	kfree(usbtouch);
}

MODULE_DEVICE_TABLE(usb, usbtouch_devices);

static struct usb_driver usbtouch_driver = 
{
	.name		= "iboardtouch",
	.probe		= usbtouch_probe,
	.disconnect	= usbtouch_disconnect,
	.id_table	= usbtouch_devices,
};

static int __init usbtouch_init(void)
{

	init_timer(&timer_s);
	timer_s.expires = jiffies + 1*HZ;
	timer_s.function = timer_enent;
	add_timer(&timer_s);

	return usb_register(&usbtouch_driver);

}

static void __exit usbtouch_cleanup(void)
{
	del_timer(&timer_s);

	usb_deregister(&usbtouch_driver);
}

module_init(usbtouch_init);
module_exit(usbtouch_cleanup);
MODULE_LICENSE("GPL");


