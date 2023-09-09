#ifndef SnowflakeFactory_h
#define SnowflakeFactory_h
#include <Adafruit_SSD1306.h>
#include "Arduino.h"
#include "Snowflake.h"

class SnowflakeFactory {
  public:
    Snowflake generateSnowflake(int quad_width, int quad_height);

  private: 
    
};
#endif