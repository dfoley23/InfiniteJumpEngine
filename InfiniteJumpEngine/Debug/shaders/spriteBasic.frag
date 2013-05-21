#version 150

in vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D tex;

out vec4 end_color;

void main() {
    vec4 tex_color = vec4(texture2D(tex, tex_coord));
	
	vec4 final_color = frag_color;

    end_color = normalize( final_color * tex_color);
}