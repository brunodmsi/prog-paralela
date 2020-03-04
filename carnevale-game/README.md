# 3 threads, 3 atividades
Jogo de Desafio de Carnaval.   
A declaração dele é a seguinte: 
```
Escreva um programa que possa simular um jogo de tabuleiro onde um número 4 jogadores devem percorrer todas as 100 (cem) casas de um tabuleiro. Os jogadores são munidos de dois dados de seis faces e jogam sem turnos, ou seja, cada um joga sem parar.   
   
Cada jogador deve possuir, no mínimo, um nome (nickname), dois dados e começa com R$0,00 de dinheiro. Enquanto percorre o tabuleiro cada um juntará um montante em dinheiro. As jogadas dos jogadores se baseiam em rolar seus dados, observar os valores obtidos nos dados e percorrer o tabuleiro.   
```
   
**Regras**:   
1.  Quando o jogador tirar valores iguais nos dados, deverá permanecer PRESO na mesma casa do tabuleiro e continua rolando os dados sem se mexer até que consiga tirar valores de dados dobrados novamente, aí estará livre. OBS:. Uma vez livre, o jogador não anda o valor que tirou nos dados dobrados que o libertaram, e sim, o valor obtido nos dados na jogada seguinte.    
2. Quando o jogador não cair em nenhuma das regras citadas anteriormente, então deverá apenas avançar no tabuleiro o número de casas obtido nos dados.     
3. Cada jogador deve informar seus passos na medida que vão acontecendo. Faça com que cada jogador imprima as seguintes informações: nome do jogador, valor tirado nos dados, em que casa do tabuleiro se encontra, valor arrecadado e seu status (se está sendo punido, preso, libertado ou se está avançando).     
4. O jogo termina quando todos os jogadores chegam ao final do tabuleiro, ou seja, na casa número 100.    
5. Cada vez que o jogador cair em alguma casa PAR do tabuleiro, ele será recompensado com o valor de R$79,99.     
6. Cada vez que o jogador cair em alguma casa IMPAR do tabuleiro, ele será recompensado com o valor de R$53,21.   
7. Com o jogo finalizado imprima para cada jogador:- Nome, Quantidade de jogadas, Valor total arrecadado.    
8. Marque, de alguma forma, o jogador mais rápido e o mais rico.   
   
## Como usar?
Gere o arquivo main usando ```gcc -o main Program.c -lpthread``` e apos isso, execute o arquivo gerado com ```./main```
~                                                                                                                                                                                                                  
~                                                                                                                          