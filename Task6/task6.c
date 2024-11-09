#include <stdio.h>
#include <stdlib.h>

int proverka() {
    int n;
    int valid;
    char c;
    do {
        printf("Введите значение: ");
        
        valid = scanf("%d", &n);
        
        if (valid != 1) {
            // Если значение не является целым числом, очищаем поток ввода
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Введите значение повторно\n");
            // Очистка флага ошибки
            clearerr(stdin);
            continue;
        }
        
        // Проверяем, что после числа нет других символов, кроме новой строки
        c = getchar();
        if (c != '\n') {
            valid = 0;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Введите значение повторно\n");
            // Очистка флага ошибки
            clearerr(stdin);
        }

    } while (!valid);
    return n;
}

int menu() {
    printf("Выберите интересующий пункт меню: \n");
    printf("1. Кто выполнил задание\n");
    printf("2. Результат программы\n");
    printf("3. Суть программы\n");
    printf("4. Выход из программы\n");
    printf(">>>\n");
    int n;
    n = proverka();
    
}

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
    printf("Магический квадрат порядка %d (нечётный):\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", magicSquare[i][j]);
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
    printf("Магический квадрат порядка %d (чётный, кратный 4):\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", magicSquare[i][j]);
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
    generateOddMagicSquare(halfN);
    int **magicSquare = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < halfN; j++) {
            int x = i * 2;
            int y = j * 2;
            magicSquare[i][j] = subGrid[i][j];
            magicSquare[i + halfN][j] = subGrid[i][j] + subGridSize * 2;
            magicSquare[i][j + halfN] = subGrid[i][j] + subGridSize * 3;
            magicSquare[i + halfN][j + halfN] = subGrid[i][j] + subGridSize;
        }
    }
    free(subGrid);
    printf("Магический квадрат порядка %d (чётный, некратный 4):\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", magicSquare[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}


void program() {
    int n;
    printf("Введите порядок магического квадрата(не превышает 100000): ");
    n = proverka();


    if (n == 2){
        printf("NO\n");
    }
    else if (n % 2 == 1) {
        generateOddMagicSquare(n);
    } else if (n % 4 == 0) {
        generateDoublyEvenMagicSquare(n);
    } else {
        generateSinglyEvenMagicSquare(n);
    }
}

int main() {
    while (1) {
        int number = menu();
        if (number == 1) {
            printf("Попова Яна\n");
        } else if (number == 2) {
            program();
        } else if (number == 3) {
            printf("Магический квадрат\n");
        } else if (number == 4) {
            printf("Выход выполнен успешно!\n");
            return 0;
        } else {
            printf("Неверно ввели значение, попробуйте еще раз: \n");
            continue;
        }
        printf(">>>\n");
    }
}
