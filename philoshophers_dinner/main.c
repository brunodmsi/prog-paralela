
/*
  * Centro Universitario do Estado do Para
  * Bruno De Masi e Joao Tome
  * Programacao Paralela (Jack)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int pick_forks(int id, int left_num, int right_num);
void return_forks(int left_num, int right_num);
void pick_token();
void return_token();
void *philosopher(void *num);

#define FAIL 0;
#define SUCCESS 1;


//Globais
int NUM_PHILOSOPHERS;
unsigned TIME_TO_EAT;
unsigned TIME_TO_THINK;
int NUM_TOKENS;
int FOOD_IN_TABLE;
pthread_mutex_t LOCK_NUM_TOKENS;
pthread_mutex_t *FORKS;


void pick_token() {
	int ret = 0;
	while (!ret) {
		pthread_mutex_lock(&LOCK_NUM_TOKENS);
		if (NUM_TOKENS > 0) {
			NUM_TOKENS--;
			ret = 1;
		}
		else {
			ret = 0;
		}
		pthread_mutex_unlock(&LOCK_NUM_TOKENS);
		usleep(100);
	}
}

void return_token(){
	pthread_mutex_lock(&LOCK_NUM_TOKENS);
	NUM_TOKENS++;
	pthread_mutex_unlock(&LOCK_NUM_TOKENS);
}

int pick_forks(int id, int left_num, int right_num) {
	pthread_mutex_lock(&FORKS[left_num]);
	printf("\nTalher %d pego pelo filósofo %d.", left_num, id);
	pthread_mutex_lock(&FORKS[right_num]);
	printf("\nTalher %d pego pelo filósofo %d.", right_num, id);
	return SUCCESS;
}

void return_forks(int left_num, int right_num) {
	pthread_mutex_unlock(&FORKS[left_num]);
	pthread_mutex_unlock(&FORKS[right_num]);
}

void *philosopher(void *num) {
	int id = (int)num;
	int alimentado = 0;
	int left_fork, right_fork;

	left_fork = id;
	right_fork = id+1;

	if (right_fork == NUM_PHILOSOPHERS) { //FORKS dão a volta na mesa
		right_fork = 0;
	}

	while(FOOD_IN_TABLE) {
		printf("\nFilósofo %d está pronto pra comer.", id);
		pick_token();

		printf("\nFilósofo %d sentou-se à mesa. (token %d)", id, NUM_TOKENS);
		pick_forks(id, left_fork, right_fork);

		printf("\nFilósofo %d começou a comer... (FORKS %d, %d)", id, left_fork, right_fork);
		usleep(TIME_TO_EAT * 1000);
		alimentado += TIME_TO_EAT / 100;

		printf("\nFilósofo %d terminou de comer. Total ingerido: %dg", id, alimentado);
		return_forks(left_fork, right_fork);
		return_token();

		printf("\nFilósofo %d levantou-se para pensar...", id);
		usleep(TIME_TO_THINK * 1000);
	}

	printf("\nFilósofo %d acabou de comer.", id);
	return (void *) 0;
}


int main(void) {
	int i;

	printf("\n*** Problema do Jantar dos filosofos ***\n"
			"*** Trabalho 2 de SO1 ***\n"
			"Solucao de N-1 Tokens\n");
	printf("\nNumero filosofos: ");
	scanf("%d", &NUM_PHILOSOPHERS);
	printf("Tempo comendo (ms): ");
	scanf("%d", &TIME_TO_EAT);
	printf("Tempo pensando (ms): ");
	scanf("%d", &TIME_TO_THINK);

	FOOD_IN_TABLE = 1;
	NUM_TOKENS = NUM_PHILOSOPHERS - 1;

	pthread_t philosophers[NUM_PHILOSOPHERS];
	FORKS = malloc(sizeof(pthread_mutex_t) * NUM_PHILOSOPHERS); //aloca array de mutexes de FORKS

	pthread_mutex_init(&LOCK_NUM_TOKENS, NULL);

	for (i=0; i < NUM_PHILOSOPHERS; i++) {
		pthread_mutex_init(&FORKS[i], NULL);
	}

	for (i=0; i < NUM_PHILOSOPHERS; i++) {
		pthread_create(&philosophers[i], NULL, philosopher, (void *) i);
	}

	for (i=0; i < NUM_PHILOSOPHERS; i++) {
		pthread_join(philosophers[i], NULL);
	}

	return EXIT_SUCCESS;
}