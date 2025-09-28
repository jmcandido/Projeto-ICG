#include "../include/astro.h"

Astro::Astro() {}
Astro::~Astro() {}

Astro::Astro(float dist, float r, float incl, float velRot, float velTrans, float angRot, float angTrans, GLuint tex)
    : distancia(dist), raio(r), inclinacaoEixo(incl) , velRotacao(velRot), velTranslacao(velTrans), anguloRotacao(angRot), anguloTranslacao(angTrans), textura(tex){}

float Astro::get_distancia()
{
    return this->distancia;
}

float Astro::get_raio()
{
    return this->raio;
}

float Astro::get_inclinacaoEixo()
{
    return this->inclinacaoEixo;
}

float Astro::get_anguloRotacao()
{
    return this->anguloRotacao;
}

float Astro::get_anguloTranslacao()
{
    return this->anguloTranslacao;
}

GLuint Astro::get_textura()
{
    return this->textura;
}

void Astro::set_distancia(float distancia)
{
    this->distancia = distancia;
}

void Astro::set_raio(float raio)
{
    this->raio = raio;
}

void Astro::set_inclinacaoEixo(float inclinacaoEixo)
{
    this->inclinacaoEixo = inclinacaoEixo;
}

void Astro::set_velRotacao(float velRotacao)
{
    this->velRotacao = velRotacao;
}

void Astro::set_velTranslacao(float velTranslacao)
{
    this->velTranslacao = velTranslacao;
}

void Astro::set_anguloRotacao(float anguloRotacao)
{
    this->anguloRotacao = anguloRotacao;
}

void Astro::set_anguloTranslacao(float anguloTranslacao)
{
    this->anguloTranslacao = anguloTranslacao;
}

void Astro::set_textura(GLuint textura)
{
    this->textura = textura;
}

void Astro::update_anguloRotacao()
{
    this->anguloRotacao += velRotacao;
}

void Astro::update_anguloTranslacao()
{
    this->anguloTranslacao += velTranslacao;
}   
