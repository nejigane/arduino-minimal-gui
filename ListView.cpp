#include "ListView.h"

namespace minimal {

const uint8_t ListView::SCROLL_BAR_WIDTH = 12;

ListView::ListView(const char* name) 
  : View(name), head_(NULL), visibleHead_(NULL), focused_(NULL), activeSubView_(NULL) {
}

void ListView::drawItem(Item* item, uint8_t position) {
  uint8_t buffer[AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH] = {0};
  Font::getData(item->name, buffer + 4, AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH - 4, true);
  if (item->subView != NULL)
    Font::getData(">", buffer + AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH - 12, Font::GLYPH_WIDTH, true);
  if (item == focused_) {
    for (uint8_t i = 0; i < AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH; ++i) 
      buffer[i] = ~buffer[i];
  }
  AD12864SPI::write(2 + position * 2, 0, buffer, AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH);

  for (uint8_t i = 0; i < AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH; ++i) buffer[i] = 0;
  Font::getData(item->name, buffer + 4, AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH - 4, false);
  if (item->subView != NULL)
    Font::getData(">", buffer + AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH - 12, Font::GLYPH_WIDTH, false);
  if (item == focused_) {
    for (uint8_t i = 0; i < AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH; ++i)
     buffer[i] = ~buffer[i];
  }
  AD12864SPI::write(3 + position * 2, 0, buffer, AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH);
}

void ListView::drawScrollBar() {
  uint8_t visibleHeadPosition = 0;
  uint8_t itemCount = 0;
  Item* current = head_;
  while (current != NULL) {
    if (current == visibleHead_) visibleHeadPosition = itemCount;
    current = current->next;
    ++itemCount;
  }

  uint8_t maxHeight = AD12864SPI::PAGE_SIZE * 6 - 3;
  uint8_t thumbY = visibleHeadPosition * maxHeight / itemCount + 1;
  uint8_t thumbHeight = (itemCount <= 3) ? maxHeight : 3 * maxHeight / itemCount;

  for (uint8_t i = 0; i < 6; ++i) {
    uint8_t data = 0;
    for (uint8_t j = 0; j < 8; ++j) {
      uint8_t bit = (j + i * 8 >= thumbY && j + i * 8 < thumbY + thumbHeight) ? 1 : 0;
      data |= bit << j;
    }
    uint8_t buffer[SCROLL_BAR_WIDTH] = {0};
    buffer[0] = 255;
    buffer[SCROLL_BAR_WIDTH - 1] = 255;
    for (uint8_t k = 2; k < SCROLL_BAR_WIDTH - 2; ++k) buffer[k] = data;
    if (i == 5) {
      for (uint8_t k = 0; k < SCROLL_BAR_WIDTH; ++k)
        buffer[k] |= 128;
    }
    
    AD12864SPI::write(2 + i, AD12864SPI::COLUMN_SIZE - SCROLL_BAR_WIDTH, buffer, SCROLL_BAR_WIDTH);
  }
}

void ListView::draw() {
  if (activeSubView_) {
    activeSubView_->draw();
    return;
  }

  View::draw();
  drawScrollBar();
  uint8_t position = 0;
  Item* current = visibleHead_;
  while (current != NULL) {
    drawItem(current, position);
    current = current->next;
    ++position;
  }
}

void ListView::forward() {
  if (focused_ == NULL) return;

  if (activeSubView_ != NULL) {
    activeSubView_->forward();
    return;
  }

  if (focused_->next != NULL) {
    if (focused_ == visibleHead_->next->next) visibleHead_ = visibleHead_->next;
    focused_ = focused_->next;
  }
}

void ListView::backward() {
  if (focused_ == NULL) return;
  
  if (activeSubView_ != NULL) {
    activeSubView_->backward();
    return;
  }

  if (focused_->prev != NULL) {
    if (focused_ == visibleHead_) visibleHead_ = visibleHead_->prev;
    focused_ = focused_->prev;
  }
}

bool ListView::click() {
  if (focused_ == NULL) return true;
  if (activeSubView_ != NULL) {
    if(activeSubView_->click()) {
      AD12864SPI::clear();
      activeSubView_ = NULL;
    }
  } else {
    if (focused_->callback) focused_->callback(focused_->name);
    if (focused_->subView) {
      AD12864SPI::clear();
      activeSubView_ = focused_->subView;
    }
  }
  return false;
}

void ListView::addItem(const char* name, void (*callback)(const char*)) {
  Item *item = new Item();
  item->callback = callback;
  item->subView = NULL;
  addItem(name, item);
}

void ListView::addItem(View* subView) {
  Item *item = new Item();
  item->callback = NULL;
  item->subView = subView;
  addItem(subView->getName(), item);
}

void ListView::addItem(const char* name, Item* item) {
  item->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(item->name, name);
  item->next = NULL;
  
  if (head_ == NULL) {
    head_ = item;
    visibleHead_ = item;
    focused_ = item;
    item->prev = NULL;
  } else {
    Item* current = head_;
    while (current->next != NULL) current = current->next;
    current->next = item;
    item->prev = current;
  }
}

}