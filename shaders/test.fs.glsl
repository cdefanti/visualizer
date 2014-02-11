#version 120
varying vec3 pos;
uniform float t;

void main()
{
  vec3 fpos = pos;
  fpos.z = (1 + cos(8 * (fpos.x * fpos.x + fpos.y * fpos.y - t))) / 2;
  gl_FragColor = vec4(fpos.z, 0, 0, 1);
}
