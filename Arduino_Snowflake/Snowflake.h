#ifndef Snowflake_h
#define Snowflake_h
#include <Adafruit_SSD1306.h>
#include "Arduino.h"



class Snowflake {
  public:
    Snowflake(boolean ** grid, int snowflakeHeight1, int snowflakeWidth1);
    void drawSnowflake(Adafruit_SSD1306* display, int displayHeight, int displayWidth);
    void moveSnowflake() {
      xPos += xVel;
      yPos += yVel;
    }

  private: 
    boolean** pixelGrid;
    int snowflakeHeight, snowflakeWidth;
    int xPos, yPos; // refers to the position of the top-left corner of the snowflake pixel grid
    int xVel, yVel;
    
};
#endif