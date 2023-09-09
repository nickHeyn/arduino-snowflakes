#ifndef Snowflake_h
#define Snowflake_h
#include <Adafruit_SSD1306.h>
#include "Arduino.h"



class Snowflake {
  public:
    Snowflake(boolean ** grid, int snowflakeHeight1, int snowflakeWidth1);
    void drawSnowflake(Adafruit_SSD1306 display);

  private: 
    boolean** pixelGrid;
    int snowflakeHeight, snowflakeWidth;
    int xPos, yPos;
    
};
#endif