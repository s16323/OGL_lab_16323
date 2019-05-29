#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "matma.h"


class Camera {
	public:
			Camera();
			operator Mat4()const;
			void RotateAboutX(GLfloat d){theta_x_ += d;}
			void RotateAboutY(GLfloat d){theta_y_ += d;}
			void Translate(GLfloat dx, GLfloat dy, GLfloat dz);
			
	private:
			GLfloat theta_x_;
			GLfloat theta_y_;
			GLfloat d_x_;
			GLfloat d_y_;
			GLfloat d_z_;
			//Mat4 view_matrix_;
			//Mat4 projection_matrix_; 
	};
	
	#endif // CAMERA_H

