#include <variable.h>

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
 Wire.begin(21, 22);
pca.begin();
pca.setPWMFreq(50);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("aa:aa:aa:aa:aa:aa");
 
  setupMotor();
  
}

void loop() {
  // put your main code here, to run repeatedly:
 onConnect();
 

}
