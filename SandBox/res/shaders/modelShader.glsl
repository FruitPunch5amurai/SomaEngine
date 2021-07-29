/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#if defined(VS_BUILD)
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140) uniform Matrices
{
    mat4 u_projection;
	mat4 u_view;
	mat4 u_model;
};



out vec2 TexCoord;

void main()
{
	TexCoord = aTexCoord;
    //Normal = mat3(transpose(inverse(u_model))) * aNormal; 
	
    gl_Position =  u_projection * u_view * u_model * vec4(aPosition, 1.0) ; // see how we directly give a vec3 to vec4's constructor
}

#elif defined(FS_BUILD)
out vec4 FragColor;

layout (std140) uniform Material
{
    vec4 mat_ambient;
	vec4 mat_diffuse;
	vec4 mat_specular;
	float mat_shininess;
};
uniform sampler2D tex_diffuse0;

in vec2 TexCoord;

void main()
{
	FragColor = mat_diffuse * vec4(texture(tex_diffuse0, TexCoord));
	//FragColor = mix(texture(u_diffuse0, TexCoord), texture(u_diffuse1, TexCoord), 0.5);
	//float spreadX = 0.1;
	//float spreadY = 0.1;
	//
	//vec4 color = vec4(1.0,0.0,0.0,1.0);
	//    if(TexCoord.x < spreadX) {
    //	color.rgb *= smoothstep( 0.0, spreadX, TexCoord.x );
    //} 
	//if(TexCoord.x > 1.0 - spreadX) {
    //	color.rgb *= smoothstep( 1.0, 1.0 - spreadX, TexCoord.x );
    //} 
	//if(TexCoord.y < spreadY) {
    //	color.rgb *= smoothstep( 0.0, spreadY, TexCoord.y );
    //} 
	//if(TexCoord.y > 1.0 - spreadY) {
    //	color.rgb *= smoothstep( 1.0, 1.0 - spreadY, TexCoord.y );
    //}
    //FragColor = color;
}
#endif
