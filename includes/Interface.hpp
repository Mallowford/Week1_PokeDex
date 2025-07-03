#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Parser.hpp"
#include "ECS/ECS.hpp"
#include "Button.hpp"

extern TTF_Font* gFont;


class Interface {
  private:
    SDL_Renderer* ren;
    SDL_Window* window;
    bool running;
    Uint64 FLAGS;
    SDL_Event event;
    void keyboardHelper();
    Parser* ParseManager;
    std::vector<SDL_Texture*> textures;
    std::vector<Button> buttons;
    std::string inputText;
  SDL_FRect inputRect = {100, 50, 200, 40}; // Position and size of input box
  public:
    Interface();
    ~Interface();
    Interface(Interface&) = delete;
    Interface & operator=(Interface&) = delete;
    bool init(const std::string& title, int width, int height);
    bool isRunning();
    void update();
    void render();
    void handleEvents();
};