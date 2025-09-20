#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL");
		return false;
	}
	
	// create a SDL window
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,		// pos x
		SDL_WINDOWPOS_CENTERED, 	// pos y
		800,	// width
		600,	// height
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		fprintf(stderr, "Error creating SDL window");
		return false;
	}
	
	// create a SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer");
		return false;
	}

	return true;
}


// render loop related functions 

void setup(void) {}

void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type){
		case SDL_QUIT:			// close button is detected
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				is_running = false;
			}
	}

}

void update(void) {}

void render(void) {			
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	 // R G B A
	SDL_RenderClear(renderer);
	
	SDL_RenderPresent(renderer);
}



int main(void) {
	
	// Create a SDL Window
	is_running = initialize_window();
	
	setup();


	// render loop
	while(is_running) {
		process_input();
		update();
		render();
	}
	
	return 0;
}
