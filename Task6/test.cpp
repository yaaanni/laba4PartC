#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void ms1(long long n) {
    long long** magicSquare = (long long**) malloc(n * sizeof(long long*));
    for (int i = 0; i < n; ++i) {
        magicSquare[i] = (long long*)malloc(n * sizeof(long long));
    }
    long long row = 0, col = n / 2; // Начальная позиция (первая строка, центр)

    for (int num = 1; num <= n * n; num++) {
        magicSquare[row][col] = num; // Помещаем число

        // Пытаемся переместиться вверх и вправо
        long long  newRow = (row - 1 + n) % n;
        long long newCol = (col + 1) % n;

        // Если верхняя ячейка уже занята, перемещаемся вниз
        if (magicSquare[newRow][newCol] != 0) {
            row = (row + 1) % n; // Переход вниз
        } else {
            row = newRow; // Переход вверх
            col = newCol; // Переход вправо
        }
    }

    // Выводим магический квадрат
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%lld\t", magicSquare[i][j]);
        }
        printf("\n");
    }

    // Освобождаем память
    for (int i = 0; i < n; ++i) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

void ms2(long long n) {
    long long** magicSquare = (long long**)malloc(n * sizeof(long long*));
    for (int i = 0; i < n; ++i) {
        magicSquare[i] = (long long*)malloc(n * sizeof(long long));
    }

    // Заполняем квадрат числами от 1 до n*n
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            magicSquare[i][j] = i * n + j + 1;
        }
    }

    // Перекрытие для четных порядков, кратных 4
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j += 4) {
            for (int x = 0; x < 4; ++x) {
                for (int y = 0; y < 4; ++y) {
                    if (x == y || x + y == 3) { // Перекрываем диагонали
                        long long temp = magicSquare[i + x][j + y];
                        magicSquare[i + x][j + y] = n*n - temp + 1;
                    }
                }
            }
        }
    }

    // Выводим магический квадрат
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%lld\t", magicSquare[i][j]);
        }
        printf("\n");
    }

    // Освобождаем память
    for (int i = 0; i < n; ++i) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

void ms3(long long n) {
    int sz = n;
    int* sqr = (int*)malloc(sz * sz * sizeof(int));
    for (int i = 0; i < sz * sz; ++i) { 
        sqr[i] = 0; 
    }

    int n2 = n / 2;
    int n2sz = n2 * sz;
    int size = sz * sz;
    int add1 = size / 2;
    int add3 = size / 4;
    int add2 = 3 * add3;

    // Заполнение подквадрата размера n/2
    int oneSide = n2, curCol = oneSide / 2, curRow = 0, count = oneSide * oneSide, s = 1;

    while (count > 0) {
        int done = 0;
        while (0 == done) {
            if (curCol >= oneSide) curCol = 0;
            if (curRow < 0) curRow = oneSide - 1;
            done = 1;
            if (sqr[curCol + sz * curRow] != 0) {
                curCol -= 1; curRow += 2;
                if (curCol < 0) curCol = oneSide - 1;
                if (curRow >= oneSide) curRow -= oneSide;

                done = 0;
            }
        }
        sqr[curCol + sz * curRow] = s;
        s++; count--; curCol++; curRow--;
    }

    // Заполнение остальных частей
    for (int r = 0; r < n2; r++) {
        int row = r * sz;
        for (int c = n2; c < sz; c++) {
            int m = sqr[c - n2 + row];

            sqr[c + row] = m + add1;
            sqr[c + row + n2sz] = m + add3;
            sqr[c - n2 + row + n2sz] = m + add2;
        }
    }

    // Перестановка элементов
    int lc = (sz - 2) / 4, co = sz - (lc - 1);
    for (int r = 0; r < n2; r++) {
        int row = r * sz;
        for (int c = co; c < sz; c++) {
            sqr[c + row] -= add3;
            sqr[c + row + n2sz] += add3;
        }
    }
    for (int r = 0; r < n2; r++) {
        int row = r * sz;
        for (int c = 0; c < lc; c++) {
            int cc = c;
            if (r == lc) cc++;
            sqr[cc + row] += add2;
            sqr[cc + row + n2sz] -= add2;
        }
    }

    // Печать магического квадрата
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d ", sqr[i * n + j]);
        }
        printf("\n");
    }

    free(sqr);
}

int main() {
    long long n;
    char agreement[10];
    while (1) {
            scanf("%lld", &n);
            if (n == 2) {
                printf("\nNO\n"); 
            }
            else if (n % 2 == 1) {
                ms1(n);
            } else if (n % 4 == 0) {
                ms2(n);
            } else {
                ms3(n);
            }
              
        }
    
    return 0;
}