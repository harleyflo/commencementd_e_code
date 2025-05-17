#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
//ecran
// Définissez les broches de connexion
#define TFT_CS 10
#define TFT_RST 6
#define TFT_DC 12

// #define PWM A2

// Créez une instance de l'écran
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//bouton
int Valeur_num;
float Tension;

void setup() {
  //bouton
  Serial.begin(9600);

  //ecran
  // pinMode(PWM, INPUT);
  //  analogWrite(PWM, 20);

  Serial.begin(9600);
  tft.begin();         // Initialise l'écran
  tft.setRotation(1);  // Définissez l'orientation de l'écran

  // Efface l'écran avec une couleur de fond
  tft.fillScreen(ILI9341_BLACK);

  // Afficher du texte
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Hello,World!");

  delay(2000);



  // Dessinez quelques formes
  // tft.fillRect(10, 30, 100, 50, ILI9341_RED);      // Rectangle rouge
  //tft.drawCircle(150, 60, 30, ILI9341_ORANGE);     // Cercle bleu
  //tft.drawLine(10, 100, 200, 100, ILI9341_GREEN);  // Ligne verte
}

void loop() {

 // tft.clear();

  Valeur_num = analogRead(A4);
  tft.print("valeur_num = ");
  tft.println(Valeur_num);

  Tension = Valeur_num * (3.3 / 1024.0);
  tft.print("tension = ");
  tft.print(Tension);
  tft.println(" V");

  delay(1000);
}
