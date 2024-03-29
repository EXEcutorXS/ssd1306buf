#ifndef SSD1306L
#define SSD1306L

#include "main.h"

// I2c port as defined in main generated by CubeMx
#define SSD1306_I2C_PORT		hi2c1
// I2c address
#define SSD1306_I2C_ADDR        0x78
// SSD1306 width in pixels
#define SSD1306_WIDTH           128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT          64

#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH*SSD1306_HEIGHT/8)

void ssd1306_WriteCommand(uint8_t command);
void ssd1306_Init(void);
void ssd1306_GotoXY(int x, int y);
void ssd1306_PutRuC(char* c);
void ssd1306_Put(char c);
void ssd1306_PutString(char *c);
void ssd1306_Clean(void);
void ssd1306_Update(void);
void ssd1306_DrawBitmap(unsigned char* buf);
void ssd1306_PutPixel(uint8_t x, uint8_t y);
void ssd1306_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void ssd1306_DrawDottedLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void ssd1306_DrawFilledRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);


#endif
