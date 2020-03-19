# Semaforo controlado por ciclo de vida
Atividade feita como atividade de faculdade  

### Desafio
Semáforo - escrever um programa que declare dois
objetos que funcionam como semáforos. Cada semáforo
é uma `thread` e controla de forma `independente` o seu
tempo de troca de sinal.   
   
Utilize a controle de troca por ciclo de vida com a
função sleep para que o semáforo permaneça por algum
tempo num estado até trocar para outro:   
`VERDE - deve permanecer 30ms`    
`AMARELO - deve permanecer 20ms`   
`VERMELHO - deve permanecer 50ms`    
    
Inicie o primeiro semáforo no estado `VERDE` e o segundo
em `VERMELHO` para ter um efeito parecido com o abaixo   
    
```
semaforo1[verde] semaforo2[vermelho]   
semaforo1[amarelo] semaforo2[vermelho]   
semaforo1[vermelho] semaforo2[verde]   
``` 
    
... repita por `100 vezes` as trocas em cada semáforo


## Como usar?
Gere o arquivo main usando ```gcc -o main main.c -lpthread``` e apos isso, execute o arquivo gerado com ```./main```
