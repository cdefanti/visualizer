#version 120
const float PI = 3.1415926535;
varying vec3 pos;
uniform float t;

void main()
{
  pos = gl_Vertex.xyz;
  gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
}
