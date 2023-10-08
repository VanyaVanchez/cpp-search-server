// Решите загадку: Сколько чисел от 1 до 1000 содержат как минимум одну цифру 3?
// Напишите ответ здесь:

#include <iostream>

using namespace std;

bool IsThree(const int& a) {
    int b = a;
    while (b > 0) {
        if (b % 10 == 3) {
            return true;
        }
        b /= 10;
    }
    return false;
}

int main() {
    int counter = 0;

    for (int i = 0; i < 1000; ++i) {
        if (IsThree(i)) {
            ++counter;
        }
    }

    cout << counter << endl;

    return 0;

}
// Закомитьте изменения и отправьте их в свой репозиторий.
