<img width="64" height="64" alt="icons8-scrabble-64" src="https://github.com/user-attachments/assets/e4073b6b-355d-4622-850d-9617bda9256e" /> **SCRABBLE RETRO-ECLAIRE**



Ce dispositif permet de pimper votre jeu de scrabble avec un peu de RGB parce que tout le monde adore ça ;)
<img width="1461" height="1940" alt="PXL_20261111_092327948" src="https://github.com/user-attachments/assets/f7ce3347-965a-417a-b5ab-4d9f123c3246" />


**Matériel utilisé :**
  - ESP32 CP 2012
  - ESP32 GPIO Breakout Board 25,5 mm x 38 Pins
  - Ruban LED adressable WS2812B (5V)
  - Alimentation secteur 5V DC 8A
  - Connecteur femelle 12v de 5,5 × 2,1 mm
  - Prototype board
  - BTF-LIGHTING SMD 3pin 10mm LED Connecteur kit
  - Condensateur Électrolytiques 1000uF
  - Résistance 330 ohm
  - Jeu scrabble édition 60ème anniversaire (car plateau déjà transparent dépoli)
  - Plaque plexyglass 40x36cm
  - Entretoises m3

L'espace entre les leds du bandeau ne permettant pas de faire une matrice 15x15, c'est un tableau de 19 leds par lignes pour 15 colonnes.

<img width="617" height="640" alt="Capture d&#39;écran 2026-11-11 093501" src="https://github.com/user-attachments/assets/ed3bfa29-cb55-4048-8b56-892c435a0974" />


**Etapes de réalisation :**
1) Découpage du bandeau led
2) Assemblage du zigzag de leds avec les connecteurs 3 pins (Attention de respecter le sens du courant du bandeau)
<img width="899" height="1599" alt="IMG-20261106-WA0002" src="https://github.com/user-attachments/assets/7c0a85a1-c4ae-404a-b513-d87a7e4207a9" />

3) Souder en respectant le montage suivant 
<img width="494" height="202" alt="image" src="https://github.com/user-attachments/assets/8671a471-15a9-4494-ac8a-79c6f2d702ba" />


4) Coller le bandeau sur la plaque de plexyglass (prévoir des trous pour tomber sur les vis du plateau de jeu et de quoi fixer l'électronique aussi.)
<img width="1034" height="1113" alt="IMG-20261109-WA0001~2" src="https://github.com/user-attachments/assets/f72309a2-2618-4b2c-a44a-378627229b4b" />

5) Brancher l'ESP32 et téleverser le code sur le bon port COM.
6) Lier la plaque au plateau
7) Jouer !
<img width="3072" height="1249" alt="PXL_20261110_222309314" src="https://github.com/user-attachments/assets/5b39894f-8384-4163-86f5-3c3739d19b13" />


**Tips:** pensez à coller au pistolet a colle les connecteurs entre les bandes leds sur la plaque pour éviter que le bandeau se décolle à long terme.

Beaucoup d'améliorations sont possibles, c'est un prototype. 
