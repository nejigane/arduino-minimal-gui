#ifndef __MINIMAL_AD12864SPI_H__
#define __MINIMAL_AD12864SPI_H__

#include <Arduino.h>
#include <SPI.h>

namespace minimal {

class AD12864SPI {
private:
  static uint8_t cs1_;
  static uint8_t a0_;
  static void transfer(uint8_t data);
  static void moveTo(uint8_t page, uint8_t column);
public:
  static const uint8_t COLUMN_SIZE = 128;
  static const uint8_t PAGE_SIZE = 8;
  static void begin(uint8_t cs1, uint8_t res, uint8_t a0);
  static void write(uint8_t page, uint8_t column, const uint8_t* data, uint8_t length);
  static void clear();
};

}

#endif
