#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void CreateRows(int** a, const int rows, const int cols, const int Low, const int High, int i = 0, int j = 0);
void PrintRows(int** a, const int rows, const int cols, int i = 0, int j = 0);
void SwapMinMaxInColumns(int** a, const int rows, const int cols, int j = 1);
void FindMinInColumn(int** a, int& minRow, const int rows, int j, int i = 0);
void FindMaxInColumn(int** a, int& maxRow, const int rows, int j, int i = 0);

int main() {
    srand((unsigned)time(NULL));
    const int rows = 5;
    const int cols = 6;
    const int Low = -10;
    const int High = 20;

    int** a = new int* [rows];
    for (int i = 0; i < rows; i++)
        a[i] = new int[cols];

    CreateRows(a, rows, cols, Low, High);
    cout << "Initial Matrix:" << endl;
    PrintRows(a, rows, cols);

    SwapMinMaxInColumns(a, rows, cols);
    cout << "Modified Matrix:" << endl;
    PrintRows(a, rows, cols);

    for (int i = 0; i < rows; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Рекурсивне створення матриці
void CreateRows(int** a, const int rows, const int cols, const int Low, const int High, int i, int j) {
    if (i >= rows) return;
    a[i][j] = Low + rand() % (High - Low + 1);
    if (j + 1 < cols)
        CreateRows(a, rows, cols, Low, High, i, j + 1);
    else
        CreateRows(a, rows, cols, Low, High, i + 1, 0);
}

// Рекурсивне виведення матриці
void PrintRows(int** a, const int rows, const int cols, int i, int j) {
    if (i >= rows) return;
    cout << setw(4) << a[i][j];
    if (j + 1 < cols)
        PrintRows(a, rows, cols, i, j + 1);
    else {
        cout << endl;
        PrintRows(a, rows, cols, i + 1, 0);
    }
}

// Рекурсивний обмін мінімального елемента парного стовпця з максимальним попереднього непарного
void SwapMinMaxInColumns(int** a, const int rows, const int cols, int j) {
    if (j >= cols) return;

    int minRow = 0, maxRow = 0;
    FindMinInColumn(a, minRow, rows, j);
    FindMaxInColumn(a, maxRow, rows, j - 1);

    int temp = a[minRow][j];
    a[minRow][j] = a[maxRow][j - 1];
    a[maxRow][j - 1] = temp;

    SwapMinMaxInColumns(a, rows, cols, j + 2);
}

// Пошук мінімального елемента в парному стовпці
void FindMinInColumn(int** a, int& minRow, const int rows, int j, int i) {
    if (i >= rows) return;
    if (a[i][j] < a[minRow][j])
        minRow = i;
    FindMinInColumn(a, minRow, rows, j, i + 1);
}

// Пошук максимального елемента в попередньому непарному стовпці
void FindMaxInColumn(int** a, int& maxRow, const int rows, int j, int i) {
    if (i >= rows) return;
    if (a[i][j] > a[maxRow][j])
        maxRow = i;
    FindMaxInColumn(a, maxRow, rows, j, i + 1);
}
