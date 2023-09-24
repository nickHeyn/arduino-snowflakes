#ifndef SnowflakeFactory_h
#define SnowflakeFactory_h
#include "Snowflake.h"
#include "SnowflakePixel.h"
#include <vector>

#define MAX_GROWTH_STEPS 3
#define MAX_GROWTH_LOCATIONS 5

class SnowflakeFactory {
  public:
    SnowflakeFactory(int quad_w, int quad_h) {
      quad_width = quad_w;
      quad_height = quad_h;
    }

    Snowflake generateSnowflake(int xPos, int yPos);

  private: 
    int quad_width, quad_height;
    void growSnowflake(boolean** grid, int row, int col, std::vector<SnowflakePixel> history);
    boolean isOutOfBoundsOfQuadHalf(int row, int col);
};
#endif