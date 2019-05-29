#ifndef POINTLIGHTMISTPROGRAM_H
#define POINTLIGHTMISTPROGRAM_H

#include "pointlightprogram.h"
#include "mistprogram.h"

class PointLightMistProgram : public PointLightProgram, public MistProgram{
public:
    void Initialize(const char *vertex_shader_file, const char *fragment_shader_file);
};

#endif // POINTLIGHTMISTPROGRAM_H
