#version 150
precision highp float;
in  vec3 ex_Color;
out vec4 color;

in vec2 fragTexCoord;

uniform sampler2D s_texture;

// selector
uniform bool useTexture;

void main(void)
{
    if(useTexture)
        color = texture(s_texture, fragTexCoord);
    else
        color = vec4(ex_Color, 1);
}
