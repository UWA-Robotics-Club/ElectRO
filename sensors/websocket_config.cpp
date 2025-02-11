#include "websocket_config.h"

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_DISCONNECTED) {
    Serial.println("WebSocket disconnected");
  } else if (type == WStype_CONNECTED) {
    Serial.println("WebSocket connected");
  } else if (type == WStype_TEXT) {
    Serial.printf("Received: %s\n", payload);
  }
}

void initWebsocket(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  webSocket.begin(WS_URL, WS_PORT, WS_ENDPOINT); // Replace with your server's IP address
  webSocket.onEvent(webSocketEvent);
}

