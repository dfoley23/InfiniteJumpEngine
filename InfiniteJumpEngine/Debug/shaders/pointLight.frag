#version 150

in vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D tex;

out vec4 end_color;

void main() {

    end_color = frag_color;
}