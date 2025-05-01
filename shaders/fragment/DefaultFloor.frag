#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

// Simulate carpet noise
float random(vec2 st)
{
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

void main()
{
    float noise = random(TexCoords * 50.0); // 50 is noise frequency
    vec3 baseColor = mix(vec3(0.25, 0.22, 0.18), vec3(0.3, 0.28, 0.23), noise); // Dark brown carpet colors
    FragColor = vec4(baseColor, 1.0);
}


