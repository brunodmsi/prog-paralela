#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define THREAD_NUM 2
#define TIMES_TO_ITERATE 100

#define LIGHT_1 1
#define LIGHT_2 2

#define GREEN_LIGHT 30
#define YELLOW_LIGHT 20
#define RED_LIGHT 50

void *lifecycle(void *tmp) {
  int light_id = tmp;
  // printf("%d ", light_id);
  
  int state;  
  if (light_id == LIGHT_1) {
    state = GREEN_LIGHT;
  } else if (light_id == LIGHT_2) {
    state = RED_LIGHT;
  }

  char* currentLightText;
  for (int i = 0; i < TIMES_TO_ITERATE; i++) {
    switch (state) {
      case GREEN_LIGHT:
        currentLightText = "verde";
        break;
      case YELLOW_LIGHT:
        currentLightText = "amarelo";
        break;
      case RED_LIGHT:
        currentLightText = "vermelho";
        break;
    }

    printf("semaforo%d[%s]\n", light_id, currentLightText);
    usleep(state * 100000);

    switch (state) {
      case GREEN_LIGHT:
        state = YELLOW_LIGHT;
        break;
      case YELLOW_LIGHT:
        state = RED_LIGHT;
        break;
      case RED_LIGHT:
        state = GREEN_LIGHT;
        break;
    }
  }
}

int main() {
	pthread_t t1, t2;

	srand(time(NULL));
	
	pthread_create(&t1, NULL, lifecycle, (void *) LIGHT_1);
	pthread_create(&t2, NULL, lifecycle, (void *) LIGHT_2);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

	pthread_exit(NULL);
}
