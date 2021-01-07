#shader vertex
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 inColor;

layout(location = 0) out vec2 outTexCoord;
layout(location = 1) out vec4 outColor;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    outTexCoord = texCoord;
    outColor = inColor;
}

#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

out vec4 fragmentColor;

layout(location = 0) in vec2 outTexCoord;
layout(location = 1) in vec4 outColor;

uniform sampler2D albedo;

uniform vec4 color;

void main()
{
    // fragmentColor = texture(albedo, outTexCoord);
    fragmentColor = color;
}
