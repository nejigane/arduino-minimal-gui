#include "AD12864SPI.h"

namespace minimal {

uint8_t AD12864SPI::cs1_ = 255;
uint8_t AD12864SPI::a0_ = 255;

void AD12864SPI::transfer(uint8_t data) {
  digitalWrite(cs1_, LOW);
  SPI.transfer(data);
  digitalWrite(cs1_, HIGH);
}

void AD12864SPI::moveTo(uint8_t page, uint8_t column) {
  digitalWrite(a0_, LOW);
  transfer(0xb0 | page);
  transfer(0x00 | (column & 0xf));
  transfer(0x10 | ((column & 0xf0) >> 4));
}

void AD12864SPI::begin(uint8_t cs1, uint8_t res, uint8_t a0) {
  cs1_ = cs1;
  a0_ = a0;
  
  pinMode(cs1_, OUTPUT);
  digitalWrite(cs1_, HIGH);

  pinMode(a0_, OUTPUT);
  digitalWrite(a0_, LOW);

  pinMode(res, OUTPUT);
  digitalWrite(res, LOW);
  delay(50);
  digitalWrite(res, HIGH);
  delay(50);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setDataMode(SPI_MODE0);
  transfer(0xaf);
  transfer(0x2f);
  transfer(0x81);
  transfer(0x17);
  transfer(0x24);
  transfer(0xa3);
  transfer(0xc8);
  transfer(0xa0);
  transfer(0xa4);
  transfer(0xa6);
  transfer(0xad);
  transfer(0x00);
  transfer(0x40);

  clear();
}

void AD12864SPI::write(uint8_t page, uint8_t column, const uint8_t* data, uint8_t length) {
  if (page >= PAGE_SIZE || column >= COLUMN_SIZE) return;

  moveTo(page, column);
  digitalWrite(a0_, HIGH);
  for (uint8_t i = 0; i < length && column + i < COLUMN_SIZE; ++i) {
    transfer(*(data + i));
  }
}

void AD12864SPI::clear() {
  for(uint8_t page = 0; page < PAGE_SIZE; ++page) {
    moveTo(page, 0);
    digitalWrite(a0_, HIGH);
    for(uint8_t column = 0; column < COLUMN_SIZE; ++column) transfer(0);
  }
}

}