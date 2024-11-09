#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
            printf("Ошибка: введено некорректное значение. Введите целое число.\n");
            // Очистка флага ошибки
            clearerr(stdin);
            continue;
        }
        
        // Проверяем, что после числа нет других символов, кроме новой строки
        c = getchar();
        if (c != '\n') {
            valid = 0;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Ошибка: после числа не должно быть других символов. Введите значение повторно.\n");
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
    return n;
}

void program() {
    int n;
    printf("Введите сторону трехмерного массива: ");
    n = proverka();
    
    int ***arr = (int ***)malloc(n * sizeof(int **));
    for (int i = 0; i < n; i++) {
        arr[i] = (int **)malloc(n * sizeof(int *));
        for (int j = 0; j < n; j++) {
            arr[i][j] = (int *)malloc(n * sizeof(int));
        }
    }

    // Ввод элементов массива
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int g = 0; g < n; g++) {
                printf("Введите элемент массива с индексами (%d %d %d): ", i, j, g);
                scanf("%d", &arr[i][j][g]);
            }
        }
    }

    // Вывод элементов массива
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int g = 0; g < n; g++) {
                printf("%d\t", arr[i][j][g]);
            }
            printf("\n");
        }
        printf("\n");
    }

    int sum = 0;
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i][i][i];
        sum1 += arr[n-1-i][i][i];
        sum2 += arr[i][n-1-i][i];
        sum3 += arr[i][i][n-1-i];
    }

    printf("Сумма основной диагонали: %d\n", sum);
    printf("Сумма обратной диагонали по первому измерению: %d\n", sum1);
    printf("Сумма обратной диагонали по второму измерению: %d\n", sum2);
    printf("Сумма обратной диагонали по третьему измерению: %d\n", sum3);



     int max = INT_MIN; // Инициализируем максимальное значение наименьшим возможным значением int

    if (sum > max) {
        max = sum;
    }
    if (sum1 > max) {
        max = sum1;
    }
    if (sum2 > max) {
        max = sum2;
    }
    if (sum3 > max) {
        max = sum3;
    }
    
    printf("Максимальная сумма диагоналей: %d\n", max);
    

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
}

    int main() {
    while (1) {
        int number = menu();
        if (number == 1) {
            printf("Попова Яна\n");
        } else if (number == 2) {
            program();
        } else if (number == 3) {
            printf("Ввести статический одномерный массив из k чисел и сдвинуть элементы массива циклически на п позиций вправо\n");
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
