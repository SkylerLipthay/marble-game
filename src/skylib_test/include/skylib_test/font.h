#ifndef SKYLIB_TEST_FONT_H_
#define SKYLIB_TEST_FONT_H_

#include <skylib/engine.h>
#include <skylib/resource/texture.h>
#include <skylib/resource/sprite.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

namespace skylib_test {

struct FontChar {
  FontChar(int _x, int _y, int _w, int _h, int _xoff, int _yoff, int _xadv,
           skylib::Texture *texture) : sprite(*texture) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    xoff = _xoff;
    yoff = _yoff;
    xadv = _xadv;

    sprite.Initialize(w, h, x, x + w, y, y + h);
  }

  void Draw(float xpos, float ypos) {
    sprite.Render(skylib::Transform::Translate(xpos + xoff, ypos + yoff, 0));
  }

  int x;
  int y;
  int w;
  int h;
  int xoff;
  int yoff;
  int xadv;
  skylib::Sprite sprite;
};

class Font {
 public:
  Font(std::string const& path, std::string const& texture,
       skylib::Engine *engine);
  ~Font();

  const bool IsValid() const;
  const int GetLineHeight() const;
  const int GetBaseline() const;
  FontChar const& GetCharacter(char symbol);
  void Draw(std::string const& text, float x, float y);
  void Bind();

 private:
  typedef boost::shared_ptr<FontChar> FontCharPtr;

  bool valid_;
  skylib::Texture *texture_;
  skylib::Engine *engine_;
  int line_height_;
  int baseline_;
  std::map<char, FontCharPtr> characters_;
  std::string texture_name_;
};

} // namespace skylib_test

#endif // SKYLIB_TEST_FONT_H_
