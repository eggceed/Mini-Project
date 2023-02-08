#include <Arduino.h>
#include <HTTPClient.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include "credentials.h"

#define GET_INTERVAL 5000

bool powered[3] = {0, 0, 0};
int LED_PINS[3] = {26, 25, 33};
int SW_PINS[3] = {T0, T1, T2};

const String API_URL = "http://ecourse.cpe.ku.ac.th/exceed03/light";
HTTPClient httpClient;
DynamicJsonDocument data(1024);

/*
 * Task Handles
 */
TaskHandle_t taskGetAPI = nullptr;
TaskHandle_t taskPutAPI = nullptr; 

/*
 * Prototypes
 */
void connect_WiFi();
void update_lights(void*);
void set_light_state(int roomId, bool powered, int intensity);
void toggle_light(void*);

void setup() {
  for (int i = 1; i <= 3; i++) {
    pinMode(LED_PINS[i-1], OUTPUT);
    ledcSetup(i, 5000, 8);
    ledcAttachPin(LED_PINS[i-1], i);
  }
  connect_WiFi();
  xTaskCreatePinnedToCore(
      update_lights,
      "Lights Sync",
      10240,
      NULL,
      0,
      &taskGetAPI,
      1
  );
}

void loop() {
  // Condition to toggle with pin.
  if (0) {
    xTaskCreatePinnedToCore(
        toggle_light,
        "Toggle Light",
        10240,
        (void*) 1, // Substitute this with pin
        2,
        &taskPutAPI,
        1
    );
  }
}

void update_lights(void* param) {
  while(1) {
    /*
     * GET and update to the light parameters
     */
    httpClient.begin(API_URL);
    int responseCode = httpClient.GET();
    if (responseCode == 200) {
      Serial.println("GET lights statuses from API.");
      String payload = httpClient.getString();
      deserializeJson(data, payload);
      
      JsonArray arr = data["rooms"].as<JsonArray>();
      for (JsonVariant room : arr) {
        set_light_state(room["id"].as<int>(), room["powered"].as<bool>(), room["intensity"].as<int>());
      }

    } else {
      Serial.print("HTTP Error: ");
      Serial.println(responseCode);
    }
    vTaskDelay(GET_INTERVAL / portTICK_PERIOD_MS);
  }
}

void set_light_state(int roomId, bool powered, int intensity) {
  ledcWrite(roomId,
    (powered ? map(intensity, 0, 100, 0, 255) : 0)
  );
  ::powered[roomId - 1] = powered;
}

void toggle_light(void* param) {
  int channel = (int)(size_t) param;
  set_light_state(channel, !powered[channel - 1], ledcRead(channel));
}
