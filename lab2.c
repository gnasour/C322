#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc,char *argv[])
{
  pid_t pid;
  int system(const char *command);
  int parentPID = getpid();
  int fileCounter=1;
  int newARGC = argc;

  for(argc; argc > 1; argc--){
   pid =  fork();
   if( pid < 0){
     printf("ERROR IN FORK\n");
   }//error
   else if(pid == 0){
      printf("Filename: %s \t  PID: %d\n", argv[fileCounter], getpid());
      exit(0);
   }//child if
   fileCounter++;
  }//for loop
  for(newARGC; newARGC > 1; newARGC--){
    wait();
  }//wait for loop
  //  if(getpid()==parentPID){
  system("ps -H");
  printf("DONE\n");
    //}
}//main
