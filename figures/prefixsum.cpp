auto prefixsum(const int *const arr, const int n, int *const pr) noexcept
    -> void {
  pr[0] = 0;

  for (auto i = 0; i < n; ++i) {
    pr[i + 1] = pr[i] + arr[i];
  }
}
