#include "watchy_romantime.h"

RTC_DATA_ATTR int showState = 0;

void WatchyRomantime::drawWatchFace() {

  sun.setPosition(settings.lat.toFloat(), settings.lon.toFloat(), settings.gmtOffset / 3600);

  //from minutes past midnight
  sun.setCurrentDate(tmYearToCalendar(currentTime.Year), currentTime.Month, currentTime.Day);
  sun.setTZOffset(settings.gmtOffset / 3600);
  minutesSunrise = sun.calcSunrise();
  minutesSunset = sun.calcSunset();
  minutesDaytime = (minutesSunset - minutesSunrise);
  minutesNighttime = (1440 - minutesDaytime);

  minutesBeforeSunset = minutesSunset -  (currentTime.Hour * 60 + currentTime.Minute); // i.e.zero degrees

  fillColor = GxEPD_WHITE;
  detailColor = GxEPD_BLACK;
  hourAngle = 0.0;

  drawWatchFaceDecider();

  }


void WatchyRomantime::drawWatchFaceModeMoon(){
  int16_t  x_center, y_center;
  uint16_t w_center, h_center;


  display.fillScreen(GxEPD_BLACK);

  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(GxEPD_WHITE);


  long long unix_time = makeTime(currentTime) + settings.gmtOffset;
  int moonphase = sun.moonPhase(unix_time);


  display.setFont(&MoonPhases20pt7b);
  display.setCursor(90, 110);
  display.print((char)(moonphase+0x50));
  }

