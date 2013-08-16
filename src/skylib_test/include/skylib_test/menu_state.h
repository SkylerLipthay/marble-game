#ifndef SKYLIB_TEST_MENU_STATE_H_
#define SKYLIB_TEST_MENU_STATE_H_

#include <skylib/state.h>
#include <skylib/engine.h>
#include <skylib_test/level.h>
#include <skylib_test/font.h>
#include <vector>
#include <string>

namespace skylib_test {

class MenuState : virtual public skylib::State {
 public:
  MenuState();

  void Initialize(Font *font);
  void Update();
  void Draw();
  static std::vector<std::string> ListFiles(std::string const& directory);
  const bool Selected() const;
  std::string const& Filename() const;
  void Left();
  void Right();
  void Enter();

 private:
  Font *font_;
  std::vector<std::string> files_;
  int index_;
  bool selected_;
};

} // namespace skylib_test

#endif // SKYLIB_TEST_MENU_STATE_H_
