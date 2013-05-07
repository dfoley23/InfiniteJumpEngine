#version 150

in vec4 vertex_color;

out vec4 end_color;

void main() {
    end_color = vertex_color;
}