#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>

std::vector<std::vector<char>> generateField(int n, int m, int bombCount) {
    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Создание и заполнение поля пустыми ячейками
    std::vector<std::vector<char>> field(n, std::vector<char>(m, '0'));

    // Расстановка бомб
    while (bombCount > 0) {
        int x = rand() % n;
        int y = rand() % m;
        if (field[x][y] == '0') {
            field[x][y] = '*';
            bombCount--;
        }
    }

    // Подсчет количества соседних бомб для каждой ячейки
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != '*') {
                int count = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && field[ni][nj] == '*') {
                            count++;
                        }
                    }
                }
                field[i][j] = count + '0';
            }
        }
    }
    
    return field;
}

TEST(MinesweeperTest, TestBombCount) {
    int n = 5, m = 5, bombs = 5;

    std::vector<std::vector<char>> result = generateField(n, m, bombs);

    // Проверка количества бомб на поле
    int bombCount = 0;
    for (const auto &row : result) {
        for (char cell : row) {
            if (cell == '*') {
                bombCount++;
            }
        }
    }

    // Сравнение количества бомб с ожидаемым значением
    ASSERT_EQ(bombCount, bombs);
}

TEST(MinesweeperTest, TestFieldSize) {
    int n = 5, m = 5, bombs = 5;

    std::vector<std::vector<char>> result = generateField(n, m, bombs);

    // Проверка количества строк
    ASSERT_EQ(result.size(), n);
}

TEST(MinesweeperTest, TestFieldSize2) {
    int n = 5, m = 5, bombs = 5;

    std::vector<std::vector<char>> result = generateField(n, m, bombs);

    // Проверка количества столбцов в каждой строке
    for (const auto &row : result) {
        ASSERT_EQ(row.size(), m);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
