#include "starprogram.h"


void StarProgram::Initialize(const char *vertex_shader_file, const char *fragment_shader_file){
    TextureCameraProgram::Initialize(vertex_shader_file, fragment_shader_file);
    star_color_location_ = GetUniformLocationOrDie("star_color");
}


void StarProgram::SetStarColor(const TransparentMaterial &color) const{
    glUniform4fv(star_color_location_, 1, color.diffuse);
}
