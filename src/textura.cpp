#include "../include/textura.h"

GLuint loadTexture(const char* path) {
    GLuint texture = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!texture) {
        std::cerr << "Falha ao carregar a textura: " << path << std::endl;
        exit(1);
    }
    return texture; 
}

// void configurarTextura(GLuint texturaID) {
//     glBindTexture(GL_TEXTURE_2D, texturaID); 

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
// }
