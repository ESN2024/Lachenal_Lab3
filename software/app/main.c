#include <stdio.h>
#include "system.h"
#include <sys/alt_irq.h>
#include <io.h>
#include <alt_types.h>
#include "sys/alt_sys_init.h"
#include "unistd.h" //access to usleep
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include <stdbool.h>

// #define I2C_DEBUG


// Register address
#define X0 0x32
#define X1 0x33
#define Y0 0x34
#define Y1 0x35
#define Z0 0x36
#define Z1 0x37

#define Xoff 0x1E
#define Yoff 0x1F
#define Zoff 0x20

#define DEVICE 0x1D

#define addr_dataFormat 0x31

__int8_t state_button = 0x00;

bool negative_stateX = 0;
bool negative_stateY = 0;
bool negative_stateZ = 0;
bool global_negative_state = 0;

__int8_t LSBX = 0x00;
__int8_t MSBX = 0x00;
__int8_t LSBY = 0x00;
__int8_t MSBY = 0x00;
__int8_t LSBZ = 0x00;
__int8_t MSBZ = 0x00;

__int16_t dataX = 0x0000;
__int16_t dataY = 0x0000;
__int16_t dataZ = 0x0000;

__int16_t dataBCD = 0x0000;

__int8_t test;


volatile __uint32_t speed;


alt_u8 read_data(alt_u8 address) {
        I2C_start(OPENCORES_I2C_0_BASE, DEVICE, 0);
        I2C_write(OPENCORES_I2C_0_BASE,address,0);
        I2C_start(OPENCORES_I2C_0_BASE, DEVICE, 1);
        return I2C_read(OPENCORES_I2C_0_BASE, 1);
        
}

void write_data(alt_u8 address, __int8_t wr_data){

        I2C_start(OPENCORES_I2C_0_BASE, DEVICE, 0);
        I2C_write(OPENCORES_I2C_0_BASE, address, 0);
        I2C_write(OPENCORES_I2C_0_BASE, wr_data, 1);
}



void BCD(alt_u16 data, bool state)
{   
        __uint8_t u4;
        __uint8_t u3;
        __uint8_t u2;
        __uint8_t u1;
        __uint8_t u0;

        u4 = data / 10000;
        u3 = (data % 10000) / 1000;
	u2 = (data % 1000) / 100;
	u1 = (data % 100) / 10;
        u0 = data % 10;
				
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE,u0);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_2_BASE,u1);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_3_BASE,u2);
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_4_BASE,u3);
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_5_BASE,u4);

        if(state == 1)
        {
                IOWR_ALTERA_AVALON_PIO_DATA(PIO_6_BASE,0xf);
        }
        else if ( state == 0){
                IOWR_ALTERA_AVALON_PIO_DATA(PIO_6_BASE,0x0);
        }
			
}

static void button_axis_irq(void* context,  alt_u32 id)
{   
        if (state_button == 0x00){
                alt_printf("Affichage 7seg Y\n");
                state_button = 0x01;
        }
        else if (state_button == 0x01){
                alt_printf("Affichage 7seg Z\n");
                state_button = 0x02;
        }
        else if (state_button == 0x02){
                alt_printf("Affichage 7seg X\n");
                state_button = 0x00;
        }

        IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_0_BASE,0);
}

static void clk_irq(void* context,  alt_u32 id) 
{
        // Read data for activate write
        LSBX = read_data(X0);
        MSBX = read_data(X1);
        LSBY = read_data(Y0);
        MSBY = read_data(Y1);
        LSBZ = read_data(Z0);
        MSBZ = read_data(Z1);

        dataX = MSBX << 8 | LSBX;
        dataY = MSBY << 8 | LSBY;
        dataZ = MSBZ << 8 | LSBZ;

        // if the msb bit is 1 (0x8000) change the value to negative (A2 complement)

        if (dataX & 0x8000){

                dataX = ~dataX;
                dataX = dataX +1;
        }

        if (dataY & 0x8000){
                dataY = ~dataY;
                dataY = dataY +1;
        }

        if (dataZ & 0x8000){
                dataZ = ~dataZ;
                dataZ = dataZ +1;
        }

        // sensitivity +/-2g so scale factor is 3.9

        dataX = dataX * 3.9;
        dataY = dataY * 3.9;
        dataZ = dataZ * 3.9;

        if (state_button == 0x00){
                dataBCD = dataX;
                global_negative_state = negative_stateX;
        }
        else if (state_button == 0x01){
                dataBCD = dataY;
                global_negative_state = negative_stateY;
        }
        else if (state_button == 0x02){
                dataBCD = dataZ;
                global_negative_state = negative_stateZ;
        }

        BCD(dataBCD,global_negative_state);

        IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);

}

int main(){

	// Initialisation du bus I2C
        speed = 100000;
        I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,speed);

        if (!I2C_start(OPENCORES_I2C_0_BASE, DEVICE, 0)){
                alt_printf("reset\n");
        }

        //Read to activate write 
        LSBX = read_data(X0);

        //DATA FORMAT
        write_data(addr_dataFormat,0x08);

        // Set offset 
        write_data(Xoff, 0x00);
        write_data(Yoff, 0x00);
        write_data(Zoff, 0x00);

        // Button init
        IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_0_BASE, 1);
        IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_0_BASE, 0);
        alt_irq_register( PIO_0_IRQ, NULL, button_axis_irq );

        //Timer init
        IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
	alt_irq_register(TIMER_0_IRQ,NULL,clk_irq);

        alt_printf("Affichage 7seg X\n");

        while(1);
	
	return 0;
}
