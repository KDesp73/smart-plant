#pragma once
#include <HTTPClient.h>
#include "WString.h"
#include "env.h"

static inline void send_notification(String title, String message)
{
    HTTPClient http;

    String url = "https://api.pushbullet.com/v2/pushes";
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(PUSHBULLET_API_KEY));

    String payload = "{\"type\":\"note\", \"title\":\"" + title + "\", \"body\":\"" + message + "\", \"device_iden\":\"" + PUSHBULLET_DEVICE_ID + "\"}";

    int httpCode = http.POST(payload);

    if (httpCode > 0) {
        Serial.println("Notification sent!");
    } else {
        Serial.println("Error sending notification");
    }

    http.end();
}
