#include "player.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Player::Player() :
  barty_("barty.png", 8, kWidth, kHeight),
  x_(0), y_(0), vx_(0), vy_(0), ax_(0),
  facing_(Facing::Right), grounded_(false)
#ifndef NDEBUG
  , xcol_({0, 0, 0, 0}), ycol_({0, 0, 0, 0})
#endif
{}

void Player::update(Audio& audio, const Map& map, unsigned int elapsed) {
  const double ovy = vy_;

  updatex(audio, map, elapsed);
  updatey(audio, map, elapsed);

  // Shitty "friction"
  vx_ *= kDampen;
  vy_ *= kDampen;

  if (vy_ >= kFallSpeed && ovy < kFallSpeed) audio.play_sample("fall.wav");
}

void Player::draw(Graphics& graphics, int xoffset, int yoffset) const {
  const int x = x_ - kHalfWidth - xoffset;
  const int y = y_ - kHeight - yoffset;
  barty_.draw_ex(graphics, aframe(), x, y, facing_ == Facing::Left, 0, 0, 0);

#ifndef NDEBUG
  const Rect h = boxh();
  const SDL_Rect hr {
      (int)(h.left - xoffset),
      (int)(h.top - yoffset),
      (int)(h.right - h.left),
      (int)(h.bottom - h.top)
      };
  graphics.draw_rect(&hr, 0x0000ffff, false);

  const Rect v = boxv();
  const SDL_Rect vr {
      (int)(v.left - xoffset),
      (int)(v.top - yoffset),
      (int)(v.right - v.left),
      (int)(v.bottom - v.top)
      };
  graphics.draw_rect(&vr, 0x0000ffff, false);

  const SDL_Rect crx { xcol_.x - xoffset, xcol_.y - yoffset, xcol_.w, xcol_.h };
  graphics.draw_rect(&crx, 0xff0000ff, false);
  const SDL_Rect cry { ycol_.x - xoffset, ycol_.y - yoffset, ycol_.w, ycol_.h };
  graphics.draw_rect(&cry, 0x800000ff, false);
#endif
}

double Player::xpos() const {
  return x_;
}

double Player::ypos() const {
  return y_;
}

bool Player::on_ground() const {
  return grounded_;
}

void Player::set_pos(double x, double y) {
  x_ = x;
  y_ = y;
}

void Player::move_left() {
  facing_ = Facing::Left;
  ax_ = -kAccel;
}

void Player::move_right() {
  facing_ = Facing::Right;
  ax_ = kAccel;
}

void Player::stop_moving() {
  ax_ = 0;
}

void Player::jump(GameState& state, Audio& audio) {
  if (!on_ground()) {
    if (state.redbull > 0) {
      --state.redbull;
      audio.play_sample("jump.wav");
    } else {
      return;
    }
  }

  vy_ -= kJumpSpeed;
}

void Player::updatex(Audio& audio, const Map& map, unsigned int elapsed) {
  vx_ += ax_ * elapsed;

  Map::Tile tile = map.collision(boxh(), vx_ * elapsed, 0);
  if (tile.obstruction) {
#ifndef NDEBUG
    xcol_ = {
      (int) tile.left,
      (int) tile.top,
      (int) (tile.right - tile.left),
      (int) (tile.bottom - tile.top)
    };
#endif
    if (std::abs(vx_) > 0.1) audio.play_sample("bump.wav");
    x_ = vx_ > 0 ? tile.left - kHalfWidth : tile.right + kHalfWidth;
    vx_ = -vx_;
  } else {
    x_ += vx_ * elapsed;
  }
}

void Player::updatey(Audio&, const Map& map, unsigned int elapsed) {
  vy_ += kGravity * elapsed;
  grounded_ = false;

  Map::Tile tile = map.collision(boxv(), 0, vy_ * elapsed);
  if (tile.obstruction) {
#ifndef NDEBUG
    ycol_ = {
      (int) tile.left,
      (int) tile.top,
      (int) (tile.right - tile.left),
      (int) (tile.bottom - tile.top)
    };
#endif
    if (vy_ > 0) {
      y_ = tile.top;
      grounded_ = true;
    } else {
      y_ = tile.bottom + kHeight;
    }
    vy_ = 0;
  } else {
    y_ += vy_ * elapsed;
  }
}

Rect Player::boxh() const {
  return Rect(x_ - kHalfWidth, y_ - kHeight + 4, x_ + kHalfWidth, y_ - 4);
}

Rect Player::boxv() const {
  return Rect(x_ - kHalfWidth + 2, y_ - kHeight, x_ + kHalfWidth - 2, y_);
}

int Player::aframe() const {
  const int f = SDL_GetTicks() / 100;
  if (vy_ >= kFallSpeed) return 4 + f % 2;
  if (std::abs(vx_) >= 0.15) return f % 4;
  return 0;
}
