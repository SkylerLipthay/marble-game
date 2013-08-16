#include <skylib_test/font.h>
#include <json/json.h>
#include <fstream>

namespace skylib_test {

Font::Font(std::string const& path, std::string const& texture,
           skylib::Engine *engine) {
  valid_ = false;
  engine_ = engine;

  std::ifstream file_stream(path.c_str());
  if (file_stream.fail()) {
    return;
  }

  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(file_stream, root)) {
    return;
  }

  Json::Value const& common = root["common"];
  line_height_ = common.get("lineHeight", 0).asInt();
  baseline_ = common.get("base", 0).asInt();

  Json::Value const& characters = root["chars"];

  texture_name_ = std::string("__" + texture);
  std::ifstream file;
  file.open(texture.c_str(), std::ios::binary);
  engine_->GetResourceManager().Load(texture_name_.c_str(), file, texture_);
  file.close();

  for (int index = 0; index < characters.size(); ++index) {
    Json::Value const& character = characters[index];
    char symbol = character.get("id", 0).asInt();

    boost::shared_ptr<FontChar> font_char(
        new FontChar(character.get("x", 0).asInt(),
                     character.get("y", 0).asInt(),
                     character.get("width", 0).asInt(),
                     character.get("height", 0).asInt(),
                     character.get("xoffset", 0).asInt(),
                     character.get("yoffset", 0).asInt() -
                       (line_height_ - baseline_),
                     character.get("xadvance", 0).asInt(), texture_));
    characters_[symbol] = font_char;
  }

  valid_ = true;
}

Font::~Font() {
  if (valid_) {
    engine_->GetResourceManager().Unload(texture_name_);
  }
}

const bool Font::IsValid() const {
  return valid_;
}

const int Font::GetLineHeight() const {
  return line_height_;
}

const int Font::GetBaseline() const {
  return baseline_;
}

FontChar const& Font::GetCharacter(char symbol) {
  boost::shared_ptr<FontChar> font_char = characters_[symbol];
  return *font_char;
}

void Font::Bind() {
  texture_->Bind();
}

void Font::Draw(std::string const& text, float x, float y) {
  for (int index = 0; index < text.size(); index++) {
    char symbol = text.at(index);
    if (characters_.count(symbol) == 0) {
      continue;
    }

    FontChar& font_char = *(characters_[symbol]);
    font_char.Draw(x, y);

    x += font_char.xadv;
  }
}

} // namespace skylib_test
