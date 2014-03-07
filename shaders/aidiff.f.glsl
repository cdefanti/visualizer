uniform sampler2D qt_Texture0;
varying vec4 qt_TexCoord0;

uniform int a_radius;
uniform int i_radius;

float getAvgVal(int r, vec2 coords)
{
    float val = 0;
    for (int i = coords.x - r; i < coords.x + r; i++)
    {
        for (int j = coords.y - r; j < coords.y + r; j++)
        {
            if (distance(coords, vec2(i, j)) < r) val += texture2D(qt_Texture0);
        }
    }
    return val;
}

void main(void)
{
    gl_FragColor = getAvgVal(a_radius, gl_FragCoord[0]) - getAvgVal(i_radius, gl_FragCoord[0]);
}
