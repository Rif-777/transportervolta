
void kinematikMotor(int x, int y, int th) {
  // Konversi sudut ke radian
  float rad45 = PI / 4.0;      // 45 derajat
  float rad315 = 7 * PI / 4.0; // -45 derajat (315 derajat)
  float rad225 = 5 * PI / 4.0; // -135 derajat (225 derajat) 
  float rad135 = 3 * PI / 4.0; // 135 derajat
  float rad150 = 150.0 * PI / 180.0;   // 150 derajat
  float rad270 = 270.0 * PI / 180.0;   // 270 derajat
  float rad30  = 30.0  * PI / 180.0;   // 30 derajat

  float radLeft  = 0;    // motor kiri 0 derajat
  float radRight = PI;   // motor kanan 180 derajat
  // Faktor skala untuk rotasi - sesuaikan dengan robot Anda
  float rotationScale = 3;

  // Kinematik inverse untuk omni wheel 4 roda
  m1 = lambda * (cos(rad150) * x + sin(rad150) * y + LengthAlpha * th * rotationScale);
  m2 = lambda * (cos(rad30) * x + sin(rad30) * y + LengthAlpha * th * rotationScale);
  m3 = lambda * (cos(rad270) * x + sin(rad270) * y + LengthAlpha * th * rotationScale);
 // m4 = lambda * (cos(radRight) * x + sin(radRight) * y + LengthAlpha * th * rotationScale);

  // Serial.printf("Kinematik Input - x:%d y:%d th:%d\n", x, y, th);
  // Serial.printf("M1:%d M2:%d M3:%d M4:%d\n", m1, m2, m3, m4);

  // Deadzone dan constrain
  if (abs(m1) < 30) m1 = 0;
  if (abs(m2) < 30) m2 = 0;
  if (abs(m3) < 30) m3 = 0;
  //if (abs(m4) < 30) m4 = 0;

  m1 = constrain(m1, -1000, 1000);
  m2 = constrain(m2, -1000, 1000);
  m3 = constrain(m3, -1000, 1000);
 // m4 = constrain(m4, -1000, 1000);

  // int pwm[4] = { m1, m2, m3, m4 };
  // setPwm(pwm);

  set_pwm(M1 , m1);
  set_pwm(M2 , m2);
  set_pwm(M3 , m3);
  //set_pwm(M4 , m4);
}

// void setPwm(int pwm[4]) {
//   int pinA[] = { PWM1A, PWM2A, PWM3A, PWM4A };
//   int pinB[] = { PWM1B, PWM2B, PWM3B, PWM4B };

//   for (int i = 0; i < 4; i++) {
//     if (pwm[i] > 0) {
//       ledcWrite(pinA[i], pwm[i]);
//       ledcWrite(pinB[i], 0);
//     } else if (pwm[i] < 0) {
//       ledcWrite(pinA[i], 0);
//       ledcWrite(pinB[i], abs(pwm[i]));
//     } else {
//       ledcWrite(pinA[i], 0);
//       ledcWrite(pinB[i], 0);
//     }
//   }
// }


void set_pwm(byte MTR , int val_pwm){
  switch(MTR){
    case M1 : 
      if(val_pwm > 0){
        digitalWrite(EN1 , HIGH);
        ledcWrite(PWM1A, val_pwm);
        ledcWrite(PWM1B, 0);
      }else if(val_pwm < 0){
        digitalWrite(EN1 , HIGH);
        ledcWrite(PWM1B, abs(val_pwm));
        ledcWrite(PWM1A, 0);
      }else{
        digitalWrite(EN1 , LOW);
        ledcWrite(PWM1A, 0);
        ledcWrite(PWM1B, 0);
      }
      break;

    case M2 : 
      if(val_pwm > 0){
        digitalWrite(EN2 , HIGH);
        ledcWrite(PWM2A, val_pwm);
        ledcWrite(PWM2B, 0);
      }else if(val_pwm < 0){
        digitalWrite(EN2 , HIGH);
        ledcWrite(PWM2B, abs(val_pwm));
        ledcWrite(PWM2A, 0);
      }else{
        digitalWrite(EN2 , LOW);
        ledcWrite(PWM2A, 0);
        ledcWrite(PWM2B, 0);
      }
      break;

      case M3 : 
      if(val_pwm > 0){
        digitalWrite(EN3 , HIGH);
        ledcWrite(PWM3A, val_pwm);
        ledcWrite(PWM3B, 0);
      }else if(val_pwm < 0){
        digitalWrite(EN3 , HIGH);
        ledcWrite(PWM3B, abs(val_pwm));
        ledcWrite(PWM3A, 0);
      }else{
        digitalWrite(EN3 , LOW);
        ledcWrite(PWM3A, 0);
        ledcWrite(PWM3B, 0);
      }
      break;

      case M4 : 
      if(val_pwm > 0){
        digitalWrite(EN4 , HIGH);
        ledcWrite(PWM4A, val_pwm);
        ledcWrite(PWM4B, 0);
      }else if(val_pwm < 0){
        digitalWrite(EN4 , HIGH);
        ledcWrite(PWM4B, abs(val_pwm));
        ledcWrite(PWM4A, 0);
      }else{
        digitalWrite(EN4 , LOW);
        ledcWrite(PWM4A, 0);
        ledcWrite(PWM4B, 0);
      }
      break;

  }
}


