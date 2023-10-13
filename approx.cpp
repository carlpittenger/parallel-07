#include <cmath>
#include <cstdio>
#include <cstdlib>

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
  if (argc != 3) {
    return EXIT_FAILURE;
  }

  // atof is an unsafe function
  // really should use
  // strtof and check error float b = atof(argv[2]);
  // float a = atof(argv[1]);

  float a;
  float b;
  if (std::sscanf(argv[1], "%f", &a) != 1) {
    return EXIT_FAILURE;
  }
  if (std::sscanf(argv[2], "%f", &b) != 1) {
    return EXIT_FAILURE;
  }

  return std::fabs(a - b) > 0.1;
}
