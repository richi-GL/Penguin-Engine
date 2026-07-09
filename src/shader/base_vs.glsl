#version 330 core

// Este 'location = 0' coincide perfectamente con el primer PushFloat(3) 
// que configuraste en tu VertexBufferLayout.
layout(location = 0) in vec4 position; 

void main()
{
    // 'gl_Position' es una variable interna y obligatoria de OpenGL.
    // Aquí le asignamos la posición final del vértice.
    gl_Position = position; 
}