attribute vec3 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_uv;
attribute vec4 a_color;


//global variables from the CPU
uniform mat4 model;
uniform mat4 viewprojection;
uniform vec3 lightPosition;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform vec3 lightAmbient;
uniform vec3 positionCamera;
uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform vec3 matSpecular;
uniform float matShininess;

//vars to pass to the pixel shader
varying vec2 v_coord;
varying vec3 v_wPos;
varying vec3 v_wNormal;
varying vec3 v_lightPosition;
varying vec3 v_lightDiffuse;
varying vec3 v_lightSpecular;
varying vec3 v_lightAmbient;
varying vec3 v_positionCamera;
varying vec3 v_matAmbient;
varying vec3 v_matDiffuse;
varying vec3 v_matSpecular;
varying float v_matShininess;
varying mat4 v_model;
void main()
{
	vec3 wPos = (model * vec4( a_vertex, 0.0)).xyz;
	vec3 wNormal = (model * vec4( a_normal, 0.0) ).xyz;
	//get the texture coordinates (per vertex) and pass them to the pixel shader
	v_coord = a_uv;
	v_model=model;
	v_wPos = wPos;
	v_wNormal = wNormal;
	v_lightPosition=lightPosition;
	v_lightDiffuse=lightDiffuse;
	v_lightSpecular=lightSpecular;
	v_lightAmbient=lightAmbient;
	v_positionCamera=positionCamera;
	v_matAmbient=matAmbient;
	v_matDiffuse=matDiffuse;
	v_matSpecular=matSpecular;
	v_matShininess=matShininess;

	//project the vertex by the model view projection
	gl_Position = viewprojection * vec4(wPos,1.0); //output of the vertex shader
}
