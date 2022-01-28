#include "../kernel/types.h"
#include "user.h"

int is_prime(int n) {
  for (int i = 2; i < n; i++)
    if (n % i == 0) return 0;

  return 1;
}

int write_n(int fd, int n) {
  uint64 n_ptr[] = {n};
  return write(fd, n_ptr, sizeof(uint64));
}

int read_n(int fd) {
  uint64 n;
  read(fd, &n, sizeof(uint64));

  return n;
}

void transfer(int prime, int left_fd, int right_fd) {
  int i;

  while ((i = read_n(left_fd))) {
    if (i % prime != 0)
      write_n(right_fd, i);
  }

  write_n(right_fd, 0);
}

int main() {
  int fds[2];

  pipe(fds);

  for (int i = 2; i <= 35; i++) {
    write_n(fds[1], i);
  }

  write_n(fds[1], 0);

  int n;

  while ((n = read_n(fds[0]))) {
    close(fds[1]);

    int left_fd = fds[0];

    if (!is_prime(n)) continue;

    printf("prime %d\n", n);

    pipe(fds);

    int right_fd = fds[1];

    if (fork()) {
      close(fds[0]);

      transfer(n, left_fd, right_fd);

      close(left_fd);
      close(right_fd);

      wait(0);

      break;
    }
  }

  exit(0);
}
