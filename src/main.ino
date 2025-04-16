#include <LiquidCrystal.h>

// Ultrasonic sensor signal pins definitions
#define ECHO_SENS1 A2  // ultrasonic sensor output signal
#define TRIG_SENS1 A3  // ultrasonic sensor input signal
#define ECHO_SENS2 A5  // ultrasonic sensor output signal
#define TRIG_SENS2 A4  // ultrasonic sensor input signal
#define W_LED_R 3      // operating LED of the device
#define W_LED_G 5      // LED indicating active pump operation
#define W_LED_B 6      // blue LED
#define BUZZ 4         // pin for buzzer
#define GLASS_ECHO_SENS A0 // glass sensor output signal
#define GLASS_TRIG_SENS A1 // glass sensor input signal
#define PUMP 2         // water pump pin

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// UNIT OF MEASUREMENT: centimeters
// SENSOR ERROR: 3mm = 0.3cm

long duration;       // sensor reading
float distance;      // distance from sensor to water level
float distance2;     // distance from sensor when the glass is being filled
int volume;          // current water volume in ml and previous volume

const float min_dist = 3;       // minimum distance until the glass is filled
const float dist_glass = 7;     // activation distance when the glass is in the filling area
const float min_water = 3;      // minimum water level required to activate the empty reservoir warning
const float bottle_height = 23; // cm, height of the bottle
const float bottle_width = 8;   // cm, side of the bottle (square)
const float sens_dist = 2;      // cm, distance at which the sensor is placed
const float sens_error =  0.3;  // cm, sensor error
float water_lvl;              // cm of water in the bottle

void setup() {
  pinMode(TRIG_SENS1, OUTPUT);
  pinMode(ECHO_SENS1, INPUT);
  pinMode(TRIG_SENS2, OUTPUT);
  pinMode(ECHO_SENS2, INPUT);        // -> PIN ASSIGNMENT
  pinMode(W_LED_R, OUTPUT);
  pinMode(W_LED_G, OUTPUT);
  pinMode(W_LED_B, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(GLASS_TRIG_SENS, OUTPUT);
  pinMode(GLASS_ECHO_SENS, INPUT);
  pinMode(PUMP, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);     // TURN ON SCREEN
  lcd.print("CANTITATE APA: "); // DISPLAY INITIAL MESSAGE ("WATER AMOUNT:")
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // allow the sensor to read the distance for 15 µs
  delayMicroseconds(15);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);  // return the measured distance
}

void loop() {
  duration = readUltrasonicDistance(TRIG_SENS1, ECHO_SENS1); // read sensors
  distance = duration / 58; // calculate distance in cm
  water_lvl = bottle_height - (distance - sens_dist); // current water level in the bottle
  volume = bottle_width * bottle_width * water_lvl; // water volume in ml (conversion: cm³ = ml)
  // volume = area * height (area = side * side)

  // Check water level
  if (water_lvl <= min_water) {
    lcd.setCursor(0, 1);
    lcd.print("  REZERVOR GOL   "); // "RESERVOIR EMPTY"
    analogWrite(W_LED_R, LOW);     // turn off RED LED
    tone(BUZZ, 262, 150);
    delay(2000);
    noTone(BUZZ);
  } else if (water_lvl < bottle_height - sens_error) {
    analogWrite(W_LED_R, HIGH); // turn on RED LED
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(volume);
    lcd.print("  ml     ");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("  REZERVOR PLIN"); // "RESERVOIR FULL"
    analogWrite(W_LED_R, HIGH); // turn on RED LED
  }
  delay(100);  // short delay to prevent abrupt calculations

  duration = readUltrasonicDistance(GLASS_TRIG_SENS, GLASS_ECHO_SENS); // read the glass sensor
  distance = duration / 58;

  duration = readUltrasonicDistance(TRIG_SENS2, ECHO_SENS2);
  distance2 = duration / 58;

  while ((distance <= dist_glass) && (water_lvl > sens_error + min_water) && (distance2 > min_dist)) {
    analogWrite(W_LED_R, LOW); // turn off red LED
    lcd.setCursor(0, 0);
    lcd.print("   ALIMENTARE   "); // "REFILLING"
    lcd.setCursor(0, 1);
    lcd.print("    RECIPIENT       "); // "CONTAINER"
    analogWrite(W_LED_G, HIGH); // GREEN LED indicates pump operation
    delay(500);
    digitalWrite(PUMP, HIGH);   // start pump
    delay(150);

    duration = readUltrasonicDistance(TRIG_SENS1, ECHO_SENS1); // read sensors
    distance = duration / 58; // calculate distance
    water_lvl = bottle_height - (distance - sens_dist); // update current water level

    duration = readUltrasonicDistance(GLASS_TRIG_SENS, GLASS_ECHO_SENS); // read glass sensor
    distance = duration / 58;

    duration = readUltrasonicDistance(TRIG_SENS2, ECHO_SENS2);
    distance2 = duration / 58;
  }
  
  digitalWrite(PUMP, LOW); // stop pump
  delay(100);
  analogWrite(W_LED_G, LOW); // turn off green LED
  analogWrite(W_LED_R, HIGH); // turn on red LED - DEVICE OPERATIONAL
  lcd.setCursor(0, 0);
  delay(50);
  lcd.print(" CANTITATE APA: "); // reset the screen with the message "WATER AMOUNT:"
}