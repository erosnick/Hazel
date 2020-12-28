#shader vertex
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 inColor;
layout(location = 1) out vec4 outColor;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    outColor = inColor;
}

#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 color;
layout(location = 1) in vec4 outColor;

void main()
{
    color = outColor;
}
