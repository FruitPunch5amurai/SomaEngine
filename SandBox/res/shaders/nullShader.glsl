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
layout (location = 0) in vec3 position;
out vec4 vertexColor; // specify a color output to the fragment shader

layout (std140) uniform Matrices
{
    mat4 u_projection;
	mat4 u_view;
};
void main()
{
    gl_Position =  u_projection * u_view * vec4(position, 1.0) ; // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0) ; // set the output variable to a dark-red color
}

#elif defined(FS_BUILD)
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
	FragColor = vertexColor;
}
#endif
