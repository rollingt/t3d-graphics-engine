out vec4 color;

void main()
{
    // Transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	// Ambient calculation
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightModel.ambient;
	
	// Emission calculation
	vec4 emission = gl_FrontMaterial.emission;
	
	// Diffuse calculation
	vec4 P = gl_ModelViewMatrix * gl_Vertex;
	vec3 N = normalize(gl_NormalMatrix * gl_Normal);
	
	vec3 L = normalize(gl_LightSource[0].position.xyz - vec3(P * gl_LightSource[0].position.w));
	float diffuseIntensity = max(dot(N, L),0);
	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseIntensity;
	
	color = clamp(ambient+emission+diffuse, 0, 1);
}