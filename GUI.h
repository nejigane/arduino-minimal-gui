#ifndef __MINIMAL_GUI_H__
#define __MINIMAL_GUI_H__

#include "View.h"
#include "ListView.h"
#include "ChartView.h"
#include "SliderView.h"
#include "AD12864SPI.h"

namespace minimal {

class GUI {
private:
  static View* view_;
public:
  static void begin(View* view, uint8_t cs1, uint8_t res, uint8_t a0);
  static void draw();
  static void forward();
  static void backward();
  static void click();
};

}

#endif
