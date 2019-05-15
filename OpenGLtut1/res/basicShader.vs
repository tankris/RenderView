#version 400

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal; //Lambersion Lighting is done per pixel

varying vec2 texCoord0;
varying vec3 normal0;

//Take in a matrix and transform our position bind

uniform mat4 transform; //Saving 4x4 matrix to uniform
//uniform is a variable that can be set by the CPU

void main()
{
   gl_Position = transform * vec4(position, 1.0);
   texCoord0 = texCoord; //Sharing texCoords with the fragment shader
   normal0 = (transform * vec4(normal, 0.0)).xyz; //Sharing data with the fragment shader. Also doesn't transform normal as if it is a position
}