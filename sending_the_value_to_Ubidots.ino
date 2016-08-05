/*
  Ubidots WiFi client

  This sketch reads an analog input and sends this value to Ubidots

  Change the macro WIFI_AP, WIFI_PASSWORD, WIFI_AUTH, URL, TOKEN and VARIABLE_ID accordingly.

  based on the Web Client example created 13 July 2010
  by dlf (Metodo2 srl)
  modified 31 May 2012
  by Tom Igoe
  modified 20 Aug 2014
  by MediaTek Inc.
  modified 2 Sep 2015
  by Ubidots, Inc.
*/

#include <LTask.h>//to include LTask.h header file.
#include <LWiFi.h>//to include LWifi.h header file.
#include <LWiFiClient.h>//to include LWifiClient.h header file.

#define WIFI_AP "Pallavi"//name of wifi network the board is connected to.
#define WIFI_PASSWORD "7032"//password of that wifi network if it is secured with WPA or WPA2.
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP, based on whether it is free or secured.

// Ubidots information

#define URL    "things.ubidots.com"       //the URL that values will be sent to.
#define TOKEN  "muNabx2IsIoAvktq0UnqFn8JXkPgjY"          // replace with your Ubidots token generated in your profile tab
#define ID "579111747625425c9979d4c0"                // create a variable in Ubidots and put its ID here (http://app.ubidots.com/ubi/datasources/)


void setup()//function that encloses instructions to be executed only once.
{
  LTask.begin();//function call to
  LWiFi.begin();//function call to begin the wifi configuration.
  Serial.begin(9600);//sets the baud rate to 9600 bits per second.

  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))//to connect to the wifi network using name and password, and to check if it connected.
  {
    delay(1000);//delay of 1 second
  }
}

// I plan to use this function in the future to reconnect to WiFi if the connection drops:
boolean wifi_status(LWifiStatus ws) {
  switch (ws) {
    case LWIFI_STATUS_DISABLED:// if the wifi network isn't available.
      return false;
      break;
    case LWIFI_STATUS_DISCONNECTED:// if the board is disconnected from the wifi network.
      return false;
      break;
    case LWIFI_STATUS_CONNECTED:// if the board is connected to the wifi network.
      return true;
      break;
  }
  return false;
}


void loop()//instructions given here will repeat continuously in a loop.
{
  Serial.println("Connecting to Ubidots...");//prints on the serial monitor.
  LWiFiClient c;//define a variable of type LWifiClient, named c.
  while (!c.connect(URL, 80))//while c is not connected to ubidots..try to connect to Ubidots.
  {
    Serial.println("Retrying to connect...");
    delay(100);
  }

  Serial.println("Connected!");

  while (1) //infinite loop.
  {
    LWifiStatus ws = LWiFi.status();// variable that stores the status of the wifi connection.
    boolean status = wifi_status(ws);//boolean variable so it stores the value TRUE or FALSE depending on the wifi status.
    if (!status) // if the board is disconnected from the wifi.
    {
      Serial.println("Connecting to AP");
      while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))//trying to reconnect to the wifi.
      {
        delay(500);
      }
    }
    String payload = "{\"value\":" + String(1) + "}"; //string that is sent to the cloud(Ubidots) which consists of the value to be sent along with other parts to form the pyload.
    String le = String(payload.length());//to find the length of the payload and store it a variable le.

    if (!c.connected()) {
      while (!c.connect(URL, 80)) {
        delay(100);
      }
      Serial.println("Client reconnected!");
    }

    // Build HTTP POST request
    c.print(F("POST /api/v1.6/variables/"));//building the first part of the request .
    c.print(ID);the variable id is used to continue the request.
    c.println(F("/values HTTP/1.1"));//cotinuation of the requrst, version and security type are mentioned here.
    c.println(F("User-Agent: LinKit One/1.0"));//The type of device that is connected to the cloud.
    c.print(F("X-Auth-Token: "));//The unique token that is given too every user.
    c.println(TOKEN);
    c.println(F("Connection: close"));//printing the type of connection to Ubitdots.
    c.println(F("Content-Type: application/json"));//format in which the data is being sent to the cloud.
    c.print(F("Content-Length: "));//Length of the content.
    c.println(le);
    c.print(F("Host: "));//the host URL to which data is sent.
    c.println(URL);
    c.println();
    c.println(payload);//Value to be sent to the cloud.
    c.println();

    int v;declaration of int v.
    while (c.available()) {
      v = c.read();//The value that is sent to ubidots.
      Serial.println("v:");
      Serial.print(v);
      if (v < 0) {
        Serial.println("No response.");
        break;
      }
    }
    delay(1000);//delay of one second.
  }
}

