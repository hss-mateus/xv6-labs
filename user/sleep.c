#include "../kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    fprintf(2, "error: missing argument\n");
    exit(1);
  }

  int n = atoi(argv[1]);

  sleep(n);
  exit(0);
}

