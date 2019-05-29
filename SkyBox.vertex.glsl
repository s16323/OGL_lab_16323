#version 430 core

layout(location=0) in vec4 in_position;
layout(location=2) in vec3 in_texture;


uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec3 tex_coord;


void main(void){
    tex_coord = in_texture;

    gl_Position = (projection_matrix * view_matrix) * in_position;
}

