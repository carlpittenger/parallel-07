#include <stdio.h>
#include <stdlib.h>

void generateReduceData(int *const arr, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      arr[i] = i / 2;
    } else {
      arr[i] = -(i / 2);
    }
  }
}

void generateMergeSortData(int *const arr, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    arr[i] = i;
  }

  for (int i = n - 1; i > 0; --i) {
    const int swap_with = rand() % i;
    const int temp = arr[i];
    arr[i] = arr[swap_with];
    arr[swap_with] = temp;
  }
}

void generatePrefixSumData(int *const arr, const int n) {
  for (int i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      arr[i] = i / 2;
    } else {
      arr[i] = -(i / 2);
    }
  }
}

void checkPrefixSumResult(const int *const arr, const size_t n) {
  int correct = 1;

  int *const data = malloc(sizeof(int) * n);
  generatePrefixSumData(data, n);

  correct = correct && (arr[0] == 0);

  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += data[i];
    if (arr[i + 1] != sum) {
      correct = 0;
    }
  }

  if (correct) {
    printf("checked\n");
  } else {
    printf("incorrect\n");
  }

  free(data);
}

// this is based on how merge sort data is generated
void checkMergeSortResult(const int *const arr, const size_t n) {
  int correct = 1;

  for (int i = 0; i < n - 1; ++i) {
    correct = correct && (arr[i] == i);
  }

  if (correct) {
    printf("checked\n");
  } else {
    printf("incorrect\n");
  }
}
