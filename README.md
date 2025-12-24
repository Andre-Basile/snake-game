# Snake Console Game (C++)

Bienvenue dans mon projet de **Snake** en console ! C'est un jeu développé en C++ qui permet de jouer au célèbre serpent directement dans votre terminal. Ce projet m'a permis de mettre en pratique la manipulation de tableaux dynamiques (vecteurs) et la logique de jeu procédurale.

## 🚀 Fonctionnalités
* **Construction de niveau personnalisée** : Dessinez votre propre aire de jeu en plaçant les murs, le serpent et les items.
* **Mouvements fluides** : Déplacement dans les quatre directions (Haut, Bas, Gauche, Droite).
* **Croissance dynamique** : Le serpent grandit à chaque fois qu'il mange un item `*`.
* **Système de Score** : Votre score final est basé sur le nombre d'items mangés.
* **Mode Furtif** : L'affichage nettoie les points de vide pour une meilleure visibilité.

## 🎮 Comment jouer ?

### 1. Prérequis
Vous devez avoir un compilateur C++ installé (comme `g++`).

### 2. Compilation
Ouvrez votre terminal et lancez la commande suivante :
g++ main.cpp -o snake

Exécution
Lancez le jeu avec :
./snake

Commandes
Le jeu vous demandera d'entrer une direction après chaque mouvement :

U : Haut (Up)

D : Bas (Down)

L : Gauche (Left)

R : Droite (Right)

🛠️ Détails Techniques

Le projet utilise plusieurs concepts clés du C++ :

Vecteurs 2D : Pour représenter la grille de jeu (vector<vector<char>>).

Logique de collision : Vérification des murs (#) et du propre corps du serpent (O).

Gestion du buffer : Utilisation de cin.clear() et cin.ignore() pour une saisie utilisateur robuste.

📝 Licence

Ce projet est sous licence LGPL (GNU Lesser General Public License). Vous pouvez l'utiliser et le modifier librement, tant que les améliorations apportées à la bibliothèque elle-même restent libres.



👤 Auteur
© 2025 – André KOVOHOUANDE
