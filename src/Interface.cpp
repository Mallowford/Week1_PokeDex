#include "../includes/Interface.hpp"
pokemonNode* data;
SDL_Texture* spriteTexture;

Interface::Interface() {
  FLAGS = SDL_INIT_VIDEO;
};

Interface::~Interface() {
  delete ParseManager;
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(ren);
  SDL_Quit();
};

void Interface::init(const std::string& title, int width, int height) {
  if (SDL_Init(FLAGS)) {
    this->window = SDL_CreateWindow(title.c_str(), width, height, FLAGS);

    this->ren = SDL_CreateRenderer(window, NULL);
    SDL_Surface* iconSurf = IMG_Load("assets/icon.png");
    if (!iconSurf) {
      fprintf(stderr, "Error creating icon surface: %s\n", SDL_GetError());
    };
    if (!SDL_SetWindowIcon(window, iconSurf)) {
      fprintf(stderr, "Error setting Window Icon: %s\n", SDL_GetError());
    };

    SDL_DestroySurface(iconSurf);
    running = true;
  }
  else {
    running = false;
  };

  ParseManager = new Parser();
  data = ParseManager->ParsePokemon("kyogre");
  // SDL_FRect src;
  // SDL_FRect dest;
  std::string imagePath = ParseManager->easyImage(data);
  SDL_Surface* pokemonSprite = IMG_Load(imagePath.c_str());
  spriteTexture = SDL_CreateTextureFromSurface(ren, pokemonSprite);
};

void Interface::update() {
};
void Interface::render() {
  SDL_RenderClear(ren);
  SDL_RenderTexture(ren, spriteTexture, NULL, NULL);
  SDL_RenderPresent(ren);
};
void Interface::handleEvents() {

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        keyboardHelper();
        break;
      default:
        break;
    };
  };

};
void Interface::keyboardHelper() {
  switch (event.key.scancode) {
    case SDL_SCANCODE_ESCAPE:
      running = false;
      break;
    default:
      break;
  };
};

bool Interface::isRunning() {
  return this->running;
};