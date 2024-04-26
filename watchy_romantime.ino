// Romantime for Watchy by Sudrien
// Copyright 2023 Sudrien _+watchy@sudrien.net
// Based on https://romanti.me/ by @wilbr@glitch.social
// Released under free MIT License : https://github.com/sudrien/watchy_wadokei/blob/main/LICENSE

#include "watchy_romantime.h"
#include "settings.h"

WatchyRomantime watchy(settings);

void setup(){
  watchy.init();
}

void loop(){}
