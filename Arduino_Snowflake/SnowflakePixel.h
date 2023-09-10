#ifndef SnowflakePixel_h
#define SnowflakePixel_h

class SnowflakePixel {
  public:
    SnowflakePixel(int row1, int col1) {
      row = row1;
      col = col1;
    }
    SnowflakePixel() {
      
    }
    int getRow() { return row; }
    int getCol() { return col; }
    boolean isEqual(SnowflakePixel snowflakePixel) { return snowflakePixel.getRow() == row && snowflakePixel.getCol() == col; }
    bool operator== ( const SnowflakePixel &s) {
       return s.row == row && s.col == col;
    }

  private: 
    int row, col;
    
};
#endif