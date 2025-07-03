#pragma once
#include "Interface.hpp"

class Button {
  private:
    SDL_FRect rect;
    std::string label;
    std::function<void()> onClick;

  public:

    Button(float x, float y, float w, float h, std::string lbl, std::function<void()> cb)
      : rect{x, y, w, h}, label(lbl), onClick(cb) {}

    void render(SDL_Renderer* ren) {
      // Draw button rectangle (fill)
      SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
      SDL_RenderFillRect(ren, &rect);
      // Draw border
      SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
      SDL_RenderRect(ren, &rect);
      // Render label (requires SDL_ttf)
      if (!label.empty()) {
        extern TTF_Font* gFont;
        SDL_Color textColor = {0, 0, 0, 255};

        SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, label.c_str(), label.size(), textColor);
        if (textSurface) {
          SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
          if (textTexture) {
            SDL_FRect textRect;
            textRect.w = static_cast<float>(textSurface->w);
            textRect.h = static_cast<float>(textSurface->h);
            textRect.x = rect.x + (rect.w - textRect.w) / 2.0f;
            textRect.y = rect.y + (rect.h - textRect.h) / 2.0f;
            SDL_RenderTexture(ren, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
          };
          SDL_DestroySurface(textSurface);
        };
      };

    };

    bool handleEvent(const SDL_Event& event) {
      if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int mx = event.button.x;
        int my = event.button.y;
        if (mx >= rect.x && mx <= rect.x + rect.w &&
          my >= rect.y && my <= rect.y + rect.h) {
          if (onClick) onClick();
          return true;
        };
      };
      return false;
    };
};