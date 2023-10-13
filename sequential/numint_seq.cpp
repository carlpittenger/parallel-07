#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

float sequential_integrate(int argc, const char *const *argv);

#ifdef __cplusplus
}
#endif

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
  if (argc < 6) {
    std::cerr << "usage: " << argv[0]
              << " <function_id> <a> <b> <n> <intensity>\n";
    return -1;
  }

  const auto start = std::chrono::system_clock::now();

  const auto integrate = sequential_integrate(argc, argv);

  const auto end = std::chrono::system_clock::now();

  std::cout << integrate << '\n';

  const auto elapsed_seconds =
      static_cast<std::chrono::duration<double>>(end - start);

  std::cerr << elapsed_seconds.count() << '\n';

  return EXIT_SUCCESS;
}
