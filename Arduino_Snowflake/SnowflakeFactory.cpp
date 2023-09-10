#include "HardwareSerial.h"
#include "SnowflakeFactory.h"
#include "SnowflakePixel.h"
#include "Snowflake.h"
#include "Arduino.h"
#include <stdlib.h>
#include <time.h>
#include <vector>


boolean isOutOfBoundsOfQuadHalf(int row, int col, int quad_width, int quad_height) {
  return row >= quad_height || row < 0 || col >= quad_width || col < 0 || col >= row;
}

void growSnowflake(boolean** grid, int row, int col, std::vector<SnowflakePixel> history, int quad_width, int quad_height) {
  int histSize = history.size();
  boolean willGrow = random(0, histSize+1) == 0;
  SnowflakePixel pixel(row, col);
  Serial.println("Trying to grow " + willGrow);
  willGrow ? Serial.println("Will Grow") : Serial.println("Will not grow");


  if(willGrow && !isOutOfBoundsOfQuadHalf(row, col, quad_width, quad_height) && histSize <= MAX_GROWTH_STEPS && std::find(history.begin(), history.end(), pixel) == history.end()) {
    grid[row][col] = true;
    Serial.println("Success here");
    std::vector<SnowflakePixel> newHist(history);
    newHist.push_back(pixel);
    growSnowflake(grid, row+1, col, newHist, quad_width, quad_height);
    growSnowflake(grid, row-1, col, newHist, quad_width, quad_height);
    growSnowflake(grid, row, col + 1, newHist, quad_width, quad_height);
    growSnowflake(grid, row, col - 1, newHist, quad_width, quad_height);
  }
}


Snowflake SnowflakeFactory::generateSnowflake(int quad_width, int quad_height) {
  boolean ** quad = new boolean * [quad_height];
  srand(time(0));

  // make empty quad
  for(int row = 0; row < quad_height; row++) {
    quad[row] = new boolean[quad_width];
    for(int col = 0; col < quad_width; col++) {
      quad[row][col] = false;
    }
  }

  // Light up edges
  for(int row = 0; row < quad_height; row++) {
    if(row == quad_height - 1) {
      // light up bottom row of quad
      for(int col = 0; col < quad_width; col++) {
        quad[row][col] = true;
      }
    }
    else {
      // light up diagonal and last column
      quad[row][quad_width - 1] = true;
      quad[row][row] = true;
    }
  
  }
  Serial.println("Sanity test");

  // grow parts of snowflake
  SnowflakePixel growthLocations[MAX_GROWTH_LOCATIONS];
  for(int i = 0; i < MAX_GROWTH_LOCATIONS; i++) {
    int row = random(0, quad_height);
    int col = random(0, row+1);
    SnowflakePixel start(row, col);
    growthLocations[i] = SnowflakePixel(row, col);
    std::vector<SnowflakePixel> hist;
    //hist.push_back(start);
    growSnowflake(quad, row, col, hist, quad_width, quad_height);
  }




  // reflect the half-quad pattern

  int fullHeight = quad_height*2 - 1;
  int fullWidth = quad_width*2 - 1;
  boolean ** fullSnowflake = new boolean * [fullHeight];

  // reflect quad into full snowflake
  for(int row = 0; row < fullHeight; row++) {
    fullSnowflake[row] = new boolean[fullWidth];
    for(int col = 0; col < fullWidth; col++) {
      boolean pixel = false;
      if(row < quad_height && col < quad_width) {
        // original quad
        pixel = quad[row][col];
      }
      else if(row >= quad_height && col < quad_width) {
        // reflect row
        int diff = row - quad_height;
        int reflectedRow = quad_height - diff - 2;
        //pixel = fullSnowflake[reflectedRow][col];// changeme
      }
      else if(col >= quad_width) {
        // reflect column
        int diff = col - quad_width;
        int reflectedCol = quad_width - diff - 2;
        //pixel = fullSnowflake[row][reflectedCol];// changeme
      }
      

      fullSnowflake[row][col] = pixel;
    }
  }


  // temp result
  Snowflake snowflake(fullSnowflake, fullHeight, fullWidth);
  Serial.println("Printed Snowflake");
  return snowflake;
}