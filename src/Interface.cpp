#include "../includes/Interface.hpp"

Interface::Interface() {
  FLAGS = SDL_INIT_VIDEO;
};

void Interface::init(const std::string& title, int width, int height) {
  if (SDL_Init(FLAGS)) {
    this->window = SDL_CreateWindow(title.c_str(), width, height, FLAGS);

    this->ren = SDL_CreateRenderer(window, NULL);
    running = true;
  }
  else {
    running = false;
  };
};

void Interface::update() {
};
void Interface::render() {

};
void Interface::handleEvents() {

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;
      default:
        break;
    };
  };

};

bool Interface::isRunning() {
  return this->running;
};