void WatchyRomantime::drawWatchFaceModeNight(){
  display.fillScreen(fillColor);
  display.fillRect(0, 0, 200, 10, detailColor);
  
  for(int16_t i = 13; i <= 23; i++) {
    display.drawLine(
      100,
      10,
      100 + 200 * cos(i * 15 * DEG2RAD),
      10 + 200 * sin(i * 15 * DEG2RAD),
      fillColor
      );
    }

  for(int16_t i = 1; i < 12; i++) {
    display.drawLine(
      100,
      10,
      100 + 200 * cos(i * 15 * DEG2RAD),
      10 + 200 * sin(i * 15 * DEG2RAD),
      detailColor
      );
    }


  display.drawRect(0, 0, 200, 200, GxEPD_BLACK);

  char numerals[12][6] = { "I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII" };

  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(detailColor);

  int16_t  x_center, y_center;
  uint16_t w_center, h_center;

  //just hardcode text positions. squaring circles doesn't have much benefit.

  display.getTextBounds(numerals[0], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(18 - w_center / 2, 28);
  display.println(numerals[0]);

  display.getTextBounds(numerals[1], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(18 - w_center / 2, 53);
  display.println(numerals[1]);

  display.getTextBounds(numerals[2], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(18 - w_center / 2, 83);
  display.println(numerals[2]);
  
  display.getTextBounds(numerals[3], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(18 - w_center / 2, 130);
  display.println(numerals[3]);


  display.getTextBounds(numerals[4], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(30 - w_center / 2, 190);
  display.println(numerals[4]);

  display.getTextBounds(numerals[5], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(78 - w_center / 2, 190);
  display.println(numerals[5]);

  display.getTextBounds(numerals[6], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(122 - w_center / 2, 190);
  display.println(numerals[6]);

  display.getTextBounds(numerals[7], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(170 - w_center / 2, 190);
  display.println(numerals[7]);


  display.getTextBounds(numerals[8], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(182 - w_center / 2, 130);
  display.println(numerals[8]);

  display.getTextBounds(numerals[9], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(182 - w_center / 2, 83);
  display.println(numerals[9]);

  display.getTextBounds(numerals[10], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(182 - w_center / 2, 53);
  display.println(numerals[10]);

  display.getTextBounds(numerals[11], 100, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(182 - w_center / 2, 28);
  display.println(numerals[11]);

 // hour hand black outline
  display.fillTriangle(
    100 + 50 * cos(( hourAngle ) * DEG2RAD),
    10 + 80 * sin(( hourAngle ) * DEG2RAD),
    100 + 6 * cos(( hourAngle + 90 + 0 ) * DEG2RAD),
    10 + 6 * sin(( hourAngle + 90 + 0 ) * DEG2RAD),
    100 + 6 * cos(( hourAngle - 90 + 0 ) * DEG2RAD),
    10 + 6 * sin(( hourAngle - 90 + 0 ) * DEG2RAD),
    detailColor
    );

  // hour hand white outline
  display.fillTriangle(
    100 + 40 * cos(( hourAngle ) * DEG2RAD),
    10 + 64 * sin(( hourAngle ) * DEG2RAD),
    100 + 3 * cos(( hourAngle + 90 + 0 ) * DEG2RAD),
    10 + 3 * sin(( hourAngle + 90 + 0 ) * DEG2RAD),
    100 + 3 * cos(( hourAngle - 90 + 0 ) * DEG2RAD),
    10 + 3 * sin(( hourAngle - 90 + 0 ) * DEG2RAD),
    fillColor
    );
  }


void WatchyRomantime::drawWatchFaceModeModern(){
  int16_t  x_center, y_center;
  uint16_t w_center, h_center;


  display.fillScreen(fillColor);

  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(detailColor);

  char h[8];
  char m[8];
  char time_buffer[16];

  integerToRoman(currentTime.Hour == 0 ? 24 : currentTime.Hour, h);
  integerToRoman(currentTime.Minute == 0 ? 60 : currentTime.Minute, m);

  sprintf(time_buffer, "%s:%s\0", h, m);


  display.getTextBounds(time_buffer, 0, 100, &x_center, &y_center, &w_center, &h_center);
  display.setCursor(100 - w_center / 2, 100 - h_center / 2);
  display.println(time_buffer);
  }




void WatchyRomantime::drawWatchFaceDecider(){
  if(minutesBeforeSunset > minutesDaytime) {
    hourAngle =  180.0 * (minutesBeforeSunset - minutesDaytime) / minutesNighttime;
    detailColor = GxEPD_WHITE;
    switch(showState) {
      case 1:
        drawWatchFaceModeNight();
        break;
      case 2:
        drawWatchFaceModeModern();
        break;
      default:
        drawWatchFaceModeMoon();
      }
    }
  else if(minutesBeforeSunset > 0 ) {
    hourAngle = 180.0 * minutesBeforeSunset / minutesDaytime;
    switch(showState) {
      case 1:
        drawWatchFaceModeNight();
        break;
      case 2:
        drawWatchFaceModeModern();
        break;
      default:
        drawWatchFaceModeNight();
      }
    }
  else {
    hourAngle = 180 + 180.0 * minutesBeforeSunset / minutesNighttime;
    fillColor = GxEPD_BLACK;
    detailColor = GxEPD_WHITE;
    switch(showState) {
      case 1:
        drawWatchFaceModeNight();
        break;
      case 2:
        drawWatchFaceModeModern();
        break;
      default:
        drawWatchFaceModeMoon();
      }
    }
  }




void WatchyRomantime::integerToRoman(int num, char *result) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int pos = 0; // Position in the result array
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            for (int j = 0; symbols[i][j] != '\0'; j++, pos++) {
                result[pos] = symbols[i][j];
            }
            num -= values[i];
        }
    }
    result[pos] = '\0'; // Null-terminate the string
}




/*
 * If Up or down are pressed, change the mode
 */
void WatchyRomantime::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    if (wakeupBit & UP_BTN_MASK) {
      showState--;
      if(showState == -1) showState = 2;
      RTC.read(currentTime);
      showWatchFace(true);
      }

    if (wakeupBit & DOWN_BTN_MASK) {
      showState++;
      if(showState == 3) showState = 0;
      RTC.read(currentTime);
      showWatchFace(true);
      }

    if (wakeupBit & MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
      }
    }
  else {
    Watchy::handleButtonPress();
    }
  return;
  }
