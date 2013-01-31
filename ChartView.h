#ifndef __MINIMAL_CHARTVIEW_H__
#define __MINIMAL_CHARTVIEW_H__

#include "View.h"

namespace minimal {

class ChartView : public View {
protected:
  uint8_t history_[100];
  int16_t min_;
  int16_t max_;
  int16_t value_;
  void drawValue();
  void drawChart();

public:
  ChartView(const char* name, int16_t min = 0, int16_t max = 1023);
  virtual void draw();
  void update(int16_t value);
};

}

#endif
