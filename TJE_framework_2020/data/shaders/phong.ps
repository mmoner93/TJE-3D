//this var comes from the vertex shader
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
//the texture passed from the application
uniform sampler2D color_texture;
uniform sampler2D nomal_texture;

void main()
{
	//read the pixel RGBA from the texture at the position v_coord
	vec4 color = texture2D( color_texture, v_coord );
	vec3 normalTemp = (2*texture2D( nomal_texture, v_coord ).xyz)-1;

	if( color.w < 0.5 ) discard;
	vec3 newNormal=normalize(v_wNormal);


	newNormal=(v_model* vec4( newNormal.xyz, 0.0)).xyz;

	vec3 pSubsLp=  v_lightPosition - v_wPos;
	vec3 wLight=normalize(pSubsLp);

	vec3 pSubsCp= v_positionCamera - v_wPos;
	vec3 wEye =normalize(pSubsCp);

	vec3 wReflect = - reflect(wLight,newNormal);

	vec3 matAW=v_matAmbient*color.xyz;
	vec3 matDW=v_matDiffuse*color.xyz;

	vec3 matSW2=v_matSpecular*color.xyz*color.w;

	vec3 factorAmbient= matAW * v_lightAmbient;

	float LdotN=dot(wLight,newNormal);
	LdotN=clamp(LdotN,0.0,1.0);


	vec3 factorDiffuse=matDW*(LdotN)*v_lightDiffuse;


	float RdotE=dot(wReflect,wEye);
	RdotE=clamp(RdotE,0.0,1.0);

	float RdotVElevate2=pow(RdotE,color.w);
	float RdotVElevate=pow(RdotE,v_matShininess);

	vec3 factorSpecular=matSW2*(RdotVElevate)*v_lightSpecular;
	vec3 ligthEquation=factorAmbient+(factorDiffuse+factorSpecular);

	//assign the color to the output
	//gl_FragColor = color;
	gl_FragColor = vec4( ligthEquation, 1.0 );
}
