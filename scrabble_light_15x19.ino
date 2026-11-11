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

// --- ANIMATION ARC-EN-CIEL EN DIAGONALE ---
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

void dessinerPlateauScrabble() {
  FastLED.clear();

  // 1. Remplir TOUTES les LED du plateau en blanc (fond général et espaces intermédiaires)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = C_BLANCHE;
  }

  // 2. Superposer les couleurs officielles des cases spéciales du Scrabble aux bons endroits
  for (int y_logique = 0; y_logique < 15; y_logique++) {
    int y_physique = obtenirLedPhysique(y_logique);

    for (int x = 0; x < 15; x++) {
      int index = XY(x, y_physique);

      // Attribution géométrique des cases spéciales du Scrabble
      if ((y_logique == 0 || y_logique == 7 || y_logique == 14) && (x == 0 || x == 7 || x == 14)) {
        if (x == 7 && y_logique == 7) {
          leds[index] = C_START;   // Case Départ au centre
        } else {
          leds[index] = C_MTRIPLE; // Mots Compte Triple
        }
      }
      else if (y_logique == 1 || y_logique == 13) {
        if (x == 5 || x == 9) leds[index] = C_LTRIPLE;
        else if (x == 1 || x == 13) leds[index] = C_MDOUBLE;
      }
      else if (y_logique == 2 || y_logique == 12) {
        if (x == 2 || x == 12) leds[index] = C_MDOUBLE; // Corrigé : M2 (Violet)
        else if (x == 6 || x == 8) leds[index] = C_LDOUBLE; // Corrigé : L2 (Cyan)
      }
      else if (y_logique == 3 || y_logique == 11) {
        if (x == 0 || x == 7 || x == 14) leds[index] = C_LDOUBLE;
        else if (x == 3 || x == 11) leds[index] = C_MDOUBLE;
      }
      else if (y_logique == 4 || y_logique == 10) {
        if (x == 4 || x == 10) leds[index] = C_MDOUBLE; // Corrigé : M2 (Violet) au lieu de L2
      }
      else if (y_logique == 5 || y_logique == 9) {
        if (x == 1 || x == 5 || x == 9 || x == 13) leds[index] = C_LTRIPLE;
      }
      else if (y_logique == 6 || y_logique == 8) {
        if (x == 2 || x == 6 || x == 8 || x == 12) leds[index] = C_LDOUBLE;
      }
      else if (y_logique == 7) {
        if (x == 0 || x == 14) leds[index] = C_MTRIPLE;
        else if (x == 3 || x == 11) leds[index] = C_LDOUBLE;
        else if (x == 7) leds[index] = C_START;
      }
    }
  }
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  
  // 1. Lance l'animation en diagonale dès l'allumage
  animationArcEnCielDiagonale();
  
  // 2. Affiche ensuite le plateau de Scrabble figé
  dessinerPlateauScrabble();
  FastLED.show();
}

void loop() {
  delay(1000);
}