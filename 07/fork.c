#include <bits/types/struct_timeval.h>
#include <errno.h>
#include <libgen.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

//1 -> 2 SIGUSR1;   2 -> (3,4) SIGUSR2; 4 -> 5 SIGUSR1; 3 -> 6 SIGUSR1; 6 -> 7 SIGUSR1; 7 -> 8 SIGUSR1; 8 -> 1 SIGUSR1
//1 -> 2; 2 -> (3, 4); 4 -> 5; 3 -> 6; 6 -> 7; 7 -> 8

/* DATA */

#define PROCESSES_COUNT 9
#define PARENTS_COUNT 7

static int RECEIVERS_IDS[PROCESSES_COUNT] = { -1, 2, 3, 6, 5, -1, 7, 8, 1 };
static int SIGNALS_TO_SEND[PROCESSES_COUNT] = { -1, SIGUSR1, SIGUSR2, SIGUSR1, SIGUSR1, -1, SIGUSR1, SIGUSR1, SIGUSR1 };
static int GROUPS_INFO[PROCESSES_COUNT] = { 0, 1, 2, 3, 3, 5, 6, 7, 8 };

typedef struct {
	int process_number;
	int children_count;
	int *children;
} info;

void createForkingScheme(info *tree) {
	int sus = 0;
	tree[sus].process_number = 0;
	tree[sus].children_count = 1;
	tree[sus].children = malloc(sizeof(int));
	tree[sus].children[0] = 1;
	sus++;
	tree[sus].process_number = 1;
	tree[sus].children_count = 1;
	tree[sus].children = malloc(sizeof(int));
	tree[sus].children[0] = 2;
	sus++;
	tree[sus].process_number = 2;
	tree[sus].children_count = 2;
	tree[sus].children = malloc(sizeof(int) * 2);
	tree[sus].children[0] = 3;
	tree[sus].children[1] = 4;
	sus++;
	tree[sus].process_number = 4;
	tree[sus].children_count = 1;
	tree[sus].children = malloc(sizeof(int));
	tree[sus].children[0] = 5;
	sus++;
	tree[sus].process_number = 3;
	tree[sus].children_count = 1;
	tree[sus].children = malloc(sizeof(int));
	tree[sus].children[0] = 6;
	sus++;
	tree[sus].process_number = 6;
	tree[sus].children_count = 1;
	tree[sus].children = malloc(sizeof(int));
	tree[sus].children[0] = 7;
	sus++;
	tree[sus].process_number = 7;
	tree[sus].children_count = 1;
	tree[sus].children = malloc(sizeof(int));
	tree[sus].children[0] = 8;
}

/* UTILS */
long long currentTime() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_usec / 1000;
}

char* signalName(int signum) {
	switch (signum) {
	case SIGUSR1:
		return "USR1";
	case SIGUSR2:
		return "USR2";
	default:
		return "not found";
	}
}

void printInfo(int process_number, char is_received, int signal_number) {
	if (is_received) {
		printf("%d [%d] received %s  from %d; %lld\n", process_number, getpid(), signalName(signal_number), getppid(), currentTime());
	} else {
		printf("%d [%d] sent     %s; ppid %d; %lld\n", process_number, getpid(), signalName(signal_number), getppid(), currentTime());
	}
	fflush(stdout);
}

void printStat(int usr1_count, int usr2_count) {
	printf("%d %d finished after USR1 №%d and USR2 №%d\n", getpid(), getppid(), usr1_count, usr2_count);
}

/* PROGRAM BODY */

char *MODULE_NAME;
int *PROCESSES_PIDS;
int PROCESS_NUMBER = 0;
int sig_received = 0;
int sig_usr1_sent = 0;
int sig_usr2_sent = 0;
info *FORKING_SCHEME;

info* getForkInfo(int process_number, info *tree) {
	for (int i = 0; i < PARENTS_COUNT; i++) {
		if (tree[i].process_number == process_number) {
			return &(tree[i]);
		}
	}
	return NULL;
}

