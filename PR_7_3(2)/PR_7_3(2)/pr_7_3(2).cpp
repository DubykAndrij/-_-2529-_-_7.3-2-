#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(5) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
}

bool HasZeroInRow(int** a, const int rowNo, const int colCount, int colNo) {
    if (a[rowNo][colNo] == 0)
        return true;
    if (colNo < colCount - 1)
        return HasZeroInRow(a, rowNo, colCount, colNo + 1);
    return false;
}

int CountNonZeroRows(int** a, const int rowCount, const int colCount, int rowNo) {
    int count = !HasZeroInRow(a, rowNo, colCount, 0) ? 1 : 0;
    if (rowNo < rowCount - 1)
        return count + CountNonZeroRows(a, rowCount, colCount, rowNo + 1);
    return count;
}

bool FindDuplicate(int** a, const int rowCount, const int colCount, int current, int r, int c, int skipR, int skipC) {
    if (a[r][c] == current && (r != skipR || c != skipC))
        return true;

    if (c < colCount - 1)
        return FindDuplicate(a, rowCount, colCount, current, r, c + 1, skipR, skipC);
    else if (r < rowCount - 1)
        return FindDuplicate(a, rowCount, colCount, current, r + 1, 0, skipR, skipC);

    return false;
}

void FindMaxRepeatedRec(int** a, const int rowCount, const int colCount, int& maxVal, bool& found, int r, int c) {
    if (FindDuplicate(a, rowCount, colCount, a[r][c], 0, 0, r, c)) {
        if (!found || a[r][c] > maxVal) {
            maxVal = a[r][c];
            found = true;
        }
    }

    if (c < colCount - 1)
        FindMaxRepeatedRec(a, rowCount, colCount, maxVal, found, r, c + 1);
    else if (r < rowCount - 1)
        FindMaxRepeatedRec(a, rowCount, colCount, maxVal, found, r + 1, 0);
}

void GetMaxRepeated(int** a, const int rowCount, const int colCount, int& maxVal, bool& found) {
    found = false;
    FindMaxRepeatedRec(a, rowCount, colCount, maxVal, found, 0, 0);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int k, n;
    cout << "k (rows) = "; cin >> k;
    cout << "n (cols) = "; cin >> n;

    int** a = new int* [k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    cout << "Enter matrix elements:" << endl;
    InputRows(a, k, n, 0);

    cout << "\nMatrix:" << endl;
    PrintRows(a, k, n, 0);

    int nonZeroRows = CountNonZeroRows(a, k, n, 0);
    cout << "1. Кількість рядків без нулів: " << nonZeroRows << endl;

    int maxRepeated;
    bool found = false;
    GetMaxRepeated(a, k, n, maxRepeated, found);

    cout << "2. Максимальне число, що зустрічається >1 разу: ";
    if (found)
        cout << maxRepeated << endl;
    else
        cout << "не знайдено" << endl;

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}