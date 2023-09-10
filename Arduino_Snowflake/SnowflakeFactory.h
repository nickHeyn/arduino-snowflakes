#ifndef SnowflakeFactory_h
#define SnowflakeFactory_h
#include "Snowflake.h"

#define MAX_GROWTH_STEPS 3
#define MAX_GROWTH_LOCATIONS 5

class SnowflakeFactory {
  public:
    Snowflake generateSnowflake(int quad_width, int quad_height);

  private: 
  
};
#endif