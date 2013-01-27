#include "SliderView.h"

namespace minimal {

SliderView::SliderView(const char* name, int16_t min, int16_t max, int16_t step)
  : View(name), min_(min), max_(max), step_(step), 
  okFocused_(false), cancelFocused_(false), onOK_(NULL) {
    if (min_ > max_) {
      int16_t tmp = min_;
      min_ = max_;
      max_ = tmp;
    }
    value_ = min_;
}

void SliderView::update(int16_t value) {
  value_ = value;
  if (value_ < min_) value_ = min_;
  if (value_ > max_) value_ = max_;
}

void SliderView::drawValue() {
  char number[7];
  sprintf(number, "%6d", value_);
  uint8_t offset = AD12864SPI::COLUMN_SIZE - 6 * Font::GLYPH_WIDTH - 20;
  uint8_t buffer[AD12864SPI::COLUMN_SIZE] = {0};
  Font::getData(number, buffer + offset, AD12864SPI::COLUMN_SIZE - offset, true);
  AD12864SPI::write(2, 0, buffer, AD12864SPI::COLUMN_SIZE);
  memset(buffer, 0, sizeof(buffer));
  Font::getData(number, buffer + offset, AD12864SPI::COLUMN_SIZE - offset, false);
  AD12864SPI::write(3, 0, buffer, AD12864SPI::COLUMN_SIZE);
}

void SliderView::drawSlider() {
  uint16_t a = value_ - min_;
  uint16_t b = max_ - min_;
  uint16_t barLength = a * 100 / b;
  
  uint8_t buffer[AD12864SPI::COLUMN_SIZE] = {0};
  buffer[12] = 254;
  buffer[13] = 1;
  buffer[AD12864SPI::COLUMN_SIZE - 13] = 254;
  buffer[AD12864SPI::COLUMN_SIZE - 14] = 1;
  for (uint8_t i = 14; i < AD12864SPI::COLUMN_SIZE - 14; ++i)
    buffer[i] = (i - 14 < barLength) ? 253 : 1;
  AD12864SPI::write(4, 0, buffer, AD12864SPI::COLUMN_SIZE);

  memset(buffer, 0, sizeof(buffer));
  for (uint8_t i = 13; i < AD12864SPI::COLUMN_SIZE - 13; ++i) buffer[i] = 2;
  buffer[12] = 1;
  buffer[AD12864SPI::COLUMN_SIZE - 13] = 1;
  AD12864SPI::write(5, 0, buffer, AD12864SPI::COLUMN_SIZE);
}

void SliderView::draw() {
  View::draw();
  drawOkButton(okFocused_);
  drawCancelButton(cancelFocused_);
  drawSlider();
  drawValue();
}

void SliderView::toggleFocus() {
  okFocused_ = cancelFocused_;
  cancelFocused_ = !okFocused_;
}

void SliderView::forward() {
  if (okFocused_ || cancelFocused_)
    toggleFocus();
  else
    update(value_ + step_);
}

void SliderView::backward() {
  if (okFocused_ || cancelFocused_)
    toggleFocus();
  else
    update(value_ - step_);
}

bool SliderView::click() {
  if (okFocused_ || cancelFocused_) {
    if (okFocused_) {
      if (onOK_) onOK_(value_);
      prevValue_ = value_;
    } else {
      value_ = prevValue_;
    }
    okFocused_ = false;
    cancelFocused_ = false;
    return true;
  } else {
    cancelFocused_ = true;
    return false;    
  }
}

}