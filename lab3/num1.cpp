#include <sys/neutrino.h>
#include <vingraph.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int flag = 1;

struct st {
	int vwch;
	int vpch;
	int vcoid;
	int pcoid;
	int potid;
};

void* pot_thread(void *param) {
	struct st *ptr = (struct st*) param;
	char buf = 0;
	char potid = ptr->potid;
	int fuel = 0;

	int n = 10;
	int *arr = (int*)calloc(n, sizeof(int));

	while (flag) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;

		MsgSend(ptr->pcoid, (void*)&potid, 1, (void*)&buf, 1);

		fuel = buf;
		for (int i = 0; i < fuel; i++) {
			arr[i] = Rect(290 + 50 * potid, 150 + i * 30, 30, 30,  RGB(255, 255, 0));
			Fill(arr[i], RGB(255, 255, 0));
			usleep(50000);
		}

		while (fuel) {
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

	int rect = Rect(110, 110, 25, 25, RGB(255, 0, 0));
	Fill(rect, RGB(255, 0, 0));

	while (flag){
		msgid = MsgReceive(ptr->vpch, (void*)&potid, 1, 0);

		MsgSend(ptr->vcoid, NULL, 0, (void*)&buf, 1);
		
		fuel = buf;
		
		Fill(rect, RGB(0, 255, 0));
		for (int i = 110; i < 310 + potid * 50; i++) {
			MoveTo(i, 110, rect);
			usleep(1000);
		}

		MsgReply(msgid, 0, (void*)&buf, 1);

		usleep(50000 * fuel);
		Fill(rect, RGB(255, 0, 0));

		for (int i = 310 + potid * 50; i > 110; i--) {
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

		fuel = rand() % n + 1;
		for (int i = 0; i < fuel; i++) {
			arr[i] = Rect(100, 150 + i * 30, 30, 30,  RGB(255, 255, 0));
			Fill(arr[i], RGB(255, 255, 0));
			usleep(200000);
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
	struct st common;

	common.vwch = ChannelCreate(0);
	common.vpch = ChannelCreate(0);

	common.vcoid = ConnectAttach(0, 0, common.vwch, 0, 0);
	common.pcoid = ConnectAttach(0, 0, common.vpch, 0, 0);

	ConnectGraph();

	pthread_t vtid, wtid;
	pthread_create(&vtid, NULL, vehicle_thread, (void*) &common);
	pthread_create(&wtid, NULL, warehouse_thread, (void*)&common);

	pthread_t ptid1, ptid2, ptid3, ptid4;

	common.potid = 1;
	pthread_create(&ptid1, NULL, pot_thread, (void*)&common);
	usleep(1000);

	common.potid = 2;
	pthread_create(&ptid2, NULL, pot_thread, (void*)&common);
	usleep(1000);

	common.potid = 3;
	pthread_create(&ptid3, NULL, pot_thread, (void*)&common);
	usleep(1000);

	common.potid = 4;
	pthread_create(&ptid4, NULL, pot_thread, (void*)&common);
	usleep(1000);

	InputChar();
	flag = 0;
	
	pthread_join(vtid, NULL);
	pthread_join(wtid, NULL);

	pthread_join(ptid1, NULL);
	pthread_join(ptid2, NULL);
	pthread_join(ptid3, NULL);
	pthread_join(ptid4, NULL);

	CloseGraph();
	
	return 0;
}
