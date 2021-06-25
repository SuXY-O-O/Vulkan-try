#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;

    mat4 depthModel;
    mat4 depthView;
    mat4 depthProj;
    
    vec3 baseLight;
    vec3 lightPos;
    vec3 viewPos;

    float ambientStrength;
    float specularStrength;
    float diffuseStrength;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;
layout(location = 4) in float inTexNeed;

// out model
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out float fragTexNeed;
// out light
layout(location = 4) out vec3 fragBaseLight;
layout(location = 5) out vec3 lightPos;
layout(location = 6) out vec3 modelPos;
layout(location = 7) out vec3 viewPos;
layout(location = 8) out float amStrength;
layout(location = 9) out float spStrength;
layout(location = 10) out float diStrength;
// out shadow
layout(location = 11) out vec4 outShadowCoord;

const mat4 biasMat = mat4( 
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.5, 0.5, 0.0, 1.0 );

void main() {
    // pos of point
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0f);
    // point color
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragNormal = mat3(transpose(inverse(ubo.model))) * inNormal;
    fragTexNeed = inTexNeed;
    // point light source
    fragBaseLight = ubo.baseLight;
    lightPos = ubo.lightPos;
    viewPos = ubo.viewPos;
    modelPos = vec3(ubo.model * vec4(inPosition, 1.0));
	amStrength = ubo.ambientStrength;
    spStrength = ubo.specularStrength;
    diStrength = ubo.diffuseStrength;
    // point shadow source
    outShadowCoord =  ( biasMat * ubo.depthProj * ubo.depthView * ubo.depthModel * ubo.model ) * vec4(inPosition, 1.0);
}