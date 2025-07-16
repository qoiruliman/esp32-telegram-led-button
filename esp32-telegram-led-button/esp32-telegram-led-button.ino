// iot telegram
// command led1 led2 led3 all_on all_off running
// ada fitur button
// bisa on off in led 1 1 / sekaligus
// ada running led 
// bisa pake button
// ada my commad 
// https://whatsapp.com/channel/0029Vb5e33sJuyABUxO12z0u

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// kalau pake wokwi gak usah di ubah ssid sama pw nya tapi kalau pake wifi rumah ubah lah
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ini buat token sama chat id
#define BOT_TOKEN "ini token bot tele "
#define CHAT_ID "ini chat id tele mu masa harus di kasih tau"

// ini pin led nya kalau mau kurai atau tambha bebas kode udah menyesuaikan sendiri
const int LED_PINS[] = {18, 19, 21, 22};
const int LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
bool ledStatus[LED_COUNT] = {false}; 

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long lastCheck = 0;

void setupLEDs() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void updateLEDs() {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], ledStatus[i] ? HIGH : LOW);
  }
}

void toggleLED(int index) {
  if (index >= 0 && index < LED_COUNT) {
    ledStatus[index] = !ledStatus[index];
    updateLEDs();
  }
}

void setAllLEDs(bool state) {
  for (int i = 0; i < LED_COUNT; i++) {
    ledStatus[i] = state;
  }
  updateLEDs();
}

void runningLED() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      for (int k = 0; k < LED_COUNT; k++) {
        digitalWrite(LED_PINS[k], LOW);
      }
      digitalWrite(LED_PINS[j], HIGH);
      delay(300);
    }
  }
  setAllLEDs(false);
}

String buildKeyboard() {
  String keyboard = "[[";

  for (int i = 0; i < LED_COUNT; i++) {
    if (i > 0) keyboard += ",";
    keyboard += "{\"text\":\"LED" + String(i + 1);
    keyboard += (ledStatus[i] ? " OFF" : " ON");
    keyboard += "\",\"callback_data\":\"LED" + String(i + 1) + "\"}";
  }

  keyboard += "],[{\"text\":\"ALL ON\",\"callback_data\":\"ALL_ON\"},";
  keyboard += "{\"text\":\"ALL OFF\",\"callback_data\":\"ALL_OFF\"},";
  keyboard += "{\"text\":\"RUNNING\",\"callback_data\":\"RUNNING\"}]]";

  return keyboard;
}

void sendMessageWithButton(String chat_id, String text, int message_id) {
  String keyboard = buildKeyboard();
  bot.sendMessageWithInlineKeyboard(chat_id, text, "Markdown", keyboard, message_id);
}

void handleCallbackQuery(String callbackData, String chat_id, int message_id) {
  if (callbackData.startsWith("LED")) {
    int ledIndex = callbackData.substring(3).toInt() - 1;
    toggleLED(ledIndex);
  } else if (callbackData == "ALL_ON") {
    setAllLEDs(true);
  } else if (callbackData == "ALL_OFF") {
    setAllLEDs(false);
  } else if (callbackData == "RUNNING") {
    bot.sendMessage(chat_id, "Running LED dimulai...");
    runningLED();
  }

  sendMessageWithButton(chat_id, "Silakan kontrol LED di bawah ini:", message_id);
}

void handleCommand(String text, String chat_id) {
  if (text == "/status") {
    String statusMsg = "Status LED:\n";
    for (int i = 0; i < LED_COUNT; i++) {
      statusMsg += "LED " + String(i + 1) + ": ";
      statusMsg += (ledStatus[i] ? "ON" : "OFF");
      statusMsg += "\n";
    }
    bot.sendMessage(chat_id, statusMsg);
  } 
  else if (text == "/button") {
    String keyboard = buildKeyboard();
    bot.sendMessageWithInlineKeyboard(chat_id, "Kontrol LED:", "Markdown", keyboard);
  } 
  else if (text.startsWith("/led")) {
  int ledIndex = text.substring(4).toInt() - 1;
  
  if (ledIndex >= 0 && ledIndex < LED_COUNT) {
    String msg = "LED " + String(ledIndex + 1) + " led ";
    msg += (ledStatus[ledIndex] ? "di matikan" : "di hidupkan");
    bot.sendMessage(chat_id, msg, "Markdown");
    toggleLED(ledIndex);
  }
  }
}

// untuk buat MyCommands kalau pas di tele ngetik slash (/) muncul perintah  
// atau ada garis tiga tulisan menu
// kalau gak mau komen aja jangan lupa komen yg di void setup

void bot_setup() {
  String commands = "[";
  commands += "{\"command\":\"status\", \"description\":\"Lihat status LED\"},";
  commands += "{\"command\":\"button\", \"description\":\"Tampilkan tombol kontrol\"},";
  commands += "{\"command\":\"led\",    \"description\":\"Loop semua LED\"},";

  for (int i = 0; i < LED_COUNT; i++) {
    commands += "{\"command\":\"led" + String(i + 1) + "\", ";
    commands += "\"description\":\"Toggle LED " + String(i + 1) + "\"}";
    if (i < LED_COUNT - 1) commands += ",";
  }
  commands += "]";
  bot.setMyCommands(commands);
}


// untuk hapus MyCommands kalau pas di tele ngetik slash (/) muncul perintah  
// atau ada garis tiga tulisan menu
// kalau udah terlanjur bikin dan mau hilain buka komen dibawah


// void bot_setup() {
//   const String emptyCommands = "[]"; // kosongkan daftar command
//   bot.setMyCommands(emptyCommands);
// }


void setup() {
  Serial.begin(115200);
  setupLEDs();

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi!");

  client.setInsecure();

// kalau yang di atas di komen atau hapus ini juga jangan lupa
  bot_setup(); 
}
void loop() {
  if (millis() - lastCheck > 1000) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    for (int i = 0; i < numNewMessages; i++) {
      if (bot.messages[i].type == "callback_query") {
        String callbackData = bot.messages[i].text;
        String chat_id = bot.messages[i].chat_id;
        int message_id = bot.messages[i].message_id;
        handleCallbackQuery(callbackData, chat_id, message_id);
      } else {
        String text = bot.messages[i].text;
        String chat_id = bot.messages[i].chat_id;
        handleCommand(text, chat_id);
      }
    }

    if (numNewMessages > 0) {
      bot.last_message_received = bot.messages[numNewMessages - 1].update_id;
    }

    lastCheck = millis();
  }
}
