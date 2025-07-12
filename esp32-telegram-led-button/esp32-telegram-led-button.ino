// iot telegram
// command led1 led2 led3 all_on all_off running
// ada fitur button
// bisa on off in led 1 1 / sekaligus
// ada running led 
// bisa pake button gak harus kirim all_on / yg lain
// https://whatsapp.com/channel/0029Vb5e33sJuyABUxO12z0u

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// ganti sesuai wifi mu kecuali pake wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ganti sesuai bot token mu jangan bilang belum punya 
#define BOT_TOKEN "ini bot token tele "
#define CHAT_ID "ini chat id"

// kalau mau ganti pin ganti aja
const int LED1 = 18;
const int LED2 = 19;
const int LED3 = 21;

bool led1Status = false;
bool led2Status = false;
bool led3Status = false;


WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

void setupLEDs() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, led1Status ? HIGH : LOW);
  digitalWrite(LED2, led2Status ? HIGH : LOW);
  digitalWrite(LED3, led3Status ? HIGH : LOW);
}

void updateLEDs() {
  digitalWrite(LED1, led1Status ? HIGH : LOW);
  digitalWrite(LED2, led2Status ? HIGH : LOW);
  digitalWrite(LED3, led3Status ? HIGH : LOW);
}

String button() {
  String keyboard = "[";
  keyboard += "[{\"text\":\"LED1 " + String(led1Status ? "OFF" : "ON") + "\",\"callback_data\":\"LED1\"},";
  keyboard += "{\"text\":\"LED2 " + String(led2Status ? "OFF" : "ON") + "\",\"callback_data\":\"LED2\"},";
  keyboard += "{\"text\":\"LED3 " + String(led3Status ? "OFF" : "ON") + "\",\"callback_data\":\"LED3\"}],";
  keyboard += "[{\"text\":\"ALL ON\",\"callback_data\":\"ALL_ON\"},";
  keyboard += "{\"text\":\"ALL OFF\",\"callback_data\":\"ALL_OFF\"},";
  keyboard += "{\"text\":\"RUNNING LED\",\"callback_data\":\"RUNNING\"}]";
  keyboard += "]";
  return keyboard;
}

void sendMessageWithButton(String chat_id, String text) {
  String keyboardJson = button();
  bot.sendMessageWithInlineKeyboard(chat_id, text, "Markdown", keyboardJson);
}

void toggleLED(int ledNum) {
  switch (ledNum) {
    case 1: led1Status = !led1Status; break;
    case 2: led2Status = !led2Status; break;
    case 3: led3Status = !led3Status; break;
  }
  updateLEDs();
}

void setAllLEDs(bool state) {
  led1Status = state;
  led2Status = state;
  led3Status = state;
  updateLEDs();
}

void runningLED() {
  const int leds[] = {LED1, LED2, LED3};
  const int delayMs = 300;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(leds[j], HIGH);
      delay(delayMs);
    }
  }

  led1Status = true;
  led2Status = false;
  led3Status = false;
  updateLEDs();
}

void handleCallbackQuery(String callbackData, String chat_id) {
  if (callbackData == "LED1") {
    toggleLED(1);
  } else if (callbackData == "LED2") {
    toggleLED(2);
  } else if (callbackData == "LED3") {
    toggleLED(3);
  } else if (callbackData == "ALL_ON") {
    setAllLEDs(true);
  } else if (callbackData == "ALL_OFF") {
    setAllLEDs(false);
  } else if (callbackData == "RUNNING") {
    bot.sendMessage(chat_id, "Running dimulai");
    runningLED();
  }

  sendMessageWithButton(chat_id, "Status LED terbaru:");
}

void setup() {
  Serial.begin(115200);

  setupLEDs();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  client.setInsecure();
  sendMessageWithButton(CHAT_ID, "Kontrol LED siap digunakan!");
}

void loop() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (bot.messages[i].type == "callback_query") {
      String callbackData = bot.messages[i].text;
      String fromName = bot.messages[i].from_name;

      Serial.println("Pesan dari " + fromName + ":" + callbackData);
      handleCallbackQuery(callbackData, chat_id);
    }
  }

  if (numNewMessages > 0) {
    bot.last_message_received = bot.messages[numNewMessages - 1].update_id;
  }

  delay(50);
}
