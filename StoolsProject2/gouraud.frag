#version 400

layout (location = 0) out vec4 FragColor;

smooth in vec3 color;
in vec3 position;
in vec3 normal;

const float shininess = 1.0f;
const vec3 light_position = vec3(0.0, 0.0, 0.0);

vec3 ads( )
{
  vec3 n = normal;

  if (!gl_FrontFacing){
	n = -n;
  }

  //Returns the result of the phong lighting equations
  vec3 s = normalize(light_position - position);
  vec3 v = normalize(-position);
  vec3 r = reflect(-s, n);
  float s_dot_n = max(dot(s, n), 0.0);

  return 0.85*color + color * s_dot_n + (s_dot_n > 0 ? color * pow(max(dot(r, v), 0.0), shininess) : vec3(0.0));
}

void main()
{
	float dist = abs( position.z );
	float fogFactor = (60.0f - dist) /
	(60.0f - 35.0f);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	
	FragColor = vec4(mix( vec3(0.0f, 0.0f, 0.25f), ads(), fogFactor ), 1.0);
}
