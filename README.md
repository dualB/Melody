# Librairie TGP MusicScribe

Cette bibliotheque permet de jouer des notes sur un *buzzer* (avertisseur sonore) en spécifiant une suite de note selon la nomenclature suivante : "{octave}NOTE{altération}{durée}".

Cette librairie nécessite la librairie [TGP Del](https://github.com/TechnoPhysCAL/TGP_Del), puisque le contrôle d'un *buzzer* s'apparente beaucoup à celui d'une del.

## Notation musicale

### Une partition
On doit fournir au MusicScribe une partition musicale (chaîne de texte) qui est une suite de plusieurs notes. Dans la chaîne de texte, les notes successives peuvent être facultativement séparés par un ou des espaces pour plus de clarté.

Par exemple :

```cpp
 "cdefgabs" 
 "c d   e   fg ab s" 
```
Ces partitions donneront le même résultat.

### Une note

Chaque note doit avoir la nomenclature suivante  : 

**{OCTAVE}NOTE{ALTÉRATION}{DURÉE}**

{ } => optionel

#### NOTE 
- Valeurs possibles : C c D d E e F f G g A a B b S s
- Explication : le nom des notes réelles (C== do, B==si) et le 's' pour un silence. Une majuscule ou un minuscule ne fait pas de différence.

#### OCTAVE
- Valeurs possibles :2 3 4 5 6 7 + -
- Explication : Valeur absolue de l'octave sur un clavier réel. Le + et le moins indique l'octave supérieur et l'octave inférieur à l'octave par défaut. Par défaut, octave de 4. 
 
#### ALTÉRATION
- Valeurs possibles : # _
- Explication : # pour un dièse (un demi-ton plus haut) ou _ pour un bémol (un demi-ton plus bas).

#### DURÉE
- Valeurs possibles : 1 2 3 4 5 6 7 8 $ ! %
- Explication : Valeur relative un temps de tempo, $ vaut 1/2, ! vaut 1/4 et % vaut 3/4. Par défaut, 1.

### Exemples
```cpp
 "c d e f g a b +c"  //Gamme majeure
 "c d e_ f g a_ b +c"  //Gamme mineure mélodique
 "cdec cdec efg2 efg2 g$a$g$f$ec   g$a$g$f$ec  c-gc2 c -g c2 "  //Frère Jacques
```

## Utilisation

```cpp
#include <MusicScribe.h>

const uint8_t PIN_BUZZER = 12;

MusicScribe MusicScribe(PIN_BUZZER);


void setup() {

  MusicScribe.setPartition("c d e f g a +c");

  MusicScribe.setTempo(120);
  MusicScribe.setLoundness(100);

  MusicScribe.play();
}

void loop() {
  MusicScribe.refresh();
}

```

## Constructeurs
```cpp
MusicScribe(uint8_t pin);
```
On spécifie la broche sur laquelle est connectée le *buzzer*.

## Méthodes disponibles
```cpp
 void refresh()
```
Cette méthode doit être placée en début de boucle loop(): elle permet de mettre à jour l'état du MusicScribe sans bloquer l'exécution du reste de la boucle.

---
```cpp
bool play()
```
Cette méthode permet de démarrer la musique.

---
```cpp
bool stop()
```
Cette méthode permet d'arrêter la musique.

---
```cpp
void setPlaying(bool value)
bool isPlaying()
```
Cette méthode permet de lire et modifier l'état actif du MusicScribe (s'il joue ou non).
setPlaying(true) a le même effet que play(). 
setPlaying(false) a le même effet que stop(). 

---
```cpp
void setPause(bool value)
bool getPause()
```
Cette méthode permet de lire et modifier l'état de pause du MusicScribe. Lorsqu'il est en pause, l'état actif est toujours vrai (getPlaying() retourne TRUE), mais le MusicScribe est en attente avant de jouer la prochaine note.

---
```cpp
void setTempo(int value)
int getTempo()
```
Cette méthode permet de lire et modifier le tempo de la musique, qui correspond au nombre de temps musicaux durant une minute. Par exemple, un tempo de 120 signifie qu'il y aura 120 notes de 1 temps joué durant 1 minute - ou que chaque note durera 0.5 seconde.

---
```cpp
void setLoudness(float percentage)
float getLoudness()
```
Cette méthode permet de lire et modifier l'intensité sonore du *buzzer*. La valeur attendue se situe entre 0.0 et 100.0.

---
```cpp
void setPartition(char *partition)
char *getPartition()
```
Cette méthode permet de lire et modifier la partition du MusicScribe, soit une chaîne de texte formaté selon la notation expliquée à la section 'Notation musicale'.
