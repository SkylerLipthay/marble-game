#ifndef SKYLIB_RESOURCE_TEXTURE_H_
#define SKYLIB_RESOURCE_TEXTURE_H_

#include <skylib/resource/resource.h>
#include <GL/gl.h>
#include <iostream>

namespace skylib {

class Texture : virtual public Resource {
 public:
  Texture();
  ~Texture();

  // stream must be initiated with std::ios::binary, supports loading PNG and
  // JPG files
  bool Load(std::istream& stream);
  bool Unload();
  bool IsLoaded() const;
  void Bind() const;
  const int GetWidth() const;
  const int GetHeight() const;

 private:
  bool loaded_;
  GLuint name_;
  int width_;
  int height_;
  int components_;
};

} // namespace skylib

#endif // SKYLIB_RESOURCE_TEXTURE_H_
