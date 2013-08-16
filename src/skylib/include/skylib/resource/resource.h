#ifndef SKYLIB_RESOURCE_RESOURCE_H_
#define SKYLIB_RESOURCE_RESOURCE_H_

#include <iostream>

namespace skylib {

class Resource {
 public:
  virtual ~Resource();

  virtual bool Load(std::istream& stream) = 0;
  virtual bool Unload() = 0;
  virtual bool IsLoaded() const = 0;
};

} // namespace skylib

#endif // SKYLIB_RESOURCE_RESOURCE_H_
