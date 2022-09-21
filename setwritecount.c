#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {

  // printf(1, "Argv[1] in user space: %s", argv[1]);
  int newcount = atoi(argv[1]);
  // printf(1, "newcount in user space: %d", newcount);
  setwritecount(newcount);
  exit();
}
