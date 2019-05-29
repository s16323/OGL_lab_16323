#ifndef STARS_H
#define STARS_H

#include <GL/glew.h>
#include "transparentmaterialmodel.h"
#include "starprogram.h"
#include "vertices.h"
#include "arraymodel.h"
#include "texturemodel.h"
#include "transparentmaterialmodelprogram.h"


class Star : 
	public ArrayModel,
	public TextureModel,
	public TransparentMaterialModel {
public:
//  void Initialize(GLuint n);
    void Initialize();
    void Draw(const StarProgram &pr);

};


#endif // STARS_H
