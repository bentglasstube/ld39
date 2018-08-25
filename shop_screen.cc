#include "shop_screen.h"

#include "overworld_screen.h"
#include "title_screen.h"

ShopScreen::ShopScreen(GameState state) :
  text_("text.png"), backdrop_("shopkeeper.png"),
  state_(state), counter_(0), index_(0) {}

bool ShopScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (!audio.music_playing()) audio.play_music("filabrazilla.ogg");

  counter_ += elapsed;
  if (counter_ >= kTextRate) {
    ++index_;
    counter_ -= kTextRate;
  }

  if (done() && input.key_pressed(Input::Button::A)) {
    index_ = counter_ = 0;

    if (state_.dialog < 2) ++state_.dialog;
    return state_.dialog != 2;
  }

  return true;
}

void ShopScreen::draw(Graphics& graphics) const {
  backdrop_.draw(graphics);
  text_.draw(graphics, dialogs_[phase()].substr(0, index_), 8, 144);
}

Screen* ShopScreen::next_screen() const {
  if (phase() == 3) return new TitleScreen();
  return new OverworldScreen(state_);
}

int ShopScreen::phase() const {
  if (state_.collected() == 0) return state_.dialog;
  if (state_.collected() < 4) return 2;
  return 3;
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

R"(Take the new hoverboard out
for a spin.  It will be faster
to get around than walking.)",

R"(Well that's some of the
missing parts, but I still
need more pieces.)",

R"(Finally, all the pieces!
Now I can make me some jerky.

                     Fin)",
};
