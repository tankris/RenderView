#version 400

varying vec2 texCoord0; //varying is a type of variable that allows sharing between shaders
varying vec3 normal0;

uniform sampler2D diffuse; //Variable in GLSL updated by the CPU but accessible by CPU & GPU

void main ()  
{
   gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(0,0,1), normal0) , 0.0, 1.0); //Take cosine of the angle of 
   //vector 3 lightDirection and normal0. Dot product of 2 vectors is equivalent to the cosine between them
   //Reads a pixel from a 2D texture list and interpolate to the vertex
   //The reason for clamping between 0 & 1 is to ensure that there is no negative lighting or not too bright
}