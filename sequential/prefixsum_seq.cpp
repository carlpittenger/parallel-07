#include <chrono>
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

void generatePrefixSumData(int *arr, size_t n);
void checkPrefixSumResult(int *arr, size_t n);

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
  auto *const arr = new int[n];

  generatePrefixSumData(arr, n);

  const auto start = std::chrono::system_clock::now();

  auto *const prefix = new int[n + 1];

  prefix[0] = 0;

  for (auto i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + arr[i];
  }

  const auto end = std::chrono::system_clock::now();

  const auto elapsed_seconds =
      static_cast<std::chrono::duration<double>>(end - start);

  std::cerr << elapsed_seconds.count() << '\n';

  checkPrefixSumResult(prefix, n);

  delete[] arr;
  delete[] prefix;

  return EXIT_SUCCESS;
}
