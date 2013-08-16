#include <skylib_test/menu_state.h>
#include <windows.h>
#include <sstream>

namespace skylib_test {

MenuState::MenuState() {
  selected_ = false;
}

void MenuState::Initialize(Font *font) {
  font_ = font;
  int size = GetCurrentDirectory(0, NULL);
  char *path = new char[size];
  GetCurrentDirectory(size, path);

  std::string full_path = std::string(path) + "\\res\\levels\\*.json";
  delete[] path;

  files_ = ListFiles(full_path);
  if (files_.size() > 0) {
    index_ = 0;
  } else {
    index_ = -1;
  }
}

const bool MenuState::Selected() const {
  return selected_;
}

std::string const& MenuState::Filename() const {
  return files_[index_];
}

void MenuState::Left() {
  if (index_ < 0 || selected_) {
    return;
  }

  index_--;
  if (index_ < 0) {
    index_ = 0;
  }
}

void MenuState::Right() {
  if (index_ < 0 || selected_) {
    return;
  }

  index_++;
  if (index_ >= files_.size()) {
    index_ = files_.size() - 1;
  }
}

void MenuState::Enter() {
  if (index_ < 0) {
    return;
  }

  selected_ = true;
}

void MenuState::Update() {
}

void MenuState::Draw() {
  GetEngine().SetClearColor(skylib::Color::Black());
  GetEngine().Clear();

  const int height = GetEngine().SetProjectionParallel(1500, -1.0f, 1.0f);
  glLoadIdentity();
  font_->Bind();

  std::ostringstream level_count;
  level_count << files_.size() << " level(s) found";

  font_->Draw(level_count.str(), 24, 100);
  font_->Draw("Use left/right/enter to select a level", 24, 24);

  if (index_ >= 0 && files_.size() > 0) {
    font_->Draw(files_[index_], 24, height - 88);
  }
}

std::vector<std::string> MenuState::ListFiles(std::string const& directory) {
  WIN32_FIND_DATA find_data;
  HANDLE handle = FindFirstFile(directory.c_str(), &find_data);

  std::vector<std::string> file_names;
  file_names.push_back(find_data.cFileName);

  while (FindNextFile(handle, &find_data)) {
    file_names.push_back(find_data.cFileName);
  }

  return file_names;
}

} // namespace skylib_test
