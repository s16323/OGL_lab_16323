#ifndef SKYBOX_H
#define SKYBOX_H

#include "texturecameraprogram.h"
#include "vertices.h"
#include "indexmodel.h"
#include "texturemodel.h"


class SkyBox : public IndexModel, public TextureModel {
public:
    void Initialize();
    //void::Initialize(float s=30);
    void Draw(const TextureCameraProgram &pr);
};

#endif // SKYBOX_H
