#ifndef __MINIMAL_SLIDERVIEW_H__
#define __MINIMAL_SLIDERVIEW_H__

#include "View.h"

namespace minimal {

class SliderView : public View {
protected:
  int16_t min_;
  int16_t max_;
  int16_t step_;
  int16_t value_;
  int16_t prevValue_;
  void (*onOK_)(int16_t);
  bool okFocused_;
  bool cancelFocused_;
  void update(int16_t value);
  void drawSlider();
  void drawValue();
  void toggleFocus();

public:
  SliderView(const char* name, int16_t min = 0, int16_t max = 100, int16_t step = 2);
  virtual void draw();
  virtual void forward();
  virtual void backward();
  virtual bool click();
};

}

#endif
