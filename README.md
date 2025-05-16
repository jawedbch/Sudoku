# Sudoku Multithread

Ce projet implémente un générateur et un solveur de Sudoku en C, utilisant la programmation multithread avec `pthread`.

---

## Fonctionnalités

- Génération d'une grille Sudoku valide avec un nombre de cases vides choisi.
- Résolution du Sudoku à l'aide d'un algorithme backtracking.
- Utilisation de threads pour explorer les solutions possibles en parallèle.
- Affichage de la grille initiale et de la solution trouvée.

---

## Structure du projet

- `main.c` : point d'entrée du programme, gestion de la génération, gestion de la résolution multithread, résolution et affichage.
- `sudoku.h` : déclarations des fonctions liées à la grille.
- `libsudoku.so` : bibliothèque dynamique fournissant des fonctions de manipulation de grille (init, free, print, get, set).
- `Makefile` : compilation et exécution facilitée.

---

## Compilation et exécution

1. Assurez-vous que `libsudoku.so` est dans le dossier courant.

2. Compilez avec :

   ```bash
   make build
   
3. Exécutez avec :

   ```bash
   make run ou make run ARG=n (17<n<81)

Exemple d'utilisation :

+-------+-------+-------+
| 9 . . | . 8 3 | 5 . 6 |
| . 4 2 | . 7 5 | . . . |
| 5 . 6 | . 2 1 | . . 8 |
+-------+-------+-------+
| . 5 7 | . . . | 8 3 9 |
| 2 1 3 | . 9 8 | . 4 7 |
| 6 8 . | 3 4 . | . 5 . |
+-------+-------+-------+
| . 2 4 | 7 . 6 | 9 . 5 |
| 7 . 5 | . . . | 3 . . |
| 3 . 8 | 2 . . | . 1 4 |
+-------+-------+-------+
Au moins une solution trouvée.

Solution trouvée :
+-------+-------+-------+
| 9 7 1 | 4 8 3 | 5 2 6 |
| 8 4 2 | 6 7 5 | 1 9 3 |
| 5 3 6 | 9 2 1 | 4 7 8 |
+-------+-------+-------+
| 4 5 7 | 1 6 2 | 8 3 9 |
| 2 1 3 | 5 9 8 | 6 4 7 |
| 6 8 9 | 3 4 7 | 2 5 1 |
+-------+-------+-------+
| 1 2 4 | 7 3 6 | 9 8 5 |
| 7 9 5 | 8 1 4 | 3 6 2 |
| 3 6 8 | 2 5 9 | 7 1 4 |
+-------+-------+-------+



     
