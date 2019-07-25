//SPEEDOMETER FOR EBIKE
//Created by: Bryan Ford 10/21/18

double bikeVel;
double pi = 3.14159265;
double w = 0;
double Distance = 0.0;
double Distance_mem = 186.46;
int savedDistance = 0;
int wheelDiam_in = 26;
int timeDelay = 2000;
unsigned long rotCount_old = 0;
unsigned long oldTime = 2000;
volatile unsigned long rotCount = 0;
volatile unsigned long lastTime;
volatile double interval = 10000000;
volatile int HallIn = 2;

//BMS Variables
byte byte_Amps[2];
byte Cell_Volt[30];
byte byte_Array[34];
unsigned long time1;
double Current_A;
double Voltages_V[15];

//I2C LIBRARY ADDITION
// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

//EEPROM LIBRARY ADDITION
#include <EEPROM.h>
int addr = 0;

#include <SoftwareSerial.h> // This allows two digital pins to act as RX and TX to an external serial device
SoftwareSerial portOne(10, 11); // software serial #1: RX = digital pin 10, TX = digital pin 11

//Executed when Arduino receives a "RISING" digital input from Hall Sensor
void pin_ISR() {
  interval = millis() - lastTime;
  lastTime = millis();
  rotCount++;
}


void setup() {
  Serial.begin(9600);
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(HallIn), pin_ISR, RISING); //HallIn = 2. Pin 2 is an interupt pin
  // Start each software serial port
  portOne.begin(9600);
  // set up the LCD's number of columns and rows:
  setDisplay(); // See setDisplay function

  //Retrive mileage data

  if(EEPROM.read(addr) == 255){
    Distance = Distance_mem;
  }else{
    EEPROM.get(addr, Distance);
  }
}

struct Packet1 {
  byte garbage1[6];
  int16_t current;
  byte garbage2[26];
};
union Converter1 {
  Packet1 p;
  byte d[34];
} converter1;
struct Packet2 {
  byte garbage1[4];
  int16_t Volt1[2]; int16_t Volt2[2];  int16_t Volt3[2]; int16_t Volt4[2]; int16_t Volt5[2];
  int16_t Volt6[2]; int16_t Volt7[2];  int16_t Volt8[2]; int16_t Volt9[2]; int16_t Volt10[2];
  int16_t Volt11[2]; int16_t Volt12[2]; int16_t Volt13[2]; int16_t Volt14[2]; int16_t Volt15[2];
  byte garbage2[3];
};
union Converter2 {
  Packet2 p;
  byte d[37];
} converter2;
union ByteSwap {
  byte b_array[2];
  int16_t swapped;
} ByteSwap;


void loop() {

  //if two seconds have passed since last save & the wheel has rotated, calculate new milage and save
  if (millis() - oldTime > timeDelay && rotCount_old != rotCount) {
    Distance = Distance + pi * wheelDiam_in / 12 / 5280 * (rotCount - rotCount_old);
    Serial.print("Distance ");
    Serial.println(Distance);
    EEPROM.put(addr, Distance); //saves mileage to specificed address in EEPROM
    rotCount_old = rotCount;
    oldTime = millis();
  }

  //Distance Display Formatting
  if (Distance > 999.99) {
    lcd.setCursor(8, 0); lcd.print(Distance, 2);
  }
  else if (Distance > 99.99) {
    lcd.setCursor(9, 0); lcd.print(Distance, 2);
  }
  else if (Distance > 9.99) {
    lcd.setCursor(10, 0); lcd.print(Distance, 2);
  }
  else {
    lcd.setCursor(11, 0); lcd.print(Distance, 2);
  }

  //Velocity Calculation and Display
  w = 1 / (interval / 1000);
  bikeVel = w * pi * 3600 * wheelDiam_in / 12 / 5280;
  if (bikeVel > 9.999)
  {
    lcd.setCursor(10, 1);
  }
  else {
    lcd.setCursor(10, 1);
    lcd.print(" ");
  }
  lcd.print(bikeVel, 1);

  byte message[] = {0xdd, 0xa5, 0x03, 0x00, 0xff, 0xfd, 0x77}; //This is a byte array that is an info request to the BMS
  time1 = millis();

  if (portOne.available() == 0) { //see if serial port is open for output communication
    portOne.write(message, sizeof(message)); //send the info request to the BMS
  }
  portOne.listen(); Serial.println("1st Data Request:"); while (portOne.available() < 34);//Wait until 34 bytes have been received

  int n = portOne.readBytes(converter1.d, 34); // n is size of byte array received
  for (int i = 0; i < sizeof(converter1.d); i++) {
    Serial.print(converter1.d[i], HEX); //Prints out received message
    Serial.print(", ") ;
  }
  Serial.println(); Serial.print("Number of Bytes received: "); Serial.println(n);


  ByteSwap.b_array[0] = converter1.d[7]; ByteSwap.b_array[1] = converter1.d[6];
  Current_A = (double) - .01 * ByteSwap.swapped;
  Serial.print("Current: "); Serial.println(Current_A);
  //lcd.setCursor(9, 2); lcd.print(Current_A, 2);


  // ***Send 2nd request***
  byte message2[] = {0xdd, 0xa5, 0x04, 0x00, 0xff, 0xfc, 0x77};//Request info from BMS

  if (portOne.available() == 0) {
    portOne.write(message2, sizeof(message2));
  }
  portOne.listen(); Serial.println("2nd Data Request:"); while (portOne.available() < 37);
  int n2 = portOne.readBytes(converter2.d, 37); // n is size of byte array received
  for (int i = 0; i < sizeof(converter2.d); i++) {
    Serial.print(converter2.d[i], HEX);
    Serial.print(", ") ;
  }
  Serial.println(); Serial.print("Number of Bytes received: "); Serial.println(n2);

  double min_Voltage_V = 5; int index;
  double Total_Voltage_V = 0;
  for (int i = 1; i < 16; i++) {
    ByteSwap.b_array[0] = converter2.d[2 * i + 3]; ByteSwap.b_array[1] = converter2.d[2 * i + 2];
    Voltages_V[i] = (double)ByteSwap.swapped / 1000;
    Total_Voltage_V = Total_Voltage_V + Voltages_V[i]; //Add cell voltage to sum of voltages.
    if (Voltages_V[i] < min_Voltage_V) {
      index = i;
      min_Voltage_V = Voltages_V[i];
    }
    Serial.print("V"); Serial.print(i); Serial.print(": "); Serial.println(Voltages_V[i], 3);
  }

  lcd.setCursor(11, 2); lcd.print(Voltages_V[index], 2);
  Serial.print("Min Voltage: "); Serial.println(Voltages_V[index], 3);
  Serial.print("Index Num: "); Serial.println(index);

  double Power_W = Total_Voltage_V * Current_A;
  Serial.print("Power: "); Serial.println(Power_W, 2); Serial.println();
  lcd.setCursor(11, 3); lcd.print(Power_W, 1);

}

void setDisplay() {
  lcd.begin(20, 4);
  lcd.print("            ");
  lcd.setCursor(0, 1);  lcd.print("Speed: ");
  lcd.setCursor(0, 0);  lcd.print("Dist :");
  lcd.setCursor(16, 0); lcd.print("mi");
  lcd.setCursor(16, 1); lcd.print("mph");
  lcd.setCursor(0, 3); lcd.print("Power: ");
  lcd.setCursor(0, 2); lcd.print("MinVolt: ");
  lcd.setCursor(16, 3); lcd.print("W");
  lcd.setCursor(16, 2); lcd.print("V");
}



