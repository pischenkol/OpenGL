#version 330 core

uniform sampler2D sampler;

in vec3 color;
in vec2 textureCoordinates;

out vec4 outColor;

void main() {
        outColor =  texture(sampler, textureCoordinates);
}