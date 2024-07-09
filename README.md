## Alat Yang Digunakan:
- ESP32
- DHT11 (Sensor Suhu)
- MQ2 (Sensor Asap)
- IR Infrared Flame Detector
- Buzzer
- Pompa Air
- LCD 12c
- Relay

## Gambaran Umum Sistem
<p align="justify">Sistem yang akan dibangun adalah sistem monitoring pendeteksi kebakaran dan mengirimkan notifikasi melalui telegram. Sistem dapat mendeteksi kondisi ruangan yang ada asap, api, dan suhu udara yang tinggi, jika salah satu sensor mendeteksi adanya kondisi tersebut maka, sistem akan mengirimkan notifikasi ke telegram. Jika sistem mendeteksi adanya api dalam ruangan, maka lampu Led, Buzzer, Pompa air akan menyala, diikuti dengan mengirimkan notifikasi ke telegram. Begitu pula jika sistem mendeteksi suhu ruangan yang tinggi maka kipas akan secara otomatis akan hidup.
Sensor suhu, asap, dan api berfungsi untuk mendeteksi kebakaran. Sensor suhu digunakan untuk mendeteksi perubahan suhu yang terjadi pada lingkungan sekitarnya, sementara sensor asap dan api digunakan untuk mendeteksi keberadaan asap dan api. ESP32 adalah sebuah mikrokontroler yang digunakan sebagai otak dari sistem dan berfungsi untuk menghubungkan semua komponen dan mengontrol kerja sistem secara keseluruhan. ESP32 akan menerima informasi dari sensor suhu, asap, dan api dan memberikan perintah untuk menghidupkan kipas jika terdeteksi suhu terlalu tinggi dan menghidupkan pompa air melalui relay ketika terdeteksi adanya kebakaran. Selain itu, ESP32 juga dapat mengirimkan notifikasi ke aplikasi Telegram untuk memberi tahu pengguna tentang adanya api, asap, dan suhu ruangan. Kipas digunakan jika terdeteksi suhu tinggi dan Pompa air digunakan untuk memompa air dari sumber air ke jaringan pipa. Relay adalah komponen yang berfungsi sebagai saklar listrik yang mengontrol pompa air. Relay akan menerima sinyal dari ESP32 dan memicu pompa air untuk mengalirkan air ke jaringan pipa saat terdeteksi kebakaran oleh sensor asap dan api. ESP32 akan memberikan perintah untuk menghidupkan kipas serta pompa air melalui relay dan memicu melepaskan air. Air yang dikeluarkan dari selang akan membantu memadamkan api dan mencegah penyebarannya.</p>

## Hasil Pengujian
Pada saat melakukan pengujian alat monitoring kebakaran dengan menguji setiap sensor yang digunakan untuk memonitoring keadaan ruangan, hasil yang didapatkan adalah semua sensor dapat bekerja dengan baik dan dapat mengirimkan notifikasi ke pengguna melalui Telegram. Adapun hasil dari pengujian sistem diantaranya:
1. Pengujian Sensor Suhu
Pada pengujian sensor suhu, dilakukan dengan cara melakukan peningkat suhu di sekitar sensor dengan membuat api. nilai suhu udara di sekitar sensor akan ditampilkan di layar LCD. jika terdeteksi suhu ruangan yang tinggi, sistem akan mengirimkan notifikasi ke pengguna bahwa saat ini suhu ruangan sedang tinggi. Dalam pengujian ini, pengukuran Suhu udara berhasil dilakukan dengan menggunakan sensor dht11 yang bekerja dengan cara mengukur suhu yang ada di sekitar.
2. Pengujian Sensor Asap
Pada pengujian sensor asap, dilakukan pengujian dengan cara membuat asap di sekitar sensor, saat terdeteksi asap, sistem akan mengirimkan notifikasi ke pengguna bahwa ada asap pada ruangan. Selanjutnya yaitu telegram akan memberikan opsi pilihan untuk pengguna untuk menyalakan pompa air atau tidak, jika iya maka pompa air akan menyala. Dalam pengujian ini, sensor asap MQ2 berhasil berjalan dengan baik dengan cara mendeteksi asap yang ada pada sekitar sensor.
3. Pengujian Sensor Api
Pada pengujian sensor api, dilakukan dengan cara membuat api di sekitar sensor, saat terdeteksi adanya api, sistem akan mengirimkan notifikasi ke pengguna bahwa ada api di ruangan. kemudian sistem akan menyalakan lampu peringatan yaitu lampu Led, menyalakan alarm yaitu buzzer, dan menyalakan water pump untuk memadamkan api. IR Infrared Flame Detector berhasil bekerja dengan baik dengan cara mendeteksi api yang ada di sekitar sensor.
4. Pompa Air
Pompa air akan menyala ketika pengguna memberikan perintah untuk menyalakan pompa air, kemudian pompa air juga akan menyala ketika ada api pada ruangan. dalam pengujian ini pompa air dapat bekerja dengan baik dan dapat memadamkan api yang ada.
