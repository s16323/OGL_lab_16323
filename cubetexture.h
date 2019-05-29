#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include "texture.h"

class CubeTexture : public Texture{
public:
    void Initialize(const char *filename);
};

#endif // CUBETEXTURE_H
