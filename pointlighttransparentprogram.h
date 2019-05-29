#ifndef POINTLIGHTTRANSPARENTPROGRAM_H
#define POINTLIGHTTRANSPARENTPROGRAM_H

#include "transparentmaterialmodelprogram.h"
#include "light.h"


class PointLightTransparentProgram : public TransparentMaterialModelProgram{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetNormalMatrix(const Mat3 &) const;
    void SetLight(const PointLight & light) const;
private:
    GLint normal_matrix_location_;
    struct LightLocations{
        GLint ambient;
        GLint attenuation;
        GLint diffuse;
        GLint position;
        GLint specular;
    }light_locations_;
};

#endif // POINTLIGHTTRANSPARENTPROGRAM_H
