#include "texturecameraprogram.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


void TextureCameraProgram::Initialize(const char *vertex_shader_file,
                                      const char *fragment_shader_file){
    CameraProgram::Initialize(vertex_shader_file, fragment_shader_file);
    texture_unit_location_ = GetUniformLocationOrDie("texture_unit");

    glUseProgram(0);
}

void TextureCameraProgram::SetTextureUnit(GLuint t) const{
    glUniform1i(texture_unit_location_, t);
}
