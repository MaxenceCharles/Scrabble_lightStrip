Ce dispositf permet de pimper votre jeu de scrabble avec un peu de RGB parce que tout le monde adore ça ;)
<img width="1461" height="1940" alt="PXL_20261111_092327948" src="https://github.com/user-attachments/assets/f7ce3347-965a-417a-b5ab-4d9f123c3246" />


Matériel utilisé : 
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

Etapes de réalisation : 
1) Découpage du bandeau led
2) Assemblage du zigzag de leds avec les connecteurs 3 pins (Attention de respecter le sens du courant du bandeau)
<img width="899" height="1599" alt="IMG-20261106-WA0002" src="https://github.com/user-attachments/assets/7c0a85a1-c4ae-404a-b513-d87a7e4207a9" />
3) Souder en respectant le montage suivant 
<img width="494" height="202" alt="image" src="https://github.com/user-attachments/assets/8671a471-15a9-4494-ac8a-79c6f2d702ba" />

4) Coller le bandeau sur la plaque de plexyglass (prévoir des trous pour tomber sur les vis du plateau de jeu et de quoi fixer l'électronique aussi.)
<img width="1080" height="1920" alt="IMG-20261109-WA0001" src="https://github.com/user-attachments/assets/95d69efe-6525-42a0-8bfc-c3d0078502c2" />
5) Brancher l'ESP32 et téleverser le code sur le bon port COM.
6) Lier la plaque au plateau
7) Jouer !
<img width="1864" height="2475" alt="PXL_20261110_222309314" src="https://github.com/user-attachments/assets/7504f375-5d0a-4219-9523-8dea64fc051c" />

Tips: pensez à coller au pistolet a colle les connecteurs entre les bandes leds sur la plaque pour éviter que le bandeau se décolle à long terme.

Beaucoup d'améliorations sont possibles, c'est un prototype. 
