#include "web_server.h"
#include "user_config.h"
#include "esp_config.h"
#include "debugger.h"

ConfigWebServer::ConfigWebServer(EspConfig& config) : server(SERVER_WIFI_PORT, SERVER_MAX_CLIENTS), config(config) {
}

bool ConfigWebServer::initialize() {
  char ssid[32], password[32];
  if(!config.get_ap_ssid(ssid) || !config.get_ap_password(password)) {
    debug_println("No SSID or password");
    return false;
  }

  WiFi.softAP(ssid, password);

  delay(100);

  IPAddress ip(ACCESS_POINT_IP);
  IPAddress n_mask(ACCESS_POINT_NMASK);
  WiFi.softAPConfig(ip, ip, n_mask);

  delay(100);

  server.begin();
  return is_running();
}

void ConfigWebServer::stop() {
  server.stop();
  WiFi.softAPdisconnect(true);
}

void ConfigWebServer::handle_requests() {
  String header;
  WiFiClient client = server.available();   // Listen for incoming clients

  if(client) {                             // If a new client connects,
    debug_println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while(client.connected()) {            // loop while the client's connected
      if(client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        debug_print(c);                    // print it out the serial monitor
        header += c;
        if(c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if(currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println(
                "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if(c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Close the connection
    client.stop();
    debug_println("Client disconnected.");
  }
}

bool ConfigWebServer::is_running() {
  return !!server;
}
