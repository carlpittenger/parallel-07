#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <fcntl.h>
#include <omp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEBUG 0

#ifdef __cplusplus
extern "C" {
#endif

void generateMergeSortData(int *arr, size_t n);
void checkMergeSortResult(int *arr, size_t n);

#ifdef __cplusplus
}
#endif

auto merge(int *const arr, const int l, const int mid, const int r) noexcept
    -> void {
#if DEBUG
  std::cout << l << " " << mid << " " << r << '\n';
#endif

  // short circuits
  if (l == r) {
    return;
  }

  if (r - l == 1) {
    if (arr[l] > arr[r]) {
      const int temp = arr[l];
      arr[l] = arr[r];
      arr[r] = temp;
    }
    return;
  }

  const auto n = mid - l;

  // declare and init temp arrays
  auto *const temp = new int[n];
  for (auto i = 0; i < n; ++i) {
    temp[i] = arr[l + i];
  }

  auto i = 0;   // temp left half
  auto j = mid; // right half
  auto k = l;   // write to

  // merge
  while (i < n && j <= r) {
    if (temp[i] <= arr[j]) {
      arr[k++] = temp[i++];
    } else {
      arr[k++] = arr[j++];
    }
  }

  // exhaust temp
  while (i < n) {
    arr[k++] = temp[i++];
  }

  // de-allocate structs used
  delete[] temp;
}

auto mergesort(int *const arr, const int l, const int r) noexcept -> void {
  if (l < r) {
    const int mid = (l + r) / 2;
    mergesort(arr, l, mid);
    mergesort(arr, mid + 1, r);
    merge(arr, l, mid + 1, r);
  }
}

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <n>\n";
    return -1;
  }

  // command line parameter
  const auto n = atoi(argv[1]);

  // get arr data
  auto *const arr = new int[n];
  generateMergeSortData(arr, n);

#if DEBUG
  for (auto i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
#endif

  // begin timing
  const auto start = std::chrono::system_clock::now();

  // sort
  mergesort(arr, 0, n - 1);

  // end timing
  const auto end = std::chrono::system_clock::now();
  const auto elapsed_seconds =
      static_cast<std::chrono::duration<double>>(end - start);

  // display time to cerr
  std::cerr << elapsed_seconds.count() << '\n';
  checkMergeSortResult(arr, n);

#if DEBUG
  for (auto i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
#endif

  delete[] arr;

  return EXIT_SUCCESS;
}
