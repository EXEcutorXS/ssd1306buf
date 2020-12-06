#include "main.h"
#include "SSD1306Lbuf.h"

// Screen object

extern const unsigned char myFont[165][5];
extern I2C_HandleTypeDef hi2c1;
uint8_t buffer[SSD1306_HEIGHT*SSD1306_WIDTH/8];
uint16_t cursor=0;
//
//  Send a byte to the command register
//
void ssd1306_WriteCommand(uint8_t command)
{
	HAL_I2C_Mem_Write(&hi2c1,SSD1306_I2C_ADDR,0x00,1,&command,1,10);
}


//
//	Initialize the oled screen
//
void ssd1306_Init(void)
{	

	// Wait for the screen to boot
	HAL_Delay(100);
	
	/* Init LCD */
	ssd1306_WriteCommand(0xAE); //display off
	ssd1306_WriteCommand(0x20); //Set Memory Addressing Mode   
	ssd1306_WriteCommand(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	ssd1306_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction
	ssd1306_WriteCommand(0x00); //---set low column address
	ssd1306_WriteCommand(0x10); //---set high column address
	ssd1306_WriteCommand(0x40); //--set start line address
	ssd1306_WriteCommand(0x81); //--set contrast control register
	ssd1306_WriteCommand(0xFF);
	ssd1306_WriteCommand(0xA1); //--set segment re-map 0 to 127
	ssd1306_WriteCommand(0xA6); //--set normal display
	ssd1306_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
	ssd1306_WriteCommand(0x3F); //
	ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	ssd1306_WriteCommand(0xD3); //-set display offset
	ssd1306_WriteCommand(0x00); //-not offset
	ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
	ssd1306_WriteCommand(0xF0); //--set divide ratio
	ssd1306_WriteCommand(0xD9); //--set pre-charge period
	ssd1306_WriteCommand(0x22); //
	ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration
	ssd1306_WriteCommand(0x12);
	ssd1306_WriteCommand(0xDB); //--set vcomh
	ssd1306_WriteCommand(0x20); //0x20,0.77xVcc
	ssd1306_WriteCommand(0x8D); //--set DC-DC enable
	ssd1306_WriteCommand(0x14); //
	ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel
}

void ssd1306_GotoXY(int x, int y)
{
cursor=SSD1306_WIDTH*y+x;
}

void ssd1306_PutRuC(char* c)
{

	uint8_t pos;
	if (*c==0xD0) pos=*(c+1)-144+101;
	else if (*c==0xD1) pos=*(c+1)-128+149;
	else return;
	memcpy(buffer+cursor,&myFont[pos][0],5);
	cursor+=5;
}


void ssd1306_Put(char c)
{
	memcpy(buffer+cursor,&myFont[c-0x20][0],5);
	cursor+=5;
}

void ssd1306_PutString(char *c)
{
	while (*c) {
		if (*c==0xD0 || *c==0xD1)
		{
			ssd1306_PutRuC(c);
			c+=2;
		}
		else
			ssd1306_Put(*c++);
		cursor++;
	}
}

void ssd1306_Clean(void)
{
	uint16_t i;
	for (i=0;i<SSD1306_HEIGHT*SSD1306_WIDTH/8;i++)
	buffer[i]=0;
}

void ssd1306_Update(void)
{
	ssd1306_WriteCommand(0xB0);
		ssd1306_WriteCommand(0x00);
		ssd1306_WriteCommand(0x10);
		HAL_I2C_Mem_Write(&hi2c1,SSD1306_I2C_ADDR,0x40,1,buffer,SSD1306_WIDTH*SSD1306_HEIGHT/8,1000);
}

void ssd1306_DrawBitmap(uint8_t* buf)
{
	memcpy(buffer,buf,sizeof(buffer));
}
