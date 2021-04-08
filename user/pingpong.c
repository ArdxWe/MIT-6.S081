#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int fds[2], pid;
  pipe(fds);
  pid = fork();
  if(pid == 0) {
    char buffer[0x100];
    int n = read(fds[0], buffer, 0x100);
    if (n > 0) {
      printf("%d: received ping\n", getpid());
      close(fds[0]);
      write(fds[1], "f", 1);
      close(fds[1]);
      exit(0);
    }
    else {
      exit(1);
    }
  }
  else {
    write(fds[1], "f", 1);
    close(fds[1]);
    char buffer[0x100];
    wait(0);
    int n = read(fds[0], buffer, 0x100);
    if (n > 0) {
      printf("%d: received pong\n", getpid());
      close(fds[0]);
      exit(0);
    }
    else {
      exit(1);
    }
  } 
  exit(0);
}