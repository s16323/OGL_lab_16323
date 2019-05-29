#include "skybox.h"

void SkyBox::Initialize(){

    const SkyTextureVertex kVertices[8] =
    {
      //front
      {{-50.0f, 50.0f, 50.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}}, //0
      {{ 50.0f, 50.0f, 50.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},  //1
      {{ 50.0f,-50.0f, 50.0f, 1.0f}, {1.0f, -1.0f, 1.0f}}, //2
      {{-50.0f,-50.0f, 50.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}},//3
      // back
      {{ 50.0f, 50.0f,-50.0f, 1.0f}, {1.0f, 1.0f, -1.0f}}, //4
      {{-50.0f, 50.0f,-50.0f, 1.0f}, {-1.0f, 1.0f, -1.0f}}, //5
      {{-50.0f,-50.0f,-50.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}}, //6
      {{ 50.0f,-50.0f,-50.0f, 1.0f}, {1.0f, -1.0f, -1.0f}} //7
    };

    const GLuint kIndices[36] =
    {
      0, 1, 3,  1, 2, 3, // front
      4, 5, 7,  5, 6, 7, // back
      5, 4,0,  4,1,0, // top
      7,6,2, 6,3,2, // bottom
      5,0,6, 0,3,6, // left
      1,4,2, 4,7,2  // right
    };

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), NULL); //nullptr
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), reinterpret_cast<GLvoid*> (sizeof(kVertices[0].position)) );

    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kIndices), kIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void SkyBox::Draw(const TextureCameraProgram &pr){

    glUseProgram(pr);

    glBindVertexArray(vao_);

      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      glFrontFace(GL_CCW);

      glActiveTexture(texture_unit_);
      glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);

      glDepthMask(0);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL); //nulptr
      glDepthMask(1);

      glDisable(GL_CULL_FACE);

      glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

      glBindVertexArray(0);
      glUseProgram(0);

}
