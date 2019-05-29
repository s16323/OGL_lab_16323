#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H

#include <GL/gl.h>

class AnimatedModel{
public:
    AnimatedModel(GLfloat init_velocity=30, GLfloat init_angle=0);
    void SpeedUp();
    void SlowDown();
    void ToggleAnimated();
    void SetInitAngle(GLfloat angle){angle_= angle;}
    void SetVelocity(GLfloat velocity){velocity_= velocity;}
protected:
    GLfloat angle_;
    GLfloat velocity_;
    bool animated_;
};

#endif // ANIMATEDMODEL_H
