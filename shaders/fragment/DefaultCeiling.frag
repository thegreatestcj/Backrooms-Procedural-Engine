#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

void main()
{
    vec2 uv = TexCoords * 10.0; // Tile 10x10
    vec2 grid = fract(uv);

    // Grid lines
    float line = step(0.02, grid.x) * step(0.02, grid.y) * step(grid.x, 0.98) * step(grid.y, 0.98);

    vec3 panelColor = vec3(0.9, 0.9, 0.9); // Light gray
    vec3 lineColor = vec3(0.7, 0.7, 0.7);  // Darker grid lines

    FragColor = vec4(mix(lineColor, panelColor, line), 1.0);
}
