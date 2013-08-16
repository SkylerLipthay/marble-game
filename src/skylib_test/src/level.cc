#include <skylib_test/level.h>
#include <json/json.h>
#include <fstream>

namespace skylib_test {

Level::Level(std::string const& path) {
  valid_ = false;

  std::ifstream file_stream(path.c_str());
  if (file_stream.fail()) {
    return;
  }

  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(file_stream, root)) {
    return;
  }

  name_ = root.get("name", "Unknown Level").asString();

  Json::Value const& spawn = root["spawn"];
  spawn_.setValue(spawn[0u].asDouble(), spawn[1u].asDouble(),
                  spawn[2u].asDouble());
  
  Json::Value const& objects = root["objects"];
  for (int index = 0; index < objects.size(); ++index) {
    Json::Value const& object = objects[index];
    Json::Value const& position = object["position"];
    Json::Value const& rotation = object["rotation"];
    btVector3 position_vector(position[0u].asDouble(),
                              position[1u].asDouble(),
                              position[2u].asDouble());
    btQuaternion rotation_vector(rotation[0u].asDouble(),
                                 rotation[1u].asDouble(),
                                 rotation[2u].asDouble(),
                                 rotation[3u].asDouble());
    objects_.push_back(LevelObject(object.get("model", "???").asString(),
                                   position_vector,
                                   object.get("goal", false).asBool(),
                                   rotation_vector,
                                   object.get("friction", 2.0f).asDouble(),
                                   object.get("restitution", 0.4f).asDouble()));
  }

  valid_ = true;
}

const bool Level::IsValid() const {
  return valid_;
}

std::string const& Level::GetName() const {
  return name_;
}

btVector3 const& Level::GetSpawn() const {
  return spawn_;
}

std::vector<LevelObject> const& Level::GetObjects() const {
  return objects_;
}

} // namespace skylib_test
