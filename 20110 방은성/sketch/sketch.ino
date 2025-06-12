include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void)
{
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0, 15, "hello world!");
  u8g2.drawTriangle(27,50, 64,32, 100,50);
  u8g2.sendBuffer();
  delay(1000);
}

void loop(void)
{
    u8g2.setFont(u8g2_font_unifont_t_korean2);
    u8g2.clearBuffer();
    u8g2.setCursor(0, 40);
    u8g2.print("한글이 되네~");  
    u8g2.sendBuffer();
  delay(1000);

}
