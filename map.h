#pragma once

#include <vector>

#include "graphics.h"
#include "spritemap.h"

#include "game_state.h"
#include "item.h"
#include "rect.h"

class Map {
  public:

    enum class TileType {
      Empty, Block, Window, LogLeft, LogMid, LogRight, Dirt, Grass,
      BeamStart, BeamRest, DoorTop, DoorBottom, Chair, Flower, Register, Fence
    };

    struct Tile {
      TileType type;
      bool obstruction;
      double top, left, right, bottom;
    };

    Map(GameState state);

    void load(const std::string& file);
    void draw(Graphics& graphics, int xoffset, int yoffset) const;

    const Item* item(double x, double y) const;
    void remove_item(const Item* item);

    Tile tile(double x, double y) const;
    Tile collision(Rect box, double dx, double dy) const;
    int pixel_width() const;
    int pixel_height() const;

    double startx() const;
    double starty() const;
    bool out_of_bounds(double x, double y) const;

  private:

    static constexpr int kTileSize = 16;
    static constexpr Tile kNullTile = {};

    GameState state_;
    SpriteMap tileset_;
    int width_, height_;
    double sx_, sy_;
    TileType tiles_[128][1024];
    std::vector<Item> items_;

    Tile itile(int x, int y) const;
    Tile check_tiles(int x1, int x2, int y1, int y2) const;
};
