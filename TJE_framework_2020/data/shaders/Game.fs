
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform float u_time;
uniform float u_tilling;
uniform vec3 u_light_direction;
uniform vec3 u_camera_position;
void main()
{
vec2 uv = v_uv;
vec4 color=u_color * texture2D( u_texture, uv * u_tilling );
vec3 N=normalize(v_normal);
vec3 L=normalize(u_light_direction);
float NdotL=clamp(dot(N,L),0.0,1.0);

//con esto dices cuantos colores quieres en lo de las sombras
//NdotL=round(NdotL*4.0)/4.0;

//el vector es el sol
vec3 light=NdotL*vec3(1.0,1.0,1.0)*0.8;
light+=vec3(0.2,0.2,0.2);
color.xyz*=light;

float dist=length(v_world_position-u_camera_position);
//normalmente la division es entre el camera.far
dist=clamp(dist/128.0,0.0,1.0);
vec3 fog_color= vec3(0.60,0.75,0.78);
color.xyz=mix(color.xyz,fog_color,dist);

gl_FragColor =color;
}
