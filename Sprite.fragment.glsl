#version 430 core

layout (location = 0) out vec4 out_color;

uniform sampler2D texture_unit;
flat in vec4 color;

void main(void){
    out_color = color * texture(texture_unit, gl_PointCoord);
}                                                              
