#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "pqueue.h"

char *filename = "queue.dat";

int itemId = 1;

typedef struct item item;
struct item {
	int id;
};


item *
produce() {
	int time = rand() % 5 + 1;
	item *it = (item *)malloc(sizeof(item));
	
	sleep(time);
	it->id = itemId;
	itemId += 1;
	return it;
}

void
consume(item *it) {
	int time = rand() % 5 + 1;
	sleep(time);
	free(it);
}

void
myPrint(void* data){
	printf("%d",((item*)data)->id);
}

void
producer(pid_t childPid) {
//	printf("macierzysty %d\n", getpid());	
	while(1){
		pqueue *q;
		item *it = produce();
		int k = rand() % 5 + 1;

		qunserialize(&q, sizeof(item), filename);
		qinsert(&q, it, k);
		qserialize(q, sizeof(item), filename);

		printf("after produced: %d\n", it->id);
		qlist(q, myPrint);
		printf("\n");

		//free memory
		free(it);
		while(q != NULL){
			pqueue* temp = q;
			q = q->next;
			free(temp);
		}
	}
}

void
consumer() {
//	printf("potomny %d\n", getpid());	
	while(1){
		pqueue *q;
		pqueue *poped;
	
		qunserialize(&q, sizeof(item), filename);
		if(q == NULL){
			continue;
		}
	
		poped = qpop(&q);
		qserialize(q, sizeof(item), filename);
		
		int id = ((item*)poped->data)->id;
		printf("after consumed: %d\n", id);
		qlist(q, myPrint);
		printf("\n");
	
		consume(poped->data);

		//free memory
		free(poped);
		while(q != NULL){
			pqueue* temp = q;
			q = q->next;
			free(temp);
		}
	}
}

int
main(int argc, char **argv) {
	pid_t pid;
	pqueue *qu = NULL;
	/* watch -n 1 ps -l --forest */
	
	/* create empty queue */
	qserialize(qu, sizeof(item), filename);
	
	pid = fork();
	if(pid == 0){
		consumer();
	}
	else {
		producer(pid);
	}

	return 0;
}
