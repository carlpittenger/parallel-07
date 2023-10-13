#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
void generateMergeSortData(int *arr, size_t n);
void checkMergeSortResult(const int *arr, size_t n);
#ifdef __cplusplus
}
#endif

int main(const int argc, const char *const *const argv) {
  // forces openmp to create the threads beforehand
#pragma omp parallel
  {
    const int fd = open(argv[0], O_RDONLY);
    if (fd != -1) {
      close(fd);
    } else {
      std::cerr << "something is amiss\n";
    }
  }

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <n> <nbthreads>\n";
    return -1;
  }

  const int n = atoi(argv[1]);

  // get arr data
  int *const arr = new int[n];
  generateMergeSortData(arr, n);

  // insert sorting code here.

  checkMergeSortResult(arr, n);

  delete[] arr;

  return EXIT_SUCCESS;
}
