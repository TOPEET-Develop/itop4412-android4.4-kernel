#ifndef __EGALAX_H__
#define __EGALAX_H__

#define EGALAX_I2C_NAME	"egalax_i2c"
#define EGALAX_I2C_ADDR (0x04)
#define EGALAX_IRQ	IRQ_EINT(4)

struct egalax_i2c_platform_data {
	unsigned int gpio_int;
	unsigned int gpio_en;
	unsigned int gpio_rst;
};

#endif//__EGALAX_H__
