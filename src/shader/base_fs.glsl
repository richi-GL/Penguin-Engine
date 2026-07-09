#version 330 core

// Esta es la variable de salida. El color que le asignemos aquí 
// será el que se dibuje físicamente en el monitor.
layout(location = 0) out vec4 color;

// ¡NUESTRO UNIFORM! La variable mágica que controlamos desde C++ 
// usando tu método 'shader.SetUniform4f(...)'
uniform vec4 u_Color; 

void main()
{
    // Tomamos el color que nos envió C++ y se lo asignamos al píxel.
    color = u_Color; 
}