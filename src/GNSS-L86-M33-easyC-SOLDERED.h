/**
 **************************************************
 *
 * @file        GNSS-L86-M33-easyC-SOLDERED.h
 * @brief       Header file for GPS easyC module specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     robert @ soldered.com
 ***************************************************/

#ifndef __GNSS_EASYC_SOLDERED__
#define __GNSS_EASYC_SOLDERED__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

// Enum used for selecting which data to retrieve
enum GNSS_DATA_SELECT
{
    LATITUDE = 0,
    LONGITUDE = 1,
    YEAR = 2,
    MONTH_DAY = 3,
    HOUR_MINUTE = 4,
    SECOND_CENTISECOND = 5,
    SPEED = 6,
    ALTITUDE = 7,
    IS_AVAILABLE = 8,
    ALWAYS_LOCATE = 9,
    MULTI_TONE_AIC = 10,
};

class GNSS_easyC : public EasyC
{
  public:
    GNSS_easyC();
    float getLatitude();
    float getLongitude();
    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSeconds();
    float getSpeed();
    float getAltitude();
    bool GNSSAvailable();
    void setMultiToneAIC(bool _b);
    void setAlwaysLocate(bool _b);


  protected:
    void initializeNative();
};

#endif
