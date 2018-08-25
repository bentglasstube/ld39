#pragma once

#include "audio.h"
#include "input.h"
#include "graphics.h"
#include "spritemap.h"

#include "game_state.h"
#include "map.h"
#include "rect.h"

class Player {
  public:

    Player();

    void update(Audio& audio, const Map& map, unsigned int elapsed);
    void draw(Graphics& graphics, int xoffset, int yoffset) const;

    double xpos() const;
    double ypos() const;
    bool on_ground() const;

    void set_pos(double x, double y);
    void move_left();
    void move_right();
    void stop_moving();
    void jump(GameState& state, Audio& audio);

  private:

    static constexpr double kGravity = 0.001;
    static constexpr double kJumpSpeed = 0.5;
    static constexpr double kAccel = 0.001;
    static constexpr double kDampen = 0.95;
    static constexpr double kFallSpeed = 0.3;

    static constexpr double kJumpCost = 2.5;
    static constexpr double kIdleCost = 0.001;

    static constexpr int kWidth = 16;
    static constexpr int kHalfWidth = kWidth / 2;
    static constexpr int kHeight = 24;

    enum class Facing { Right, Left };

    SpriteMap barty_;
    double x_, y_, vx_, vy_, ax_;
    Facing facing_;
    bool grounded_;

#ifndef NDEBUG
    SDL_Rect xcol_, ycol_;
#endif

    void updatex(Audio& audio, const Map& map, unsigned int elapsed);
    void updatey(Audio& audio, const Map& map, unsigned int elapsed);
    void drain(Audio& audio, double amount);

    Rect boxh() const;
    Rect boxv() const;

    int aframe() const;
};
