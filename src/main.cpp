
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include "../include/astro.h"
#include "../include/camera.h"
#include "../include/textura.h"

#define PROPORCAO_SOL_MERCURIO   80
#define RAIO_MERCURIO            0.5
#define DISTANCIA_MERCURIO       50
#define VEL_ROTACAO_MERCURIO     0.1f
#define VEL_TRANSLACAO_MERCURIO  10.0f

#define SENSE_MOUSE 0.002f

// GLfloat lookfrom[3] = {80.0f, 20.0f, 200.0f};
// GLfloat lookat[3]   = {0.0f , -0.1f, -0.1f};

GLfloat lookfrom[3] = {75.0f, 0.0f, 0.0f};
GLfloat lookat[3]   = {100.0f , -0.1f, -0.1f};


Astro mercurio(     DISTANCIA_MERCURIO,      RAIO_MERCURIO,   0.01f,      VEL_ROTACAO_MERCURIO,        VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro venus   (1.3 *DISTANCIA_MERCURIO, 1.2 *RAIO_MERCURIO, 177.30f, 24*VEL_ROTACAO_MERCURIO, 0.39  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro terra   (1.6 *DISTANCIA_MERCURIO, 1.3 *RAIO_MERCURIO,  23.26f, 23.6*VEL_ROTACAO_MERCURIO, 0.24  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro marte   (2.0 *DISTANCIA_MERCURIO, 1.1 *RAIO_MERCURIO,  25.19f, 56.9*VEL_ROTACAO_MERCURIO, 0.13  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro jupiter (2.7 *DISTANCIA_MERCURIO, 8.2 *RAIO_MERCURIO,   3.13f, 143 *VEL_ROTACAO_MERCURIO, 0.02  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro saturno (3.4 *DISTANCIA_MERCURIO, 7.5 *RAIO_MERCURIO,  26.73f, 130 *VEL_ROTACAO_MERCURIO, 0.008 *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro urano   (4.0 *DISTANCIA_MERCURIO, 3.4 *RAIO_MERCURIO,  97.77f, 81.4*VEL_ROTACAO_MERCURIO, 0.003 *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro netuno  (4.5 *DISTANCIA_MERCURIO, 3.0 *RAIO_MERCURIO,  28.32f, 87.5*VEL_ROTACAO_MERCURIO, 0.0015*VEL_TRANSLACAO_MERCURIO, 0, 0, 0);



Astro lua(0.1, 0.2*1.6*RAIO_MERCURIO, 0.0f, 0.0f, 50*VEL_ROTACAO_MERCURIO, 0.0f, 0.0f, 0);

Astro* planetas[8];
Astro* alvo;

GLuint sol_tex, mercurio_tex, venus_tex, terra_tex, marte_tex, jupiter_tex, saturno_tex, urano_tex, netuno_tex, lua_tex, aneis_tex, background_tex;

bool translacaoOn = false;
bool rotacaoOn = true;
bool orbitasOn = false;
bool cameraLocked = false;

bool moveUp = false;
bool moveDown = false;
bool moveLeft = false;
bool moveRight = false;
bool moveFoward = false;
bool moveBackward = false;

float espacamentoAngular = 100.0f;

int lastMouseX;
int lastMouseY;

Camera camera(
    lookfrom[0], lookfrom[1], lookfrom[2],   
    lookat[0],   lookat[1],   lookat[2],    
    0.0f, 0.0f,            
    0.1f, 0.02f      
);

void desenhaOrbita(float distance) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINE_LOOP);
    int numSegments = 1000;
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = cos(angle) * distance;
        float z = sin(angle) * distance;
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void desenhaBackground() {
    
    glPushMatrix();

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, background_tex);
    glColor3f(1.0f, 1.0f, 1.0f);

    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, 300.0f, 50, 50);
    gluDeleteQuadric(quadric);

    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void desenhaAneisSaturno(){
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, aneis_tex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glRotatef(saturno.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);
    glTranslatef(saturno.get_distancia(), 0.0f, 0.0f);
    glRotatef(-saturno.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);
    
    glRotatef(saturno.get_inclinacaoEixo(), 1.0f, 0.0f, 0.0f);
    
    int segments = 300;
    float raioInt = 1.1161478728*saturno.get_raio();
    float raioExt = 2.327404261*saturno.get_raio();

    glBegin(GL_QUAD_STRIP);
    
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = cos(angle);
        float z = sin(angle);
        float sCoord = (float)i / (float)segments;

        glNormal3f(0.0f, 1.0f, 0.0f);

        glTexCoord2f(sCoord, 1.0f);
        glVertex3f(raioExt * x, 0.0f, raioExt * z);

        glTexCoord2f(sCoord, 0.0f);
        glVertex3f(raioInt * x, 0.0f, raioInt * z);
    }
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void desenhaLua(){
    glPushMatrix();

    glRotatef(terra.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);
    glTranslatef(terra.get_distancia(), 0.0f, 0.0f);       
    glRotatef(-terra.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);
    glRotatef(lua.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);

    float anguloOrbitalZ = 5.2*sin(lua.get_anguloTranslacao()*(M_PI/180));
    glRotatef(anguloOrbitalZ, 0.0f, 0.0f, 1.0f);
    glTranslatef((lua.get_raio()+terra.get_raio()+lua.get_distancia())*1.6, 0.0f, 0.0f);
    
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    
    if (lua.get_textura()) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, lua.get_textura());
        glColor3f(1.0f, 1.0f, 1.0f);                    
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
        glDisable(GL_TEXTURE_2D);
    }
    
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, lua.get_raio(), 50, 50);
    gluDeleteQuadric(quadric);

    glPopMatrix();
}

static void desenhaPlaneta(Astro& astro) {

    glPushMatrix();

    if(orbitasOn) {
        desenhaOrbita(astro.get_distancia());
    }

    glRotatef(astro.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);
    glTranslatef(astro.get_distancia(), 0.0f, 0.0f);
    glRotatef(-astro.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);

    glRotatef(astro.get_inclinacaoEixo()-90, 1.0f, 0.0f, 0.0f);
    glRotatef(astro.get_anguloRotacao(), 0.0f, 0.0f, 1.0f);

    if (astro.get_textura()) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, astro.get_textura());
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluSphere(q, astro.get_raio(), 50, 50);
    gluDeleteQuadric(q);

    glPopMatrix();
}

static void desenhaSol() {
    glPushMatrix();

    GLfloat emit[]     = {1.0f, 0.9f, 0.2f, 1.0f};
    GLfloat no_emit[]  = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, emit);

    if (sol_tex) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sol_tex);
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0f, 1.0f, 0.0f);
    }

    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluSphere(q, PROPORCAO_SOL_MERCURIO*RAIO_MERCURIO, 60, 60); 
    gluDeleteQuadric(q);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_emit);
    glPopMatrix();
}

