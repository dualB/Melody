# Librairie Melody

Cette librairie instaure un système de notation simple mais complet afin d'écrire des mélodies (suite de notes musicales à une seule voix) dans le but de faciliter le pont entre la notation musicale et la génération du son.

## Raison d'être de la librairie

D'un côté, la notation musicale permet d'écrire une suite de notes, selon des standards connus depuis longtemps; on y utilise des lettres et des symboles afin de nommer les notes, spécifier des changements de rythmes ou des altérations (dièses, bémols), ou même des répétitions.

De l'autre côté, la génération d'un son avec Arduino (habituellement à l'aide d'un buzzer), doit plutôt être exprimé par la fréquence du son (en Hz), sa durée (en millisecondes) et son intensité sonore (qui dépend du matériel utilisé).

En tant que musicien, écrire de la musique pour Arduino, en terme de Hz et de millisecondes est définitivement un frein et alourdit l'écriture, tout en ne mettant pas à profit la notation musicale déjà très riche. La librairie Melody vient faire le pont entre les deux.

## La notation MELO

La notation MELO (pour Melody) est un format textuel qui permet l'écriture simplifié d'une mélodie à une voix. Cette notation s'inspire notamment de la notation musicale standard.

### Mélodie

La mélodie est la forme de base de la notation. Elle est formée d'une suite de note ou de groupe de notes, suivi de modificateur. On peut espacer ou non ces suites de notes ou groupes. Chaque modifieur viendra modifier la note ou le groupe de notes qui le précède.

![Mélodie](sequence.svg)

#### Exemples

- "cdefgab"
- "c d e f  g a b"
- "c_ c c*"
- "c\* d\* e\* f\*" est équivalent à "(cdef)\*"

### Note

Une note est représenté par une lettre (majuscule ou minuscule), selon la nomenclature standard C (do), D (ré), E (mi) F (fa), G (sol), A (la), B (si). On ajoute également la lettre R (rest) pour les silences. Par défaut, les notes sont celles de la 4e octave, où la note LA est de fréquence 440 Hz; elles ont toutes une durée relative de 1.

![Note](note.svg)

#### Exemples

- "c d r" est équivalent à "C D R"

### Group

Un groupe permet facilement d'appliquer un modifieur à toute une mélodie d'un seul coup, afin d'alléger l'écriture. Un groupe est délimité par une paire de parenthèses.

![Group](group.svg)

### Modifier

Un modifieur est une suite d'altération qui permet de modifier la hauteur, la durée, le nombre de répétition ou l'intensité sonore d'une note ou d'un groupe de notes. On peut spécifier plusieurs modifieurs de suite; ils ont la propriétés d'être commutatif, c'est-à-dire que l'ordre dans lequel on les écrit n'aura pas d'importance.

![Modifier](modifier.svg)

#### Exemples
- c+
- c+.
- d*
- d,
- d**
- d

### Pitch

Un modifieur de hauteur du son permet d'augmenter ou d'abaisser une note d'un demi-ton ou d'un octave.

![Pitch](pitch.svg)

### Duration

Un modifieur de durée permet de multiplier la durée d'une note par un facteur simple (2, ½ ou ¾); il permet aussi de spécifier plus précisément n'importe quel type de pondération du temps (par exemple, pour les triolets). Par défaut, les notes ont toutes une durée de 1.

![Duration](duration.svg)

### Repetition

Un modifieur de répétition permet de spécifier un nombre de répétition consécutifs pour la note ou le groupe de notes concernés.

![Repetition](repetition.svg)

### Loudness

Un modifieur d'intensité sonore permet d'augmenter ou de diminuer la force du son. Une note a, par défaut, une intensité de 0; on peut donc avec des valeurs positives ou négatives. Puisque l'intensité sonore réelle dépend du matériel utilisé, il est suggéré d'utiliser une échelle relative allant de -3 (ppp) à +3 (fff).

![Loudness](loudness.svg)

### Integer

Un nombre entier doit être strictement positif (ne peut pas valoir zéro).
![Integer](integer.svg)

### Space

Les espaces permis incluent les caractères couramment utilisé comme espaceur; on y ajoute la barre verticale '|', car elle est souvent utilisée en notation musicale pour repérer les mesures et faciliter la lecture. Ces espaces sont facultatifs.

![Space](space.svg)


## Exemples
On doit fournir au Melody un score musical (chaîne de texte) qui est une suite de plusieurs notes. Dans la chaîne de texte, les notes successives peuvent être facultativement séparés par un ou des espaces pour plus de clarté.

Par exemple :

```cpp
 "cdefgabr" 
 "c d   e   fg ab r" 
```
Ces scores donneront le même résultat.
#### NOTE 
- Valeurs possibles : C c D d E e F f G g A a B b R r
- Explication : le nom des notes réelles (C== do, B==si) et le 'r' pour un silence. Une majuscule ou un minuscule sont tous les deux acceptables.


----- à suivre.

### Une note

Chaque note doit avoir la nomenclature suivante  : 

**{OCTAVE}NOTE{ALTÉRATION}{DURÉE}**

{ } => optionel


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
#include <Melody.h>

const uint8_t PIN_BUZZER = 12;

Melody Melody(PIN_BUZZER);


void setup() {

  Melody.setScore("c d e f g a +c");

  Melody.setTempo(120);
  Melody.setLoundness(100);

  Melody.play();
}

void loop() {
  Melody.refresh();
}

```

## Constructeurs
```cpp
Melody(uint8_t pin);
```
On spécifie la broche sur laquelle est connectée le *buzzer*.

## Méthodes disponibles
```cpp
 void refresh()
```
Cette méthode doit être placée en début de boucle loop(): elle permet de mettre à jour l'état du Melody sans bloquer l'exécution du reste de la boucle.

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
Cette méthode permet de lire et modifier l'état actif du Melody (s'il joue ou non).
setPlaying(true) a le même effet que play(). 
setPlaying(false) a le même effet que stop(). 

---
```cpp
void setPause(bool value)
bool getPause()
```
Cette méthode permet de lire et modifier l'état de pause du Melody. Lorsqu'il est en pause, l'état actif est toujours vrai (getPlaying() retourne TRUE), mais le Melody est en attente avant de jouer la prochaine note.

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
void setScore(char *score)
char *getScore()
```
Cette méthode permet de lire et modifier le score du Melody, soit une chaîne de texte formaté selon la notation expliquée à la section 'Notation musicale'.
