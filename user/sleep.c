#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int time;
  if (argc != 2 || (time = atoi(argv[1])) == 0 ) {
    fprintf(2, "sleep time...");
    exit(1);
  }
  else {
    sleep(time);
  }
  exit(0);
}