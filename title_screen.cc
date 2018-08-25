#include "title_screen.h"

#include "shop_screen.h"

#include <cmath>

TitleScreen::TitleScreen() : text_("text.png"), backdrop_("title.png") {}

bool TitleScreen::update(const Input& input, Audio& audio, unsigned int) {
  if (!audio.music_playing()) audio.play_music("filabrazilla.ogg");
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  backdrop_.draw(graphics);
  if (SDL_GetTicks() / 500 % 2 == 0) {
    text_.draw(graphics, "Press any key", 128, 220, Text::Alignment::Center);
  }
}

Screen* TitleScreen::next_screen() const {
  GameState state;
  return new ShopScreen(state);
}
