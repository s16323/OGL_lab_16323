#include "camera.h"
#include <cmath>
//test
Camera::Camera(){
	d_x_ = -10.0;
	d_y_ = -2.0;
	d_z_ = -10.0;
	
	theta_x_ = 0;
	theta_y_ = -42;

    
}


Camera::operator Mat4()const{
	Mat4 view_matrix;
	view_matrix.Translate(d_x_, d_y_, d_z_); //opengl  OX, OY, OZ
    view_matrix.RotateAboutY(theta_y_);		//25
    view_matrix.RotateAboutX(theta_x_);
    //view_matrix_.RotateAboutZ(theta_z_);
    
    return view_matrix;
	
}

//void Camera::Translate(GLfloat h){
	
	//GLfloat sy = sinf(theta_y_*static_cast<GLfloat>(M_PI)/180.0f);
	//GLfloat cy = cosf(theta_y_*static_cast<GLfloat>(M_PI)/180.0f);
	//GLfloat sx = sinf(theta_y_*static_cast<GLfloat>(M_PI)/180.0f);
	//GLfloat cx = cosf(theta_y_*static_cast<GLfloat>(M_PI)/180.0f);
	
	//	d_x_ +=h*cx*sy;
	//	d_y_ +=h*sx;
	//	d_z_ +=h*cx*cy;
//}


void Camera::Translate(GLfloat dx, GLfloat dy, GLfloat dz){
	
	d_x_ +=dx;
	d_y_ +=dy;
	d_z_ +=dz;
}
 
