#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>
#include <limits.h>

// Функции для генерации магических квадратов
void generateOddMagicSquare(int n, int** magicSquare);
void generateDoublyEvenMagicSquare(int n, int** magicSquare);
void generateSinglyEvenMagicSquare(int n, int** magicSquare);

// Основная функция программы
std::string program(int n, const std::vector<std::vector<int>>& arrNumber) {
    std::ostringstream output;

    // Обработка случая для n = 2
    if (n == 2) {
        output << "NO\n";
        return output.str();
    }

    // Объявление и инициализация магического квадрата
    int** magicSquare = new int*[n];
    for (int i = 0; i < n; i++) {
        magicSquare[i] = new int[n]();
    }

    // Инициализация magicSquare из arrNumber
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            magicSquare[i][j] = arrNumber[i][j];
        }
    }

    // Генерация магического квадрата
    if (n % 2 == 1) {
        generateOddMagicSquare(n, magicSquare);
    } else if (n % 4 == 0) {
        generateDoublyEvenMagicSquare(n, magicSquare);
    } else {
        generateSinglyEvenMagicSquare(n, magicSquare);
    }

    // Запись результата в output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output << magicSquare[i][j] << " ";
        }
        output << "\n";
    }

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] magicSquare[i];
    }
    delete[] magicSquare;

    return output.str();
}

// Функции для генерации магических квадратов
void generateOddMagicSquare(int n, int** magicSquare) {
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
}

void generateDoublyEvenMagicSquare(int n, int** magicSquare) {
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
}

void generateSinglyEvenMagicSquare(int n, int** magicSquare) {
    int halfN = n / 2;
    int subGridSize = halfN * halfN;

    int** subGrid = new int*[halfN];
    for (int i = 0; i < halfN; i++) {
        subGrid[i] = new int[halfN];
    }

    int num = 1;
    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < halfN; j++) {
            subGrid[i][j] = num++;
        }
    }

    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < halfN; j++) {
            magicSquare[i][j] = subGrid[i][j];
            magicSquare[i + halfN][j] = subGrid[i][j] + subGridSize * 2;
            magicSquare[i][j + halfN] = subGrid[i][j] + subGridSize * 3;
            magicSquare[i + halfN][j + halfN] = subGrid[i][j] + subGridSize;
        }
    }

    int k = (n - 2) / 4;
    for (int i = 0; i < halfN; i++) {
        for (int j = 0; j < k; j++) {
            std::swap(magicSquare[i][j], magicSquare[i + halfN][j]);
        }
        for (int j = n - k + 1; j < n; j++) {
            std::swap(magicSquare[i][j], magicSquare[i + halfN][j]);
        }
    }

    for (int j = 0; j < halfN; j++) {
        std::swap(magicSquare[k][j], magicSquare[k + halfN][j]);
    }

    for (int i = 0; i < halfN; i++) {
        delete[] subGrid[i];
    }
    delete[] subGrid;
}

// Тесты
TEST(SampleTest, Example1) {
    std::vector<std::vector<int>> arrNumber = {{0}};
    EXPECT_EQ(program(1, arrNumber), "1 \n");
}

TEST(SampleTest, Example2) {
    std::vector<std::vector<int>> arrNumber = {{0,0}, {0,0}};
    EXPECT_EQ(program(2, arrNumber), "NO\n");
}

TEST(SampleTest, Example3) {
    std::vector<std::vector<int>> arrNumber = {
        {0,0,0}, 
        {0,0,0},
        {0,0,0}
    };
    EXPECT_EQ(program(3, arrNumber), 
              "8 1 6 \n" 
              "3 5 7 \n" 
              "4 9 2 \n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
