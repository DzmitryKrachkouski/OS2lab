#include <iostream>
#include <Windows.h>
using namespace std;

struct ThreadData {
    int* a;
    int n;
    int* minIndex;
    int* maxIndex;
    int* midlNumber;
};

DWORD WINAPI min_max(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    int* a = data->a;
    int n = data->n;
    int& min = *data->minIndex;
    int& max = *data->maxIndex;

    min = 0;
    max = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[min]) {
            min = i;
            Sleep(7);
        }
        if (a[i] > a[max]) {
            max = i;
            Sleep(7);
        }
    }
    return 0;
}

DWORD WINAPI average(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    int* a = data->a;
    int n = data->n;
    int& midl = *data->midlNumber;
    midl = 0;
    for (int i = 0; i < n; i++) {
        midl += a[i];
        Sleep(12);
    }
    midl /= n;
    return midl;
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int min, max, midl;

    // Подготовка данных для потока
    ThreadData data = { a, n, &min, &max , &midl };

    // Создание потока
    HANDLE hThread1 = CreateThread(nullptr, 0, min_max, &data, 0, nullptr);
    HANDLE hThread2 = CreateThread(nullptr, 0, min_max, &data, 0, nullptr);
    if (hThread1 == nullptr) {
        cerr << "Ошибка создания потока!" << endl;
        delete[] a;
        return 1;
    }
    if (hThread2 == nullptr) {
        cerr << "Ошибка создания потока!" << endl;
        delete[] a;
        return 1;
    }
    // Ожидание завершения потока
    WaitForSingleObject(hThread1, INFINITE);
    CloseHandle(hThread1);

    WaitForSingleObject(hThread2, INFINITE);
    CloseHandle(hThread2);

    a[min] = midl;
    a[max] = midl;

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    delete[] a;
    return 0;
}
