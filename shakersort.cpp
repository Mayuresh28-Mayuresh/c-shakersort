#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void shaker_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n/2; i++) {
        bool swapped = false;
        // Move larger elements down
        for (int j = i; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        // Move smaller elements up
        for (int j = n-i-2; j >= i; j--) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        // If no swaps occurred, the list is sorted
        if (!swapped) {
            break;
        }
    }
}

int main() {
    // Prompt user for size of vector
    int size;
    cout << "Enter size of vector: ";
    cin >> size;

    // Generate random numbers and save to file
    vector<int> arr(size);
    ofstream file("random_numbers.txt");
    if (file.is_open()) {
        srand(time(NULL));
        for (int i = 0; i < size; i++) {
            int num = rand() % 100 + 1;
            arr[i] = num;
            file << num << endl;
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
        return 1;
    }

    // Sort the file in ascending order
    ifstream infile("random_numbers.txt");
    vector<int> numbers;
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }
    auto start_time = high_resolution_clock::now();
    shaker_sort(numbers);
    auto end_time = high_resolution_clock::now();
    infile.close();
    ofstream outfile("ascending_sorted.txt");
    if (outfile.is_open()) {
        for (int num : numbers) {
            outfile << num << endl;
        }
        outfile.close();
    }
    else {
        cout << "Unable to open file." << endl;
        return 1;
    }
    cout << "Time taken to sort in ascending order: " << duration_cast<milliseconds>(end_time - start_time).count() << " milliseconds." << endl;

    // Sort the file in descending order
    infile.open("random_numbers.txt");
    numbers.clear();
    while (infile >> num) {
        numbers.push_back(num);
    }
    start_time = high_resolution_clock::now();
    shaker_sort(numbers);
    reverse(numbers.begin(), numbers.end());
    end_time = high_resolution_clock::now();
    infile.close();
    outfile.open("descending_sorted.txt");
    if (outfile.is_open()) {
        for (int num : numbers) {
            outfile << num << endl;
        }
        outfile.close();
    }
    else {
        cout << "Unable to open file." << endl;
        return 1;
    }
    cout << "Time taken to sort in descending order: " << duration_cast<milliseconds>(end_time - start_time).count() << " milliseconds." << endl;

    return 0;
}

