#include <FastLED.h>

// --- CONFIGURATION DU MATÉRIEL ---
#define LED_PIN      23         // Broche GPIO connectée à la résistance (Data)
#define COLS         15         // 15 colonnes sur le plateau
#define LEDS_PAR_COL 19         // 19 LED physiques par colonne (fixe)
#define NUM_LEDS     (COLS * LEDS_PAR_COL) // 15 x 19 = 285 LED au total
#define BRIGHTNESS   80         // Luminosité globale (0 à 255)
#define LED_TYPE     WS2812B
#define COLOR_ORDER  GRB

CRGB leds[NUM_LEDS];

// --- DÉFINITION DES COULEURS ---
#define C_BLANCHE    CRGB(25, 25, 25)         // Fond général / espaces (blanc tamisé)
#define C_MTRIPLE    CRGB(255, 0, 0)          // Mot Compte Triple (Rouge vif)
#define C_MDOUBLE    CRGB(141, 0, 171)        // Mot Compte Double (Violet plus foncé et soutenu)
#define C_LTRIPLE    CRGB(14, 0, 171)         // Lettre Compte Triple (Bleu foncé / nuit)
#define C_LDOUBLE    CRGB(0, 220, 255)        // Lettre Compte Double (Cyan lumineux pour contraster)
#define C_START      CRGB(255, 200, 0)        // Case Départ / Étoile centrale (Or lumineux)

// --- VARIABLES POUR LA TEMPO DE LA GOUTTE D'EAU ---
unsigned long dernierDeclenchement = 0;
const unsigned long INTERVALLE_GOUTTE = 120000; // 2 minutes en millisecondes (2 * 60 * 1000)

// --- FONCTION DE GESTION DU ZIGZAG (15 colonnes de 19 LED) ---
int XY(int x, int y_physique) {
  int i;
  if (x % 2 == 0) {
    i = (x * LEDS_PAR_COL) + y_physique;
  } else {
    i = (x * LEDS_PAR_COL) + (LEDS_PAR_COL - 1 - y_physique);
  }
  return i;
}

// --- TABLEAU DE CORRESPONDANCE (15 lignes logiques -> 19 LED physiques) ---
int obtenirLedPhysique(int y_logique) {
  const int mapping[15] = {
    0,  // Ligne 0
    1,  // Ligne 1
    2,  // Ligne 2
    3,  // Ligne 3
    5,  // Ligne 4  (Espace de 1 LED blanche en index 4)
    6,  // Ligne 5
    7,  // Ligne 6
    9,  // Ligne 7  (Centre - Espace en index 8)
    11, // Ligne 8  (Espace en index 10)
    12, // Ligne 9
    13, // Ligne 10
    15, // Ligne 11 (Espace en index 14)
    16, // Ligne 12
    17, // Ligne 13
    18  // Ligne 14
  };
  return mapping[y_logique];
}

// Fonction pour obtenir la couleur d'une case spécifique du Scrabble
CRGB obtenirCouleurCase(int x, int y_logique) {
  // Attribution géométrique des cases spéciales du Scrabble
  if ((y_logique == 0 || y_logique == 7 || y_logique == 14) && (x == 0 || x == 7 || x == 14)) {
    if (x == 7 && y_logique == 7) return C_START;
    else return C_MTRIPLE;
  }
  else if (y_logique == 1 || y_logique == 13) {
    if (x == 5 || x == 9) return C_LTRIPLE;
    else if (x == 1 || x == 13) return C_MDOUBLE;
  }
  else if (y_logique == 2 || y_logique == 12) {
    if (x == 2 || x == 12) return C_MDOUBLE;
    else if (x == 6 || x == 8) return C_LDOUBLE;
  }
  else if (y_logique == 3 || y_logique == 11) {
    if (x == 0 || x == 7 || x == 14) return C_LDOUBLE;
    else if (x == 3 || x == 11) return C_MDOUBLE;
  }
  else if (y_logique == 4 || y_logique == 10) {
    if (x == 4 || x == 10) return C_MDOUBLE;
  }
  else if (y_logique == 5 || y_logique == 9) {
    if (x == 1 || x == 5 || x == 9 || x == 13) return C_LTRIPLE;
  }
  else if (y_logique == 6 || y_logique == 8) {
    if (x == 2 || x == 6 || x == 8 || x == 12) return C_LDOUBLE;
  }
  else if (y_logique == 7) {
    if (x == 0 || x == 14) return C_MTRIPLE;
    else if (x == 3 || x == 11) return C_LDOUBLE;
    else if (x == 7) return C_START;
  }
  return C_BLANCHE; // Case neutre
}

