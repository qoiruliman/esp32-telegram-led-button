# 💡 IoT Telegram Bot - Kontrol LED via Telegram (ESP32)

Proyek ini memungkinkan kamu untuk mengontrol beberapa LED menggunakan **Telegram Bot** lewat **ESP32**. Terdapat fitur tombol inline, status LED, kontrol individual, kontrol massal, dan efek **running LED** langsung dari aplikasi Telegram.

---

## 🔧 Fitur

* ✅ Kontrol **ON/OFF LED secara individual** dengan tombol Telegram
* ✅ Kontrol **semua LED sekaligus** (ALL ON / ALL OFF)
* ✅ Efek **running LED**
* ✅ Mendukung perintah custom di Telegram (`/status`, `/button`, `/led`, dll)
* ✅ Tombol inline otomatis sesuai jumlah LED

---

## ⚙️ Hardware

* Board: ESP32
* LED: Jumlah bebas (kode menyesuaikan otomatis)
* Koneksi: WiFi

---

## 🧾 Instalasi

### 1. **Library yang dibutuhkan**

Install melalui Library Manager:

* `WiFi`
* `WiFiClientSecure`
* `UniversalTelegramBot`
  (oleh Brian Lough)

### 2. **Ubah Token dan Chat ID**

```cpp
#define BOT_TOKEN "TOKEN_BOT_TELEGRAM_KAMU"
#define CHAT_ID "CHAT_ID_KAMU"
```

### 3. **WiFi Configuration**

* Untuk **Wokwi**, tidak perlu ubah.
* Untuk jaringan rumah:

```cpp
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
```

---

## 🕹️ Command Telegram

| Perintah               | Fungsi                            |
| ---------------------- | --------------------------------- |
| `/status`              | Menampilkan status semua LED      |
| `/button`              | Menampilkan tombol kontrol LED    |
| `/led1` - `/led4`      | Menyalakan/mematikan LED tertentu |
| Tekan tombol `ALL ON`  | Menyalakan semua LED              |
| Tekan tombol `ALL OFF` | Mematikan semua LED               |
| Tekan tombol `RUNNING` | Menjalankan animasi LED berjalan  |

---

## 📱 Contoh Tampilan Bot

Telegram akan menampilkan tombol seperti:

```
[ LED1 ON ] [ LED2 ON ] ...
[ ALL ON ] [ ALL OFF ] [ RUNNING ]
```

---

## 🛠️ Customisasi LED

Jumlah LED bisa ditambah atau dikurangi:

```cpp
const int LED_PINS[] = {18, 19, 21, 22};  // Ubah sesuai kebutuhan
```

---

## 📌 Catatan

* Untuk membuat tombol perintah muncul otomatis saat mengetik `/`, pastikan bagian `bot_setup()` tidak dikomentari.
* Untuk menghapus semua command dari menu Telegram, gunakan versi kosong `bot_setup()`.

---

## 🔗 Link Terkait

📢 Channel WhatsApp (Info & Update):
[https://whatsapp.com/channel/0029Vb5e33sJuyABUxO12z0u](https://whatsapp.com/channel/0029Vb5e33sJuyABUxO12z0u)

---

## 🤝 Kontribusi

Feel free untuk fork, buat pull request, atau laporkan issue jika ada yang ingin ditambahkan!

---

## 💡 Lisensi

Proyek ini open-source dan bisa digunakan bebas untuk pembelajaran dan eksperimen pribadi.

---

Kalau kamu mau saya bantu generate file `README.md` langsung atau masukkan ke proyek GitHub, tinggal bilang ya!
