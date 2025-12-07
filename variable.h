#include <Ps3Controller.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <ESP32Servo.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

// robot1
#define PWM1B 18
#define PWM1A 19
#define PWM2A 33
#define PWM2B 32
#define PWM3B 15
#define PWM3A 14
#define PWM4A 13
#define PWM4B 12
#define EN1 4
#define EN2 27
#define EN3 26
#define EN4 25

// // PARAMETER PWM
#define freq 18000  // 18 kHz frequency
#define res 10

#define M1 1
#define M2 2
#define M3 3
#define M4 4


#define d2r(x) x*(PI / 180)

#define LengthAlpha 0.105  // Ubah Disini untuk panjang dari sumbu roda ke tengah roda


int16_t x;
int16_t y;
int16_t th;

float atanVal;
// int xL, yL;
// int xR, yR;

int lx, ly, ry, rx;
int SpeedM = 255,
    SpeedM2 = 255;
int inv_yR;

int m1, m2, m3, m4;

float lambda = 6.0f;

bool servoState2 = false;

#define SERVO_OPEN2   20      // sudut servo channel 3 ketika buka
#define SERVO_CLOSE2  130    // sudut servo channel 3 ketika tutup
#define SERVO_OPEN3   134     // sudut servo channel 3 ketika buka
#define SERVO_CLOSE3  0
#define servo1 23       
Servo myServo;

bool servoState3 = false;

const int SERVOMIN = 150;
const int SERVOMAX = 600;

bool servoState = false;
static bool circlePressed = false;

// ==================== SERVO SMOOTH ====================
#define SERVO_OPEN 124
#define SERVO_CLOSE 90

int targetAngle = SERVO_OPEN;
int currentAngle = SERVO_OPEN;
unsigned long lastCirclePress = 0;
unsigned long lastSquarePress = 0;
unsigned long lastL2Press = 0;
unsigned long lastL1Press = 0;
const unsigned long debounceDelay = 200; // 200 ms aman

unsigned long lastMoveTime = 0;

int servoStep     = 3;   // kecepatan (3 = cepat halus)
int servoInterval = 8;   // refresh (8ms = cepat)

// #define d2r(x) x*(PI/180)
// #define LengthAlpha 0.15 //diameter roda

// int lx , ly , teta , rx , ry , atanVal , m1 , m2 , m3, m4;

// int lambda = 5; // Awal nilai lambda
// const int DEADZONE_RIGHT = 15; // Deadzone untuk analog kanan
