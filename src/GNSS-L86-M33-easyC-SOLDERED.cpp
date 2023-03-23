/**
 **************************************************
 *
 * @file        GNSS-L86-M33-easyC-SOLDERED.cpp
 * @brief       Functions to read data from GNSS L86 M33 easyC board
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors    robert@ soldered.com
 ***************************************************/


#include "GNSS-L86-M33-easyC-SOLDERED.h"

/**
 * @brief                   GNSS_easyC specific native constructor.
 *
 */
GNSS_easyC::GNSS_easyC()
{
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void GNSS_easyC::initializeNative()
{
}

/**
 * @brief                   Get the last measured latitude by the GPS module
 *
 * @returns                 float value of the latitude
 */
float GNSS_easyC::getLatitude()
{
    char buf[16];
    sendAddress(LATITUDE);
    readData(buf, 16);
    float latitude = atof(buf);
    return latitude;
}

/**
 * @brief                   Get the last measured longitude by the GPS module
 *
 * @returns                 float value of the longitude
 */
float GNSS_easyC::getLongitude()
{
    char buf[16];
    sendAddress(LONGITUDE);
    readData(buf, 16);
    float longitude = atof(buf);
    return longitude;
}

/**
 * @brief                   Get the last measured year by the GPS module
 *
 * @returns                 uint16_t value of the year
 */
uint16_t GNSS_easyC::getYear()
{
    char buf[2];
    uint16_t year;
    sendAddress(YEAR);
    readData(buf, 2);
    memcpy(&year, buf, 2);
    return year;
}

/**
 * @brief                   Get the last measured month by the GPS module
 *
 * @returns                 uint8_t value of the month
 */
uint8_t GNSS_easyC::getMonth()
{
    char buf[2];
    uint8_t month;
    sendAddress(MONTH_DAY);
    readData(buf, 2);
    memcpy(&month, buf, 1);
    return month;
}

/**
 * @brief                   Get the last measured day by the GPS module
 *
 * @returns                 uint8_t value of the day
 */
uint8_t GNSS_easyC::getDay()
{
    char buf[2];
    uint8_t day;
    sendAddress(MONTH_DAY);
    readData(buf, 2);
    memcpy(&day, buf + 1, 1);
    return day;
}

/**
 * @brief                   Get the last measured hour by the GPS module
 *
 * @returns                 uint8_t value of the hour
 */
uint8_t GNSS_easyC::getHour()
{
    char buf[2];
    uint8_t hour;
    sendAddress(HOUR_MINUTE);
    readData(buf, 2);
    memcpy(&hour, buf, 1);
    return hour;
}

/**
 * @brief                   Get the last measured minute (in current hour) by the GPS module
 *
 * @returns                 uint8_t value of the minute
 */
uint8_t GNSS_easyC::getMinute()
{
    char buf[2];
    uint8_t minute;
    sendAddress(HOUR_MINUTE);
    readData(buf, 2);
    memcpy(&minute, buf + 1, 1);
    return minute;
}

/**
 * @brief                   Get the last measured seconds (in current minute) by the GPS module
 *
 * @returns                 float value of the seconds
 */
uint8_t GNSS_easyC::getSeconds()
{
    char buf[2];
    uint8_t seconds;
    sendAddress(SECOND_CENTISECOND);
    readData(buf, 2);
    memcpy(&seconds, buf, 1);
    return seconds;
}

/**
 * @brief                   Get the last measured speed by the GPS module
 *
 * @returns                 float value of the speed
 */
float GNSS_easyC::getSpeed()
{
    char buf[16];
    sendAddress(SPEED);
    readData(buf, 16);
    float speed = atof(buf);
    return speed;
}

/**
 * @brief                   Get the last measured altitude by the GPS module
 *
 * @returns                 float value of the altitude
 */
float GNSS_easyC::getAltitude()
{
    char buf[16];
    sendAddress(ALTITUDE);
    readData(buf, 16);
    float altitude = atof(buf);
    return altitude;
}