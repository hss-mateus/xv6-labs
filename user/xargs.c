#include "../kernel/types.h"
#include "../kernel/param.h"
#include "user.h"

int read_line(char* buf) {
  int i = -1;

  while (read(0, buf + (++i), 1) && buf[i] != '\n') {}

  buf[i] = 0;

  return i;
}

int main(int argc, char* argv[MAXARG]) {
  char* args[MAXARG];
  char* cmd = argv[1];
  int i = 0;

  for (int j = 1; j < argc; j++, i++) {
    args[i] = argv[j];
  }

  args[i] = malloc(1024);

  while (read_line(args[i])) {
    if (fork()) {
      wait(0);
    } else {
      exec(cmd, args);
      exit(0);
    }
  }

  exit(0);
}
