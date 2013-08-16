#include <skylib/resource/resource_manager.h>

namespace skylib {

ResourceManager::~ResourceManager() {
  ResourceMap::iterator position = resources_.begin();

  for (position; position != resources_.end(); ++position) {
    delete position->second;
  }
}

bool ResourceManager::Unload(std::string const& name) {
  ResourceMap::iterator position = resources_.find(name);

  if (position == resources_.end()) {
    return false;
  }

  Resource *resource = position->second;

  if (!resource->Unload()) {
    return false;
  }

  delete resource;

  resources_.erase(position);

  return true;
}

} // namespace skylib
