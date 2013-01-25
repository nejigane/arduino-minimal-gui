#include "View.h"

namespace minimal {

View::View(const char* name) : name_(name) {
}

void View::draw() {
  char nameChar[name_.length() + 1];
  name_.toCharArray(nameChar, name_.length() + 1);

  uint8_t offset = (AD12864SPI::COLUMN_SIZE - name_.length() * Font::GLYPH_WIDTH) / 2;

  uint8_t buffer[AD12864SPI::COLUMN_SIZE] = {0};
  Font::getData(nameChar, buffer + offset, AD12864SPI::COLUMN_SIZE - offset, true);
  AD12864SPI::write(0, 0, buffer, AD12864SPI::COLUMN_SIZE);

  for (uint8_t i = 0; i < AD12864SPI::COLUMN_SIZE; ++i) buffer[i] = 128;
  Font::getData(nameChar, buffer + offset, AD12864SPI::COLUMN_SIZE - offset, false);
  AD12864SPI::write(1, 0, buffer, AD12864SPI::COLUMN_SIZE);
}

void View::forward() {
  // do nothing.
}

void View::backward() {
  // do nothing.
}

bool View::click() {
  return true;
}

}