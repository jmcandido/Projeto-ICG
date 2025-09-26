
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include "../include/astro.h"
#include "../include/camera.h"
#include "../include/textura.h"


Astro mercurio(0.19f * 2 + 6, 1,   0.01f);
Astro venus  (2.5f * 2 + 6,   1, 177.30f);
Astro terra  (4.0f  *2 + 6,   1,  23.26f);
Astro marte   (5.5f *2 + 6,  1,  25.19f);
Astro jupiter(8.5f  *2 + 6,   1,   3.13f);
Astro saturno (14.0f*2 + 6, 1,  26.73f);
Astro urano (18.0f  *2 + 6,   1,  97.77f);
Astro netuno(25.0f  *2 + 6,   1,  28.32f);

GLuint sun_tex, mercury_tex, venus_tex, earth_tex, mars_tex, jupiter_tex, saturn_tex, uranus_tex, neptune_tex;

Camera camera(
    0.0f, 25.0f, 80.0f,   
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
    gluSphere(q, 3, 60, 60); 
    gluDeleteQuadric(q);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_emit);
    glPopMatrix();
}

static void carregaTexturas() {
    sun_tex     = loadTexture("assets/sun.jpg");     configurarTextura(sun_tex);
    mercury_tex = loadTexture("assets/mercury.jpg"); configurarTextura(mercury_tex);  mercurio.set_textura(mercury_tex);
    venus_tex   = loadTexture("assets/venus.jpg");   configurarTextura(venus_tex);    venus.set_textura(venus_tex);
    earth_tex   = loadTexture("assets/terra_noite.jpg");   configurarTextura(earth_tex);    terra.set_textura(earth_tex);
    mars_tex    = loadTexture("assets/mars.jpg");    configurarTextura(mars_tex);     marte.set_textura(mars_tex);
    jupiter_tex = loadTexture("assets/jupiter.jpg"); configurarTextura(jupiter_tex);  jupiter.set_textura(jupiter_tex);
    saturn_tex  = loadTexture("assets/saturn.jpg");  configurarTextura(saturn_tex);   saturno.set_textura(saturn_tex);
    uranus_tex  = loadTexture("assets/uranus.jpg");  configurarTextura(uranus_tex);   urano.set_textura(uranus_tex);
    neptune_tex = loadTexture("assets/neptune.jpg"); configurarTextura(neptune_tex);  netuno.set_textura(neptune_tex);
}

static void setStaticAngles() {
    mercurio.set_anguloTranslacao (0.0f); mercurio.set_anguloRotacao(  0.0f);
    venus.set_anguloTranslacao   (0.0f); venus.set_anguloRotacao   (  0.0f);
    terra.set_anguloTranslacao   (0.0f); terra.set_anguloRotacao   (  0.0f);
    marte.set_anguloTranslacao    (0.0f); marte.set_anguloRotacao    (  0.0f);
    jupiter.set_anguloTranslacao (0.0f); jupiter.set_anguloRotacao (  0.0f);
    saturno.set_anguloTranslacao  (0.0f); saturno.set_anguloRotacao  (  0.0f);
    urano.set_anguloTranslacao  (0.0f); urano.set_anguloRotacao  (  0.0f);
    netuno.set_anguloTranslacao (0.0f); netuno.set_anguloRotacao (  0.0f);
}

static void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    carregaTexturas();
    setStaticAngles(); 
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

static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.1, 400.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Sol e Planetas (Estáticos)");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}