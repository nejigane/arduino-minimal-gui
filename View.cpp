#include "View.h"

namespace minimal {

View::View(const char* name) {
  name_ = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(name_, name);
}

void View::draw() {
  uint8_t offset = (AD12864SPI::COLUMN_SIZE - strlen(name_) * Font::GLYPH_WIDTH) / 2;

  uint8_t buffer[AD12864SPI::COLUMN_SIZE] = {0};
  Font::getData(name_, buffer + offset, AD12864SPI::COLUMN_SIZE - offset, true);
  AD12864SPI::write(0, 0, buffer, AD12864SPI::COLUMN_SIZE);

  for (uint8_t i = 0; i < AD12864SPI::COLUMN_SIZE; ++i) buffer[i] = 128;
  Font::getData(name_, buffer + offset, AD12864SPI::COLUMN_SIZE - offset, false);
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

void View::drawOkButton(bool focused) {
  uint8_t buffer[44] = {0};
  uint8_t bufferSize = sizeof(buffer) / sizeof(uint8_t);

  Font::getData("OK", buffer + bufferSize / 2 - Font::GLYPH_WIDTH, Font::GLYPH_WIDTH * 2, true);
  for (int8_t i = 0; i < bufferSize - 0; ++i) 
    buffer[i] = focused ? ~buffer[i] : buffer[i] | 1;
  buffer[0] = 254;
  buffer[bufferSize - 1] = 254;
  AD12864SPI::write(6, AD12864SPI::COLUMN_SIZE / 2 + 8, buffer, bufferSize);

  memset(buffer, 0, sizeof(buffer));
  Font::getData("OK", buffer + bufferSize / 2 - Font::GLYPH_WIDTH, Font::GLYPH_WIDTH * 2, false);
  for (int8_t i = 0; i < bufferSize - 0; ++i) 
    buffer[i] = focused ? ~buffer[i] : buffer[i] | 128;
  buffer[0] = 127;
  buffer[bufferSize - 1] = 127;
  AD12864SPI::write(7, AD12864SPI::COLUMN_SIZE / 2 + 8, buffer, bufferSize);
}

void View::drawCancelButton(bool focused) {
  uint8_t buffer[56] = {0};
  uint8_t bufferSize = sizeof(buffer) / sizeof(uint8_t);

  Font::getData("Cancel", buffer + bufferSize / 2 - Font::GLYPH_WIDTH * 3, Font::GLYPH_WIDTH * 6, true);
  for (int8_t i = 0; i < bufferSize; ++i) 
    buffer[i] = focused ? ~buffer[i] : buffer[i] | 1;
  buffer[0] = 254;
  buffer[bufferSize - 1] = 254;
  AD12864SPI::write(6, 12, buffer, bufferSize);

  memset(buffer, 0, sizeof(buffer));
  Font::getData("Cancel", buffer + bufferSize / 2 - Font::GLYPH_WIDTH * 3, Font::GLYPH_WIDTH * 6, false);
  for (int8_t i = 0; i < bufferSize; ++i) 
    buffer[i] = focused ? ~buffer[i] : buffer[i] | 128;
  buffer[0] = 127;
  buffer[bufferSize - 1] = 127;
  AD12864SPI::write(7, 12, buffer, bufferSize);
}

const char* View::getName() const {
  return name_;
}

}