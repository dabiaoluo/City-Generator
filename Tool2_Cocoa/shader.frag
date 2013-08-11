#version 150
precision highp float;
in  vec3 ex_Color;
out vec3 color;


// Interpolated values from the vertex shaders
in vec2 v_texCoord;

// Values that stay constant for the whole mesh.
uniform sampler2D s_texture;

// selector
uniform bool useTexture;

void main(void) {
    if(useTexture)
        color = texture( s_texture, v_texCoord).rgb;
//        FragColor = texture2D(s_texture, v_texCoord);
    else
//        color = vec3(1.0f, 1.0f, 1.0f);
        color = vec3(ex_Color);
}
