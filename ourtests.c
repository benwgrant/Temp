#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int stdout = 1;

int
main(int argc, char *argv[])
{
  int i;
  int fd;
  fd = open("small", O_CREATE|O_RDWR);

  // Basic setwritecount test
  setwritecount(10);
  int wc = writecount();
  printf(stdout, "writecount: %d\n", wc);
  if(wc != 10){
    printf(stdout, "error: writecount failed\n");
    exit();
  }
  else {
    printf(stdout, "basic writecount test passed\n");
  }

  // Test setwritecount 100 times
  for(i = 0; i < 100; i++){
    setwritecount(53);
  }
  wc = writecount();
  if (wc != 53){
    printf(stdout, "error: failed setting writecount 100 times\n");
    exit();
  }
  else {
    printf(stdout, "setwritecount 100 times passed\n");
  }

  // Write then check writecount
  setwritecount(0);
  write(fd, "this_is_a_test", 14);
  if(writecount() != 1){
    printf(stdout, "error: writecount after 1 write failed\n");
    exit();
  }
  else {
    printf(stdout, "writecount after 1 write passed\n");
  }
  // Write 10 times then check writecount
  setwritecount(0);
  for(i = 0; i < 10; i++){
    write(fd, "this_is_a_test", 14);
  }
  if(writecount() != 10){
    printf(stdout, "error: writecount after 10 writes failed\n");
    exit();
  }
  else {
    printf(stdout, "writecount after 10 writes passed\n");
  }

  // Write 1000 times then check writecount
  setwritecount(0);
  for(i = 0; i < 1000; i++){
    write(fd, "this_is_a_test", 14);
  }
  if(writecount() != 1000){
    printf(stdout, "error: writecount after 1000 writes failed\n");
    exit();
  }
  else {
    printf(stdout, "writecount after 1000 writes passed\n");
  }

  // Test writecount with multiple files
  int fd2 = open("small2", O_CREATE|O_RDWR);
  setwritecount(0);
  write(fd, "this_is_a_test", 14);
  write(fd2, "this_is_a_test", 14);
  if(writecount() != 2){
    printf(stdout, "error: writecount after writing to 2 separate files failed\n");
    exit();
  }
  else {
    printf(stdout, "writecount after writing to 2 separate files passed\n");
  }

  // Test writecount with multiple files and multiple writes
  setwritecount(0);
  for(i = 0; i < 10; i++){
    write(fd, "this_is_a_test", 14);
    write(fd2, "this_is_a_test", 14);
  }
  if(writecount() != 20){
    printf(stdout, "error: writecount after writing to 2 separate files 10 times failed\n");
    exit();
  }
  else {
    printf(stdout, "writecount after writing to 2 separate files 10 times passed\n");
  }

  // Test setwritecount with large numbers
  setwritecount(1000000000);
  wc = writecount();
  if(wc != 1000000000){
    printf(stdout, "error: setwritecount failed to set to 1000000000\n");
    exit();
  }
  else {
    printf(stdout, "setwritecount with 1000000000 passed\n");
  }

  exit();
}
