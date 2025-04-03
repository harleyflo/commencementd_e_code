#include <I2S.h>

const int frequency = 440;    //defini la frequence en Hz
const int amplitude = 500;    //defini l'amplitude
const int sampleRate = 8000;  //sample rate en Hz

const int halfWavelength = (sampleRate / frequency);
const int boutonAnalogPin = A0;  // Broche analogique utilisée pour lire la valeur

// Définir les valeurs de résistance pour chaque bouton
const int resistanceBoutons[] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000 };  // en ohms
const int nombreBoutons = 8;

short sample = amplitude;
// Tableaux pour enregistrer les valeurs des boutons
int boutonValues[nombreBoutons];
int lastBoutonState[nombreBoutons];
int count = 0;

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);

  // Initialisation des boutons (lecture analogique)
  for (int i = 0; i < nombreBoutons; i++) {
    boutonValues[i] = 0;
    lastBoutonState[i] = 0;

    //initialisation du module son sur 16-bits
    if (!I2S.begin(I2S_PHILIPS_MODE, sampleRate, 16)) {
      Serial.print("erreur dinisialisation I2S!");
      while (1)
        ;
    }
  }

  Serial.println("Test des boutons commencé...");
}

void loop() {
  if (count % halfWavelength == 0) {
    sample = -1 * sample;
  }

  I2S.write(sample);
  I2S.write(sample);

  count++;

  // Lire la valeur analogique de la broche
  int analogValue = analogRead(boutonAnalogPin);

  // Afficher la valeur lue
  Serial.print("Valeur lue : ");
  Serial.println(analogValue);

  // Vérifier quel bouton est pressé en fonction de la valeur lue
  for (int i = 0; i < nombreBoutons; i++) {
    // Calculer la plage de valeurs analogiques correspondant à chaque bouton (ajuster selon les résistances)
    int seuilMin = i * 100;
    int seuilMax = (i + 1) * 100;

    // Vérifier si la valeur lue correspond à l'un des boutons
    if (analogValue >= seuilMin && analogValue < seuilMax) {
      if (lastBoutonState[i] == 0) {  // Si le bouton n'a pas encore été détecté comme pressé
        Serial.print("Bouton ");
        Serial.print(i + 1);  // Afficher le numéro du bouton (1 à 8)
        Serial.println(" appuyé !");
        lastBoutonState[i] = 1;  // Mettre à jour l'état du bouton
      }
    } else {
      lastBoutonState[i] = 0;  // Réinitialiser l'état du bouton si ce n'est pas pressé
    }
  }

  delay(100);  // Délai pour éviter de trop lire rapidement
}