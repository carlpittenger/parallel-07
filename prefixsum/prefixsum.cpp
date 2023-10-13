#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <fcntl.h>
#include <omp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
void generatePrefixSumData(int *arr, size_t n);
void checkPrefixSumResult(int *arr, size_t n);
#ifdef __cplusplus
}
#endif

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
  // forces openmp to create the threads beforehand
#pragma omp parallel
  {
    const auto fd = open(argv[0], O_RDONLY);
    if (fd != -1) {
      close(fd);
    } else {
      std::cerr << "something is amiss\n";
    }
  }

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <n> <nb_threads>\n";
    return -1;
  }

  const auto n = atoi(argv[1]);

  auto *const arr = new int[n];
  generatePrefixSumData(arr, n);

  auto *const pr = new int[n + 1];

  // insert prefix sum code here

  checkPrefixSumResult(pr, n);

  delete[] arr;

  return EXIT_SUCCESS;
}
