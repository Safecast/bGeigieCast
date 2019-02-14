
/* bGeigieNano Xbee-ESP32 is a addon for bGeigieNano to be used as a fixed sensor device. Harware is a Xbee socket with ESP32 and some extra compants on it.
 *  Copyright (c) 2019, Safecast

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


History Versions:

Contact:Jelle Bouwhuis (email jellebouwhuis@outlook.com) and Rob Oudendijk (rob@yr-design.biz)
*/
#include <Arduino.h>

void taskOne(void *parameter) {
  for (int i = 0; i < 10; i++) {

    Serial.println("Hello from task 1");
    delay(1000);
  }
  Serial.println("Ending task 1");
  vTaskDelete(NULL);
}

void taskTwo(void *parameter) {
  for (int i = 0; i < 10; i++) {
    Serial.println("Hello from task 2");
    delay(1000);
  }
  Serial1.println("Ending task 2");
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(112500);
  delay(1000);
  xTaskCreate(taskOne,   /* Task function. */
              "TaskOne", /* String with name of task. */
              10000,     /* Stack size in bytes. */
              NULL,      /* Parameter passed as input of the task */
              1,         /* Priority of the task. */
              NULL);     /* Task handle. */
  xTaskCreate(taskTwo,   /* Task function. */
              "TaskTwo", /* String with name of task. */
              10000,     /* Stack size in bytes. */
              NULL,      /* Parameter passed as input of the task */
              1,         /* Priority of the task. */
              NULL);     /* Task handle. */
}

void loop() { delay(1000); }
