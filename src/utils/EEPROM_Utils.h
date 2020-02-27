#pragma once

#include "Enums.h"

namespace EEPROM_Utils {

  void initialiseEEPROM();
  void clearEEPROM();

  void saveScore(GameMode gameMode, uint16_t score);
  uint16_t readSaveScore(GameMode gameMode);

};

