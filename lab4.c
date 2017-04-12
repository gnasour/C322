#include <stdio.h>
#include <time.h>

void randomwait(); 
void barber_run(); 
void customer_run();

int seats[2]; 
int customers[2]; 
int barber[2]; 
int freeseats[2];

void V(int pd[]) { 
int a=1;
write(pd[1],&a,sizeof(int));
}

void P(int pd[]) { 
int a;
read(pd[0],&a,sizeof(int));
} 

void main() {

pipe(seats); // lock to modify freeseats 
pipe(customers); // how many customers are waiting on seats 
pipe(barber); // barber ready to cut?  0=no 1=yes
pipe(freeseats); // store the integer value for number of seats 

V(seats); // release the lock on seats by setting to 1 

int num=3; // Free Seats = 3
write(freeseats[1],&num,sizeof(int)); 

if (fork() == 0) {  // Start 1 barber
srand(time(0)+11); // Randomized seed 
barber_run(); 
return;
} 
 int i;
 for (i=1;i<=10;i++) { // Start 10 customers randomly
  if (fork() == 0) {
  randomwait(i); // random wait before next customer arrives srand(time(0)+ i); // different seed than barber for different delays
 customer_run(); 
 return;
 }
 }
}
void barber_run() {
  int num,i;
  for (i=1;i<=10;++i) { // at most 10 customers will get their hair cut
  printf("Barber %d is trying to get a customer\n",i);
  P(customers);
  P(seats);
  read(freeseats[0],&num,sizeof(int));
  num++;
  write(freeseats[1],&num,sizeof(int));
  printf("Seats increasing to %d \n", num);
  V(barber);
  V(seats);
  printf("Barber is now cutting hair %d\n",i); 
  randomwait(1); // random wait before finishing haircut
  }
}

void customer_run() {
  int num;
  printf("- New customer trying to find a seat\n");
  P(seats);
  read(freeseats[0],&num,sizeof(int));
  if (num > 0){
    num--;
    write(freeseats[1], &num,sizeof(int));
    printf("Seats decresing to %d \n", num);
    V(customers);
    V(seats);
    P(barber);
  }
  else{
    
    V(seats);
    printf("Customer turned away\n");
    write(freeseats[1], &num, sizeof(int));
    
  }
} 
void randomwait(int d) { // random 0 to d sec delay
  int delay; 
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  delay = abs(rand() % 1000000000) * d; tim.tv_nsec = delay; nanosleep(&tim,&tim2);
}
