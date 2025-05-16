#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "sudoku.h"

#define N 9
#define NON_ASSIGNE 0

typedef struct {
    int **sudoku;
    int ligne;
    int colonne;
    int valeur;
    int *solution_trouvee;
    pthread_mutex_t *mutex;
} DonneesThread;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Utilisation: %s num_a_laisser\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int num_a_laisser = atoi(argv[1]);
    if (num_a_laisser < 17 || num_a_laisser > 81) {
        fprintf(stderr, "Le chiffre doit être entre 17 et 81\n");
        return EXIT_FAILURE;
    }
    
    int **sudoku = sudoku_init();
    srand(time(NULL));
    
    generer_sudoku_valide(sudoku);
    retirer_nombres(sudoku, num_a_laisser);
    
    sudoku_print(sudoku);
    
    if(verifier_toutes_solutions(sudoku, 0, 0)) {
        printf("Au moins une solution trouvée.\n");
    } else {
        printf("Aucune solution trouvée.\n");
    }
    
    // Copier la grille sudoku dans une nouvelle grille solution
int **solution = sudoku_init();
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        sudoku_set(solution, i, j, sudoku_get(sudoku, i, j));
    }
}

// Résoudre la grille solution
if (resoudre_sudoku(solution, 0, 0)) {
    printf("\nSolution trouvée :\n");
    sudoku_print(solution);
} else {
    printf("\nAucune solution possible.\n");
}

sudoku_free(solution);

    
    sudoku_free(sudoku);
    
    return EXIT_SUCCESS;
}

void generer_sudoku_valide(int **sudoku) {
    genererSudoku(sudoku);
}

int genererSudoku(int **sudoku) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sudoku_get(sudoku, i, j) == NON_ASSIGNE) {
                int chiffres[9] = {1,2,3,4,5,6,7,8,9};

                // Mélanger le tableau chiffres
                for (int k = 8; k > 0; k--) {
                    int r = rand() % (k+1);
                    int temp = chiffres[k];
                    chiffres[k] = chiffres[r];
                    chiffres[r] = temp;
                }

                for (int idx = 0; idx < 9; idx++) {
                    int num = chiffres[idx];
                    if (est_sur(sudoku, i, j, num)) {
                        sudoku_set(sudoku, i, j, num);
                        if (genererSudoku(sudoku)) {
                            return 1;
                        }
                        sudoku_set(sudoku, i, j, NON_ASSIGNE);
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}


int est_sur(int **sudoku, int ligne, int colonne, int num) {
    for (int x = 0; x < N; x++) {
        if (sudoku_get(sudoku, ligne, x) == num) return 0;
        if (sudoku_get(sudoku, x, colonne) == num) return 0;
    }
    int start_ligne = ligne - ligne % 3;
    int start_colonne = colonne - colonne % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku_get(sudoku, start_ligne + i, start_colonne + j) == num)
                return 0;
        }
    }
    return 1;
}

int resoudre_sudoku(int **sudoku, int ligne, int colonne) {
    if (ligne == N - 1 && colonne == N) return 1;
    if (colonne == N) {
        ligne++;
        colonne = 0;
    }
    if (sudoku_get(sudoku, ligne, colonne) != NON_ASSIGNE) {
        return resoudre_sudoku(sudoku, ligne, colonne + 1);
    }
    for (int num = 1; num <= N; num++) {
        if (est_sur(sudoku, ligne, colonne, num)) {
            sudoku_set(sudoku, ligne, colonne, num);
            if (resoudre_sudoku(sudoku, ligne, colonne + 1)) return 1;
            sudoku_set(sudoku, ligne, colonne, NON_ASSIGNE);
        }
    }
    return 0;
}

void retirer_nombres(int **sudoku, int num_a_laisser) {
    int total_cellules = 81;
    int cellules_a_retirer = total_cellules - num_a_laisser;
    
    while (cellules_a_retirer > 0) {
        int id_cellule = rand() % total_cellules;
        int ligne = id_cellule / 9;
        int colonne = id_cellule % 9;
        
        int valeur_originale = sudoku_get(sudoku, ligne, colonne);
        if (valeur_originale == 0) continue;
        
        sudoku_set(sudoku, ligne, colonne, 0);
        
        if (!a_solution_unique(sudoku)) {
            sudoku_set(sudoku, ligne, colonne, valeur_originale);
        } else {
            cellules_a_retirer--;
        }
    }
}

int a_solution_unique(int **sudoku) {
    int compte_solution = 0;
    resoudre_et_compter_solutions(sudoku, 0, 0, &compte_solution);
    return compte_solution == 1;
}

void resoudre_et_compter_solutions(int **sudoku, int ligne, int colonne, int *compte_solution) {
    if (*compte_solution > 1) return;
    if (ligne == N) {
        (*compte_solution)++;
        return;
    }
    if (colonne == N) {
        resoudre_et_compter_solutions(sudoku, ligne + 1, 0, compte_solution);
        return;
    }
    if (sudoku_get(sudoku, ligne, colonne) != NON_ASSIGNE) {
        resoudre_et_compter_solutions(sudoku, ligne, colonne + 1, compte_solution);
        return;
    }
    
    for (int num = 1; num <= N; num++) {
        if (est_sur(sudoku, ligne, colonne, num)) {
            sudoku_set(sudoku, ligne, colonne, num);
            resoudre_et_compter_solutions(sudoku, ligne, colonne + 1, compte_solution);
            sudoku_set(sudoku, ligne, colonne, NON_ASSIGNE);
        }
    }
}

void* resoudre_thread(void *arg) {
    DonneesThread *donnees = (DonneesThread *)arg;
    int **sudoku = donnees->sudoku;
    int ligne = donnees->ligne;
    int colonne = donnees->colonne;
    int valeur = donnees->valeur;

    if (est_sur(sudoku, ligne, colonne, valeur)) {
        sudoku_set(sudoku, ligne, colonne, valeur);
        if (resoudre_sudoku(sudoku, 0, 0)) {
            pthread_mutex_lock(donnees->mutex);
            *(donnees->solution_trouvee) = 1;
            pthread_mutex_unlock(donnees->mutex);
        }
        sudoku_set(sudoku, ligne, colonne, 0);
    }

    return NULL;
}

int verifier_toutes_solutions(int **sudoku, int ligne, int colonne) {
    pthread_t threads[9];
    DonneesThread donnees_thread[9];
    int solution_trouvee = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    int thread_count = 0;
    for (int num = 1; num <= 9; num++) {
        if (sudoku_get(sudoku, ligne, colonne) == num) continue;
        
        donnees_thread[thread_count].sudoku = sudoku;
        donnees_thread[thread_count].ligne = ligne;
        donnees_thread[thread_count].colonne = colonne;
        donnees_thread[thread_count].valeur = num;
        donnees_thread[thread_count].solution_trouvee = &solution_trouvee;
        donnees_thread[thread_count].mutex = &mutex;
        
        pthread_create(&threads[thread_count], NULL, resoudre_thread, &donnees_thread[thread_count]);
        thread_count++;
    }
    
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return solution_trouvee;
}

