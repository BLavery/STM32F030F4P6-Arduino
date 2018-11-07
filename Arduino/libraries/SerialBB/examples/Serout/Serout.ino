
#include <SerialBB.h>


void setup() {
}



void loop() {
  Serial.txByte('H');  // no linefeed
  Serial.txStr("ello, I'm arriving soon...", true);// optional second parameter "true" adds linefeed
  Serial.txInt(54321, true);
  delay(500);                     
}
