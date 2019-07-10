#include "myiic.h"
#include "delay.h"
#include "AD7746.h"
#include "usart.h"


void Read_Config(u8 num_IIC)
{
	unsigned char Config;
	IIC_Start(num_IIC);
	IIC_Send_Byte(SLAVEADD,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(0x0A,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
	{
		IIC_Start(num_IIC);				//re-start
		IIC_Send_Byte(SLAVEADD+1,num_IIC);	//read function
	}
	if(!(IIC_Flag&(1<<NOACK)))
		Config = IIC_Read_Byte(0,num_IIC);	//read cap data reg
	printf("config%d\r\n",Config);
	IIC_Stop(num_IIC);
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
}



//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	IIC_SCL_1=1;
	IIC_SDA_1=1;
	IIC_SCL_2=1;
	IIC_SDA_2=1;
	IIC_SCL_3=0;
	IIC_SDA_3=0;
	IIC_SCL_4=0;
	IIC_SDA_4=0;

}


//产生IIC起始信号
void IIC_Start(u8 num_IIC)
{
	if(num_IIC==1)
	{
		SDA_OUT_1();     //sda线输出
		IIC_Flag = 0;
		IIC_SDA_1=1;	  	  
		IIC_SCL_1=1;
		delay_us(4);
		IIC_SDA_1=0;//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		IIC_SCL_1=0;//钳住I2C总线，准备发送或接收数据 
	}
	else if(num_IIC==2)
	{
		SDA_OUT_2();     //sda线输出
		IIC_Flag = 0;
		IIC_SDA_2=1;	  	  
		IIC_SCL_2=1;
		delay_us(4);
		IIC_SDA_2=0;//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		IIC_SCL_2=0;//钳住I2C总线，准备发送或接收数据 
	}
	else if(num_IIC==3)
	{
		SDA_OUT_3();     //sda线输出
		IIC_Flag = 0;
		IIC_SDA_3=1;	  	  
		IIC_SCL_3=1;
		delay_us(4);
		IIC_SDA_3=0;//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		IIC_SCL_3=0;//钳住I2C总线，准备发送或接收数据 
	}
	else if(num_IIC==4)
	{
		SDA_OUT_4();     //sda线输出
		IIC_Flag = 0;
		IIC_SDA_4=1;	  	  
		IIC_SCL_4=1;
		delay_us(4);
		IIC_SDA_4=0;//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		IIC_SCL_4=0;//钳住I2C总线，准备发送或接收数据 
	}
}	
//产生IIC停止信号
void IIC_Stop(u8 num_IIC)
{
	if(num_IIC==1)
	{
		SDA_OUT_1();//sda线输出
		IIC_SCL_1=0;
		IIC_SDA_1=0;//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		IIC_SCL_1=1; 
		IIC_SDA_1=1;//发送I2C总线结束信号
		delay_us(4);			
	}
	else if(num_IIC==2)
	{
		SDA_OUT_2();//sda线输出
		IIC_SCL_2=0;
		IIC_SDA_2=0;//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		IIC_SCL_2=1; 
		IIC_SDA_2=1;//发送I2C总线结束信号
		delay_us(4);		
	}
	else if(num_IIC==3)
	{
		SDA_OUT_3();//sda线输出
		IIC_SCL_3=0;
		IIC_SDA_3=0;//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		IIC_SCL_3=1; 
		IIC_SDA_3=1;//发送I2C总线结束信号
		delay_us(4);			
	}
	else if(num_IIC==4)
	{
		SDA_OUT_4();//sda线输出
		IIC_SCL_4=0;
		IIC_SDA_4=0;//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		IIC_SCL_4=1; 
		IIC_SDA_4=1;//发送I2C总线结束信号
		delay_us(4);			
	}			   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(u8 num_IIC)
{
	if(num_IIC==1)
	{
		u8 ucErrTime=0;
		SDA_IN_1();      //SDA设置为输入  
		IIC_SDA_1=1;delay_us(1);	   
		IIC_SCL_1=1;delay_us(1);	 
		while(READ_SDA_1)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				IIC_Stop(num_IIC);
				return 1;
			}
		}
		IIC_SCL_1=0;//时钟输出0 	   
		return 0;  
	}
	else if(num_IIC==2)
	{
		u8 ucErrTime=0;
		SDA_IN_2();      //SDA设置为输入  
		IIC_SDA_2=1;delay_us(1);	   
		IIC_SCL_2=1;delay_us(1);	 
		while(READ_SDA_2)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				IIC_Stop(num_IIC);
				return 1;
			}
		}
		IIC_SCL_2=0;//时钟输出0 	   
		return 0;  
	}
	else if(num_IIC==3)
	{
		u8 ucErrTime=0;
		SDA_IN_3();      //SDA设置为输入  
		IIC_SDA_3=1;delay_us(1);	   
		IIC_SCL_3=1;delay_us(1);	 
		while(READ_SDA_3)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				IIC_Stop(num_IIC);
				return 1;
			}
		}
		IIC_SCL_3=0;//时钟输出0 	   
		return 0;  
	}
	else if(num_IIC==4)
	{
		u8 ucErrTime=0;
		SDA_IN_4();      //SDA设置为输入  
		IIC_SDA_4=1;delay_us(1);	   
		IIC_SCL_4=1;delay_us(1);	 
		while(READ_SDA_4)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				IIC_Stop(num_IIC);
				return 1;
			}
		}
		IIC_SCL_4=0;//时钟输出0 	   
		return 0;  
	}	
	return 0;
} 
//产生ACK应答
void IIC_Ack(u8 num_IIC)
{
	if(num_IIC==1)
	{
		IIC_SCL_1=0;
		SDA_OUT_1();
		IIC_SDA_1=0;
		delay_us(2);
		IIC_SCL_1=1;
		delay_us(2);
		IIC_SCL_1=0;
	}
	else if(num_IIC==2)
	{
		IIC_SCL_2=0;
		SDA_OUT_2();
		IIC_SDA_2=0;
		delay_us(2);
		IIC_SCL_2=1;
		delay_us(2);
		IIC_SCL_2=0;
	}
	else if(num_IIC==3)
	{
		IIC_SCL_3=0;
		SDA_OUT_3();
		IIC_SDA_3=0;
		delay_us(2);
		IIC_SCL_3=1;
		delay_us(2);
		IIC_SCL_3=0;
	}
	else if(num_IIC==4)
	{
		IIC_SCL_4=0;
		SDA_OUT_4();
		IIC_SDA_4=0;
		delay_us(2);
		IIC_SCL_4=1;
		delay_us(2);
		IIC_SCL_4=0;
	}	
}
//不产生ACK应答		    
void IIC_NAck(u8 num_IIC)
{
	if(num_IIC==1)
	{
		IIC_SCL_1=0;
		SDA_OUT_1();
		IIC_SDA_1=1;
		delay_us(2);
		IIC_SCL_1=1;
		delay_us(2);
		IIC_SCL_1=0;
	}
	else if(num_IIC==2)
	{
		IIC_SCL_2=0;
		SDA_OUT_2();
		IIC_SDA_2=1;
		delay_us(2);
		IIC_SCL_2=1;
		delay_us(2);
		IIC_SCL_2=0;
	}
	else if(num_IIC==3)
	{
		IIC_SCL_3=0;
		SDA_OUT_3();
		IIC_SDA_3=1;
		delay_us(2);
		IIC_SCL_3=1;
		delay_us(2);
		IIC_SCL_3=0;
	}
	else if(num_IIC==4)
	{
		IIC_SCL_4=0;
		SDA_OUT_4();
		IIC_SDA_4=1;
		delay_us(2);
		IIC_SCL_4=1;
		delay_us(2);
		IIC_SCL_4=0;
	}	
}						     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd,u8 num_IIC)
{       

	if(num_IIC==1)
	{
		u8 t;   
		SDA_OUT_1(); 	    
		IIC_SCL_1=0;//拉低时钟开始数据传输
		delay_us(2);
		for(t=0;t<8;t++)
		{              
			IIC_SDA_1=(txd&0x80)>>7;
			txd<<=1; 	  
			delay_us(2);   //对TEA5767这三个延时都是必须的
			IIC_SCL_1=1;
			delay_us(2); 
			IIC_SCL_1=0;	
			delay_us(2);
		}	 
		SDA_IN_1();
		
		IIC_SCL_1=1;
		
		if(READ_SDA_1)
		IIC_Flag |= 1<<NOACK;
		delay_us(2);
		IIC_SCL_1=0;
	}
	else if(num_IIC==2)
	{
		u8 t;   
		SDA_OUT_2(); 	    
		IIC_SCL_2=0;//拉低时钟开始数据传输
		delay_us(2);
		for(t=0;t<8;t++)
		{              
			IIC_SDA_2=(txd&0x80)>>7;
			txd<<=1; 	  
			delay_us(2);   //对TEA5767这三个延时都是必须的
			IIC_SCL_2=1;
			delay_us(2); 
			IIC_SCL_2=0;	
			delay_us(2);
		}
		SDA_IN_2();
		
		IIC_SCL_2=1;
		
		if(READ_SDA_2)
			IIC_Flag |= 1<<NOACK;
		delay_us(2);
		IIC_SCL_2=0;
	}
	else if(num_IIC==3)
	{
		u8 t;   
		SDA_OUT_3(); 	    
		IIC_SCL_3=0;//拉低时钟开始数据传输
		delay_us(2);
		for(t=0;t<8;t++)
		{              
			IIC_SDA_3=(txd&0x80)>>7;
			txd<<=1; 	  
			delay_us(2);   //对TEA5767这三个延时都是必须的
			IIC_SCL_3=1;
			delay_us(2); 
			IIC_SCL_3=0;	
			delay_us(2);
		}
		SDA_IN_3();
		
		IIC_SCL_3=1;
		
		if(READ_SDA_3)
			IIC_Flag |= 1<<NOACK;
		delay_us(2);
		IIC_SCL_3=0;
	}
	else if(num_IIC==4)
	{
		u8 t;   
		SDA_OUT_4(); 	    
		IIC_SCL_4=0;//拉低时钟开始数据传输
		delay_us(2);
		for(t=0;t<8;t++)
		{              
			IIC_SDA_4=(txd&0x80)>>7;
			txd<<=1; 	  
			delay_us(2);   //对TEA5767这三个延时都是必须的
			IIC_SCL_4=1;
			delay_us(2); 
			IIC_SCL_4=0;	
			delay_us(2);
		}
		SDA_IN_4();
		
		IIC_SCL_4=1;
		
		if(READ_SDA_4)
			IIC_Flag |= 1<<NOACK;
		delay_us(2);
		IIC_SCL_4=0;
	}	
	

} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack,u8 num_IIC)
{
	if(num_IIC==1)
	{
		unsigned char i,rr=0;
		SDA_IN_1();//SDAéè???aê?è?
		IIC_SCL_1 = 0;
		delay_us(2);
		for(i=0;i<8;i++ )
		{
			IIC_SCL_1=0; 
			delay_us(2);
					IIC_SCL_1=1;
			rr<<=1;
			rr |= READ_SDA_1;
					IIC_SCL_1=0;
					delay_us(2); 
		}					 
			SDA_OUT_1();
			IIC_SDA_1 = ack;
			
			IIC_SCL_1 = 1;
			delay_us(2);
			IIC_SCL_1 = 0;
		return rr;
		}
	else if(num_IIC==2)
	{
		unsigned char i,rr=0;
		SDA_IN_2();
		IIC_SCL_2 = 0;
		delay_us(2);
		for(i=0;i<8;i++ )
		{
			IIC_SCL_2=0; 
			delay_us(2);
			IIC_SCL_2=1;
			rr<<=1;
			rr |= READ_SDA_2;
			IIC_SCL_2=0;
			delay_us(2); 
		}					 
		SDA_OUT_2();
		IIC_SDA_2 = ack;
		
		IIC_SCL_2 = 1;
		delay_us(2);
		IIC_SCL_2 = 0;
		return rr;
	}
	else if(num_IIC==3)
	{
		unsigned char i,rr=0;
		SDA_IN_3()
		IIC_SCL_3 = 0;
		delay_us(2);
		for(i=0;i<8;i++ )
		{
			IIC_SCL_3=0; 
			delay_us(2);
					IIC_SCL_3=1;
			rr<<=1;
			rr |= READ_SDA_3;
			IIC_SCL_3=0;
			delay_us(2); 
		}					 
			SDA_OUT_3();
			IIC_SDA_3 = ack;
			
			IIC_SCL_3 = 1;
			delay_us(2);
			IIC_SCL_3 = 0;
		return rr;
	}
	else if(num_IIC==4)
	{
		unsigned char i,rr=0;
		SDA_IN_4();
		IIC_SCL_4 = 0;
		delay_us(2);
		for(i=0;i<8;i++ )
		{
			IIC_SCL_4=0; 
			delay_us(2);
					IIC_SCL_4=1;
			rr<<=1;
			rr |= READ_SDA_4;
			IIC_SCL_4=0;
			delay_us(2); 
		}					 
			SDA_OUT_4();
			IIC_SDA_4 = ack;
			
			IIC_SCL_4 = 1;
			delay_us(2);
			IIC_SCL_4 = 0;
		return rr;
	}	
	return 0;
}

























