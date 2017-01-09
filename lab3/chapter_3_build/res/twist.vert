uniform float TWIST;
varying vec3 vertex;
varying vec3 normal;

float GetSurfaceY(float x, float y, float step)
{
	return mix(x * x + y * y, x * x - y * y, step) - 5.0;
}

vec4 GetSurfaceVertex(float x, float y, float w, float step)
{
	return vec4(x, GetSurfaceY(x, y, step), y, w);
}

void main()
{ 
	float phase = abs(TWIST) / 2.0;

    vec4 twistedCoord = GetSurfaceVertex(gl_Vertex.x, gl_Vertex.y, gl_Vertex.w, phase);

    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
 
	vec4 twistedCoord1 = GetSurfaceVertex(gl_Vertex.x + 0.1, gl_Vertex.y, gl_Vertex.w, phase);
	vec4 twistedCoord2 = GetSurfaceVertex(gl_Vertex.x, gl_Vertex.y + 0.1, gl_Vertex.w, phase);

	vec3 v1 = twistedCoord1.xyz - twistedCoord.xyz;
	vec3 v2 = twistedCoord2.xyz - twistedCoord.xyz;
	vec3 normalize_vector = normalize(cross(v1, v2));

	vertex = vec3(gl_ModelViewMatrix * twistedCoord);	
	normal = normalize(gl_NormalMatrix * normalize_vector);
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
