#ifndef SKYLIB_RESOURCE_RESOURCE_MANAGER_H_
#define SKYLIB_RESOURCE_RESOURCE_MANAGER_H_

#include <skylib/resource/resource.h>
#include <string>
#include <iostream>
#include <map>

namespace skylib {

class ResourceManager {
 public:
  ~ResourceManager();

  template <typename T> bool Load(std::string const& name, std::istream& stream,
                                  T *& resource);
  template <typename T> bool GetResource(std::string const& name,
                                         T *& resource);
  bool Unload(std::string const& name);

 private:
  typedef std::map<std::string, Resource *> ResourceMap;
  ResourceMap resources_;
};

template <typename T>
bool ResourceManager::Load(std::string const& name, std::istream& stream,
                           T *& resource) {
  if (resources_.find(name) != resources_.end()) {
    return false;
  }

  T *local_resource = new T;

  if (!local_resource->Load(stream)) {
    delete local_resource;
    return false;
  }

  resources_[name] = local_resource;
  resource = local_resource;
  return true;
}

template <typename T>
bool ResourceManager::GetResource(std::string const& name, T *& resource) {
  ResourceMap::iterator position = resources_.find(name);

  if (position == resources_.end()) {
    return false;
  }

  resource = reinterpret_cast<T *>(position->second);
  return true;
}

} // namespace skylib

#endif // SKYLIB_RESOURCE_RESOURCE_MANAGER_H_
