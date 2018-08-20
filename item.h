#pragma once

#include "graphics.h"
#include "spritemap.h"

class Item {
  public:

    Item(double x, double y);

    void draw(Graphics& graphics, int x, int y) const;
    double xpos() const;
    double ypos() const;

    bool operator==(const Item& other) const;

  private:

    SpriteMap sprites_;
    double x_, y_;
};
