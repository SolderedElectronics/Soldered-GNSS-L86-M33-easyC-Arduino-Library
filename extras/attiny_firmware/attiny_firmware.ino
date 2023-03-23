/**
 **************************************************

   @file        attiny_firmware.ino
   @brief       Firmware for GNSS Breakout with easyC

   @note        The user must have the GNSS-L86-M33-SOLDERED library installed in order for this sketch to compile.
                You can find it at https://github.com/SolderedElectronics/Soldered-GNSS-L86-M33-Arduino-Library


   @authors     Robert @ soldered.com
 ***************************************************/

#include "GNSS-L86-M33-SOLDERED.h"
#include "easyC.h"
#include <Wire.h>

#define GNSS_RX PA1
#define GNSS_TX PA2

// Buffers to store data read from the GPS module
double latitude = 0.0;
double longitude = 0.0;
uint16_t year = 0;
uint8_t month = 0;
uint8_t day = 0;
uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
uint8_t centisecond = 0;
double speedKMPH = 0;
double altitudeMtrs = 0;

// Create the GPS object
GNSS gps(GNSS_TX, GNSS_RX);

int addr = DEFAULT_ADDRESS;

// Selector for which data we require from the main device
enum DATA_SELECT
{
    LATITUDE = 0,
    LONGITUDE = 1,
    YEAR = 2,
    MONTH_DAY = 3,
    HOUR_MINUTE = 4,
    SECOND_CENTISECOND = 5,
    SPEED = 6,
    ALTITUDE = 7,
} currentSelect;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    // Set default value of the selector
    // Just in case
    currentSelect = LATITUDE;

    // Begin the GPS
    Serial.begin(9600);
    gps.begin();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
    // Periodically read from serial, decode gps data and store in the buffers
    while (gps.gnssSerial.available() > 0)
    {
        if (gps.encode(gps.gnssSerial.read()))
        {
            if (gps.location.isValid())
            {
                latitude = gps.location.lat();
                longitude = gps.location.lng();
            }
            if (gps.date.isValid())
            {
                month = gps.date.month();
                day = gps.date.day();
                year = gps.date.year();
            }
            if (gps.time.isValid())
            {
                hour = gps.time.hour();
                minute = gps.time.minute();
                second = gps.time.second();
                centisecond = gps.time.centisecond();
            }
            if (gps.speed.isValid())
            {
                speedKMPH = gps.speed.kmph();
            }
            if (gps.altitude.isValid())
            {
                altitudeMtrs = gps.altitude.meters();
            }
        }
    }
}

// On recieve, set the correct selector to the one of interest
void receiveEvent(int howMany)
{
    currentSelect = Wire.read();
}

// Send different data depending on the last request
// The data has to be cast accordingly in order to be read on the main device
void requestEvent()
{
    if (currentSelect == LATITUDE)
    {
        char buf[16];
        dtostrf(latitude, 10, 6, buf);
        Wire.write(buf, 16);
    }
    else if (currentSelect == LONGITUDE)
    {
        char buf[16];
        dtostrf(longitude, 10, 6, buf);
        Wire.write(buf, 16);
    }
    else if (currentSelect == YEAR)
    {
        uint16_t buf[1] = {year};
        Wire.write((uint8_t *)buf, 2);
    }
    else if (currentSelect == MONTH_DAY)
    {
        uint8_t buf[2] = {month, day};
        Wire.write(buf, 2);
    }
    else if (currentSelect == HOUR_MINUTE)
    {
        uint8_t buf[2] = {hour, minute};
        Wire.write(buf, 2);
    }
    else if (currentSelect == SECOND_CENTISECOND)
    {
        uint8_t buf[2] = {second, centisecond};
        Wire.write(buf, 2);
    }
    else if (currentSelect == SPEED)
    {
        char buf[16];
        dtostrf(speedKMPH, 10, 6, buf);
        Wire.write(buf, 16);
    }
    else if (currentSelect == ALTITUDE)
    {
        char buf[16];
        dtostrf(altitudeMtrs, 10, 6, buf);
        Wire.write(buf, 16);
    }
    else
    {
        // Undefined state
        char buf[2] = {'X', 'X'};
        Wire.write(buf, 2);
    }
}
