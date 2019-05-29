#include "transparentmaterialmodelprogram.h"

void TransparentMaterialModelProgram::Initialize(const char *vertex_shader_file, const char *fragment_shader_file){
    CameraProgram::Initialize(vertex_shader_file, fragment_shader_file);
    model_matrix_location_ = GetUniformLocationOrDie("model_matrix");
    material_location_ = GetUniformLocationOrDie("material");
}

void TransparentMaterialModelProgram::SetModelMatrix(const Mat4 & matrix) const{
    glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, matrix);
}

void TransparentMaterialModelProgram::SetMaterial(const TransparentMaterial & material) const{
    glUniform4fv(material_location_, 1, material.diffuse);
    
}
