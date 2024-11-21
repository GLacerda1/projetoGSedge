#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Configurações do DHT
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configurações Wi-Fi e MQTT
const char* ssid = "Wokwi-GUEST";          // Nome da rede Wi-Fi
const char* password = "";                 // Senha do Wi-Fi
const char* mqtt_server = "4.228.61.195"; // Endereço do broker MQTT
const int mqtt_port = 1883;                // Porta MQTT
const char* mqtt_id = "monitor_temp";      // ID do cliente MQTT
const char* topic_temp = "/monitor/temperature";
const char* topic_hum = "/monitor/humidity";
const char* topic_status = "/monitor/status";

WiFiClient espClient;
PubSubClient client(espClient);

// Configurações do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pinos dos LEDs
#define FAN_LED_PIN 13
#define HEATER_LED_PIN 15

void setupWiFi() {
    Serial.print("Conectando ao Wi-Fi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado.");
}

void reconnectMQTT() {
    while (!client.connected()) {
        Serial.print("Conectando ao MQTT...");
        if (client.connect(mqtt_id)) {
            Serial.println("Conectado.");
        } else {
            Serial.print("Falha. Código: ");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void sendMQTT(float t, float h, const char* status) {
    if (!client.connected()) reconnectMQTT();
    client.loop();

    char tempStr[8];
    char humStr[8];
    snprintf(tempStr, sizeof(tempStr), "%.2f", t);
    snprintf(humStr, sizeof(humStr), "%.2f", h);

    client.publish(topic_temp, tempStr);
    client.publish(topic_hum, humStr);
    client.publish(topic_status, status);
}

void setup() {
    Serial.begin(115200);
    setupWiFi();
    client.setServer(mqtt_server, mqtt_port);

    // Inicializa display OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Erro ao inicializar o display OLED.");
        while (true);
    }
    display.clearDisplay();

    // Inicializa DHT e LEDs
    dht.begin();
    pinMode(FAN_LED_PIN, OUTPUT);
    pinMode(HEATER_LED_PIN, OUTPUT);
    digitalWrite(FAN_LED_PIN, LOW);
    digitalWrite(HEATER_LED_PIN, LOW);
}

void displayInfo(float t, float h, const char* status) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Exibe informações de temperatura e umidade
    display.setCursor(0, 0);
    display.printf("Temp: %.2f C", t);
    display.setCursor(0, 10);
    display.printf("Hum: %.2f %%", h);

    // Exibe status do sistema
    display.setCursor(0, 30);
    display.println("Status:");
    display.setCursor(0, 40);
    display.println(status);

    // Exibe status da conexão Wi-Fi
    display.setCursor(0, 55);
    if (WiFi.status() == WL_CONNECTED) {
        display.print("Wi-Fi: OK");
    } else {
        display.print("Wi-Fi: OFF");
    }

    display.display(); // Atualiza o display
}

void loop() {
    if (!client.connected()) reconnectMQTT();
    client.loop();

    // Leitura do DHT
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
        Serial.println("Erro ao ler do DHT.");
        return;
    }

    // Controle de LEDs e estado do sistema
    const char* status;
    if (t < 22.0 && h > 60.0) {
        digitalWrite(FAN_LED_PIN, LOW);
        digitalWrite(HEATER_LED_PIN, LOW);
        status = "Sistema Desligado";
    } else if (t < 22.0) {
        digitalWrite(FAN_LED_PIN, LOW);
        digitalWrite(HEATER_LED_PIN, HIGH);
        status = "Aquecedor Ligado";
    } else if (t > 25.0 || h > 60.0) {
        digitalWrite(FAN_LED_PIN, HIGH);
        digitalWrite(HEATER_LED_PIN, LOW);
        status = "Ventilador Ligado";
    } else {
        digitalWrite(FAN_LED_PIN, LOW);
        digitalWrite(HEATER_LED_PIN, LOW);
        status = "Sistema Desligado";
    }

    // Atualiza informações no display
    displayInfo(t, h, status);

    // Envia dados via MQTT
    sendMQTT(t, h, status);

    delay(2000); // Aguarda 2 segundos antes de repetir
}
