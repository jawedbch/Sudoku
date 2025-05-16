#pragma once

/* Création d'une grille de sudoku */
int **sudoku_init();

/* Libération de la mémoire allouée pour la grille */
void sudoku_free(int **sudoku);

/* Affichage de la grille */
void sudoku_print(int **sudoku);

/* Récupération de la valeur d'une case (si la case est vide, renvoit 0) */
int sudoku_get(int **sudoku, int x, int y);

/* Modification de la valeur d'une case */
void sudoku_set(int **sudoku, int x, int y, int value);

/* Générer un sudoku valide */
void generer_sudoku_valide(int **sudoku);

/* Remplir les cases vides */
int genererSudoku(int **sudoku);

/* Resoudre le sudoku */
int resoudre_sudoku(int **sudoku, int ligne, int colonne);

/* Verifier si un nmbr peut etre placé dans une case */
int est_sur(int **sudoku, int ligne, int colonne, int num);

/* Supprimer les nombres */
void retirer_nombres(int **sudoku, int num_à_laisser);

/* Verifier s'il y a une solution unique */
int a_solution_unique(int **sudoku);

/* Resoudre et compter le nombre de solutions */
void resoudre_et_compter_solutions(int **sudoku, int ligne, int colonne, int *compte_solution);

/* Résoudre le sudoku en utilisant les threads */
void* resoudre_thread(void *arg);

/* Verifier les solutions possibles */
int verifier_toutes_solutions(int **sudoku, int ligne, int colonne);