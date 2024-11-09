#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>
#include <limits.h>

std::string program(int n, std::vector<std::vector<std::vector<int>>> &arrNumber) {
    std::ostringstream output;

    int*** arrNew = new int**[n];
    for (int i = 0; i < n; i++) {
        arrNew[i] = new int*[n];
        for (int j = 0; j < n; j++) {
            arrNew[i][j] = new int[n];
        }
        }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < n; l++) {
                arrNew[i][j][l] = arrNumber[i][j][l];
            }
        }
    }

    int sum = 0;
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    for (int i = 0; i < n; i++) {
        sum += arrNew[i][i][i];
        sum1 += arrNew[n-1-i][i][i];
        sum2 += arrNew[i][n-1-i][i];
        sum3 += arrNew[i][i][n-1-i];
    }



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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            delete[] arrNew[i][j];
        }
        delete[] arrNew[i];
    }
    delete[] arrNew;
    output << max;
    return output.str();
}

TEST(SampleTest, Example) {
    std::vector<std::vector<std::vector<int>>> arrNumber = {{{1,2},{3,4}},{{5,6},{7,8}}};
    EXPECT_EQ(program(2, arrNumber), "9");
}

TEST(SampleTest, Example2) {
    std::vector<std::vector<std::vector<int>>> arrNumber = {{{1}}};
    EXPECT_EQ(program(1, arrNumber), "1");
}

TEST(SampleTest, Example3) {
    std::vector<std::vector<std::vector<int>>> arrNumber = {{{23,34},{2,3}},{{4,34},{23,54}}};
    EXPECT_EQ(program(2, arrNumber), "77");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}