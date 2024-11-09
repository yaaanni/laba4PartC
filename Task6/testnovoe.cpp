#include <stdio.h>
#include <stdlib.h>

void generateOddMagicSquare(int n);
void generateDoublyEvenMagicSquare(int n);
void generateSinglyEvenMagicSquare(int n);

void generateOddMagicSquare(int n) {
    int **magicSquare = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            magicSquare[i][j] = 0;
        }
    }
    int num = 1;
    int i = 0, j = n / 2;
    while (num <= n * n) {
        magicSquare[i][j] = num++;
        int newi = (i - 1 + n) % n;
        int newj = (j + 1) % n;
        if (magicSquare[newi][newj]) {
            i++;
        } else {
            i = newi;
            j = newj;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", magicSquare[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

void generateDoublyEvenMagicSquare(int n) {
    int **magicSquare = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)malloc(n * sizeof(int));
    }
    int num = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            magicSquare[i][j] = num++;
        }
    }
    for (int i = 0; i < n / 4; i++) {
        for (int j = 0; j < n / 4; j++) {
            magicSquare[i][j] = (n * n + 1) - magicSquare[i][j];
            magicSquare[i][n - 1 - j] = (n * n + 1) - magicSquare[i][n - 1 - j];
            magicSquare[n - 1 - i][j] = (n * n + 1) - magicSquare[n - 1 - i][j];
            magicSquare[n - 1 - i][n - 1 - j] = (n * n + 1) - magicSquare[n - 1 - i][n - 1 - j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", magicSquare[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

void generateSinglyEvenMagicSquare(int n) {
    int halfN = n / 2;
    int subGridSize = halfN * halfN;

    int **subGrid = (int **)malloc(halfN * sizeof(int *));
    for (int i = 0; i < halfN; i++) {
        subGrid[i] = (int *)malloc(halfN * sizeof(int));
    }

    // Заполняем подматрицу размером halfN
    int num = 1;
    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < halfN; j++) {
            subGrid[i][j] = num++;
        }
    }

    int **magicSquare = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < halfN; j++) {
            magicSquare[i][j] = subGrid[i][j];
            magicSquare[i + halfN][j] = subGrid[i][j] + subGridSize * 2;
            magicSquare[i][j + halfN] = subGrid[i][j] + subGridSize * 3;
            magicSquare[i + halfN][j + halfN] = subGrid[i][j] + subGridSize;
        }
    }

    // Перемещение колонок
    int k = (n - 2) / 4;
    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < k; j++) {
            int temp = magicSquare[i][j];
            magicSquare[i][j] = magicSquare[i + halfN][j];
            magicSquare[i + halfN][j] = temp;
        }
        for (int j = n - k + 1; j < n; j++) {
            int temp = magicSquare[i][j];
            magicSquare[i][j] = magicSquare[i + halfN][j];
            magicSquare[i + halfN][j] = temp;
        }
    }

    // Перемещение центрального квадрата
    for (int j = 0; j < halfN; j++) {
        int temp = magicSquare[k][j];
        magicSquare[k][j] = magicSquare[k + halfN][j];
        magicSquare[k + halfN][j] = temp;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", magicSquare[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
    for (int i = 0; i < halfN; i++) {
        free(subGrid[i]);
    }
    free(subGrid);
}

int main() {
    int n;
    scanf("%d", &n);

    if (n == 2) {
        printf("NO\n");
    } else if (n % 2 == 1) {
        generateOddMagicSquare(n);
    } else if (n % 4 == 0) {
        generateDoublyEvenMagicSquare(n);
    } else {
        generateSinglyEvenMagicSquare(n);
    }

    return 0;
}
