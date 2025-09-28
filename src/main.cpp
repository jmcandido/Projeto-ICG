
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include "../include/astro.h"
#include "../include/camera.h"
#include "../include/textura.h"

#define PROPORCAO_SOL_MERCURIO   50
#define RAIO_MERCURIO            0.5
#define DISTANCIA_MERCURIO       50
#define VEL_ROTACAO_MERCURIO     0.01f
#define VEL_TRANSLACAO_MERCURIO  1.0f


Astro mercurio(     DISTANCIA_MERCURIO,      RAIO_MERCURIO,   0.01f,      VEL_ROTACAO_MERCURIO,        VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro venus   (1.3 *DISTANCIA_MERCURIO, 1.2 *RAIO_MERCURIO, 177.30f, 0.24*VEL_ROTACAO_MERCURIO, 0.39  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro terra   (1.6 *DISTANCIA_MERCURIO, 1.3 *RAIO_MERCURIO,  23.26f, 58.6*VEL_ROTACAO_MERCURIO, 0.24  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro marte   (2.0 *DISTANCIA_MERCURIO, 1.1 *RAIO_MERCURIO,  25.19f, 56.9*VEL_ROTACAO_MERCURIO, 0.13  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro jupiter (2.7 *DISTANCIA_MERCURIO, 8.2 *RAIO_MERCURIO,    3.13f, 143*VEL_ROTACAO_MERCURIO, 0.02  *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro saturno (3.4 *DISTANCIA_MERCURIO, 7.5 *RAIO_MERCURIO,   26.73f, 130*VEL_ROTACAO_MERCURIO, 0.008 *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro urano   (4.0 *DISTANCIA_MERCURIO, 3.4 *RAIO_MERCURIO,  97.77f, 81.4*VEL_ROTACAO_MERCURIO, 0.003 *VEL_TRANSLACAO_MERCURIO, 0, 0, 0);
Astro netuno  (4.5 *DISTANCIA_MERCURIO, 3.0 *RAIO_MERCURIO,  28.32f, 87.5*VEL_ROTACAO_MERCURIO, 0.0015*VEL_TRANSLACAO_MERCURIO, 0, 0, 0);

Astro* planetas[8];

GLuint sun_tex, mercury_tex, venus_tex, earth_tex, mars_tex, jupiter_tex, saturn_tex, uranus_tex, neptune_tex;

// Camera camera(
//     0.0f, 25.0f, 80.0f,   
//     0.0f, 0.0f, -1.0f,    
//     0.0f, 0.0f,            
//     0.0f, 0.0f      
// );

Camera camera(
    80.0f, 0.0f, 200.0f,   
    0.0f, 0.0f, -1.0f,    
    0.0f, 0.0f,            
    0.0f, 0.0f      
);

static void desenhaPlaneta(Astro& astro) {

    glPushMatrix();
    glRotatef(astro.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);
    glTranslatef(astro.get_distancia(), 0.0f, 0.0f);
    glRotatef(-astro.get_anguloTranslacao(), 0.0f, 1.0f, 0.0f);

    glRotatef(astro.get_inclinacaoEixo() - 90.0f, 1.0f, 0.0f, 0.0f);
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

    if (sun_tex) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sun_tex);
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

static void carregaTexturas() {
    sun_tex     = loadTexture("assets/sun.jpg");     configurarTextura(sun_tex);
    mercury_tex = loadTexture("assets/mercury.jpg"); configurarTextura(mercury_tex);  mercurio.set_textura(mercury_tex);
    venus_tex   = loadTexture("assets/venus.jpg");   configurarTextura(venus_tex);    venus.set_textura(venus_tex);
    earth_tex   = loadTexture("assets/earth.jpg");   configurarTextura(earth_tex);    terra.set_textura(earth_tex);
    mars_tex    = loadTexture("assets/mars.jpg");    configurarTextura(mars_tex);     marte.set_textura(mars_tex);
    jupiter_tex = loadTexture("assets/jupiter.jpg"); configurarTextura(jupiter_tex);  jupiter.set_textura(jupiter_tex);
    saturn_tex  = loadTexture("assets/saturn.jpg");  configurarTextura(saturn_tex);   saturno.set_textura(saturn_tex);
    uranus_tex  = loadTexture("assets/uranus.jpg");  configurarTextura(uranus_tex);   urano.set_textura(uranus_tex);
    neptune_tex = loadTexture("assets/neptune.jpg"); configurarTextura(neptune_tex);  netuno.set_textura(neptune_tex);
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

    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat lightDiff[] = {1.0f, 1.0f, 0.95f, 1.0f};
    GLfloat lightAmb[]  = {0.12f, 0.12f, 0.12f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);

    desenhaSol();
    desenhaPlaneta(mercurio);
    desenhaPlaneta(venus);
    desenhaPlaneta(terra);
    desenhaPlaneta(marte);
    desenhaPlaneta(jupiter);
    desenhaPlaneta(saturno);
    desenhaPlaneta(urano);
    desenhaPlaneta(netuno);

    glutSwapBuffers();
}

void update(int value) {
    
    for(Astro *planeta: planetas) {
        planeta->update_anguloRotacao();
        planeta->update_anguloTranslacao();
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.1, 2000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Sol e Planetas");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}