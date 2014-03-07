uniform sampler2D vartexture[];
uniform sampler2D oldpixels;
uniform int ntex;

void main(void)
{
    vec4 var = texture2D(vartexture[0], gl_TexCoord[0]);
    for (int i = 1; i < ntex; i++)
    {
        vec4 tex = texture2D(vartexture[0], gl_TexCoord[0]);
        if (var.x < tex.x) var.x = tex.x;
        if (var.y < tex.y) var.y = tex.y;
        if (var.z < tex.z) var.z = tex.z;
    }
    gl_FragColor = texture2D(oldpixels, gl_TexCoord[0]) + var;
}
