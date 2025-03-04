#version 330 core
out vec4 FragColor;

uniform sampler2D tex;
in vec2 TexCoord;

void main() {
    float gray = texture(tex, TexCoord).r; // Sample RED channel only
    FragColor = vec4(gray, gray, gray, 1.0); // Copy it to RGB
}