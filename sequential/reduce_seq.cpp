#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <fcntl.h>
#include <omp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

void generateReduceData(int *arr, size_t n);

#ifdef __cplusplus
}
#endif

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <n>\n";
    return -1;
  }

  const auto n = atoi(argv[1]);
  auto *const arr = new int[atoi(argv[1])];

  generateReduceData(arr, atoi(argv[1]));

  // init shared result variable
  auto result = 0;

  // start timing
  const auto start = std::chrono::system_clock::now();

  // reduce
  for (auto i = 0; i < n; ++i) {
    result = result + arr[i];
  }

  // end time
  const auto end = std::chrono::system_clock::now();

  // display result
  std::cout << result << '\n';

  // std::chrono::duration<double> elapsed_seconds = end - start;
  const auto elapsed_seconds =
      static_cast<std::chrono::duration<double>>(end - start);

  std::cerr << elapsed_seconds.count() << '\n';

  delete[] arr;

  return EXIT_SUCCESS;
}
