#include "GUI.h"

namespace minimal {

View* GUI::view_ = NULL;

void GUI::begin(View* view, uint8_t cs1, uint8_t res, uint8_t a0) {
  view_ = view;
  AD12864SPI::begin(cs1, res, a0);
}

void GUI::draw() {
  if (view_) view_->draw();
}

void GUI::forward() {
  if (view_) view_->forward();
}

void GUI::backward() {
  if (view_) view_->backward();
}

void GUI::click() {
  if (view_) view_->click();
}

}