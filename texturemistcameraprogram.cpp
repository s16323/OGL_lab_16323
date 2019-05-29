#include "texturemistcameraprogram.h"


void TextureMistCameraProgram::Initialize(
        const char *vertex_shader_file,
        const char *fragment_shader_file){
    TextureCameraProgram::Initialize(vertex_shader_file, fragment_shader_file);
    mist_locations_.color = GetUniformLocationOrDie("mist.color");
    mist_locations_.start = GetUniformLocationOrDie("mist.start");
    mist_locations_.end = GetUniformLocationOrDie("mist.end");
    mist_locations_.density = GetUniformLocationOrDie("mist.density");
    mist_locations_.type = GetUniformLocationOrDie("mist.type");
}
