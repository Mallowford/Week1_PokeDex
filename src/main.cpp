#include "../includes/Interface.hpp"
#include "../includes/Parser.hpp"

int main() {
  const int TARGET_FPS = 60;
  const double frameDelay = 1000 / TARGET_FPS;

  Uint64 frameStart;
  int frameTime;
  
  Interface* mainInterface = new Interface();
  mainInterface->init("PokeDex", 800, 600);
  while (mainInterface->isRunning()) {
    frameStart = SDL_GetTicks();

    mainInterface->handleEvents();
    mainInterface->update();
    mainInterface->handleEvents();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    };

  };

  delete mainInterface;

  return 0;
};