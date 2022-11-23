#include "LightBody.h"

LightBody::LightBody(const char *tex_name,
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
          GLuint lightFont) : Body(tex_name,
          origin,
          raio,
          mov_center,ang_vel,transl_vel,elipse_a,elipse_b,matDif,matSpec,matShine,0)
{
    // Seta qual fonte de luz esse corpo ira alterar
    this->lightFont = lightFont;
}


