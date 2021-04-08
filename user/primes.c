#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int a[35], pid;
  for (int i = 0; i < 33; i++) {
    a[i] = i + 2;
  }
  a[33] = 0;
  a[34] = 0;
  int first = 1;
  while(1) {
    int fds[2];
    pipe(fds);
    pid = fork();
    if (pid > 0) {
      close(fds[0]);
      int len = 0;
      for (int i = 0; i < 35; i++) {
        if (a[i] == 0) {
          len  = i;
          break;
        }
      }
      write(fds[1], a, len * sizeof(int));
      close(fds[1]);
      while(wait(0) != -1);
      exit(0);
    }
    else {
      close(fds[1]);
      int n = read(fds[0], a, sizeof(int) * 35);
      if (n == 0) {
        exit(0);
      }
      first = a[0];
      printf("prime %d\n", first);
      int buff[35];
      int len = 0;
      for (int i = 0; i < n / 4; i++) {
        if (a[i] % first != 0) {
          buff[len++] = a[i];  
        }
      }
      for (int i = 0; i < len; i++) {
        a[i] = buff[i];
      }
      for (int i = len; i < 35; i++) {
        a[i] = 0;
      }
      close(fds[0]);
    }
  }
  exit(0);
}