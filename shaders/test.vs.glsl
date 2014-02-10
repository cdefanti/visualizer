const float PI = 3.1415926535;
varying vec3 pos;
void main()
{
  float f = 2.0 / 10.0 * PI;
  pos.x = (3.0 + cos(gl_Vertex.x * f)) * cos(gl_Vertex.y * f);
  pos.y = (3.0 + cos(gl_Vertex.x * f)) * sin(gl_Vertex.y * f);
  pos.z = sin(gl_Vertex.y * f);
  gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
}
