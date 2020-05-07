# Ataque ao Servidor (Sockets)
A tarefa era:  
   
```
Estabelecer um servidor para N conexões de clientes.    
     
Como experimento:     
Ataque o servidor a partir de vários clientes enviando mensagens para o server.    
```

## Requisitos
- Um servidor a qual o cliente possa se conectar
- Usuario escolhe quantos clientes existem
- Mensagens infinitas para o servidor

## Solução
Para se ter um cenário mais real de DDOS (que é o que esse problema acaba implicando), foi desenvolvido um servidor usando TCP, e para o "ataque" foi desenvolvido um script que recebe a quantidade de clientes que desejam se conectar ao servidor, e cada um desses clientes fazem requisições infinitas ao servidor.   

### Como usar
**AVISO: TESTADO APENAS NO UBUNTU VERSAO 20.04**

- Servidor
Para compilar o servidor, rode
```sh
make server
```
e rode usando `./server` 

- Clientes
Dê permissão ao script de clientes rodando 
```sh
chmod +x ./client.sh
```
e use da seguinte forma:
```sh
./client.sh <numero_de_clientes>
```

