#include "pointlighttransparentprogram.h"


void PointLightTransparentProgram::Initialize(const char *vertex_shader_file, const char *fragment_shader_file){
    TransparentMaterialModelProgram::Initialize(vertex_shader_file, fragment_shader_file);
    normal_matrix_location_ = GetUniformLocationOrDie("normal_matrix");
    light_locations_.ambient = GetUniformLocationOrDie("light.ambient");
    light_locations_.attenuation = GetUniformLocationOrDie("light.attenuation");
    light_locations_.diffuse = GetUniformLocationOrDie("light.diffuse");
    light_locations_.position = GetUniformLocationOrDie("light.position");
    light_locations_.specular = GetUniformLocationOrDie("light.specular");
}

void PointLightTransparentProgram::SetLight(const PointLight & light) const{
    glUniform4fv(light_locations_.ambient, 1, light.ambient);
    glUniform4fv(light_locations_.diffuse, 1, light.diffuse);
    glUniform4fv(light_locations_.specular, 1, light.specular);
    glUniform4fv(light_locations_.position, 1, light.position);
    glUniform3fv(light_locations_.attenuation, 1, light.attenuation);
}


void PointLightTransparentProgram::SetNormalMatrix(const Mat3 & matrix) const{
    glUniformMatrix3fv(normal_matrix_location_, 1, GL_TRUE, matrix);
}

