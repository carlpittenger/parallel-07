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

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

using fn_type = float (*)(float x, int intensity);

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
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

  if (argc < 9) {
    std::cerr << "Usage: " << argv[0]
              << " <function_id> <a> <b> <n> <intensity> <num_threads> "
                 "<scheduling> <granularity>\n";
    return -1;
  }

  // insert code here

  const auto function_id = atoi(argv[1]);
  const auto a = atof(argv[2]);
  const auto b = atof(argv[3]);
  const auto n = atoi(argv[4]);
  const auto intensity = atoi(argv[5]);
  const auto num_threads = atoi(argv[6]);
  const auto scheduling_input = std::string{argv[7]};
  const auto granularity = atoi(argv[8]);

  auto f = fn_type{f1};

  switch (function_id) {
  case 1:
    f = f1;
    break;
  case 2:
    f = f2;
    break;
  case 3:
    f = f3;
    break;
  default:
    // case 4:
    f = f4;
  }

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

  const auto start = std::chrono::system_clock::now();

  auto sum = 0.0;

#pragma omp parallel for default(none) shared(n, a, b, intensity, f)           \
    num_threads(num_threads) schedule(runtime) reduction(+ : sum)
  for (auto i = 0; i < n; ++i) {
    const auto x = a + (i + 0.5) * (b - a) / n;
    const auto val = f(x, intensity);

    sum += val;
  }

  const auto integrate = sum * (b - a) / n;

  const auto end = std::chrono::system_clock::now();

  std::cout << integrate << '\n';

  const auto elapsed_seconds =
      static_cast<std::chrono::duration<double>>(end - start);
  std::cerr << elapsed_seconds.count() << '\n';

  return EXIT_SUCCESS;
}
