#ifndef __MINIMAL_VIEW_H__
#define __MINIMAL_VIEW_H__

#include <Arduino.h>
#include "AD12864SPI.h"
#include "Font.h"

namespace minimal {

class View {
protected:
  char* name_;	
public:
  View(const char* name);
  virtual void draw();
  virtual void forward();
  virtual void backward();
  virtual bool click();
  const char* getName() const;
  void drawOkButton(bool focused = false);
  void drawCancelButton(bool focused = false);
};

}

#endif
