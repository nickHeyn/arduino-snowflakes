#include "HardwareSerial.h"
#include "SnowflakeFactory.h"
#include "SnowflakePixel.h"
#include "Snowflake.h"
#include "Arduino.h"
#include <stdlib.h>
#include <vector>


boolean SnowflakeFactory::isOutOfBoundsOfQuadHalf(int row, int col) {
  return row >= quad_height || row < 0 || col >= quad_width || col < 0 || col >= row;
}

void SnowflakeFactory::growSnowflake(boolean** grid, int row, int col, std::vector<SnowflakePixel> history) {
  int histSize = history.size();
  boolean willGrow = random(0, histSize+1) == 0;
  SnowflakePixel pixel(row, col);

  if(willGrow && !isOutOfBoundsOfQuadHalf(row, col) && histSize <= MAX_GROWTH_STEPS && std::find(history.begin(), history.end(), pixel) == history.end()) {
    grid[row][col] = true;
    
    std::vector<SnowflakePixel> newHist(history);
    newHist.push_back(pixel);
    growSnowflake(grid, row+1, col, newHist);
    growSnowflake(grid, row-1, col, newHist);
    growSnowflake(grid, row, col + 1, newHist);
    growSnowflake(grid, row, col - 1, newHist);
  }
}


Snowflake* SnowflakeFactory::generateSnowflake(int xPos, int yPos) {
  Serial.println("Entering generateSnowflake...");
  boolean ** quad = new boolean * [quad_height];

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

  // grow parts of snowflake
  SnowflakePixel growthLocations[MAX_GROWTH_LOCATIONS];
  for(int i = 0; i < MAX_GROWTH_LOCATIONS; i++) {
    int row = random(0, quad_height);
    int col = random(0, row+1);
    SnowflakePixel start(row, col);
    growthLocations[i] = SnowflakePixel(row, col);
    std::vector<SnowflakePixel> hist;
    growSnowflake(quad, row, col, hist);
  }

  // reflect the half-quad pattern to rest of quad
  for (int row = 0; row < quad_height; row++) {
    for(int col = 0; col < row; col++) {
      boolean valueToReflect = quad[row][col];
      quad[col][row] = valueToReflect;
    }
  }

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
        // reflect into lower left quadrant
        int diff = row - quad_height;
        int reflectedRow = quad_height - diff - 2;
        pixel = fullSnowflake[reflectedRow][col];
      }
      else if(col >= quad_width) {
        // reflect right side of grid
        int diff = col - quad_width;
        int reflectedCol = quad_width - diff - 2;
        pixel = fullSnowflake[row][reflectedCol];
      }
      

      fullSnowflake[row][col] = pixel;
    }
  }

  for(int r = 0; r < quad_height; r++){
    delete[] quad[r];
  }
  delete[] quad;

  return new Snowflake(fullSnowflake, xPos, yPos, fullHeight, fullWidth, millis());
}