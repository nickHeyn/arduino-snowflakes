#include "SnowflakeFactory.h"
#include "Snowflake.h"


Snowflake SnowflakeFactory::generateSnowflake(int quad_width, int quad_height) {
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

  int fullHeight = quad_height*2;
  int fullWidth = quad_width*2;
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
        int reflectedRow = quad_height - 1 - diff;
        pixel = fullSnowflake[reflectedRow][col];
      }
      else if(col >= quad_width) {
        // reflect column
        int diff = col - quad_width;
        int reflectedCol = quad_width - 1 - diff;
        pixel = fullSnowflake[row][reflectedCol];
      }
      

      fullSnowflake[row][col] = pixel;
    }
  }


  // temp result
  Snowflake snowflake(fullSnowflake, fullHeight, fullWidth);
  Serial.println("Printed Snowflake");
  return snowflake;
}