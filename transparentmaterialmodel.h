#ifndef TRANSPARENTMATERIALMODEL_H
#define TRANSPARENTMATERIALMODEL_H

#include <GL/glew.h>
#include "material.h"



class TransparentMaterialModel{
public:
    void SetMaterial(const TransparentMaterial & material){material_=material;}
protected:
    TransparentMaterial material_;
};

#endif // TRANSPARENTMATERIALMODEL_H
