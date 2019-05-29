#include "animatedmodel.h"

AnimatedModel::AnimatedModel(GLfloat init_velocity, GLfloat init_angle){
    velocity_ = init_velocity;
    angle_ = init_angle;
    animated_ = true;
}

void AnimatedModel::SpeedUp(){
    velocity_ *= 1.09544511501f;
}

void AnimatedModel::SlowDown(){
    velocity_ /= 1.09544511501f;
}

void AnimatedModel::ToggleAnimated(){
    animated_ = ! animated_;
}
