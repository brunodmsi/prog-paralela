# Botão aleatório com threading
Atividade parte do desafio de Carnaval com Threading,
```
Criar uma janela (UXI) com um único botao ao centro. A janela deve ter as dimensoes de 500x500 e cada click no botão um contador soma +1.   
- O programa deve fechar em 1min.   
- A cada segundo o botao muda de localização   
- A cada click o tempo de troca de localização do botao deve diminuir.
```

## Como usar?
Você precisa instalar OpenGL e o GLUT (este método é para você que usa um derivado de Debian)
```
sudo apt-get install freeglut3-dev
```
Depois disto você pode rodar o programa usando `./main` ou compilando usando `gcc -o main Screen.c -lglut -lGL -lGLU -lm` e depois rodar.   

