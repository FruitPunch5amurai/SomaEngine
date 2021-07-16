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
 
#include "common.glh"

#if defined(VS_BUILD)
Layout(0) attribute vec3 position;
Layout(1) attribute vec2 texCoord;
Layout(4) attribute mat4 transformMat;

out vec2 texCoord0;
layout (std140) uniform Matrices
{
    mat4 projection;
	mat4 view;
};
void main()
{
	//Vectors are on left side of equation because GLSL uses Column Major while 
	//our math library uses Row Major
    gl_Position =  vec4(position, 1.0) * transformMat * view * projection;
    texCoord0 = texCoord;
}

#elif defined(FS_BUILD)
uniform sampler2D diffuse;
in vec2 texCoord0;

out vec4 FragColor;
void main()
{
	float spreadX = 0.1;
	float spreadY = 0.1;
	
	vec4 color = vec4(1.0,0.0,0.0,1.0);
	    if(texCoord0.x < spreadX) {
    	color.rgb *= smoothstep( 0.0, spreadX, texCoord0.x );
    } 
	if(texCoord0.x > 1.0 - spreadX) {
    	color.rgb *= smoothstep( 1.0, 1.0 - spreadX, texCoord0.x );
    } 
	if(texCoord0.y < spreadY) {
    	color.rgb *= smoothstep( 0.0, spreadY, texCoord0.y );
    } 
	if(texCoord0.y > 1.0 - spreadY) {
    	color.rgb *= smoothstep( 1.0, 1.0 - spreadY, texCoord0.y );
    }
    FragColor = color;
	//FragColor = vec4(1.0,0.0,0.0,1.0);//FragColor = texture(diffuse, texCoord0);
}
#endif
