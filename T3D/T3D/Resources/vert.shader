out vec4 color;

void main()
{
    // Transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	// Ambient calculation
	color = gl_FrontMaterial.ambient * gl_LightModel.ambient;
}