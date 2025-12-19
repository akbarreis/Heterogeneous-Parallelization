#include <iostream>
#include <omp.h>
#include <chrono>
#include <cstdlib>

using namespace std;

int main() {
    int N = 1000000;
    int* arr = new int[N];

    srand(time(0));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100 + 1;

    // вывод массива (можно отключить если N большой)
    cout << "Array example (first 20 elements): ";
    for (int i = 0; i < 20; i++)
        cout << arr[i] << " ";
    cout << "\n";

    int min_val = arr[0], max_val = arr[0];

    // последовательная версия
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    auto t2 = chrono::high_resolution_clock::now();
    double seq_time = chrono::duration<double>(t2 - t1).count();

    cout << "Sequential min: " << min_val << endl;
    cout << "Sequential max: " << max_val << endl;

    // параллельная версия
    min_val = arr[0];
    max_val = arr[0];

    auto t3 = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < N; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    auto t4 = chrono::high_resolution_clock::now();
    double par_time = chrono::duration<double>(t4 - t3).count();

    cout << "Parallel min: " << min_val << endl;
    cout << "Parallel max: " << max_val << endl;

    cout << "Sequential time: " << seq_time << " sec\n";
    cout << "Parallel time: " << par_time << " sec\n";

    delete[] arr;
    return 0;
}
