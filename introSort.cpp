//
// Created by Алексей on 24.11.2024.
//
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

#include "ArrayGenerator.cpp"

  void insertionSort(std::vector<int> &v,
    int leftBound, int rightBound) {
    for (int i = leftBound + 1; i <= rightBound; ++i) {
      int key = v[i];
      int j = i - 1;
      while (j >= leftBound && v[j] > key) {
        v[j + 1] = v[j];
        --j;
      }
      v[j + 1] = key;
    }
  }


  int parent(int i) {
    return (i - 1) / 2;
  }
  int left(int i) {
    return 2 * i + 1;
  }
  int right(int i) {
    return 2 * i + 2;
  }



  void heapify(std::vector<int> &arr, int i, int N) {
    while(2*i <= N) {
      --i;
      int l = left(i);
      int r = right(i);
      int largest = i;
      if (arr[i] < arr[l]) {
        largest = l;
      }
      if (arr[largest] < arr[r] && r < N) {
        largest = r;
      }
      if (largest == i) {
        return;
      }
      std::swap(arr[i], arr[largest]);
      i = largest;
      ++i;
    }
  }
  void buildMaxHeap(std::vector<int>& arr) {
    int N = arr.size();
    for(int i = arr.size() / 2; i >= 1; --i) {
      heapify(arr, i, N);
    }
  }

  // Heap Sort из первой задачи
  void heapSort(std::vector<int>& arr) {
    buildMaxHeap(arr);
    int N = arr.size();

    while(N > 1) {
      std::swap(arr[0], arr[N - 1]);
      --N;
      heapify(arr, 1, N);
    }
  }

  int partition(std::vector<int> &arr, int left, int right) {
    int pivot = arr[right];

    int i = left - 1;
    for (int j = left; j < right; ++j) {
      if (arr[j] <= pivot) {
        ++i;
        std::swap(arr[i], arr[j]);
      }
    }
    std::swap(arr[i + 1], arr[right]);

    return i + 1;
  }

  void quickSort(std::vector<int> &arr, int left, int right) {
    if (left < right) {
      int part = partition(arr, left, right);

      quickSort(arr, left, part - 1);
      quickSort(arr, part + 1, right);
    }
  }

  void introSort(std::vector<int> &arr, int left, int right, int recDepth = 0) {
    ++recDepth;
    if (right - left  < 16) {
      insertionSort(arr, left, right);
    } else if (recDepth > 2 * std::log2(arr.size())) {
      heapSort(arr);
    } else if (left < right) {
      int part = partition(arr, left, right);

      introSort(arr, left, part - 1, recDepth);
      introSort(arr, part + 1, right, recDepth);
    }
  }

  void print_vector(std::vector<int> v) {
    for (auto el: v) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
  }




  class SortTester {
  public:
    // Замерение quick sort на рандомных массивах
    void random_quick(std::string mergeFilePath, ArrayGenerator arrG) {
      std::ofstream mergeFile;
      mergeFile.open(mergeFilePath);
      mergeFile << "x;y\n";
      for (int i = 500; i < 10000; i += 100) {
        long long mergeTime = 0;
        std::vector<int> inputVector = arrG.generateVector(i);
        std::vector<int> v;
        for (int j = 0; j < 10; ++j) {
          v = inputVector;
          auto start = std::chrono::high_resolution_clock::now();
          quickSort(v, 0, i - 1);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          mergeTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }
        mergeFile << i << ';' << mergeTime << '\n';
      }
      mergeFile.close();
    }

    // Замерение intro sort на рандомных массивах
    void random_intro(std::string hybridFilePath, ArrayGenerator arrG) {
      std::ofstream hybridFile;
      hybridFile.open(hybridFilePath);
      hybridFile << "x;y\n";
      for (int i = 500; i < 10000; i += 100) {
        long long hybridTime = 0;
        std::vector<int> inputVector = arrG.generateVector(i);
        std::vector<int> v;
        for (int j = 0; j < 10; ++j) {
          v = inputVector;
          auto start = std::chrono::high_resolution_clock::now();
          introSort(v, 0, i - 1);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          hybridTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }
        hybridFile << i << ';' << hybridTime << '\n';
      }
      hybridFile.close();
    }

    // Замерение quick sort на отсортированных в обратном порядке массивах
    void reverse_quick(std::string mergeFilePath, ArrayGenerator arrG) {
      std::ofstream mergeFile;
      mergeFile.open(mergeFilePath);
      mergeFile << "x;y\n";
      for (int i = 500; i < 10000; i += 100) {
        long long mergeTime = 0;
        std::vector<int> inputVector = arrG.generateReversed(i);
        std::vector<int> v;
        for (int j = 0; j < 10; ++j) {
          v = inputVector;
          auto start = std::chrono::high_resolution_clock::now();
          quickSort(v, 0, i - 1);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          mergeTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }
        mergeFile << i << ';' << mergeTime << '\n';
      }
      mergeFile.close();
    }

    // Замерение intro sort на отсортированных в обратном порядке массивах
    void reverse_intro(std::string hybridFilePath, ArrayGenerator arrG) {
      std::ofstream hybridFile;
      hybridFile.open(hybridFilePath);
      hybridFile << "x;y\n";
      for (int i = 500; i < 10000; i += 100) {
        long long hybridTime = 0;
        std::vector<int> inputVector = arrG.generateReversed(i);
        std::vector<int> v;
        for (int j = 0; j < 10; ++j) {
          v = inputVector;
          auto start = std::chrono::high_resolution_clock::now();
          introSort(v, 0, i - 1);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          hybridTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }
        hybridFile << i << ';' << hybridTime << '\n';
      }
      hybridFile.close();
    }

    // Замерение quick sort на почти отсортированных массивах
    void almostSorted_quick(std::string mergeFilePath, ArrayGenerator arrG) {
      std::ofstream mergeFile;
      mergeFile.open(mergeFilePath);
      mergeFile << "x;y\n";
      for (int i = 500; i < 10000; i += 100) {
        long long mergeTime = 0;
        std::vector<int> inputVector = arrG.generateAlmostSorted(i);
        std::vector<int> v;
        for (int j = 0; j < 10; ++j) {
          v = inputVector;
          auto start = std::chrono::high_resolution_clock::now();
          quickSort(v, 0, i - 1);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          mergeTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }
        mergeFile << i << ';' << mergeTime << '\n';
      }
      mergeFile.close();
    }

    // Замерение hybrid sort на почти отсортированных массивах
    void almostSorted_intro(std::string hybridFilePath, ArrayGenerator arrG) {
      std::ofstream hybridFile;
      hybridFile.open(hybridFilePath);
      hybridFile << "x;y\n";
      for (int i = 500; i < 10000; i += 100) {
        long long hybridTime = 0;
        std::vector<int> inputVector = arrG.generateAlmostSorted(i);
        std::vector<int> v;
        for (int j = 0; j < 10; ++j) {
          v = inputVector;
          auto start = std::chrono::high_resolution_clock::now();
          introSort(v, 0, i - 1);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          hybridTime += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }
        hybridFile << i << ';' << hybridTime << '\n';
      }
      hybridFile.close();
    }
  };


int main() {
  SortTester tester = SortTester();
  ArrayGenerator arrG = ArrayGenerator(333);
  tester.random_quick("A3\\quick_random.csv", arrG);
  tester.reverse_quick("A3\\quick_reversed.csv", arrG);
  tester.almostSorted_quick("A3\\quick_almostSorted.csv", arrG);
  tester.random_intro("A3\\intro_random.csv", arrG);
  tester.reverse_intro("A3\\intro_reversed.csv", arrG);
  tester.almostSorted_intro("A3\\intro_almostSorted.csv", arrG);

  return 0;
}