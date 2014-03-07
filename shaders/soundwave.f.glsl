uniform sampler1D soundTex;
uniform sampler2D pixelTex;

void main(void)
{
    vec4 color;
    if (gl_TexCoord[0].t == 0.0)
    {
        color = texture1D(soundTex, gl_TexCoord[0].t);
    }
    else
    {
        color = texture2D(pixelTex, gl_TexCoord[0].st + vec2(0, 1.0 / 800.0));
    }
    color = vec4(1, 0, 0, 1);
    gl_FragColor = color;
}
