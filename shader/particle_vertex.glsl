
#version 400 core

uniform	mat4	mvp;

in	vec4	inPosition;
in	vec4	inVelocity;

out	vec3	passPosition;

void	main()
{
	gl_Position = mvp * vec4(inPosition.xyz, 1);
	passPosition = inPosition.xyz;
}
