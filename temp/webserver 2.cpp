//* Made for testing RGB LED on IO32,IO33 and IO25. 2019-02-23 rob

#include <Arduino.h>

#include <WiFi.h>

// Please change to Wi-Fi to use and its password
const char *ssid = "";
const char *password = "";

// use port 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Variable used to set value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

//ledpin
const int ledR = A18;
const int ledG = A4;
const int ledB = A5;

void setup()
{
  //ledc setting
  //R
  ledcSetup(0, 12800, 8);
  // Connect ledR to channel 0
  ledcAttachPin(ledR, 0);

  //G
  ledcSetup(1, 12800, 8);
  // Connect ledG to channel 1
  ledcAttachPin(ledG, 1);

  //B
  ledcSetup(2, 12800, 8);
  // Connect ledB to channel 2
  ledcAttachPin(ledB, 2);

  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Display local IP (Access this IP from smartphone etc.)
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>ESP32 RGB LED controller</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println("#servoPosR{color: red;}");
            client.println("#servoPosG{color: green;}");
            client.println("#servoPosB{color: blue;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");

            // Web Page
            client.println("</head><body><h1>ESP32 bGeigieNano RGBLED </h1>");
            //R slide bar
            client.println("<p>Brightness of R: <span id=\"servoPosR\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"servoSliderR\" onchange=\"servo(this.value,'R')\" value=\"" + valueString + "\"/>");
            //G slide bar
            client.println("<p>Brightness of G: <span id=\"servoPosG\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"servoSliderG\" onchange=\"servo(this.value,'G')\" value=\"" + valueString + "\"/>");
            //B slide bar
            client.println("<p>Brightness of B: <span id=\"servoPosB\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"servoSliderB\" onchange=\"servo(this.value,'B')\" value=\"" + valueString + "\"/>");

            client.println("<script>");
            //send R value
            client.println("var sliderR = document.getElementById(\"servoSliderR\");");
            client.println("var servoPR = document.getElementById(\"servoPosR\"); servoPR.innerHTML = sliderR.value;");
            client.println("sliderR.oninput = function() { sliderR.value = this.value; servoPR.innerHTML = this.value; }");

            //send G value
            client.println("var sliderG = document.getElementById(\"servoSliderG\");");
            client.println("var servoPG = document.getElementById(\"servoPosG\"); servoPG.innerHTML = sliderG.value;");
            client.println("sliderG.oninput = function() { sliderG.value = this.value; servoPG.innerHTML = this.value; }");
            //send B value
            client.println("var sliderB = document.getElementById(\"servoSliderB\");");
            client.println("var servoPB = document.getElementById(\"servoPosB\"); servoPB.innerHTML = sliderB.value;");
            client.println("sliderB.oninput = function() { sliderB.value = this.value; servoPB.innerHTML = this.value; }");

            // Function for HTTP get
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos,color) { ");
            client.println("$.get(\"/?value\" + color + \"=\" + pos + \"&\"); {Connection: close};}</script>");

            client.println("</body></html>");

            // Processing part of HTTP request
            //GET /?value=180& HTTP/1.1
            // Convert the value of R to the output of led
            if (header.indexOf("GET /?valueR=") >= 0)
            {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);

              // LED lit with valueString value
              ledcWrite(0, valueString.toInt());
              Serial.println(valueString);
            }
            // Convert the value of G to the output of led
            if (header.indexOf("GET /?valueG=") >= 0)
            {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);

              // LED lit with valueString value
              ledcWrite(1, valueString.toInt());
              Serial.println(valueString);
            }

            // Convert the value of B to led output
            if (header.indexOf("GET /?valueB=") >= 0)
            {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);

              // LED lit with valueString value
              ledcWrite(2, valueString.toInt());
              Serial.println(valueString);
            }
            // End of HTTP response client.println();
            // Break out of the while loop
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }
    // Clear the header variable
    header = "";
    // Disconnect connection client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}