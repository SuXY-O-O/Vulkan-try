#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

// in model
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in float fragTexNeed;
// in light
layout(location = 4) in vec3 fragBaseLight;
layout(location = 5) in vec3 lightPos;
layout(location = 6) in vec3 modelPos;
layout(location = 7) in vec3 viewPos;
layout(location = 8) in float amStrength;
layout(location = 9) in float spStrength;
layout(location = 10) in float diStrength;

// out color
layout(location = 0) out vec4 outColor;

void main() {
    // Texture color
    vec4 textureColor;
    if (fragTexNeed == 1.0)
    {
        textureColor = texture(texSampler, fragTexCoord);
    }
    else
    {
        textureColor = vec4(fragColor, 1.0);
    }

    // Ambient light
    vec3 ambient = fragBaseLight * amStrength;

    // Diffuse light
    vec3 normNormal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - modelPos);
    float diffuseStr = max(dot(normNormal, lightDir), 0.0) * diStrength;
    vec3 diffuse = diffuseStr * fragBaseLight;

    // Specular light
    vec3 viewDir = normalize(viewPos - modelPos);
    vec3 reflectDir = reflect(-lightDir, normNormal);
    float specularStr = pow(max(dot(viewDir, reflectDir), 0.0), 16) * spStrength;
    if (diffuseStr <= 0.00001)
    {
        specularStr = 0.0;
    }
    vec3 specular = specularStr * fragBaseLight;

    vec3 light = ambient + diffuse + specular;
    vec3 result = light * textureColor.rgb;
    outColor = vec4(result, 1.0);
    // outColor = vec4(light, 1.0);
    // outColor = vec4(amStrength, spStrength, diStrength, 1.0);
}