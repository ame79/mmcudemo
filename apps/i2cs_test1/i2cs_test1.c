/* File:   i2cs_test1.c
   Author: M. P. Hayes, UCECE
   Date:   13 April 2013
   Descr: 
*/
#include "i2c_slave.h"
#include <string.h>


#define SDA_PIO PIO_DEFINE(PORT_A, 5)
#define SCL_PIO PIO_DEFINE(PORT_A, 6)

static const i2c_bus_cfg_t i2c_bus_cfg =
{
    .scl = SCL_PIO,
    .sda = SDA_PIO
};


static const i2c_slave_cfg_t i2c_slave1_cfg =
{
    .id = 0x32,
};


int
main (void)
{
    i2c_t i2c_slave1;
    uint8_t data[] = {0, 1, 2, 3};

    i2c_slave1 = i2c_slave_init (&i2c_bus_cfg, &i2c_slave1_cfg);

    while (1)
    {
        i2c_addr_t addr;
        uint8_t buffer[5];
        i2c_ret_t ret;

        ret = i2c_slave_read (i2c_slave1, buffer, sizeof (buffer), 1000);

        addr = buffer[0];

        if (addr >= sizeof (data))
            addr = 0;

        if (ret == 1)
            i2c_slave_write (i2c_slave1, &data[addr], sizeof(data[0]), 1000);
        else if (ret == 5)
            memcpy (&data[addr], buffer + 1, sizeof(data[0]));
    }
}

