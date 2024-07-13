#include <WiFi.h>
#include <WiFiManager.h> // Tambahkan ini
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WiFiServer server(80);

String header;
String tempData = "";

void setup() {
  dht.begin();
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Mulai Konfigurasi");

  // WiFiManager
  WiFiManager wifiManager;
  
  // Menambahkan waktu tunggu koneksi WiFi (dalam detik)
  wifiManager.setConnectTimeout(30); // Set waktu tunggu 30 detik
  
  // Coba autoConnect dan tampilkan pesan
  if (!wifiManager.autoConnect("ESP32_AP")) {
    Serial.println("Gagal menghubungkan ke WiFi. Memasuki mode AP");
    Serial.println("IP address (AP Mode): ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("WiFi connected.");
    Serial.println("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.println("Memulai Server");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client Baru");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            Serial.println();

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html; charset=UTF-8");
            client.println("Connection: close");
            client.println();
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta http-equiv=\"refresh\" content=\"5\">"); // Mengubah meta refresh menjadi 5 detik
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\">"); // Tambahkan link Font Awesome
            client.println("<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>"); // Tambahkan link Chart.js
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; padding-top: 10px;}"); // Mengubah padding-top menjadi 10px
            client.println("body { margin-top: 0.5cm; }"); // Menambahkan margin-top untuk body
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println(".button-warning { background-color: #FF0000; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; animation: blinker 1s linear infinite;}");
            client.println("@keyframes blinker { 50% { opacity: 0; }}");
            client.println(".header-text { color: #00008B; }"); // Mengubah warna teks "Next Koding Enterprise" menjadi biru tua
            client.println(".esp-text { color: #D10069; }"); // Mengubah warna teks "ESP32 Web Server" menjadi pink tua
            client.println(".data-text { font-size: 2em; margin: 10px 0; }</style></head>");
            
            client.println("<body><h1 class='header-text'>Next Koding Enterprise</h1>");
            client.println("<h1 class='esp-text'>ESP32 Web Server</h1>");

            float h = dht.readHumidity();
            float t = dht.readTemperature();
            if (isnan(h) || isnan(t)) {
              client.println("<p>Gagal membaca dari sensor DHT!</p>");
            } else {
              if (t > 28) {
                client.println("<p><a href=\"#\"><button class=\"button-warning\">Suhu melebihi 29°C</button></a></p>");
              }
              client.println("<p class='data-text'><i class=\"fas fa-thermometer-half\" style=\"color:#059e8a;\"></i> Suhu: " + String(t) + " °C</p>");
              client.println("<p class='data-text'><i class=\"fas fa-tint\" style=\"color:#00add6;\"></i> Kelembapan: " + String(h) + " %</p>");
              
              tempData += String(t) + ",";
              if (tempData.length() > 500) {
                int commaIndex = tempData.indexOf(',');
                tempData = tempData.substring(commaIndex + 1);
              }

              client.println("<canvas id=\"tempChart\" width=\"400\" height=\"200\"></canvas>");
              client.println("<script>");
              client.println("var ctx = document.getElementById('tempChart').getContext('2d');");
              client.println("var tempData = [" + tempData + "];");
              client.println("var labels = new Array(tempData.length).fill('');");
              client.println("var tempChart = new Chart(ctx, {");
              client.println("type: 'line',");
              client.println("data: {");
              client.println("labels: labels,");
              client.println("datasets: [{");
              client.println("label: 'Temperature',");
              client.println("data: tempData,");
              client.println("backgroundColor: 'rgba(75, 192, 192, 0.2)',");
              client.println("borderColor: 'rgba(75, 192, 192, 1)',");
              client.println("borderWidth: 1");
              client.println("}]");
              client.println("},");
              client.println("options: {");
              client.println("scales: {");
              client.println("y: {");
              client.println("beginAtZero: true");
              client.println("}");
              client.println("}");
              client.println("}");
              client.println("});");
              client.println("</script>");
            }

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client Terputus");
    header = "";
  }
}
