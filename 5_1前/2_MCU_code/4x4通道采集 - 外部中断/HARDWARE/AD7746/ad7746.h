#include "sys.h"			//此头文件为stm32相关配置头文件

/**************************************************************************************
名    称：宏定义definetwo
功    能：对AD7746的端口进行申明定义
参    数：无
返回值  ：无
*****************************************************************************************/
#define AD7746_RDY  PCin(1)

/**************************************************************************************
名    称：宏定义definethree
功    能：对固定值的定义
参    数：无
返回值  ：无
*****************************************************************************************/
#define SLAVEADD         	0x90
#define CDC_RESET_ADDR   	0xBF
#define CDC_CAPDATA_ADDR 	0x01
#define CAPDAC			0x40
#define ERR 			0
#define NOACK 			1


/* AD7746 Register Definition */
#define AD7746_REG_STATUS				0
#define AD7746_REG_CAP_DATA_HIGH		1
#define AD7746_REG_CAP_DATA_MID			2
#define AD7746_REG_CAP_DATA_LOW			3
#define AD7746_REG_VT_DATA_HIGH			4
#define AD7746_REG_VT_DATA_MID			5
#define AD7746_REG_VT_DATA_LOW			6
#define AD7746_REG_CAP_SETUP			7
#define AD7746_REG_VT_SETUP				8
#define AD7746_REG_EXC_SETUP			9
#define AD7746_REG_CFG					10
#define AD7746_REG_CAPDACA				11
#define AD7746_REG_CAPDACB				12
#define AD7746_REG_CAP_OFFH				13
#define AD7746_REG_CAP_OFFL				14
#define AD7746_REG_CAP_GAINH			15
#define AD7746_REG_CAP_GAINL			16
#define AD7746_REG_VOLT_GAINH			17
#define AD7746_REG_VOLT_GAINL			18

/* AD7746_REG_STATUS bits */
#define AD7746_STATUS_EXCERR			(1 << 3)
#define AD7746_STATUS_RDY				(1 << 2)
#define AD7746_STATUS_RDYVT				(1 << 1)
#define AD7746_STATUS_RDYCAP			(1 << 0)

/* AD7746_REG_CAP_SETUP bits */
#define AD7746_CAPSETUP_CAPEN			(1 << 7)
#define AD7746_CAPSETUP_CIN2			(1 << 6)
#define AD7746_CAPSETUP_CAPDIFF			(1 << 5)
#define AD7746_CAPSETUP_CACHOP			(1 << 0)

/* AD7746_REG_VT_SETUP bits */
#define AD7746_VTSETUP_VTEN				(1 << 7)
#define AD7746_VTSETUP_VTMD_INT_TEMP	(0 << 5)
#define AD7746_VTSETUP_VTMD_EXT_TEMP	(1 << 5)
#define AD7746_VTSETUP_VTMD_VDD_MON		(2 << 5)
#define AD7746_VTSETUP_VTMD_EXT_VIN		(3 << 5)
#define AD7746_VTSETUP_EXTREF			(1 << 4)
#define AD7746_VTSETUP_VTSHORT			(1 << 1)
#define AD7746_VTSETUP_VTCHOP			(1 << 0)

/* AD7746_REG_EXC_SETUP bits */
#define AD7746_EXCSETUP_CLKCTRL			(1 << 7)
#define AD7746_EXCSETUP_EXCON			(1 << 6)
#define AD7746_EXCSETUP_EXCB			(1 << 5)
#define AD7746_EXCSETUP_NEXCB			(1 << 4)
#define AD7746_EXCSETUP_EXCA			(1 << 3)
#define AD7746_EXCSETUP_NEXCA			(1 << 2)
#define AD7746_EXCSETUP_EXCLVL(x)		(((x) & 0x3) << 0)

/* AD7746_REG_CFG bits */
#define AD7746_CONF_VTFS(x)				(((x) & 0x3) << 6)
#define AD7746_CONF_CAPFS(x)			(((x) & 0x7) << 3)
#define AD7746_CONF_MODE_IDLE			(0 << 0)
#define AD7746_CONF_MODE_CONT_CONV		(1 << 0)
#define AD7746_CONF_MODE_SINGLE_CONV	(2 << 0)
#define AD7746_CONF_MODE_PWRDN			(3 << 0)
#define AD7746_CONF_MODE_OFFS_CAL		(5 << 0)
#define AD7746_CONF_MODE_GAIN_CAL		(6 << 0)

/* AD7746_REG_CAPDACx bits */
#define AD7746_CAPDAC_DACEN				(1 << 7)
#define AD7746_CAPDAC_DACP(x)			((x) & 0x7F)


void AD7746Init(void);
void CDC_RDCAP(void);
unsigned char CDC_RDREG(unsigned char addr);
void CDC_WRREG(unsigned char addr, unsigned char reg);
void CDC_Reset(void);
float Read_7746data(void);
void CD4051_Switch(u8 chip, u8 channel);

extern char IIC_Flag;
