/* File:   i2cs_test2.c
   Author: M. P. Hayes, UCECE
   Date:   13 April 2013
   Descr: 
*/
#include "i2c_slave.h"
#include "usb_cdc.h"
#include "sys.h"
#include <stdio.h>
#include <string.h>


#define SDA_PIO PIO_DEFINE(PORT_A, 3)
#define SCL_PIO PIO_DEFINE(PORT_A, 4)

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
    usb_cdc_t usb_cdc;

    i2c_slave1 = i2c_slave_init (&i2c_bus_cfg, &i2c_slave1_cfg);

    usb_cdc = usb_cdc_init ();
    
    sys_redirect_stdin ((void *)usb_cdc_read, usb_cdc);
    sys_redirect_stdout ((void *)usb_cdc_write, usb_cdc);
    sys_redirect_stderr ((void *)usb_cdc_write, usb_cdc);

#if 1
    /* Wait until USB configured.  */
    while (! usb_cdc_update ())
        continue;
#endif

    printf ("i2cs_test2\r\n");
    
    while (1)
    {
        i2c_addr_t addr;
        uint8_t buffer[5];
        i2c_ret_t ret;
        int i;

        usb_cdc_update ();

        ret = i2c_slave_read (i2c_slave1, buffer, sizeof (buffer), 500000);
        if (ret == I2C_ERROR_TIMEOUT
            || ret == I2C_ERROR_BUSY)
            continue;

        fprintf (stderr, "%d: ", ret);
        for (i = 0; i < ret; i++)
            fprintf (stderr, "%d, ", buffer[i]);
        fprintf (stderr, "\r\n");
#if 0
        addr = buffer[0];

        if (addr >= sizeof (data))
            addr = 0;

        if (ret == 1)
            i2c_slave_write (i2c_slave1, &data[addr], sizeof(data[0]), 1000);
        else if (ret == 5)
            memcpy (&data[addr], buffer + 1, sizeof(data[0]));
#endif
    }
}

