#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;
layout(location = 4) in float inTexNeed;

layout (binding = 0) uniform ShadowUniformBufferObject 
{
	mat4 depthModel;
    mat4 depthView;
    mat4 depthProj;
} ubo;

out gl_PerVertex 
{
    vec4 gl_Position;   
};

 
void main()
{
	gl_Position =  ubo.depthModel * ubo.depthView * ubo.depthProj * vec4(inPos, 1.0);

}