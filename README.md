# EmbarcaTech   
### TAREFA 2 - U4C2O1234A - V1, Unidade 4 - Capítulo 3
#### Grupo 4 - Subgrupo 7
#### Integrantes:
* Marcel Mascarenhas Andrade
* Davi Nascimento Leao
* Hilquias Rodrigues de Oliveira
* Roberto Vítor Lima Gomes Rodrigues
* Kaique Rangel Da Silva

#### Vídeo de funcionamento
* https://youtu.be/cxncyUd3MmM

#### Instruções de compilação
Certifique-se de que você tem o ambiente configurado conforme abaixo:
* Pico SDK instalado e configurado.
* VSCode com todas as extensões configuradas, CMake e Make instalados.
* Clone o repositório e abra a pasta do projeto, a extensão Pi Pico criará a pasta build
* Clique em Compile na barra inferior, do lado direito (ao lado esquerdo de RUN | PICO SDK)
* Abra o diagram.json
* Clique em Play

#### Manual do programa
Ao executar o programa, todos os leds serão ligados com a cor branca.
A lógica do programa é que ao apertar os botões de números, serão desenhadas animações (em outra cor) a 1,25 frames por segundo (cada animação é mantida por 800 milissegundos).
As animações saem cor branca até o desenho principal, e depois voltam de forma simétrica à tela inicial (cor branca). Cada integrante fez uma animação:
* Para o número 1, o programa desenha um X em verde. (Roberto)
* Para o número 3, o programa desenha um quadrado roxo. (Davi)
* Para o número 4, o programa desenha um M vermelho. (Marcel)
* Para o número 5, o programa desenha uma cruz lilás. (Hilquias)
* Para o número 6, o programa desenha uma estrela rosa. (Kaique)
    * Obs.: em todas as animações, o buzzer é ligado quando as figuras se iniciam e desligado quando chegam na figura principal (X, quadrado, W, cruz).
Para as letras:
* Para a letra A, o programa apaga todas as luzes.
* Para a letra B, o programa liga todas as luzes na cor azul, com 100% de intensidade.
* Para a letra C, o programa liga todas as luzes na cor vermelha, com 80% de intensidade.
* Para a letra D, o programa liga todas as luzes na cor verde, com 50% de intensidade.
* Para o caracter #, o programa liga todas as luzes na cor branca, com 20% de intensidade.
    * Obs.: implementamos o quesito opcional do *, que sai do loop e chama a função de pôr a placa em bootsel.
