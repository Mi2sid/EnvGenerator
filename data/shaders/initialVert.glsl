#version 450

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aVertexColor;

out vec4 Color;

uniform mat4 uMVPMatrix;

void main() {
    gl_Position = uMVPMatrix * vec4(aPosition, 1.0);

    Color = aVertexColor;
}