#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

void main(int argc,char *argv[])
{
  struct stat perm;
  pid_t pid;
  int system(const char *command);
  int parentPID = getpid();
  int fileCounter=1;
  int newARGC = argc;
  DIR *dp;
  char cwd[1024];
  int waitForDirent = 1;
  struct dirent *ep;
  
  if(argc <2){
    if((dp = opendir("./")) != NULL){
      while((ep =readdir(dp))!=NULL){
	char *nfp = ep -> d_name;
	stat(nfp, &perm);
	pid = fork();
    if( pid < 0){
      printf("ERROR IN FORK\n");
    }//error
    else if(pid == 0){
     
      if(getuid() == perm.st_uid){
        printf("FILE ");
	printf("%s\n", ep ->d_name); 
	printf("DIRECTORY: ");
	if(getcwd(cwd, sizeof(cwd)) != NULL){
	  printf("%s\n", cwd);
        }
	printf("You have owner permissions: ");
	if(perm.st_mode & S_IRUSR){
	  printf("READ");
	}
	if(perm.st_mode & S_IWUSR){
	  printf(" WRITE");
	}
	if(perm.st_mode & S_IXUSR){
	  printf(" EXECUTE");
	}
	printf("\n");
      }
      else if(getgid() == perm.st_gid){
        printf("FILE ");
	printf("%s\n", ep ->d_name);
	printf("DIRECTORY: ");
	if(getcwd(cwd, sizeof(cwd)) != NULL){
	  printf("%s\n", cwd);
        }
	printf("You have group permissions: ");
	if(perm.st_mode & S_IRGRP){
	  printf("READ");
	}
	if(perm.st_mode & S_IWGRP){
	  printf(" WRITE");
	}
	if(perm.st_mode & S_IXGRP){
	  printf(" EXECUTE");
	}
	printf("\n");
      }
      else{
	printf("FILE: ");
	printf("%s\n", ep ->d_name);
	printf("DIRECTORY: ");
	if(getcwd(cwd, sizeof(cwd)) != NULL){
	  printf("%s\n", cwd);
        }
	printf("You have general permissions: ");
	if(perm.st_mode & S_IROTH){
	  printf("READ");
	}
	if(perm.st_mode & S_IWOTH){
	  printf(" WRITE");
	}
	if(perm.st_mode & S_IXOTH){
	  printf(" EXECUTE");
	}
	printf("\n");
      }
      exit(0);
    }//child if
    waitForDirent++;
      }
      closedir(dp);
    }
    else{
      perror("DIRENT");
      exit(EXIT_FAILURE);
    }//ELSE ERROR
  }
  else{
    if(stat(argv[1], &perm)<0){
    perror("stat");
    exit(EXIT_FAILURE);
    }//STAT IF STATEMENT
  for(argc; argc > 1; argc--){
    char *fd = argv[fileCounter];
    stat(fd,&perm);
    dp = opendir("./");
    pid = fork();
    if( pid < 0){
      printf("ERROR IN FORK\n");
    }//error
    else if(pid == 0){
     
      if(getuid() == perm.st_uid){
        printf("FILE %s\n", argv[fileCounter]);
	printf("DIRECTORY: ");
	if(getcwd(cwd, sizeof(cwd)) != NULL){
	  printf("%s\n", cwd);
	  }
	printf("You have owner permissions: ");
	if(perm.st_mode & S_IRUSR){
	  printf("READ");
	}
	if(perm.st_mode & S_IWUSR){
	  printf(" WRITE");
	}
	if(perm.st_mode & S_IXUSR){
	  printf(" EXECUTE");
	}
	printf("\n");
      }
      else if(getgid() == perm.st_gid){
        printf("FILE %s\n", argv[fileCounter]);
	printf("DIRECTORY: ");
	if(getcwd(cwd, sizeof(cwd)) != NULL){
	  printf("%s\n", cwd);
	  }
	printf("You have group permissions: ");
	if(perm.st_mode & S_IRGRP){
	  printf("READ");
	}
	if(perm.st_mode & S_IWGRP){
	  printf(" WRITE");
	}
	if(perm.st_mode & S_IXGRP){
	  printf(" EXECUTE");
	}
	printf("\n");
      }
      else{
	printf("FILE %s\n", argv[fileCounter]);	
	printf("DIRECTORY: ");
	if(getcwd(cwd, sizeof(cwd)) != NULL){
	  printf("%s\n", cwd);
	  }
	printf("You have general permissions: ");
	if(perm.st_mode & S_IROTH){
	  printf("READ");
	}
	if(perm.st_mode & S_IWOTH){
	  printf(" WRITE");
	}
	if(perm.st_mode & S_IXOTH){
	  printf(" EXECUTE");
	}
	printf("\n");
      }
      exit(0);
    }//child if
    fileCounter++;
  }//for loop
  }
  for(newARGC; newARGC > 1; newARGC--){
    wait();
  }//wait for loop
  for(waitForDirent; waitForDirent > 1; waitForDirent--){
    wait();
  }//wait for loop if argc <= 1
  system("ps -H");
  printf("DONE\n");
}//main
