#ifndef SnowflakePixel_h
#define SnowflakePixel_h
#include <Adafruit_SSD1306.h>
#include "Arduino.h"
#include "Snowflake.h"

class SnowflakePixel {
  public:
    Snowflake generateSnowflake(int quad_width, int quad_height);

  private: 
    int row, col;
    
};
#endif