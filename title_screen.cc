#include "title_screen.h"

#include "level_screen.h"

#include <cmath>

void TitleScreen::init() {
  text_.reset(new Text("text.png"));
  backdrop_.reset(new Backdrop("title.png"));
}

bool TitleScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);
  text_->draw(graphics, "Press any key", 128, 208, Text::Alignment::CENTER);
}

Screen* TitleScreen::next_screen() {
  return new LevelScreen();
}

std::string TitleScreen::get_music_track() const {
  return "";
}
