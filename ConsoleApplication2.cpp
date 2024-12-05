#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
void bubblesort_for_for_pointer(T* arr, size_t n) {
    T* w1, * w2, temp;

    for (size_t i = 0; i < n; i++) {
        w1 = arr;
        w2 = w1 + 1;
        for (size_t j = 0; j < n - 1; j++) {
            if (*w1 > *w2) {
                temp = *w2;
                *w2 = *w1;
                *w1 = temp;
            }
            w1++;
            w2++;
        }
    }
}

template <typename T>
void bubblesort_for_for_index(T arr[], size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <typename T>
void bubblesort_vector_swap(vector<T>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T>
bool is_sorted(T arr[], size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool is_sorted_vector(const vector<T>& vec) {
    for (size_t i = 0; i < vec.size() - 1; i++) {
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}

template <typename Func, typename T>
double measure_time(Func func, T arr[], size_t n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

template <typename Func, typename T>
double measure_time_vector(Func func, vector<T>& vec) {
    auto start = chrono::high_resolution_clock::now();
    func(vec);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

void run_and_measure(int n, ofstream& file) {
    int* arr_int = new int[n];
    float* arr_float = new float[n];
    vector<int> vec_int(n);
    vector<float> vec_float(n);

    for (int i = 0; i < n; i++) {
        arr_int[i] = n - i;
        arr_float[i] = sqrt(n - i);
        vec_int[i] = n - i;
        vec_float[i] = sqrt(n - i);
    }

    double time_int = measure_time(bubblesort_for_for_index<int>, arr_int, n);
    double time_float = measure_time(bubblesort_for_for_index<float>, arr_float, n);
    double time_ptr_int = measure_time(bubblesort_for_for_pointer<int>, arr_int, n);
    double time_ptr_float = measure_time(bubblesort_for_for_pointer<float>, arr_float, n);
    double time_vec_int = measure_time_vector(bubblesort_vector_swap<int>, vec_int);
    double time_vec_float = measure_time_vector(bubblesort_vector_swap<float>, vec_float);

    double perc_ptr_int = ((time_ptr_int - time_int) / time_int) * 100.0;
    double perc_ptr_float = ((time_ptr_float - time_float) / time_float) * 100.0;
    double perc_vec_int = ((time_vec_int - time_int) / time_int) * 100.0;
    double perc_vec_float = ((time_vec_float - time_float) / time_float) * 100.0;

    file << "| " << setw(18) << n << " | "
        << setw(21) << time_int << " | "
        << setw(24) << time_float << " | "
        << setw(15) << time_ptr_int << " (" << fixed << setprecision(2) << perc_ptr_int << "%) | "
        << setw(16) << time_ptr_float << " (" << fixed << setprecision(2) << perc_ptr_float << "%) | "
        << setw(9) << time_vec_int << " (" << fixed << setprecision(2) << perc_vec_int << "%) | "
        << setw(11) << time_vec_float << " (" << fixed << setprecision(2) << perc_vec_float << "%) |" << endl;

    cout << "Dla " << n << " elementów:" << endl;
    cout << "Tablica int: " << (is_sorted(arr_int, n) ? "posortowana" : "nieposortowana") << endl;
    cout << "Tablica float: " << (is_sorted(arr_float, n) ? "posortowana" : "nieposortowana") << endl;
    cout << "Wskaźnik int: " << (is_sorted(arr_int, n) ? "posortowany" : "nieposortowany") << endl;
    cout << "Wskaźnik float: " << (is_sorted(arr_float, n) ? "posortowany" : "nieposortowany") << endl;
    cout << "Wektor int: " << (is_sorted_vector(vec_int) ? "posortowany" : "nieposortowany") << endl;
    cout << "Wektor float: " << (is_sorted_vector(vec_float) ? "posortowany" : "nieposortowany") << endl;

    delete[] arr_int;
    delete[] arr_float;
}

int main() {
    srand(time(0));

    ofstream file("results2.txt");

    if (file.is_open()) {
        file << "| Number of Elements |For-For Index Int (ms) | For-For Index Float (ms) | For-For Pointer Int (ms) | For-For Pointer Float (ms) | Vector Swap Int (ms) | Vector Swap Float (ms) |" << endl;
        file << "|--------------------|-----------------------|--------------------------|--------------------------|----------------------------|----------------------|------------------------|" << endl;

        run_and_measure(100, file);
        run_and_measure(1000, file);
        run_and_measure(10000, file);
        run_and_measure(20000, file);

        file.close();
    }
    else {
        cerr << "Nie mogę otworzyć pliku";
    }

    return 0;
}
