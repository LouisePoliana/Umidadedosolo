#include <WiFi.h>
#include <WebServer.h>

// Defina o SSID e a senha da rede Wi-Fi
const char* ssid = "";
const char* password = "";
// Defina o pino onde o sensor de umidade do solo está conectado
const int soilSensorPin = 26; // Pino analógico A0

WebServer server(80); // Cria um servidor web na porta 80

// Função para ler a umidade do solo
int readSoilMoisture() {
  int sensorValue = analogRead(soilSensorPin); // Lê o valor do sensor (0-1023)
  return sensorValue;
}

// Função para retornar a página inicial
void handleRoot() {
  String html = "<html><head><meta http-equiv='refresh' content='3'></head>";
  html += "<body><h1>Leitura da Umidade do Solo</h1><br>";
  html += "<p>Umidade: " + String(readSoilMoisture()) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Função de inicialização
void setup() {
  // Configura o pino do sensor de umidade como entrada
  pinMode(soilSensorPin, INPUT);

  // Conecta-se à rede Wi-Fi
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    //delay(1000);
    //Serial.print
    Serial.println("Conectando à rede Wi-Fi...");
  }
  Serial.println("Conectado à rede Wi-Fi");

  // Exibe o IP do servidor
  Serial.println("IP do servidor: ");
  Serial.println(WiFi.localIP());

  // Roteia a URL raiz para exibir a umidade do solo
  server.on("/", handleRoot);

  // Inicia o servidor
  server.begin();
  Serial.println("Servidor iniciado");
}

// Função de loop principal
void loop() {
  server.handleClient(); // Lida com os pedidos do cliente
}