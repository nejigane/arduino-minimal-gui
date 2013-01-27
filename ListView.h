#ifndef __MINIMAL_LISTVIEW_H__
#define __MINIMAL_LISTVIEW_H__

#include "View.h"

namespace minimal {

class ListView : public View {
protected:
  static const uint8_t SCROLL_BAR_WIDTH;
  struct Item {
    char* name;
    void (*callback)(const char*);
    View* subView;
    Item* next;
    Item* prev;
  };
  Item* head_;
  Item* visibleHead_;
  Item* focused_;
  View* activeSubView_;
  void drawScrollBar();
  void drawItem(Item* item, uint8_t position);
  void addItem(const char* name, Item* item);

public:
  ListView(const char* name);
  virtual void draw();
  virtual void forward();
  virtual void backward();
  virtual bool click();
  void addItem(const char* name, void (*callback)(const char*));
  void addItem(View* subView);
};

}

#endif
