#pragma once

#include "KeyboardManager.hpp"
#include "MouseManager.hpp"

struct Platform {
  KeyboardManager keyboard_manager {};
  MouseManager mouse_manager{};
  bool exit = false;
};
