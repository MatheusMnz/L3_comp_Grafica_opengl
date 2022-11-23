#include "Body.h"
#include <math.h>

Body::Body(const char *tex_name,
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
           bool interactWithLight)
{
    this->origin = origin;
    this->raio = raio;

    this->mov_center = mov_center;
    this->ang_vel = ang_vel;
    this->transl_vel = transl_vel;
    this->elipse_a = elipse_a;
    this->elipse_b = elipse_b;
    this->interactWithLight = interactWithLight;

    // Gambs
    this->texture = new Texturazer(tex_name, matDif, matSpec, matShine);
}

Body::~Body()
{
    if (this->texture != NULL)
    {
        delete this->texture;
    }
}

void Body::draw()
{
    glPushMatrix();

    // A origem é translada na move()
    // Usa de coordenadas de elipse para transladar
    glTranslatef(origin.x, origin.y, origin.z);

    // Rotaciona em torno do proprio eixo z
    glRotatef(this->rot_angle, 0, 0, 1);

    // Muda o material do Bodya de acordo com os parametros da textura
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->texture->matDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->texture->matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, this->texture->matShine);

    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    solidSphere(this->raio, DEF_STACKS, DEF_COLS);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Body::move()
{
    // Soma ao angulo na translacao e na rotacao do Bodya
    this->transl_angle += transl_vel;
    this->rot_angle += ang_vel;

    // Utiliza de coordenadas polares para descrever uma elipse
    // X = a * cos (angulo) + x0
    // Y = b * sen (angulo) + y0
    // Z (Nao esta mexida, se for necessario, usa coordenada esferica ou cilindrica >_<

    this->origin.x = mov_center.x + elipse_a * cos(transl_vel * M_PI / 180.0f);
    this->origin.y = mov_center.y + elipse_b * sin(transl_vel * M_PI / 180.0f);
    this->origin.z = 0;
}

bool Body::isLight()
{
    return this->interactWithLight;
}