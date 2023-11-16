#ifndef SETTINGS_H
#define SETTINGS_H

//Weather Settings
//#define CITY_ID "5128581" //New York City https://openweathermap.org/current#cityid
#define LAT "42.280827" //Ann Arbor, https://www.latlong.net/
#define LON "-83.743034" 
#define OPENWEATHERMAP_APIKEY "1f7a03d64fe74951ab16660f20dc4351" //used my own API key :)
#define OPENWEATHERMAP_URL "http://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&lang={lang}&units={units}&appid={apiKey}" //open weather api
#define TEMP_UNIT "metric" //metric = Celsius , imperial = Fahrenheit
#define TEMP_LANG "en"
#define WEATHER_UPDATE_INTERVAL 30 //must be greater than 5, measured in minutes
//NTP Settings
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 3600 * -5 //New York is UTC -5 EST, -4 EDT, will be overwritten by weather data

watchySettings settings{
    .lat = LAT,
    .lon = LON,
//    .cityID = CITY_ID,
    .weatherAPIKey = OPENWEATHERMAP_APIKEY,
    .weatherURL = OPENWEATHERMAP_URL,
    .weatherUnit = TEMP_UNIT,
    .weatherLang = TEMP_LANG,
    .weatherUpdateInterval = WEATHER_UPDATE_INTERVAL,
    .ntpServer = NTP_SERVER,
    .gmtOffset = GMT_OFFSET_SEC,
    .vibrateOClock = false,
};


RTC_DATA_ATTR int mode = 0;

#endif
