#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define THREAD_NUM 4
#define BOARD_MAX 100
#define NAME_SIZE 50

typedef struct {
  char* nickname;
  double money;
  char status;
  int position;
  int playsCounter;
  float timeToFinish;
} Player;

char* board[BOARD_MAX];
void *game(void *inputPlayer) {
  Player *player;
  player = inputPlayer;

  time_t start, end;
  player->playsCounter = 0;
  char prevStatus;

  _Bool isFinished = 0;
  start = clock();
  while (!isFinished) {
    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;

    prevStatus = player->status;

    if (player->status == 'P') {
      if (dice1 == dice2) {
        // free(player->status);
        player->status = 'L';
      }
    } else if (dice1 == dice2) {
      player->status = 'P';
    } else {
      int positionsToMove = dice1 + dice2;
      if (player->position + positionsToMove >= 100) {
        isFinished = 1;
        continue;
      }

      board[player->position] = " ";
      player->position += positionsToMove;
      board[player->position] = player->nickname;

      if (player->position % 2 == 0) {
        player->money += 79.99;
      } else if (player->position % 2 != 0) {
        player->money += 53.21;
      }
    }
    player->playsCounter += 1;

    char* currStatusText = "";    
    if (prevStatus == 'P' && player->status =='L') {
      currStatusText = "está sendo liberado";
    } else if (prevStatus == 'L' && player->status =='P') {
      currStatusText = "está sendo punido";
    } else if (prevStatus == 'L' && player->status == 'L') {
      currStatusText = "está avançando";
    } else if (prevStatus == 'P' && player->status == 'P') {
      currStatusText = "está preso";
    }
    
    printf("[ %s ]\tPOS: %d \t R$%.2f \t DADOS: %d \t STATUS: %s\n",
      player->nickname,
      player->position,
      player->money,
      dice1 + dice2,
      currStatusText  
    );

    // sleep(1);
  }

  end = clock();
  float totalTime = (float) (end - start) / CLOCKS_PER_SEC;
  player->timeToFinish = totalTime;
}

void remove_newline_ch(char *line) {
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

int main() {
	pthread_t lines[THREAD_NUM];

	srand(time(NULL));
  
  char name1[NAME_SIZE];
  char name2[NAME_SIZE];
  char name3[NAME_SIZE];
  char name4[NAME_SIZE];

  printf("Nome 1 -> ");
  if (fgets(name1, NAME_SIZE, stdin) == NULL) {
    printf("Quer zoar? Fechando...\n\n");
    exit(0);
  }

  printf("Nome 2 -> ");
  if (fgets(name2, NAME_SIZE, stdin) == NULL) {
    printf("Quer zoar? Fechando...\n\n");
    exit(0);
  }

  printf("Nome 3 -> ");
  if (fgets(name3, NAME_SIZE, stdin) == NULL) {
    printf("Quer zoar? Fechando...\n\n");
    exit(0);
  }

  printf("Nome 4 -> ");
  if (fgets(name4, NAME_SIZE, stdin) == NULL) {
    printf("Quer zoar? Fechando...\n\n");
    exit(0);
  }

  remove_newline_ch(name1);
  remove_newline_ch(name2);
  remove_newline_ch(name3);
  remove_newline_ch(name4);

  Player p1, p2, p3, p4;
  p1.nickname = malloc(strlen(name1) + 1);
  p2.nickname = malloc(strlen(name2) + 1);
  p3.nickname = malloc(strlen(name3) + 1);
  p4.nickname = malloc(strlen(name4) + 1);
  strcpy(p1.nickname, name1);
  strcpy(p2.nickname, name2);
  strcpy(p3.nickname, name3);
  strcpy(p4.nickname, name4);
  p1.status = 'L';
  p2.status = 'L';
  p3.status = 'L';
  p4.status = 'L';
  // printf("%s %s %s %s", p1.status, p2.status, p3.status, p4.status);
  p1.money = 0.0;
  p2.money = 0.0;
  p3.money = 0.0;
  p4.money = 0.0;
  p1.position = 0;
  p2.position = 0;
  p3.position = 0;
  p4.position = 0;
  
	for(int i = 0; i < BOARD_MAX; i++) {
		board[i] = " ";
	}	

	int exec;
	
	exec = pthread_create(&lines[0], NULL, game, &p1);
	exec = pthread_create(&lines[1], NULL, game, &p2);
	exec = pthread_create(&lines[2], NULL, game, &p3);
	exec = pthread_create(&lines[3], NULL, game, &p4);

  sleep(1);

  float money[4];
  money[0] = p1.money;
  money[1] = p2.money;
  money[2] = p3.money;
  money[3] = p4.money;
  
  float richest = money[0];
  int location_money;
  for (int c = 1; c < THREAD_NUM; c++) {
    if (money[c] > richest)
    {
       richest  = money[c];
       location_money = c+1;
    }
  }

  float time[4];
  time[0] = p1.timeToFinish;
  time[1] = p2.timeToFinish;
  time[2] = p3.timeToFinish;
  time[3] = p4.timeToFinish;

  float fastest = time[0];
  int location_time = 0;
  for (int c = 1; c < THREAD_NUM; c++) {
    if (time[c] < fastest)
    {
       fastest  = time[c];
       location_time = c+1;
    }
  }

  printf("\n\n---  FINAL  ---\n\n");

  printf("[ %s ]\tRODADAS: %d\tR$%.2f\tTempo(ms): %f\n",
    p1.nickname,
    p1.playsCounter,
    p1.money,
    p1.timeToFinish
  );
  printf("[ %s ]\tRODADAS: %d\tR$%.2f\tTempo(ms): %f\n",
    p2.nickname,
    p2.playsCounter,
    p2.money,
    p2.timeToFinish
  );
  printf("[ %s ]\tRODADAS: %d\tR$%.2f\tTempo(ms): %f\n",
    p3.nickname,
    p3.playsCounter,
    p3.money,
    p3.timeToFinish
  );
  printf("[ %s ]\tRODADAS: %d\tR$%.2f\tTempo(ms): %f\n",
    p4.nickname,
    p4.playsCounter,
    p4.money,
    p4.timeToFinish
  );

  Player players[THREAD_NUM];
  players[0] = p1;
  players[1] = p2;
  players[2] = p3;
  players[3] = p4;

  printf("\n\nMais R$: \t%s\n", players[location_money - 1].nickname);
  printf("Mais rapido: \t%s\n\n", players[location_time - 1].nickname);

	pthread_exit(NULL);

  // printf("")
}
