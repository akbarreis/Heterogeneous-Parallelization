#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    int N;
    cout << "Введите размер массива: ";
    cin >> N;

    // -----------------------------
    // Создание динамического массива
    // -----------------------------
    int* arr = new int[N];

    // Заполнение случайными числами от 1 до 100
    srand(time(0));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100 + 1;

    cout << "Первые 10 элементов массива: ";
    for (int i = 0; i < min(10, N); i++)
        cout << arr[i] << " ";
    cout << "...\n";

    // -----------------------------
    // Последовательное вычисление среднего
    // -----------------------------
    auto start_seq = high_resolution_clock::now();

    long long sum_seq = 0;
    for (int i = 0; i < N; i++)
        sum_seq += arr[i];

    double avg_seq = (double)sum_seq / N;

    auto end_seq = high_resolution_clock::now();
    double seq_time = duration<double, milli>(end_seq - start_seq).count();

    cout << "Среднее (последовательно): " << avg_seq 
         << ", время: " << seq_time << " мс\n";

    // -----------------------------
    // Параллельное вычисление среднего с OpenMP
    // -----------------------------
    auto start_par = high_resolution_clock::now();

    long long sum_par = 0;

#pragma omp parallel for reduction(+:sum_par)
    for (int i = 0; i < N; i++)
        sum_par += arr[i];

    double avg_par = (double)sum_par / N;

    auto end_par = high_resolution_clock::now();
    double par_time = duration<double, milli>(end_par - start_par).count();

    cout << "Среднее (параллельно): " << avg_par
         << ", время: " << par_time << " мс\n";

    // -----------------------------
    // Освобождение памяти
    // -----------------------------
    delete[] arr;

    return 0;
}
