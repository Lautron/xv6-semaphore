#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define exit_if_zero(error) if(error == 0){printf("Error in pingpong\n");return 0;}

int
main(int argc, char *argv[])
{
  if(argc != 2){
    exit_if_zero(0);

  }

  int error = 1;

  error = sem_open(0,1); // Ping
  exit_if_zero(error);
  error = sem_open(1,0); // Pong
  exit_if_zero(error);

  int N = atoi(argv[1]);
  
  int pid = fork();
  if(pid < 0){
    exit_if_zero(0);

  }else if(pid == 0){
    for(unsigned int i = 0; i < N; i++){
      error = sem_down(0);
      exit_if_zero(error);
      
      printf("ping\n");

      error = sem_up(1);
      exit_if_zero(error);
    }

  }else{
    for(unsigned int i = 0; i < N; i++){
      error = sem_down(1);
      exit_if_zero(error);

      printf("\tpong\n");

      error = sem_up(0);
      exit_if_zero(error);
    }

    error = sem_close(0);
    exit_if_zero(error);

    error = sem_close(1);
    exit_if_zero(error);
  }

  return 1;
}
