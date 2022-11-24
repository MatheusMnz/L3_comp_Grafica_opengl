#include "LightBody.h"

LightBody::LightBody(const char *tex_name,
                     vec3f_t origin,
                     double raio,
                     vec3f_t mov_center,
                     double ang_vel,
                     double transl_vel,
                     double elipse_a,
                     double elipse_b,
                     int n_luas,
                     float *lightAmb,
                     float *lightDif,
                     float *lightSpec,
                     GLuint lightFont) : Body(tex_name,
                                              origin,
                                              raio,
                                              mov_center, ang_vel, transl_vel, elipse_a, elipse_b, n_luas, 0)
{
    memcpy(this->lightAmb, lightAmb, sizeof(float) * 4);
    memcpy(this->lightDif, lightDif, sizeof(float) * 4);
    memcpy(this->lightSpec, lightSpec, sizeof(float) * 4);

    // Seta qual fonte de luz esse corpo ira alterar
    this->lightFont = lightFont;
}

void LightBody::draw()
{
    // glColor3f(1.0, 1.0, 1.0);
    lightSourcePos[0] = this->origin.x;
    lightSourcePos[1] = this->origin.y;
    lightSourcePos[2] = this->origin.z;
    lightSourcePos[3] = 1.0;

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, this->lightSourcePos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, this->lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, this->lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, this->lightSpec);

    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);

    // Rotaciona em torno do eixo y, pois o y é o eixo para cima no ngc
    glRotatef(-this->rot_angle, 0, 1, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    solidSphere(this->raio, DEF_STACKS, DEF_COLS);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
