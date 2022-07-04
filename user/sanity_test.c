#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


void
write_blocks(int fd, int num_of_blocks, char* buf){
    int written;
    int i;
    for(i = 0; i < num_of_blocks; i++){
        written = write(fd, buf, sizeof(buf));
        if(written < 0){
            printf("failed writing direct block number %d\n", i);
            exit(1);
        }
    }
}


void
main(int argc, char *argv[])
{
  int fd;
  char buf[1024];
  char* name = "sanity_test.txt";
  int i;
  //initalize with '0'
  for(i=0; i<1024; i++){
      buf[i] = '0';
  }
  fd = open(name, O_CREATE | O_RDWR);
  if(fd < 0){
      printf("failed\n");
      exit(1);
  }

  //write direct
  write_blocks(fd, 12, buf);
  printf("Finished writing 12KB (direct)\n");
  //write single direct
  write_blocks(fd, 256, buf);
  printf("Finished writing 268KB (single indirect)\n");
  //write double direct
  write_blocks(fd, 256*256, buf);
  printf("Finished writing 10MB (double indirect)\n");

//   unlink(name);
  close(fd);
  exit(0);
}