void signalHandler(int signum) {
	//if not killer
	if (signum != SIGTERM) {
		//receiver
		printInfo(PROCESS_NUMBER, 1, signum);
		int receiver_number = RECEIVERS_IDS[PROCESS_NUMBER];
		sig_received++;
		if (PROCESS_NUMBER == 1) {
			//off after parent got 101
			if (sig_received == 101) {
				//kill children and wait
				kill(-PROCESSES_PIDS[RECEIVERS_IDS[PROCESS_NUMBER]], SIGTERM);
				while (wait(NULL) > 0) {
				}
				exit(0);
			}
		}
		//if he shouldn't skip signals
		if (receiver_number != -1) {
			//choose needed basing on our process
			int signal_to_send = SIGNALS_TO_SEND[PROCESS_NUMBER];
			usleep(100);
			if (kill(-PROCESSES_PIDS[RECEIVERS_IDS[PROCESS_NUMBER]], signal_to_send) == -1) {
				exit(1);
			} else {
				//sender
				printInfo(PROCESS_NUMBER, 0, signal_to_send);
				//count signals
				if (signal_to_send == SIGUSR1) {
					sig_usr1_sent++;
				} else {
					sig_usr2_sent++;
				}
			}
		}
	} else {
		kill(-PROCESSES_PIDS[RECEIVERS_IDS[PROCESS_NUMBER]], SIGTERM);
		while (wait(NULL) > 0) {
		}
		//first will be shown after
		if (PROCESS_NUMBER != 1) {
			printStat(sig_usr1_sent, sig_usr2_sent);
		}
		exit(0);
	}
}

void clearForkingScheme(info *tree) {
	for (int i = 0; i < PARENTS_COUNT; i++) {
		free(tree[i].children);
	}
	free(tree);
}

char isAllSet(pid_t *process_pids) {
	for (int i = 0; i < PROCESSES_COUNT; i++) {
		if (!process_pids[i]) {
			return 0;
		}
	}
	return 1;
}

void startProcess() {
	PROCESSES_PIDS[0] = getpid();
	int forked_process_number;
	int child_number = 0;
	pid_t group_leader;
	info *forking_info;

	struct sigaction sig_handler;
	sig_handler.sa_handler = &signalHandler;
	sig_handler.sa_flags = 0;
	sigset_t sigset;
	//clear
	sigemptyset(&sigset);

	//fork all existing children
	while ((forking_info = getForkInfo(PROCESS_NUMBER, FORKING_SCHEME)) && (child_number < forking_info->children_count)) {
		forked_process_number = forking_info->children[child_number]; //child value
		pid_t child = fork();
		switch (child) {
		case 0: //child only
			child_number = 0;
			PROCESS_NUMBER = forked_process_number; //child value
			break;
		case -1: //error only
			exit(1);
		default: //parent only
			while (!(group_leader = PROCESSES_PIDS[GROUPS_INFO[forked_process_number]])) {
			}
			//set leader id to children, either fail
			if (setpgid(child, group_leader) == -1) {
				exit(1);
			}
			child_number++; //next
		}
	}
	//set own handler and do signals
	sigaction(SIGUSR1, &sig_handler, 0);
	sigaction(SIGUSR2, &sig_handler, 0);
	sigaction(SIGTERM, &sig_handler, 0);
	PROCESSES_PIDS[PROCESS_NUMBER] = getpid();
	if (PROCESS_NUMBER == 1) {
		while (!isAllSet(PROCESSES_PIDS)) {
		}
		int signal_to_send = SIGNALS_TO_SEND[PROCESS_NUMBER];
		kill(-PROCESSES_PIDS[RECEIVERS_IDS[PROCESS_NUMBER]], signal_to_send);
		printInfo(PROCESS_NUMBER, 0, signal_to_send);
	}
	if (PROCESS_NUMBER == 0) {
		wait(NULL);
		return;
	}
	while (1) {
		sleep(1);
	};
}

int main(int argc, char *argv[]) {
	MODULE_NAME = basename(argv[0]);
	FORKING_SCHEME = malloc(sizeof(info) * PARENTS_COUNT);
	createForkingScheme(FORKING_SCHEME);
	//включение отображения объекта в адресное пространство процесса
	PROCESSES_PIDS = mmap(NULL, PROCESSES_COUNT * sizeof(pid_t),
	PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	startProcess();
	//отключение отображения объекта в адресное пространство процесса
	munmap(PROCESSES_PIDS, sizeof(pid_t) * PROCESSES_COUNT);
	clearForkingScheme(FORKING_SCHEME);
	return 0;
}
