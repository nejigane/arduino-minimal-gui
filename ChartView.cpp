#include "ChartView.h"

namespace minimal {

ChartView::ChartView(const char* name, int16_t min, int16_t max) 
  : View(name), min_(min), max_(max), value_(0) {
  if (min_ > max_) {
    int16_t tmp = min_;
    min_ = max_;
    max_ = tmp;
  }
  memset(history_, 0, sizeof(history_));
}

void ChartView::drawChart() {
  uint8_t buffer[100] = {0};
  
  for (uint8_t i = 0; i < 4; ++i) {
    uint8_t offset = (3 - i) * 8;
    memset(buffer, 0, sizeof(buffer));
    for (uint8_t j = 0; j < 100; ++j) {
      if (history_[j] + 4 > offset) {
        uint8_t diff = history_[j] + 4 - offset;
        if (diff >= 8) {
          buffer[j] = 255;
        } else {
          for (uint8_t k = 0; k < diff; ++k) buffer[j] = (buffer[j] >> 1) | 128;
        }
      }
    }
    if (i == 3) {
      for (uint8_t j = 0; j < 100; ++j) buffer[j] &= 15;
    }
    AD12864SPI::write(i + 2, 14, buffer, 100);
  }
}

void ChartView::drawValue() {
  char number[7];
  sprintf(number, "%6d", value_);
  uint8_t buffer[Font::GLYPH_WIDTH * 6] = {0};
  uint8_t bufferLength = Font::GLYPH_WIDTH * 6;
  Font::getData(number, buffer, bufferLength, true);
  AD12864SPI::write(6, 20, buffer, bufferLength);
  memset(buffer, 0, sizeof(buffer));
  Font::getData(number, buffer, bufferLength, false);
  AD12864SPI::write(7, 20, buffer, bufferLength);
}

void ChartView::update(int16_t value) {
  value_ = value;
  if (value_ < min_) value_ = min_;
  if (value_ > max_) value_ = max_;

  for (uint8_t i = 0; i < 99; ++i) history_[i] = history_[i + 1];
  
  uint16_t a = value_ - min_;
  uint16_t b = max_ - min_;    
  history_[99] = b == 0 ? 24 : a * 24 / b;
}

void ChartView::draw() {
  View::draw();
  drawOkButton(true);
  drawChart();
  drawValue();
}

}