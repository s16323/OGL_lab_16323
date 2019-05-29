#include "star.h"
#include "vertices.h"
//#include <ctime>
//#include <cmath>
//#include <cstdlib>

//float random_float(){
//  return ((float)rand() / RAND_MAX);
//}


void Star::Initialize(){
	
	const Vertex kStarVertex = {
		2.57f, 3.21f, -5.43f, 1.0f
		};

//    const Vertex kStarVertex = {
//            -6.125f, 7.211f, -3.133f, 1.0f
//    };


    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kStarVertex), &kStarVertex, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);

}

void Star::Draw(const StarProgram &pr){
    glUseProgram(pr);

//    pr.SetTime(time_);
	pr.SetStarColor(material_);
    
    glBindVertexArray(vao_);
    
    glActiveTexture(texture_unit_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glEnable(GL_PROGRAM_POINT_SIZE);

    glDrawArrays(GL_POINTS, 0, 1);

    glDisable(GL_BLEND);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glBindVertexArray(0);
    glUseProgram(0);

}

//void Star::Move(GLfloat t){
//   time_ = t;
//}
