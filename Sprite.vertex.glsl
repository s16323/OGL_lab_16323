#version 430 core

layout (location = 0) in vec4 in_position;
//layout (location = 1) in vec4 in_color;

//uniform float time;
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform vec4 star_color;

flat out vec4 color;

void main(void){
    vec4 vertex = in_position;
	
	float size = 30.0;
//	float size = 40.0;
	color = star_color;
    gl_Position = projection_matrix * view_matrix * vertex;
    gl_PointSize = size;
}
