#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

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

  if (argc < 5) {
    std::cerr << "Usage: " << argv[0]
              << " <n> <num_threads> <scheduling> <granularity>\n";
    return -1;
  }

  const auto n = std::atoi(argv[1]);
  const auto num_threads = std::atoi(argv[2]);
  const auto scheduling_input = std::string{argv[3]};
  const auto granularity = std::atoi(argv[4]);

  auto scheduling_kind = omp_sched_static;
  if (scheduling_input == "static") {
    scheduling_kind = omp_sched_static;
  } else if (scheduling_input == "dynamic") {
    scheduling_kind = omp_sched_dynamic;
  } else if (scheduling_input == "guided") {
    scheduling_kind = omp_sched_guided;
  } else if (scheduling_input == "auto") {
    scheduling_kind = omp_sched_auto;
  } else {
    std::cerr << "Invalid scheduling kind\n";
    return -1;
  }

  omp_set_schedule(scheduling_kind, granularity);

  auto *const arr = new int[n];

  generateReduceData(arr, n);

  const auto start = std::chrono::system_clock::now();

  // reduction code

  auto reduction = 0;

#pragma omp parallel for default(none) num_threads(num_threads) \
    schedule(runtime) reduction(+ : reduction)
  for (auto i = 0; i < n; ++i) {
    reduction += arr[i];
  }

  const auto end = std::chrono::system_clock::now();

  std::cout << reduction << '\n';

  const auto elapsed_seconds =
      static_cast<std::chrono::duration<double>>(end - start);
  std::cerr << elapsed_seconds.count() << '\n';

  delete[] arr;

  return EXIT_SUCCESS;
}
