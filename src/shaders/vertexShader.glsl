#version 430

layout (location = 0) in vec3 position;
uniform mat4x4 iCameraView;
uniform mat4x4 iProject;
uniform mat4x4 iModelRotation;
uniform mat4x4 iMove;
uniform mat4x4 iRotate;

vec3 vertColors[3] = {
	vec3(0.075,0.094,0.259),
	vec3(0.902,0.514,0.412),
	vec3(0.925,0.808,0.682)
};

//vec3 vertColors[3] = {
//	vec3(1.,0.,0.),
//	vec3(0.,1.,0.),
//	vec3(0.,0.,1.)
//};

out vec4 vertexColor;

void main() {

	gl_Position = iProject * iCameraView * iMove * iRotate * iModelRotation * vec4(position, 1.0f);
	vertexColor = vec4(vertColors[(gl_VertexID + gl_VertexID) % 3], 1.0f);
}
