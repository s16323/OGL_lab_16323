#ifndef TEXTUREMISTCAMERAPROGRAM_H
#define TEXTUREMISTCAMERAPROGRAM_H

#include "texturecameraprogram.h"
#include "mistprogram.h"

class TextureMistCameraProgram : public TextureCameraProgram, public MistProgram{
public:
    void Initialize(const char *vertex_shader_file, const char *fragment_shader_file);
};

#endif // TEXTUREMISTCAMERAPROGRAM_H
