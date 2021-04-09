#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[])
{
  char *buff[0x100];
  int pid;
  int first = 1;
  if (strcmp("-n", argv[1]) == 0 && strcmp("1", argv[2]) == 0) {
      first = 3;
  }

  int start = 0;
  for (int i = first; i < argc; i++) {
    buff[start++] = argv[i];
  }
  
  char input[0x100];
  int n = read(0, input, 0x100);
  input[n] = 0;
  int index = 0;
  for (int i = 0; i < n; i++) {
    if (input[i] == '\n') {
      input[i] = 0;
      buff[start] = &input[index];
      buff[start+1] = 0;
      index = i + 1;
      pid = fork();
      if (pid == 0) {
        exec(buff[0], &buff[0]);
      }
      else {
        wait(0);
      }
    }
  }
  exit(0);
}