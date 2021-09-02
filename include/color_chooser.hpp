#ifndef _COLOR_CHOOSER_H_
#define _COLOR_CHOOSER_H_

#include <FastLED.h>
#include <stdint.h>

#define USED_COLORS     4

class ColorChooser
{
    public:
        static CRGB getNextColor(CRGB actColor);
        static CRGB getPreviousColor(CRGB actColor);
    private:
        static CRGB colors[USED_COLORS];
};

#endif // _COLOR_CHOOSER_H_
