#include <sys/neutrino.h>
#include <vingraph.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int flag = 1;

struct st {
	int vwch;
	int vpch;
	int pulsech;
	int vcoid;
	int pcoid;
	int pulsecoid;
	int potid;
	int vid;
};

void* pot_thread(void *param) {
	struct st *ptr = (struct st*) param;
	char buf = 0;
	char potid = ptr->potid;
	int fuel = 0;

	int n = 10;
	int *arr = (int*)calloc(n, sizeof(int));
	
	//send first pulse to start interaction
	MsgSendPulse (ptr->pulsecoid, 1, potid, 0);

	while (flag) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;

		//request vehicle to unload fuel
		MsgSend(ptr->pcoid, (void*)&potid, 1, (void*)&buf, 1);

		fuel = buf;
		for (int i = 0; i < fuel; i++) {
			arr[i] = Ellipse(290 + 50 * potid, 150 + i * 30, 40, 25, RGB(255, 0, 0));
			Fill(arr[i], RGB(255, 0, 0));
			usleep(50000);
		}

		while (fuel) {
			if (fuel == 2){
				//send pulse on running out of fuel
				MsgSendPulse (ptr->pulsecoid, 1, potid, 0);
			}
			usleep(1000000);
			fuel -= 1;
			Delete(arr[fuel]);
		}
	}
}

void* vehicle_thread(void *param) {
	struct st *ptr = (struct st*) param;
	char buf = 0;
	int fuel = 0;
	char potid = 0;
	int msgid = 0;
	int vid = ptr->vid;
	struct _pulse pulse;

	int rect = Ellipse(160 - vid * 30, 110, 25, 25, RGB(60, 0, 60));
	Fill(rect, RGB(60, 0, 50));

	while (flag){
		//wait for a pulse from a pot
		MsgReceive(ptr->pulsech, (void*)&pulse, sizeof(pulse), 0);

		MsgSend(ptr->vcoid, NULL, 0, (void*)&buf, 1);
		
		fuel = buf;
		
		Fill(rect, RGB(0, 255, 0));
		for (int i = 160 - vid * 30; i < 310 + pulse.code * 50; i++) {
			MoveTo(i, 110, rect);
			usleep(1000);
		}
		
		// recieve a message from pot and reply to send resources
		msgid = MsgReceive(ptr->vpch, (void*)&potid, 1, 0);
		MsgReply(msgid, 0, (void*)&buf, 1);

		usleep(50000 * fuel);
		Fill(rect, RGB(100, 100, 100));

		for (int i = 310 + potid * 50; i > 160 - vid * 30; i--) {
			MoveTo(i, 110, rect);
			usleep(1000);
		}
	}
}

void* warehouse_thread(void *param) {
	struct st *ptr = (struct st*) param;
	
	char buf = 0;
	int fuel = 0;
	int msgid = 0;
	int n = 10;
	int *arr = (int*) calloc(n, sizeof(int));

	while (flag) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;

		fuel = rand() % (n - 5) + 5;
		for (int i = 0; i < fuel; i++) {
			arr[i] = Ellipse(100, 150 + i * 30, 50, 25, RGB(100, 100, 100));
			Fill(arr[i], RGB(100, 100, 100));
			usleep(50000);
		}

		msgid = MsgReceive(ptr->vwch, NULL, 0, 0);

		buf = fuel;
		for (int i = fuel - 1; i >= 0; i--) {
			Delete(arr[i]);
			usleep(50000);
		}

		MsgReply(msgid, 0, (void*)&buf, 1);
	}
}

int main() {
	int fd = 0;
	int chid = 0;
	pid_t pid = 0;
	struct st common;
	
	common.vwch = ChannelCreate(0);
	
	fd = open ("/dev/shmem/EnterElectro", O_CREAT+O_RDWR, 0666);
	pid = getpid();
	write (fd, &pid, 4);
	chid = common.vwch; write (fd, &chid, 4);
	close(fd);

	ConnectGraph();

	pthread_t wtid;
	pthread_create(&wtid, NULL, warehouse_thread, (void*)&common);

	InputChar();
	flag = 0;
	
	pthread_join(wtid, NULL);

	CloseGraph();
	
	return 0;
}
