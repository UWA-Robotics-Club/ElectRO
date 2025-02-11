#pragma once
#include <WiFi.h>
#include <WebSocketsClient.h>

constexpr char WIFI_SSID[] = "Stealth";
constexpr char WIFI_PASSWORD[] = "Magic2010";

constexpr char WS_URL[] = "192.168.2.230";
constexpr int WS_PORT = 8080;
constexpr char WS_ENDPOINT[] = "/";

extern WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);
void initWebsocket();