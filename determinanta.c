#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void freeArray(int **a, int m)
{
    int i;
    for (i = 0; i < m; ++i)
    {
        free(a[i]);
    }
    free(a);
}

void kopirajMatriko(int** matrika, int** nova, int dim, int razvojY) {
    for (int i = 1; i < dim; i++) {
        bool cez = false;
        for (int j = 0; j < dim; j++) {
            if (j == razvojY) cez = true;
            else if (cez) {
                nova[i-1][j-1] = matrika[i][j];
            }
            else {
                nova[i-1][j] = matrika[i][j];
            }
        }
    }
}

int determinanta(int** matrika, int dim) {
    int rezultat = 0;

    if (dim==1) return matrika[0][0];

    for (int i = 0; i < dim; i++) {

        //dodeli prostor novi matriki
        int **nova = (int **)malloc((dim - 1) * sizeof(int *));
        for (int i = 0; i < dim; i++)
        {
            nova[i] = (int *)malloc((dim - 1) * sizeof(int));
        }
        

        //KOPIRAJ MATRIKO (crtas prvo vrstico in i-ti stolpec)

        kopirajMatriko(matrika, nova, dim, i);


        if (i % 2 == 0)
            rezultat += matrika[0][i] * determinanta(nova, dim-1);
        else
            rezultat -= matrika[0][i] * determinanta(nova, dim - 1);

        freeArray(nova, dim-1);
    }

    return rezultat;

}

int main() {
    int n;
    printf("Vpisi dimenzijo matrike: ");
    scanf("%d", &n);
    printf("\n");

    int** matrika = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrika[i] = (int*) malloc(n*sizeof(int));
    }

    printf("Vpisi matriko:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrika[i][j]);
        }
    }

    //printf("USPESNO PREBRANO \n");
    printf("\n");

    int rezultat = determinanta(matrika, n);
    printf("%d\n", rezultat);


    freeArray(matrika, n);
    
    return 0;
}
