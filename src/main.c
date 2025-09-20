#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL;

int window_width = 800;
int window_height = 600;

SDL_Texture* color_buffer_texture = NULL;

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
		window_width,	// width
		window_height,	// height
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
void setup(void) {
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

	// create a SDL Texture Buffer
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}

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

void clear_color_buffer(uint32_t color) {
	for(int y = 0; y < window_height ; y ++) {
		for(int x = 0; x < window_width; x++) {
			color_buffer[window_width * y + x] = color;
		}
	}
}

// copy from array to SDL texture 
void render_color_buffer(void) {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int) window_width * sizeof(uint32_t)
	);

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}


void render(void) {			
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	 // R G B A
	SDL_RenderClear(renderer);


	render_color_buffer();

	clear_color_buffer(0xFFFFFF00);
	
	SDL_RenderPresent(renderer);
}

void destroy_window() {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
	
	destroy_window();

	return 0;
}
