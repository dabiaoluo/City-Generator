#version 150

precision highp float;

// Input
in vec3 in_Position;
in vec3 in_Color;
in vec2 uv_texCoord;

// Output
out vec2 fragTexCoord;

uniform mat4 modelViewProjectionMatrix;

out vec3 ex_Color;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(in_Position, 1.0);
    ex_Color = in_Color;
    fragTexCoord = uv_texCoord;
}