void dessinerPlateauScrabble() {
  FastLED.clear();

  // 1. Remplir TOUTES les LED du plateau en blanc (fond général et espaces intermédiaires)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = C_BLANCHE;
  }

  // 2. Superposer les couleurs officielles des cases spéciales du Scrabble
  for (int y_logique = 0; y_logique < 15; y_logique++) {
    int y_physique = obtenirLedPhysique(y_logique);
    for (int x = 0; x < 15; x++) {
      int index = XY(x, y_physique);
      leds[index] = obtenirCouleurCase(x, y_logique);
    }
  }
}

// --- ANIMATION ARC-EN-CIEL EN DIAGONALE (au démarrage) ---
void animationArcEnCielDiagonale() {
  for (int j = 0; j < 120; j++) {
    for (int x = 0; x < COLS; x++) {
      for (int y_physique = 0; y_physique < LEDS_PAR_COL; y_physique++) {
        int index = XY(x, y_physique);
        uint8_t hue = (x * 12 + y_physique * 12 + j * 4);
        leds[index] = CHSV(hue, 255, 255);
      }
    }
    FastLED.show();
    delay(25);
  }
}

// --- ANIMATION GOUTTE D'EAU DEPUIS LE CENTRE ---
void animationGoutteD_Eau() {
  int centreX = 7;
  int centreY = 7;
  float maxDistance = 10.0; // Distance max approximative du centre vers les coins

  // On fait grandir l'onde du centre vers l'extérieur
  for (float rayon = 0; rayon < maxDistance; rayon += 0.5) {
    
    // On redessine le plateau de base en arrière-plan
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = C_BLANCHE;
    }
    for (int y_logique = 0; y_logique < 15; y_logique++) {
      int y_physique = obtenirLedPhysique(y_logique);
      for (int x = 0; x < 15; x++) {
        int index = XY(x, y_physique);
        leds[index] = obtenirCouleurCase(x, y_logique);
      }
    }

    // On illumine ou on fait briller les cases qui forment le contour de l'onde
    for (int y_logique = 0; y_logique < 15; y_logique++) {
      int y_physique = obtenirLedPhysique(y_logique);
      for (int x = 0; x < 15; x++) {
        // Calcul de la distance géométrique par rapport au centre (7, 7)
        float distance = sqrt(pow(x - centreX, 2) + pow(y_logique - centreY, 2));

        // Si la case se trouve sur le front de l'onde (avec une petite épaisseur)
        if (abs(distance - rayon) < 0.8) {
          int index = XY(x, y_physique);
          // On prend la vraie couleur de la case du jeu, mais on la booste en blanc/lumineux pour l'effet d'onde
          CRGB couleurOrigine = obtenirCouleurCase(x, y_logique);
          leds[index] = couleurOrigine + CRGB(120, 120, 120); // Effet flash lumineux conservant la teinte
        }
      }
    }
    FastLED.show();
    delay(50); // Vitesse d'expansion de l'onde
  }

  // À la fin de l'animation, on remet proprement le plateau figé normal
  dessinerPlateauScrabble();
  FastLED.show();
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  
  // 1. Lance l'animation en diagonale dès l'allumage
  animationArcEnCielDisagonaleSiBesoin : // (juste l'appel normal ci-dessous)
  animationArcEnCielDiagonale();
  
  // 2. Affiche ensuite le plateau de Scrabble figé et initialise le chrono
  dessinerPlateauScrabble();
  FastLED.show();
  dernierDeclenchement = millis();
}

void loop() {
  // Vérifie si 2 minutes se sont écoulées
  if (millis() - dernierDeclenchement >= INTERVALLE_GOUTTE) {
    animationGoutteD_Eau();
    dernierDeclenchement = millis(); // On reset le chronomètre
  }
  
  // Petite pause pour ne pas surcharger le processeur de l'ESP32 / Arduino
  delay(100);
}