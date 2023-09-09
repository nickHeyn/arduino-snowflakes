#ifndef Snowflake_h
#define Snowflake_h
#include <Adafruit_SSD1306.h>
#include "Arduino.h"


#define SNOWFLAKE_QUADRANT_HEIGHT 9
#define SNOWFLAKE_QUADRANT_WIDTH 9
#define SNOWFLAKE_FULL_HEIGHT SNOWFLAKE_QUADRANT_HEIGHT * 2 - 1
#define SNOWFLAKE_FULL_WIDTH SNOWFLAKE_QUADRANT_WIDTH * 2 - 1


class Snowflake {
  public:
    Snowflake();
    void drawSnowflake(Adafruit_SSD1306 display);
    void setSerial();

  private: 
    unsigned char snowflakeQuadrant[SNOWFLAKE_QUADRANT_HEIGHT][SNOWFLAKE_QUADRANT_WIDTH];
    unsigned char ** generateFullSnowflake();
    int xPos, yPos;
    
};
#endif