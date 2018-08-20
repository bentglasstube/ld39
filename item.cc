#include "item.h"

#include <cmath>
#include <iostream>

Item::Item(double x, double y) :
  sprites_("objects.png", 8, 8, 8),
  x_(x), y_(y)
{}

void Item::draw(Graphics& graphics, int x, int y) const {
  const int f = SDL_GetTicks();
  const int yo = 3 * std::sin(f / 200.0);
  const int n = (f / 100 % 8) + 8;
  sprites_.draw(graphics, n, x - 4, y + yo - 4);
}

double Item::xpos() const {
  return x_;
}

double Item::ypos() const {
  return y_;
}

bool Item::operator==(const Item& other) const {
  return other.xpos() == x_ && other.ypos() == y_;
}
