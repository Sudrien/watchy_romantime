#ifndef WATCHY_S32_H
#define WATCHY_S32_H

#include <Watchy.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <sunset.h>
#include "MoonPhases20pt7b.h"


#define DEG2RAD 0.0174532925

class WatchyRomantime : public Watchy{
    using Watchy::Watchy;
    public:
      SunSet sun;
      int16_t minutesSunrise;
      int16_t minutesSunset;
      int16_t minutesDaytime;
      int16_t minutesNighttime;
      int16_t minutesBeforeSunset;

      uint16_t fillColor;
      uint16_t detailColor;
      float_t hourAngle;

      WatchyRomantime(const watchySettings& s) : Watchy(s) {}
      void drawWatchFace();

      void drawWatchFaceDecider();
      void drawWatchFaceModeMoon();
      void drawWatchFaceModeNight();
      void drawWatchFaceModeModern();
      virtual void handleButtonPress();
    private:
      void integerToRoman(int, char *);

  };
#endif
