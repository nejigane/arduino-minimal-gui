#ifndef __MINIMAL_AD12864SPI_H__
#define __MINIMAL_AD12864SPI_H__

#include <Arduino.h>
#include <SPI.h>

namespace minimal {

class AD12864SPI {
private:
  uint8_t cs1_;
  uint8_t a0_;
  void transfer(uint8_t data);
  void moveTo(uint8_t page, uint8_t column);
public:
  void begin(uint8_t cs1, uint8_t res, uint8_t a0);
  void write(uint8_t page, uint8_t column, const uint8_t* data, uint8_t length);
  void clear();
};

extern AD12864SPI Display;

}

#endif
