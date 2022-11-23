#include "Body.h"

// Mesma coisa q um body, mas emite luz >_<
class LightBody : Body
{
private:
    GLuint lightFont;


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
              float *matDif,
              float *matSpec,
              float *matShine,
              GLuint lightFont);

    void draw() override;
};