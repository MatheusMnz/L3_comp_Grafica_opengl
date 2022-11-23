#ifndef __LIGHTBODY__
#define __LIGHTBODY__

#include "Body.h"

// Mesma coisa q um body, mas emite luz >_<
class LightBody : public Body
{
private:
    GLuint lightFont;
    float lightAmb[4];
    float lightDif[4];
    float lightSpec[4];

public:
    using Body::Body;
    LightBody(const char *tex_name,
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
              GLuint lightFont);

    void draw() override;
};

#endif