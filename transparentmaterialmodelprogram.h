#ifndef TRANSPARENTMATERIALMODELPROGRAM_H
#define TRANSPARENTMATERIALMODELPROGRAM_H

#include "cameraprogram.h"
#include "material.h"

class TransparentMaterialModelProgram : public CameraProgram{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetModelMatrix(const Mat4 &) const;
    void SetMaterial(const TransparentMaterial &material) const;
private:
    GLint model_matrix_location_;
    GLint material_location_;

};

#endif // TRANSPARETNMATERIALMODELPROGRAM_H