void follow() {
    if (!alvo) 
        return; // evita crash se não tiver alvo selecionado
    camera.set_posZ(alvo->get_distancia() * cos((alvo->get_anguloTranslacao()+espacamentoAngular)*0.0174533));
    camera.set_posX(alvo->get_distancia() * sin((alvo->get_anguloTranslacao()+espacamentoAngular)*0.0174533));
    camera.set_posY(0.0);

    camera.set_angle_hor(-alvo->get_anguloTranslacao()*0.0174533f - 0.1f);
    camera.set_angle_ver(0.0f);
}

static void toggleLock(Astro* novoAlvo, float esp) {
    if (cameraLocked && alvo == novoAlvo) {
        cameraLocked = false;  // destrava se já estava no mesmo
    } else {
        alvo = novoAlvo;
        espacamentoAngular = esp;
        cameraLocked = true;   // trava no novo alvo
    }
}

static void carregaTexturas() {
    
    sol_tex      = loadTexture("assets/sun.jpg");     
    aneis_tex    = loadTexture("assets/saturnRing.png"); 
    mercurio_tex = loadTexture("assets/mercury.jpg"); mercurio.set_textura(mercurio_tex); 
    venus_tex    = loadTexture("assets/venus.jpg");   venus.set_textura(venus_tex);       
    terra_tex    = loadTexture("assets/earth.jpg");   terra.set_textura(terra_tex);       
    marte_tex    = loadTexture("assets/mars.jpg");    marte.set_textura(marte_tex);       
    jupiter_tex  = loadTexture("assets/jupiter.jpg"); jupiter.set_textura(jupiter_tex);   
    saturno_tex  = loadTexture("assets/saturn.jpg");  saturno.set_textura(saturno_tex);  
    urano_tex    = loadTexture("assets/uranus.jpg");  urano.set_textura(urano_tex);       
    netuno_tex   = loadTexture("assets/neptune.jpg"); netuno.set_textura(netuno_tex);  
    
    lua_tex      = loadTexture("assets/moon.jpg");    lua.set_textura(lua_tex);

    

    background_tex = loadTexture("assets/background.jpg");
}

