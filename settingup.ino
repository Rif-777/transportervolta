void setAnglePCA(int ch, int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pca.setPWM(ch, 0, pulse);
}


void notify() {
  // Baca nilai stick secara langsung
  lx = Ps3.data.analog.stick.lx;  // Stick kiri X
  ly = Ps3.data.analog.stick.ly;  // Stick kiri Y
  rx = Ps3.data.analog.stick.rx;  // Stick kanan X (untuk rotasi)
  ry = Ps3.data.analog.stick.ry;  // Stick kanan Y

  // Deadzone untuk semua stick
  if (abs(lx) < 20) lx = 0;
  if (abs(ly) < 20) ly = 0;
  if (abs(rx) < 20) rx = 0;
  if (abs(ry) < 20) ry = 0;

  // Proses stick kiri (movement) - gerakan translasi
  if (Ps3.data.analog.stick.lx != 0 || Ps3.data.analog.stick.ly != 0) {
    if (Ps3.data.button.up) {
      lx = 0;
      ly = 200;
    } else if (Ps3.data.button.down) {
      lx = 0;
      ly = -200;
    } else if (Ps3.data.button.left) {
      lx = -200;
      ly = 0;
    } else if (Ps3.data.button.right) {
      lx = 200;
      ly = 0;
    } else {
      lx = (Ps3.data.analog.stick.lx * 225 / 128);
      ly = Ps3.data.analog.stick.ly * 225 / 128;

      if (abs(lx) < 60) lx = 0;
      if (abs(ly) < 60) ly = 0;
      if (abs(ly) > abs(lx)) {
        if (abs(ly) > 60) lx = 0;
      } else {
        if (abs(lx) > 60) ly = 0;
      }
    }
  } else {
    lx = 0;
    ly = 0;
  }

  // Proses stick kanan (rotasi) - gunakan hanya sumbu X untuk rotasi sederhana
  float rotation = 0;
  if (abs(rx) > 20) {
    rotation = (rx / 127.0) * 400; // Skala rotasi dari -400 sampai 400
  }
  
 kinematikMotor(-ly, -lx, -rotation);

// if (Ps3.data.button.circle) {
//     servoState = !servoState;
//     int angle = servoState ? SERVO_CLOSE : SERVO_OPEN;
//     setAnglePCA(0, angle);
// }

if (Ps3.data.button.circle) {
    unsigned long now = millis();
    if (now - lastCirclePress > debounceDelay) {
        
        servoState = !servoState;
        int angle = servoState ? SERVO_CLOSE : SERVO_OPEN;
        setAnglePCA(0, angle);

        Serial.printf("Gripper toggle -> %d°\n", angle);

        lastCirclePress = now;   // update waktu terakhir
    }
}

// ====== Servo tambahan di PCA channel 3, kontrol tombol KOTAK ======
// if (Ps3.data.button.square) {
//     unsigned long now = millis();
//     if (now - lastSquarePress > debounceDelay) {   // FIXED

//         servoState2 = !servoState2;
//         servoState3 = !servoState3;
//         int angle2 = servoState2 ? SERVO_CLOSE2 : SERVO_OPEN2;
//         int angle3 = servoState3 ? SERVO_CLOSE3 : SERVO_OPEN3;

//         setAnglePCA(2, angle2);
//         setAnglePCA(4, angle3);

//         Serial.printf("Servo CH2 toggle -> %d°\n", angle2);
//         Serial.printf("Servo CH3 toggle -> %d°\n", angle3);

//         lastSquarePress = now;  // FIXED
//     }

// ======= L1 TOGGLE CH2 =======
if (Ps3.data.button.l1) {
    unsigned long now = millis();
    if (now - lastL1Press > debounceDelay) {

        servoState2 = !servoState2;   // toggle state
        int angle2 = servoState2 ? SERVO_CLOSE2 : SERVO_OPEN2;

        setAnglePCA(2, angle2);
        Serial.printf("Servo CH2 toggle (L1) -> %d°\n", angle2);

        lastL1Press = now;
    }
}

// ======= L2 TOGGLE CH4 =======
if (Ps3.data.button.r1) {
    unsigned long now = millis();
    if (now - lastL2Press > debounceDelay) {

        servoState3 = !servoState3;   // toggle state
        int angle3 = servoState3 ? SERVO_CLOSE3 : SERVO_OPEN3;

        setAnglePCA(3, angle3);
        Serial.printf("Servo CH4 toggle (L2) -> %d°\n", angle3);

        lastL2Press = now;
    }
}

    



 static int lifterTarget = 0;
  static int lifterSpeed = 0;
  const int lifterStep = 50;

  if ( Ps3.event.button_down.triangle ||
       Ps3.event.button_down.cross    ||
       Ps3.event.button_up.triangle   ||
       Ps3.event.button_up.cross )
  {
      if (Ps3.event.button_down.triangle) lifterTarget = -1023;
      if (Ps3.event.button_down.cross)    lifterTarget =  1023;
      if (Ps3.event.button_up.triangle || Ps3.event.button_up.cross)
          lifterTarget = 0;
  }

  if (lifterSpeed < lifterTarget) lifterSpeed += lifterStep;
  else if (lifterSpeed > lifterTarget) lifterSpeed -= lifterStep;

  if (lifterSpeed > 1023)  lifterSpeed = 1023;
  if (lifterSpeed < -1023) lifterSpeed = -1023;

  m4 = lifterSpeed;
  set_pwm(M4 , m4);

  //Serial.printf("lx:%d ly:%d rx:%d rotation:%.1f\n", lx, ly, rx, rotation);
}

  

void onConnect() {
  if (Ps3.isConnected()) {
    // Serial.println("Connected!");
  }
}


void setupMotor(){
  int pin[] = { PWM1A, PWM1B, PWM2A, PWM2B, PWM3A, PWM3B, PWM4A, PWM4B};
  for (int i = 0; i <8; i++) {
  ledcAttach(pin[i], freq, res);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, LOW);
  }

}



