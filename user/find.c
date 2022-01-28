#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"
#include "../kernel/fs.h"

int find(char *path, char *name) {
  int fd = open(path, 0);

  if (fd < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    close(fd);

    return -1;
  }

  struct stat st;

  if (fstat(fd, &st) == -1) {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);

    return -1;
  }

  if (st.type == T_DIR) {
    struct dirent de;

    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (!strcmp(".", de.name) ||
          !strcmp("..", de.name) ||
          !strcmp("", de.name)) continue;

      if (!strcmp(name, de.name)) {
        printf("%s/%s\n", path, de.name);
      }

      char new_path[strlen(path) + strlen(de.name) + 1];

      strcpy(new_path, path);
      new_path[strlen(path)] = '/';
      strcpy(&new_path[strlen(path) + 1], de.name);

      find(new_path, name);
    }
  }

  close(fd);

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("usage: find [directory] [name]\n");
    exit(0);
  }

  char *path = argv[1];
  char *name = argv[2];

  if (find(path, name) == -1) exit(1);

  exit(0);
}
