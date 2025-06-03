#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 9;

void task1() {
    int n = 10;
    int* arr = new int[n];
    srand(time(0));
    int sum = 0;
    for (int* p = arr; p < arr + n; p++) {
        *p = rand() % 100;
        sum += *p;
    }
    for (int* p = arr; p < arr + n; p++) cout << *p << " ";
    cout << "\n" << (float)sum / n << endl;
    delete[] arr;
}

void task2() {
    int n = 10;
    int* arr = new int[n];
    srand(time(0));
    for (int* p = arr; p < arr + n; p++) *p = rand() % 50;
    for (int* p = arr + n - 1; p >= arr; p--) cout << *p << " ";
    cout << endl;
    delete[] arr;
}

void task3() {
    int n = 10;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) *(arr + i) = i;
    int a = 2, b = 5;
    int temp = *(arr + a);
    *(arr + a) = *(arr + b);
    *(arr + b) = temp;
    for (int* p = arr; p < arr + n; p++) cout << *p << " ";
    cout << endl;
    delete[] arr;
}

void task4() {
    int n = 10;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) *(arr + i) = i;
    int* start = arr;
    int* end = arr + n - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    for (int* p = arr; p < arr + n; p++) cout << *p << " ";
    cout << endl;
    delete[] arr;
}

void task5() {
    int n = 10;
    int* arr = new int[n];
    srand(time(0));
    for (int* p = arr; p < arr + n; p++) *p = rand() % 50;
    for (int i = 0; i < n - 1; i++) {
        for (int* p = arr; p < arr + n - i - 1; p++) {
            if (*p > *(p + 1)) {
                int temp = *p;
                *p = *(p + 1);
                *(p + 1) = temp;
            }
        }
    }
    for (int* p = arr; p < arr + n; p++) cout << *p << " ";
    cout << endl;
    delete[] arr;
}

bool isValid(int** board, int row, int col, int num) {
    for (int i = 0; i < SIZE; i++)
        if (board[row][i] == num || board[i][col] == num)
            return false;
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;
    return true;
}

void generateSudoku(int** board, int fillCount) {
    srand(time(0));
    int filled = 0;
    while (filled < fillCount) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        int num = rand() % 9 + 1;
        if (board[row][col] == 0 && isValid(board, row, col, num)) {
            board[row][col] = num;
            filled++;
        }
    }
}

void printSudoku(int** board, bool** fixed) {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool isFull(int** board) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 0)
                return false;
    return true;
}

void playSudoku() {
    int** board = new int* [SIZE];
    bool** fixed = new bool* [SIZE];
    for (int i = 0; i < SIZE; i++) {
        board[i] = new int[SIZE] {};
        fixed[i] = new bool[SIZE] {};
    }

    generateSudoku(board, 25);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 0)
                fixed[i][j] = true;

    while (true) {

        printSudoku(board, fixed);
        if (isFull(board)) {
            cout << "\nВітаємо! Ви заповнили Sudoku!\n";
            break;
        }

        int r, c, val;
        cout << "\nВведіть рядок, стовпець і число (1-9). 0 0 0 — вихід: ";
        cin >> r >> c >> val;

        if (r == 0 && c == 0 && val == 0)
            break;

        if (r < 1 || r > 9 || c < 1 || c > 9 || val < 1 || val > 9) {
            cout << "Некоректне значення. Від 1 до 9.\n";
            continue;
        }

        r--; c--;

        if (fixed[r][c]) {
            cout << "Цю клітинку змінити не можна.\n";
            continue;
        }

        if (isValid(board, r, c, val)) {
            board[r][c] = val;
        }
        else {
            cout << "Не можна поставити це число тут.\n";
        }
    }

    for (int i = 0; i < SIZE; i++) {
        delete[] board[i];
        delete[] fixed[i];
    }
    delete[] board;
    delete[] fixed;
}

int main() {
    setlocale(LC_ALL, "ukr,ru");
    cout << "===== Прості завдання по темі Покажчик =====\n";
    task1();
    task2();
    task3();
    task4();
    task5();

    cout << "\n===== Sudoku Game =====\n";
    playSudoku();

    return 0;
}
