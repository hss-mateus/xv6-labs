#include "../kernel/types.h"
#include "user.h"

int main() {
  int parent_pipe[2];
  int child_pipe[2];

  char *msg = "a";
  char len = 1;
  char buf[1];

  pipe(parent_pipe);
  pipe(child_pipe);

  int is_parent = fork();
  int pid = getpid();

  if (is_parent) {
    write(child_pipe[1], msg, len);
    read(parent_pipe[0], buf, len);
    printf("%d: received pong\n", pid);
  } else {
    read(child_pipe[0], buf, len);
    printf("%d: received ping\n", pid);
    write(parent_pipe[1], msg, len);
  }

  exit(0);
}
