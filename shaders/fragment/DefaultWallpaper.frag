#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;

// procedural wallpaper base color
vec3 getWallpaperColor(vec2 uv)
{
    vec3 baseColor = vec3(1.0, 0.95, 0.6); // soft yellow
    float noise = fract(sin(dot(uv * 50.0, vec2(12.9898,78.233))) * 43758.5453);
    float grime = smoothstep(0.5, 0.7, noise);
    return mix(baseColor, vec3(0.3, 0.25, 0.1), grime * 0.3); // mix dirty spots
}

void main()
{
    // Lighting
    vec3 ambient = vec3(0.2);

    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.8);

    vec3 color = getWallpaperColor(TexCoords);
    vec3 result = (ambient + diffuse) * color;

    FragColor = vec4(result, 1.0);
    // FragColor = vec4(1.0, 0.8, 0.3, 1.0); // pure yellow for debug
}
