#ifndef ASTRO_H
#define ASTRO_H

#include <GL/glut.h> 
class Astro {
private:
    float distancia;         
    float raio;               
    float inclinacaoEixo;     
    float velRotacao;
    float velTranslacao;
    float anguloRotacao;      
    float anguloTranslacao;   
    GLuint textura;           

public:
    Astro(); 
    ~Astro(); 

    Astro(float dist, float r, float incl, float velRot, float velTrans, float angRot, float angTrans, GLuint tex); 

    float get_distancia();
    float get_raio();
    float get_inclinacaoEixo();
    float get_anguloRotacao();
    float get_anguloTranslacao();
    GLuint get_textura();

    void set_distancia(float distancia);
    void set_raio(float raio);
    void set_inclinacaoEixo(float inclinacaoEixo);
    void set_velRotacao(float velRotacao);
    void set_velTranslacao(float velTranslacao);
    void set_anguloRotacao(float anguloRotacao);
    void set_anguloTranslacao(float anguloTranslacao);
    void set_textura(GLuint textura);

    void draw();

    void update_anguloRotacao();
    void update_anguloTranslacao();
};

#endif // ASTRO_H