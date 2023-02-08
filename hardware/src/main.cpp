#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include "credentials.h"

#define GET_INTERVAL 5000

int check = 0;
int check_1 = 0;
int check_2 = 0;

void click();
void click_1();
void click_2();

int touch_red;
int touch_yellow;
int touch_green;

bool powered[3] = {0, 0, 0};
int LED_PINS[3] = {26, 25, 33};
int SW_PINS[3] = {T5, T1, T2};

const String API_URL = "https://ecourse.cpe.ku.ac.th/exceed03/light/";
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

void click(){
  if(check){
    return;
  }
    xTaskCreatePinnedToCore(
        toggle_light,
        "Toggle Light",
        10240,
        (void*) 1, // Substitute this with pin
        2,
        &taskPutAPI,
        1
    );
   check =1;
}

void click_1(){
  if(check_1){
    return;
  }
    xTaskCreatePinnedToCore(
        toggle_light,
        "Toggle Light",
        10240,
        (void*) 2, // Substitute this with pin
        2,
        &taskPutAPI,
        1
    );
   check_1 =1;
}

void click_2(){
  if(check_2){
    return;
  }
    xTaskCreatePinnedToCore(
        toggle_light,
        "Toggle Light",
        10240,
        (void*) 3, // Substitute this with pin
        2,
        &taskPutAPI,
        1
    );
   check_2 =1;
}

void setup() {
  Serial.begin(115200);
  pinMode(27, INPUT);
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
      1,
      &taskGetAPI,
      1
  );
}

void loop() {
  touch_red = touchRead(SW_PINS[0]);
  touch_yellow = touchRead(SW_PINS[1]);
  //Serial.println(touchRead(YELLOW_BUTTON));
  touch_green = touchRead(SW_PINS[2]);
  if(touch_red < 50)
  {
    click();
  }
  else{
    check =0;
  }
  if(touch_yellow < 47)
  {
    click_1();
  }
  else{
    check_1 = 0;
  }
  if(touch_green < 38)
  {
    click_2();
  }
  else{
    check_2 = 0;
  }
  delay(10);
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
      
      JsonArray arr = data.as<JsonArray>();
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
  Serial.print("SETTING LIGHT "); Serial.print(roomId); Serial.print(" "); Serial.println(powered ? "ON" : "OFF");
  ledcWrite(roomId,
    (powered ? map(intensity, 0, 100, 0, 255) : 0)
  );
  ::powered[roomId - 1] = powered;
}

void toggle_light(void* param) {
  vTaskSuspend(taskGetAPI);

  int channel = (int)(size_t) param;
  set_light_state(channel, !powered[channel - 1], ledcRead(channel));

  DynamicJsonDocument doc(512);
  String json;
  doc["type"] = "device";
  doc["id"] = channel;
  doc["powered"] = powered[channel - 1];
  serializeJson(doc, json);

  httpClient.begin(API_URL);
  httpClient.addHeader("Content-Type", "application/json");
  int responseCode = httpClient.PUT(json);

  if (responseCode == 200) {
    Serial.println("Successfully update status to API.");
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(responseCode);
  }

  vTaskResume(taskGetAPI);
  vTaskDelete(nullptr);
}

void connect_WiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}
