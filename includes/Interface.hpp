#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Parser.hpp"

class Interface {
  private:
    SDL_Renderer* ren;
    SDL_Window* window;
    bool running;
    Uint64 FLAGS;
    SDL_Event event;
  public:
    Interface();
    ~Interface();
    Interface(Interface&) = delete;
    Interface & operator=(Interface&) = delete;
    void init(const std::string& title, int width, int height);
    bool isRunning();
    void update();
    void render();
    void handleEvents();
};