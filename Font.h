#ifndef __MINIMAL_FONT_H__
#define __MINIMAL_FONT_H__

#include <Arduino.h>

namespace minimal {

class Font {
public:
	static uint8_t getWidth() { return 7; };
	static void getData(const char* string, uint8_t* buffer, uint8_t bufferLength, bool isUpper);
};

}

#endif
