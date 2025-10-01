# Sistema Solar (OpenGL/GLUT)
## Oque o programa faz:  

Pequena simulação do sistema solar para estudos de computação gráfica.  

## Passos para compilação e execução do programa:
#1  Instalação do pacote de desenvolvimento do FreeGLUT  
```bash
sudo apt-get install freeglut3-dev
```

#2 Instalação do pacote da biblioteca SOIL
```bash
sudo apt-get install libsoil-dev
```

#3 Compilação e execução do código
```bash
g++ src/main.cpp  src/astro.cpp src/camera.cpp src/textura.cpp -o sis -lGL -lGLU -lSOIL -lglut -lm  && ./sis
```

## Texturas
Site com as texturas: https://www.solarsystemscope.com/textures/

## Imagens do projeto

 <img src="./assets/terra.png" alt="Imagem da Terra" width="85%" />
</p>

 <img src="./assets/sis_solar.png" alt="Cena geral do sistema solar" width="85%" />
</p>

## Principais problemas encontrados:

Alterar as propriedades do material(Sol) para que deixe ele emitindo luz,problemas para achar os melhores valores para as rotações e translações dos planetas.

## O que pode ser melhorado:  

Melhorar as texturas, colocar o cinturão de cometas e fazer o anel de saturno melhorado.

## O que cada integrante fez:

No geral fizemos juntos em call, porém Rodrigo e João Marcelo focando em iluminação,textura,camera,teclas de movimento e Anderson no posicionamento dos planetas
e movimento deles(rotação e translação).

