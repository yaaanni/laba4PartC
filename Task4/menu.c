#include <stdio.h>
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
    printf("4. Выход из программы\n");
    printf("5. Вариант\n");
    printf(">>>\n");
    int n;
    n = proverka();
    return n;
    
}
    int main() {
    while (1) {
        int number = menu();
        if (number == 1) {
            printf("Попова Яна\n");
        } else if (number == 2) {
            // program();
        } else if (number == 3) {
            printf("Ввести статический одномерный массив из k чисел и сдвинуть элементы массива циклически на п позиций вправо\n");
        } else if (number == 4) {
            printf("Выход выполнен успешно!\n");
            return 0;
        } else if (number == 5) {
            printf("Вариант: 6\n");
        } else {
            printf("Неверно ввели значение, попробуйте еще раз: \n");
            continue;
        }
        printf(">>>\n");
    }
}
