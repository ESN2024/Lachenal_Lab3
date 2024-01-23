#include <stdio.h>
#include "system.h"
#include <sys/alt_irq.h>
#include <io.h>
#include <alt_types.h>
#include "sys/alt_sys_init.h"
#include "unistd.h" //access to usleep
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"

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


__int8_t LSBX = 0x00;
__int8_t MSBX = 0x00;
__int8_t LSBY = 0x00;
__int8_t MSBY = 0x00;
__int8_t LSBZ = 0x00;
__int8_t MSBZ = 0x00;

__int16_t dataX = 0x0000;
__int16_t dataY = 0x0000;
__int16_t dataZ = 0x0000;




/*
static void handle_interrupts(void* context, alt_u32 id)
{   
	
}
*/
volatile __uint32_t speed;


alt_u8 read_data(alt_u8 address) {
        I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 0);
        I2C_write(OPENCORES_I2C_0_BASE,address,0);
        I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 0);
        return I2C_read(OPENCORES_I2C_0_BASE, 1);
        
}

void write_data(alt_u8 address, __int8_t wr_data){

        I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 0);
        I2C_write(OPENCORES_I2C_0_BASE, address, 0);
        I2C_write(OPENCORES_I2C_0_BASE, wr_data, 1);
}


/*
void BCD(alt_u16 data)
{   
        __uint16_t u4;
        __uint16_t u3;
        __uint16_t u2;
        __uint16_t u1;
        __uint16_t u0;

        u4 = data / 10000;
        u3 = (data % 10000) / 1000;
	u2 = (data % 1000) / 100;
	u1 = (data % 1000) / 10;
        u0 = data % 10;
				
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE,u0);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_2_BASE,u1);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_3_BASE,u2);
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_4_BASE,u3);
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_5_BASE,u4);
			
}
*/
int main(){

	// Initialisation du bus I2C
        speed = 100000;
        I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,speed);

        while(1){
                
                // Read data for activate write
                LSBX = read_data(X0);
                MSBX = read_data (X1);

                if (dataX & 0x8000) dataX = -(0xFFFF - dataX + 1);
                dataX = MSBX << 8 | LSBX;

	        dataX=dataX*3.9;

                
                alt_printf("Data read: 0x%x\n", dataX);
        }
        


        //Calibration

        // X axis
        

        // Y axis
        //I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 0);
        //I2C_write(OPENCORES_I2C_0_BASE, 0x1E, 0);
        //I2C_write(OPENCORES_I2C_0_BASE, 0, 1);

        // Z axis
        //I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 0);
        //I2C_write(OPENCORES_I2C_0_BASE, 0x1E, 0);
        //I2C_write(OPENCORES_I2C_0_BASE, 0, 1);
	

    
    
	
	return 0;
}
