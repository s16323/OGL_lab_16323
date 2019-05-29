/****************************************************************************
** Copyright (C) 2013 Aleksander Denisiuk
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
****************************************************************************/

#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "matma.h"
#include "lightprogram.h"
#include "material.h"


typedef struct NamedMaterial{
  char name_[30];
  Material m;
} NamedMaterial;


typedef struct VertexGroup{
  GLuint vao;
  GLuint vertices;
  int mat_number;
  int n_of_vertices;
} VertexGroup;


class ObjModel{
public:
    void Initialize(const char *obj_file, const char *mtl_file);
    void Draw(const LightProgram &);
    void SetTexture(GLuint t){texture_=t;}
    void SetTextureUnit(GLenum t){texture_unit_=t;}
    ~ObjModel();

private:
    Mat4 model_matrix_;
    Mat3 normal_matrix_;

    GLuint texture_;
    GLenum texture_unit_;

    NamedMaterial * materials_;
    VertexGroup * groups_;
    int n_of_groups_;
    int n_of_materials_;

    int LoadGroups(const char * filename);
    int LoadMaterials(const char* filename);
    int FindMatNumber(const char* MatName);

    void DestroyGroup(VertexGroup gr);
    void DestroyGroups();
    void DestroyMaterials(void);

    void cpf(GLfloat* from, GLfloat* to, int n);

};



#endif
