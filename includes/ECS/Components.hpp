#pragma once
#include <string>
#include <functional>

struct TransformComponent {
  int x, y, width, height;
};

struct LabelComponent {
  std::string label;
};

struct ButtonComponent {
  std::function<void()> onClick;
  bool hovered = false;
  bool pressed = false;
};