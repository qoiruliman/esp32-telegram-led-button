# ESP32 Telegram LED Button

Proyek **IoT menggunakan ESP32 dan Telegram Bot** untuk mengontrol 3 buah LED. Kontrol dapat dilakukan baik melalui **command** maupun **inline button** di Telegram, tanpa perlu mengetik perintah manual.

---

## 🔧 Fitur Utama

- 🔘 Kontrol LED via Telegram **button inline**
- 💬 Mendukung perintah manual:  
  `led1`, `led2`, `led3`, `all_on`, `all_off`, `running`
- 🚦 Fitur **Running LED** (LED menyala bergantian)
- ✅ Bisa menyalakan/mematikan LED satu per satu atau sekaligus
- 📱 Tidak perlu ngetik perintah — cukup tekan tombol

---

## 💡 Daftar Perintah Telegram

| Perintah      | Fungsi                      |
|---------------|-----------------------------|
| `led1`        | Toggle LED1                 |
| `led2`        | Toggle LED2                 |
| `led3`        | Toggle LED3                 |
| `all_on`      | Nyalakan semua LED          |
| `all_off`     | Matikan semua LED           |
| `running`     | Jalankan LED secara bergantian |

Atau cukup tekan tombol yang muncul di Telegram. Bot akan menampilkan tombol-tombol ini secara otomatis setiap kali kamu mengaksesnya.

---

## 📲 Syarat Sebelum Memulai

1. Buat bot Telegram di [@BotFather](https://t.me/BotFather)
2. Dapatkan:
   - **Bot Token**
   - **Chat ID** kamu
3. Ubah variabel berikut di kode:
   ```cpp
   #define BOT_TOKEN "isi_token_anda"
   #define CHAT_ID "isi_chat_id_anda"


🛠️ Kebutuhan Hardware
- ESP32
- 3x LED (atau gunakan internal LED jika board mendukung)
- Kabel jumper
- Koneksi WiFi

📦 Library yang Digunakan
- WiFi.h
- WiFiClientSecure
- UniversalTelegramBot

🔗 Tautan Terkait
📢 Channel WhatsApp (info & update):
https://whatsapp.com/channel/0029Vb5e33sJuyABUxO12z0u
