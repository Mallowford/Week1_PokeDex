#include "../includes/Interface.hpp"
#include "../includes/Parser.hpp"

#define TITLE "PokeDex"
#define WIDTH 800
#define HEIGHT 600

int main() {
  const int TARGET_FPS = 60;
  const double frameDelay = 1000 / TARGET_FPS;

  Uint64 frameStart;
  int frameTime;
  
  Interface* mainInterface = new Interface();
  mainInterface->init(TITLE, WIDTH, HEIGHT);

  while (mainInterface->isRunning()) {
    frameStart = SDL_GetTicks();

    mainInterface->handleEvents();
    mainInterface->update();
    mainInterface->render();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    };
  };

  delete mainInterface;

  return 0;
};