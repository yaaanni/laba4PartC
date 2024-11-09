#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    printf("3. Суть задания\n");    
    printf("4. Выход из программы\n");
    printf(">>>\n");
    int n;
    n = proverka();
    return n;
}

void program() {
    int n, m, bombs;
    printf("Введите размеры поля n и m: ");
    n = proverka();
    m = proverka();
    printf("Введите количество бомб: ");
    bombs = proverka();
    
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    // Создание двумерного массива для хранения поля
    char **field = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        field[i] = (char *)malloc((m + 1) * sizeof(char));
    }
    
    // Заполнение поля пустыми местами
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            field[i][j] = '.';
        }
        field[i][m] = '\0';
    }
    
    // Расстановка бомб
    for (int b = 0; b < bombs; b++) {
        int x, y;
        do {
            x = rand() % n;
            y = rand() % m;
        } while (field[x][y] == '*'); // Проверяем, что в этом месте нет бомбы
        field[x][y] = '*';
    }
    
    // Создание массива для результата
    char **result = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        result[i] = (char *)malloc((m + 1) * sizeof(char));
    }
    
    // Обработка поля
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == '*') {
                result[i][j] = '*';
            } else {
                int count = 0;
                // Проверка всех соседних ячеек
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && field[ni][nj] == '*') {
                            count++;
                        }
                    }
                }
                result[i][j] = count + '0'; // Преобразуем число в символ
            }
        }
        result[i][m] = '\0'; // Завершаем строку
    }
    
    // Вывод результата
    printf("Результат:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", result[i]);
        free(field[i]);
        free(result[i]);
    }
    free(field);
    free(result);
}

int main() {
    while (1) {
        int number = menu();
        if (number == 1) {
            printf("Попова Яна\n");
        } else if (number == 2) {
            program(); 
        } else if (number == 3) {
            printf("Поле для сапера\n");
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
