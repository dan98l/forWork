#include <vingraph.h>
#include <stdio.h>
#include <process.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/neutrino.h>

int gen(){
	int top = rand()%10+1;
	return top;	
}

bool zhrat(int food){
		usleep(1000000);
		food--;
		if(food == 0) return 0;
		else return 1;
}

void funiculer(){
	usleep(1000000);
	int food = gen();
	if(
}

int main(){
	int chan1 = ChannelCreate(0); 
	int soed1 = ConnectAttach(0,0,chan1,0,0);
	pthread car, RPC, kot1, kot2, kot3, kot4;
	pthread_create(&RPC, 0, gen);
	pthread_create(&kot1, 0, zhrat, (void*) food);
	pthread_create(&kot2, 0, zhrat, (void*) food);
	pthread_create(&kot3, 0, zhrat, (void*) food);
	pthread_create(&kot4, 0, zhrat, (void*) food);
	pthread_create(&car, 0, funiculer);
		
	return 0;
}