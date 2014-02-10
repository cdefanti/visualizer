varying vec3 pos;

void main()
{
  gl_FragColor = vec4(0, 0, (pos.z + 1.0) / 2.0, 1);
}
