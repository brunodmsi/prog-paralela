#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define THREAD_NUM 3
#define ARR_MAX 5000

int isVowel(char c) {
	if (c == 'a' || c == 'A' || 
			c == 'e' || c == 'E' || 
			c == 'i' || c == 'I' || 
			c == 'o' || c == 'O' || 
			c == 'u' || c == 'U'
	) return 1;
	else return 0;
}

char anne[ARR_MAX];
void *order_array(void *tmp) {
	char new_array[ARR_MAX];
	 
	for(int i = 0; i < ARR_MAX; i++) {
		new_array[i] = anne[i];
	}	

	char temp;
	int i, j, count;
	for (i = 0; i < ARR_MAX - 1; i++) {
		for (j = i + 1; j < ARR_MAX; j++) {
			if (new_array[i] > new_array[j]) {
				temp = new_array[i];
				new_array[i] = new_array[j];
				new_array[j] = temp;
				count++;
				printf("[ORDER THREAD] CHANGES = %d\n", count);
			}
		}
		sleep(1);
	}
}

void *count_vowels(void *tmp) {
	char new_array[ARR_MAX];
	 
	for(int i = 0; i < ARR_MAX; i++) {
		new_array[i] = anne[i];
	}	

	int count = 0;
	for(int i = 0; i < ARR_MAX; i++) {
		if (isVowel(new_array[i])) {
			count++;
			printf("\t[VOWELS THREAD] COUNTER = %d\n", count);
		}
		sleep(1);
	}
}

void *count_consonants(void *tmp) {
	char new_array[ARR_MAX];
	 
	for(int i = 0; i < ARR_MAX; i++) {
		new_array[i] = anne[i];
	}	

	int count = 0;
	for(int i = 0; i < ARR_MAX; i++) {
		if (!isVowel(new_array[i])) {
			count++;
			printf("\t\t[CONSONANTS THREAD] COUNTER = %d\n", count);
		}
		sleep(1);
	}
}

int main() {
	pthread_t lines[THREAD_NUM];

	srand(time(NULL));

	int exec;

	for (int i = 0; i < ARR_MAX; i++) {
		anne[i] = (rand() % (90 - 65)) + 65;
	}
	
	exec = pthread_create(&lines[0], NULL, order_array, (void *) anne);	
	exec = pthread_create(&lines[1], NULL, count_vowels, (void *) anne);
	exec = pthread_create(&lines[2], NULL, count_consonants, (void *) anne);

	pthread_exit(NULL);
}