static void initGL() {
    
    planetas[0] = &mercurio;
    planetas[1] = &venus;
    planetas[2] = &terra;
    planetas[3] = &marte;
    planetas[4] = &jupiter;
    planetas[5] = &saturno;
    planetas[6] = &urano;
    planetas[7] = &netuno;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    carregaTexturas(); 
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera.applyView();
    desenhaBackground();

    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat lightDiff[] = {1.0f, 1.0f, 0.95f, 1.0f};
    GLfloat lightAmb[]  = {0.12f, 0.12f, 0.12f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);

    desenhaSol();
    for(Astro *planeta: planetas) {
        desenhaPlaneta(*planeta);
    }

    desenhaAneisSaturno();
    desenhaLua();

    glutSwapBuffers();
}

void update(int value) {
    
    if(translacaoOn) {
        for(Astro *planeta: planetas) {
            planeta->update_anguloTranslacao();
        }
        lua.update_anguloTranslacao();
    }

    if(rotacaoOn) {
        for(Astro *planeta: planetas) {
            planeta->update_anguloRotacao();
        }
    }

    if (cameraLocked) 
        follow();
    else{                                       // Atualiza a posição da câmera com base na direção de visualização
        if (moveFoward) camera.moveForward();       // Se a tecla de mover para frente estiver pressionada
        if (moveBackward) camera.moveBackward();    // Se a tecla de mover para trás estiver pressionada
        if (moveLeft) camera.moveLeft();            // Se a tecla de mover para a esquerda estiver pressionada
        if (moveRight) camera.moveRight();          // Se a tecla de mover para a direita estiver pressionada
        if (moveUp) camera.moveUp();              // Mover a câmera para cima
        if (moveDown) camera.moveDown();          // Mover a câmera para baixo
    }

    camera.updateLookDirection();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void movementKeys(unsigned char key, int x, int y) {
    // Verifica qual tecla foi pressionada e altera o estado das variáveis de movimento da câmera
    switch (key) {
        case 'a':  // Mover a câmera para a esquerda
            moveLeft = !moveLeft; // Alterna o estado do movimento para a esquerda
            break;
        case 'd':  // Mover a câmera para a direita
            moveRight = !moveRight; // Alterna o estado do movimento para a direita
            break;
        case 'w':  // Mover a câmera para frente
            moveFoward = !moveFoward; // Alterna o estado do movimento para frente
            break;
        case 's':  // Mover a câmera para trás
            moveBackward = !moveBackward; // Alterna o estado do movimento para trás
            break;
        case ' ':  // Mover a câmera para cima (eixo y)
            moveUp = !moveUp; // Alterna o estado do movimento para cima
            break;
        case 'c':   // Mover a câmera para baixo (eixo y)
            moveDown = !moveDown; // Alterna o estado do movimento para baixo
            break;
    }
    glutPostRedisplay(); // Solicita uma nova exibição após a mudança de estado
}

void handleKeys(unsigned char key, int x, int y) {
    movementKeys(key, x, y);

    switch (key) {
        case 'o': orbitasOn = !orbitasOn; break;
        case 'r': rotacaoOn = !rotacaoOn; break;
        case 't': translacaoOn = !translacaoOn; break;

        case '1': toggleLock(&mercurio, 88.3f); break;
        case '2': toggleLock(&venus,    88.3f); break;
        case '3': toggleLock(&terra,    88.3f); break;
        case '4': toggleLock(&marte,    88.3f); break;
        case '5': toggleLock(&jupiter,  82.6f); break;
        case '6': toggleLock(&saturno,  82.6f); break;
        case '7': toggleLock(&urano,    87.4f); break;
        case '8': toggleLock(&netuno,   87.8f); break;

        case '0': cameraLocked = false; break; // atalho: destravar sempre

        case 'l': // reset de câmera -> faz sentido também destravar
            camera.set_posX(lookfrom[0]);
            camera.set_posY(lookfrom[1]);
            camera.set_posZ(lookfrom[2]);
            camera.set_angle_hor(0.0f);
            camera.set_angle_ver(0.0f);
            cameraLocked = false; // solta o lock ao resetar
            break;
    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    camera.set_angle_hor(camera.get_angle_hor() + deltaX * SENSE_MOUSE);
    camera.set_angle_ver(camera.get_angle_ver() - deltaY * SENSE_MOUSE);

    lastMouseX = x;
    lastMouseY = y;
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Sistema Solar");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeys);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}