#ifndef __BODY__
#define __BODY__

typedef struct vec3f
{
    float x;
    float y;
    float z;
} vec3f_t;

#include "Texturazer.h"

// Parâmetros:
// Raio do corpo,
// velocidade de rotação
// velocidade translação
// reflexão da textura

void solidSphere(int radius, int stacks, int columns)
{
    // cria uma quádrica
    GLUquadric *quadObj = gluNewQuadric();
    // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
    // ou GLU_POINT
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);
    // cria os vértices de uma esfera
    gluSphere(quadObj, radius, stacks, columns);
    // limpa as variáveis que a GLU usou para criar
    // a esfera
    gluDeleteQuadric(quadObj);
}

// Constantes para desenho dos circulos
#define DEF_STACKS 160
#define DEF_COLS 160

class Body
{

protected:
    // Parametros para definir a esfera
    vec3f_t origin;
    double raio;

    // Textura
    Texturazer *texture;

    // Parametros para translacao, rotacao e orbitas elipticas
    vec3f_t mov_center;
    double ang_vel;
    double transl_vel;
    double rot_angle;
    double transl_angle;
    double elipse_a;
    double elipse_b;
    GLuint interactWithLight;

public:
    Body(const char *tex_name,
         vec3f_t origin,
         double raio,
         vec3f_t mov_center,
         double ang_vel,
         double transl_vel,
         double elipse_a,
         double elipse_b,
         float *matDif,
         float *matSpec,
         float *matShine,
         bool interactWithLight);
    ~Body();
    virtual void draw();
    void move();
    bool isLight();
};

#endif