#include "Lightstrip.h"
#include "mServer.h"

const char *field_brightness = "brightness";
const char *field_enabled = "enabled";
const char *field_color = "color";

void registerLightstripHandlers(mServer *server, Lightstrip *light) {
  server->addRoute("/lightstrip")
    .get([server, light]() {
      message[field_brightness] = light->brightness;
      message[field_enabled] = light->enabled;
      JsonArray color = message.createNestedArray(field_color);
      color.add(light->r);
      color.add(light->g);
      color.add(light->b);
      server->send();
    })
    .put("/color", [server, light]() {
      if (!server->parseMessage()
        || !message.containsKey(field_brightness)
        || !message.containsKey(field_color)
      ) {
        return server->sendStatus(REQUEST_BAD);
      }
      bool is_success = light->setColor(
        message["brightness"],
        message["color"][0],
        message["color"][1],
        message["color"][2]
      );
      server->sendStatus(is_success ? REQUEST_SUCCESS : REQUEST_ERROR);
    })
    .put("/power", [server, light]() {
      if (!server->parseMessage() || !message.containsKey(field_enabled)) {
        return server->sendStatus(REQUEST_BAD);
      }
      if (message[field_enabled] == light->enabled) {
        return server->sendStatus(REQUEST_SUCCESS);
      }
      bool is_success;
      if (message[field_enabled]) {
        is_success = light->powerOn();
      } else {
        is_success = light->powerOff();
      }
      server->sendStatus(is_success ? REQUEST_SUCCESS : REQUEST_ERROR);
    });
}

// void registerLightstripOldHandlers(Lightstrip *light) {
//   Server.on("/lightstrip", HTTP_GET, [light]() {
//     message.clear();
//     message["brightness"] = light->brightness;
//     message["enabled"] = light->enabled;
//     JsonArray color = message.createNestedArray("color");
//     color.add(light->r);
//     color.add(light->g);
//     color.add(light->b);
//     sendJson();
//   });



//   Server.on("/light/power_on", [light]() {
//     is_success = light->powerOn();
//     message.clear();
//     message["status"] = is_success ? "ok" : "error";
//     sendJson();
//   });

//   Server.on("/light/power_off", [light]() {
//     is_success = light->powerOff();
//     message.clear();
//     message["status"] = is_success ? "ok" : "error";
//     sendJson();
//   });
// }