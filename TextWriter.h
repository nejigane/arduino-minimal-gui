#ifndef __MINIMAL_TEXT_WRITER_H__
#define __MINIMAL_TEXT_WRITER_H__

#include <Arduino.h>

namespace minimal {

class TextWriter {
private:
  //static uint8_t 
public:
  static void write(const char* string, uint8_t* buffer, uint8_t bufferLength, bool isUpper);
};

}

#endif
