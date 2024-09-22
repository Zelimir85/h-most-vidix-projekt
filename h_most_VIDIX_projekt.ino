#include <Adafruit_ILI9341.h> 
#include <Adafruit_GFX.h> 
// ILI9341 TFT LCD deklaracija pinova 
#define TFT_CS 5 
#define TFT_DC 21 
// stvaranje objekta ekrana koji će se zvati tft 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC); 


const int TRIG_PIN1  = 32; //Pin connected to Ultrasonic Sensor's TRIG1 pin
const int ECHO_PIN1  = 34; //Pin connected to Ultrasonic Sensor's ECHO1 pin
const int OPTO1 = 14; // Pinin connected to OPTO izolator 1
const int udaljenost_od_senzora = 10; // centimeters

const int TRIG_PIN2  = 2; // Pin connected to Ultrasonic Sensor's TRIG2 pin
const int ECHO_PIN2  = 27; // Pin connected to Ultrasonic Sensor's ECHO2 pinpin
const int OPTO2 = 22; // Pin connected to OPTO izolator
const int DISTANCE_THRESHOLD2 = 10; // centimeters

// variables will change:
float duration_us1, distance_cm1;
float duration_us2, distance_cm2;

void setup() {
tft.begin(); // inicijalizacija zaslona 

  Serial.begin (9600);        // initialize serial port
  pinMode(TRIG_PIN1, OUTPUT);  // set trig pin1 to output mode
  pinMode(ECHO_PIN1, INPUT);   // set echo pin1 to input mode
  pinMode(OPTO1, OUTPUT); // set OPTO1 pin to output mode

  pinMode(TRIG_PIN2, OUTPUT);  // set trig pin2 to output mode
  pinMode(ECHO_PIN2, INPUT);   // set echo pin2 to input mode
  pinMode(OPTO2, OUTPUT); // set OPTO2 pin to output mode
}

void loop() {
   
  // generate 10-microsecond pulse to TRIG1 pin
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);
  // measure duration of pulse from ECHO1 pin
  duration_us1 = pulseIn(ECHO_PIN1, HIGH);
  // calculate the distance
  distance_cm1 = 0.017 * duration_us1;

 delay(300);

  // generate 10-microsecond pulse to TRIG2 pin
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  // measure duration of pulse from ECHO2 pin
  duration_us2 = pulseIn(ECHO_PIN2, HIGH);
  // calculate the distance
  distance_cm2 = 0.017 * duration_us2;
   delay(300);

if (distance_cm1 >= 10 && distance_cm2 >= 10) {       // ako je udaljenost od senzora veća od 10cm
                      
      digitalWrite(OPTO1, LOW);    // 
       digitalWrite(OPTO2, LOW);
      tft.setRotation(3); // postavi orijentaciju 
tft.fillScreen(ILI9341_BLUE); // boja zaslona 
tft.setTextColor(ILI9341_YELLOW); // boja teksta 
tft.setCursor(5, 105); // polozaj pocetka ispisa tekst 
tft.setTextSize(4); // velicina teksta 
tft.print("CEKANJE STARTA MOTORA"); // ispis teksta 
    } 
     if (distance_cm1 < 10) {                 // Ako se lijevi senzor aktivira prvo
     digitalWrite(OPTO1, HIGH);     
    digitalWrite(OPTO2, LOW);
    tft.fillScreen(ILI9341_BLUE); // boja zaslona 
    tft.setCursor(25, 85); // polozaj pocetka ispisa tekst 
tft.setTextSize(3); // velicina teksta 
tft.print("ROTACIJA MOTORA LIJEVO"); // ispis teksta 
    }
      if (distance_cm2 < 10) { //Ako se desni senzor aktivira prvo
      digitalWrite(OPTO2, HIGH);     
    digitalWrite(OPTO1, LOW);
     tft.fillScreen(ILI9341_BLUE); // boja zaslona 
    tft.setCursor(25, 85); // polozaj pocetka ispisa tekst 
tft.setTextSize(3); // velicina teksta 
tft.print("ROTACIJA MOTORA DESNO"); // ispis teksta 
}


   //print the value to Serial Monitor
  Serial.print("Udaljenost od senzora Lijevo ");
  Serial.print(distance_cm1);
   Serial.println(" cm");
    Serial.print("Udaljenost od senzora Desno ");
  Serial.print(distance_cm2);
  Serial.println(" cm");
  delay(500);
}
