#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <iostream>
#include <string>

void initShaders(sf::Shader& shader, std::string vert, std::string frag) {
	
	if (!shader.loadFromFile("assets/shaders/shader.vert", "assets/shaders/shader.frag")) {
		printf( "Couldnt load shaders. \n");
	}
	else {
		std::cout << "Shaders loaded." << std::endl;
	}
}

void display(sf::Window* window){
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw...
	window->display();
	// end the current frame (internally swaps the front and back buffers)
}
int main()
{
	// create the window
	sf::Window window(sf::VideoMode(1600, 900), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	
	// load resources, initialize the OpenGL states, ...
	sf::Shader shader;
	initShaders(shader, "assets/shaders/shader.vert", "assets/shaders/shader.frag");

	shader.bind(&shader);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	glewExperimental = GL_TRUE;

	GLfloat vertices[12] = {
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			1.0f, 0.1f,
			1.0f, 0.5f,
			0.0f, 0.5f,
	};


	GLuint VAOs[5];
	GLuint VBOs[5];
	glGenVertexArrays(5, VAOs);
	glBindVertexArray(*VAOs);
	glGenBuffers(5, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, *VBOs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	///test
	// run the main loop
	bool running = true;

	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F12) {
					if (!shader.loadFromFile("assets/shaders/shader.vert", "assets/shaders/shader.frag")) {
						std::printf("Couldnt load shaders.\n");
					}
					else {
						std::printf("Shader's reloaded. \n");
					}
				}
				
			}
		}

		
		display(&window);
		
		
	}
	
	// release resources...

	return 0;
}