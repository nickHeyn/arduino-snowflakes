#ifndef Snowflake_h
#define Snowflake_h
#include <Adafruit_SSD1306.h>
#include "Arduino.h"



class Snowflake {
  public:
    Snowflake() {
      
    }
    Snowflake(boolean ** grid, int xPos1, int yPos1, int snowflakeHeight1, int snowflakeWidth1, unsigned long spawnTime);
    void drawSnowflake(Adafruit_SSD1306* display, int displayHeight, int displayWidth);
    void moveSnowflake(unsigned long currentTime) {
      unsigned long timeDiff = currentTime - timeAtLastMove;
      xPos += (xVel * timeDiff * 0.001);
      yPos += (yVel * timeDiff * 0.001);
      timeAtLastMove = currentTime;
    }

    double getXPos() {
      return xPos;
    }

    double getYPos() {
      return yPos;
    }

    void deletePixelGrid() {
      for(int row = 0; row < snowflakeHeight; row++) {
        delete[] pixelGrid[row];
      }

      delete[] pixelGrid;
    }

  private: 
    boolean** pixelGrid;
    int snowflakeHeight, snowflakeWidth;
    double xPos, yPos; // refers to the position of the top-left corner of the snowflake pixel grid
    double xVel, yVel;
    unsigned long timeAtLastMove;
    
};
#endif