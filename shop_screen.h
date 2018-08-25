#pragma once

#include "audio.h"
#include "backdrop.h"
#include "graphics.h"
#include "screen.h"
#include "spritemap.h"
#include "text.h"

#include "game_state.h"

class ShopScreen : public Screen {
  public:

    ShopScreen(GameState state);

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() const override;

  private:

    static const std::string dialogs_[];
    static constexpr int kTextRate = 50;

    Text text_;
    Backdrop backdrop_;
    GameState state_;
    SpriteMap mouf_;
    size_t counter_, index_;

    int phase() const;
    bool done() const;
};

