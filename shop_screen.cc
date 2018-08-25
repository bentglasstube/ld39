#include "shop_screen.h"

#include "overworld_screen.h"
#include "title_screen.h"

ShopScreen::ShopScreen(GameState state) :
  text_("text.png"), backdrop_("shopkeeper.png"),
  state_(state), counter_(0), index_(0) {}

bool ShopScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  counter_ += elapsed;
  if (counter_ >= kTextRate) {
    ++index_;
    counter_ -= kTextRate;
  }

  if (done() && input.key_pressed(Input::Button::A)) {
    index_ = counter_ = 0;
    return false;
  }

  return true;
}

void ShopScreen::draw(Graphics& graphics) const {
  backdrop_.draw(graphics);
  text_.draw(graphics, dialogs_[phase()].substr(0, index_), 8, 144);
}

Screen* ShopScreen::next_screen() const {
  if (phase() == 2) return new TitleScreen();
  return new OverworldScreen(state_);
}

std::string ShopScreen::get_music_track() const {
  return "filabrazilla.ogg";
}

int ShopScreen::phase() const {
  if (state_.collected() == 0) return 0;
  if (state_.collected() < 4) return 1;
  return 2;
}

bool ShopScreen::done() const {
  return index_ >= dialogs_[phase()].length();
}

const std::string ShopScreen::dialogs_[] = {

R"(This dinner would be so much
better with some beef jerky.
I will have to go look around
town for parts to fix the
dehydrator to make some.)",

R"(Well that's some of the
missing parts, but I still
need more pieces.)",

R"(Finally, all the pieces!
Now I can make me some jerky.

                     Fin)",
};
