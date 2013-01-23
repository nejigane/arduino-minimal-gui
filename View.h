#ifndef __MINIMAL_VIEW_H__
#define __MINIMAL_VIEW_H__

#include <Arduino.h>
#include "AD12864SPI.h"
#include "Font.h"

namespace minimal {

class View {
private:
  String name_;	
public:
  View(const char* name);
  virtual void draw();
  virtual void forward();
  virtual void backward();
  virtual bool click();
};

}

#endif
