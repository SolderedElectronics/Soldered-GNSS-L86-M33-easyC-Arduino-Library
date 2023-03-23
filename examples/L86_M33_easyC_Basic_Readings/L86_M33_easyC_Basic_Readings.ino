/**
 **************************************************
 *
 * @file        L86_M33_easyC_Basic_Readings.ino
 * @brief       This code will try to read GNSS Latitude, Longitude, Time, Date, Speed and Altitude and display it on
 *the Serial monitor at 115200 baud. To successfuly run the sketch, connect a GPS antenna to the GNSS module, connect
 *GNSS module to one of the Dasduino boards via easyC, upload the code and open the serial monitor at 115200 bauds to
 *see the data.
 *
 *              For best results, GPS antenna must be outside!
 *
 *              Soldered L86-M33 GNSS easyC Breakout: www.solde.red/333213
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 *
 * @authors     robert@soldered.com
 ***************************************************/

#include "GNSS-L86-M33-easyC-SOLDERED.h"

// Create the GNSS_easyC object
GNSS_easyC gnss;

// Note that the first couple of readings won't be correct as the L86 takes a couple seconds to set up.

void setup()
{
    // Enable Serial output
    Serial.begin(115200);

    // Initialize GNSS_easyC
    gnss.begin();
}

void loop()
{
    // Get all available data
    // Note the data types
    float lat = gnss.getLatitude();
    float lng = gnss.getLongitude();
    uint16_t year = gnss.getYear();
    uint8_t month = gnss.getMonth();
    uint8_t day = gnss.getDay();
    uint8_t hour = gnss.getHour();
    uint8_t minute = gnss.getMinute();
    uint8_t seconds = gnss.getSeconds();
    float speed = gnss.getSpeed();
    float altitude = gnss.getAltitude();

    // Print all the data
    Serial.print("Latitude: ");
    Serial.println(lat, 6);
    Serial.print("Longitude: ");
    Serial.println(lng, 6);
    Serial.print("Year: ");
    Serial.println(year);
    Serial.print("Month: ");
    Serial.println(month);
    Serial.print("Day: ");
    Serial.println(day);
    Serial.print("Hour: ");
    Serial.println(hour);
    Serial.print("Minute: ");
    Serial.println(minute);
    Serial.print("Seconds: ");
    Serial.println(seconds);
    Serial.print("Speed: ");
    Serial.print(speed, 6);
    Serial.println(" km/h");
    Serial.print("Altitude: ");
    Serial.print(altitude, 6);
    Serial.println(" m");

    // Pprint a newline and wait a bit before the next output
    Serial.println(" ");
    delay(3000);
}