#include <skylib/resource/model.h>
#include <skylib/math/vector.h>
#include <skylib/vertex/vertex.h>
#include <skylib/vertex/vertex_color.h>
#include <skylib/vertex/vertex_normal.h>
#include <skylib/vertex/vertex_normal_color.h>
#include <skylib/vertex/vertex_normal_texture.h>
#include <skylib/vertex/vertex_texture.h>
#include <skylib/vertex/batch.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lambda/lambda.hpp>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>

namespace skylib {

Model::Model() {
  loaded_ = false;
}

Model::~Model() {
  Unload();
}

bool Model::Unload() {
  if (!loaded_) {
    return false;
  }

  switch (buffer_type_) {
    case kVertex:
      delete[] reinterpret_cast<Vertex *>(buffer_);
      break;

    case kVertexColor:
      delete[] reinterpret_cast<VertexColor *>(buffer_);
      break;

    case kVertexNormal:
      delete[] reinterpret_cast<VertexNormal *>(buffer_);
      break;

    case kVertexNormalColor:
      delete[] reinterpret_cast<VertexNormalColor *>(buffer_);
      break;

    case kVertexNormalTexture:
      delete[] reinterpret_cast<VertexNormalTexture *>(buffer_);
      break;

    case kVertexTexture:
      delete[] reinterpret_cast<VertexTexture *>(buffer_);
      break;
  }

  loaded_ = false;

  return true;
}

bool Model::Load(std::istream& stream) {
  if (loaded_) {
    return false;
  }

  stream.seekg(0, std::ios::beg);

  std::string line;

  std::vector< Vector<3> > normals;
  std::vector< Vector<3> > vertices;
  std::vector< Vector<2> > texture_coords;
  std::vector<unsigned int> face_vertices;
  std::vector<unsigned int> face_texture_coords;
  std::vector<unsigned int> face_normals;

  while (!stream.eof()) {
    std::getline(stream, line);
    boost::trim(line);

    // compress whitespace (any repeated occurrence of space becomes one space)
    boost::function<bool(char, char)> functor;
    functor = (boost::lambda::_1 == ' ') && (boost::lambda::_2 == ' ');
    line.erase(std::unique(line.begin(), line.end(), functor), line.end());

    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_space());

    std::string const& command = tokens.at(0);

    if (command == "vn" && tokens.size() == 4) {
      normals.push_back(Vector<3>(boost::lexical_cast<float>(tokens[1]),
                                  boost::lexical_cast<float>(tokens[2]),
                                  boost::lexical_cast<float>(tokens[3])));
    } else if (command == "vt" && tokens.size() == 3) {
      // Wavefront OBJ files considers the origin to be top left, OpenGL
      // considers the origin to be bottom left; we invert the y-coordinate
      // because of this discrepancy
      texture_coords.push_back(
          Vector<2>(boost::lexical_cast<float>(tokens[1]),
                    1.0f - boost::lexical_cast<float>(tokens[2])));
    } else if (command == "v" && tokens.size() == 4) {
      vertices.push_back(Vector<3>(boost::lexical_cast<float>(tokens[1]),
                                   boost::lexical_cast<float>(tokens[2]),
                                   boost::lexical_cast<float>(tokens[3])));
    } else if (command == "f" && tokens.size() >= 4) {
      // a valid face has at least 3 vertices
      struct Triple {
        int vertex;
        int normal;
        int texture;
      };

      int triple_count = tokens.size() - 1;
      Triple *triples = new Triple[triple_count];

      for (unsigned int index = 1; index < tokens.size(); index++) {
        std::string const& point = tokens.at(index);
        std::vector<std::string> indices;
        boost::split(indices, point, boost::is_any_of("/"));

        if (indices.empty()) {
          delete[] triples;
          return false;
        }

        triples[index - 1].vertex = boost::lexical_cast<int>(indices[0]) - 1;

        if (indices.size() < 3) {
          triples[index - 1].texture = -1;
          triples[index - 1].normal = -1;
          continue;
        }

        if (!indices[1].empty()) {
          triples[index - 1].texture = boost::lexical_cast<int>(indices[1]) - 1;
        } else {
          triples[index - 1].texture = -1;
        }

        if (!indices[2].empty()) {
          triples[index - 1].normal = boost::lexical_cast<int>(indices[2]) - 1;
        } else {
          triples[index - 1].normal = -1;
        }
      }

      const Triple *first = &triples[0];
      for (unsigned int index = 2; index < triple_count; index++) {
        face_vertices.push_back(first->vertex);
        if (first->normal != -1) {
          face_normals.push_back(first->normal);
        }
        if (first->texture != -1) {
          face_texture_coords.push_back(first->texture);
        }

        const Triple *second = &triples[index - 1];
        face_vertices.push_back(second->vertex);
        if (first->normal != -1) {
          face_normals.push_back(second->normal);
        }
        if (first->texture != -1) {
          face_texture_coords.push_back(second->texture);
        }

        const Triple *third = &triples[index];
        face_vertices.push_back(third->vertex);
        if (first->normal != -1) {
          face_normals.push_back(third->normal);
        }
        if (first->texture != -1) {
          face_texture_coords.push_back(third->texture);
        }
      }

      delete[] triples;
    }
  }

  buffer_size_ = face_vertices.size();

  bool use_normals = face_normals.size() == face_vertices.size();
  bool use_texture_coords = face_texture_coords.size() == face_vertices.size();
  btVector3 triangle[3];

  if (use_normals && use_texture_coords) {
    VertexNormalTexture *buffer = new VertexNormalTexture[buffer_size_];

    for (unsigned int index = 0; index < buffer_size_; index++) {
      bool vertex_valid = face_vertices[index] < vertices.size();
      bool normal_valid = face_normals[index] < normals.size();
      bool texture_valid = face_texture_coords[index] < texture_coords.size();

      if (!(vertex_valid && normal_valid && texture_valid)) {
        delete[] buffer;
        return false;
      }

      Vector<3>& location = vertices[face_vertices[index]];
      triangle[index % 3].setValue(location.At(0), location.At(1),
                                   location.At(2));
      if (index % 3 == 2) {
        triangle_mesh_.addTriangle(triangle[0], triangle[1], triangle[2]);
      }

      buffer[index] = VertexNormalTexture(
          location,
          normals[face_normals[index]],
          texture_coords[face_texture_coords[index]]);
    }

    buffer_ = reinterpret_cast<void *>(buffer);
    buffer_type_ = kVertexNormalTexture;
  } else if (use_normals) {
    VertexNormal *buffer = new VertexNormal[buffer_size_];
    for (unsigned int index = 0; index < buffer_size_; index++) {
      bool vertex_valid = face_vertices[index] < vertices.size();
      bool normal_valid = face_normals[index] < normals.size();

      if (!(vertex_valid && normal_valid)) {
        delete[] buffer;
        return false;
      }

      Vector<3>& location = vertices[face_vertices[index]];
      triangle[index % 3].setValue(location.At(0), location.At(1),
                                   location.At(2));
      if (index % 3 == 2) {
        triangle_mesh_.addTriangle(triangle[0], triangle[1], triangle[2]);
      }

      buffer[index] = VertexNormal(location,
                                   normals[face_normals[index]]);
    }

    buffer_ = reinterpret_cast<void *>(buffer);
    buffer_type_ = kVertexNormal;
  } else if (use_texture_coords) {
    VertexTexture *buffer = new VertexTexture[buffer_size_];
    for (unsigned int index = 0; index < buffer_size_; index++) {
      bool vertex_valid = face_vertices[index] < vertices.size();
      bool texture_valid = face_texture_coords[index] < texture_coords.size();

      if (!(vertex_valid && texture_valid)) {
        delete[] buffer;
        return false;
      }

      Vector<3>& location = vertices[face_vertices[index]];
      triangle[index % 3].setValue(location.At(0), location.At(1),
                                   location.At(2));
      if (index % 3 == 2) {
        triangle_mesh_.addTriangle(triangle[0], triangle[1], triangle[2]);
      }

      buffer[index] = VertexTexture(location,
                                    texture_coords[face_texture_coords[index]]);
    }

    buffer_ = reinterpret_cast<void *>(buffer);
    buffer_type_ = kVertexTexture;
  } else {
    Vertex *buffer = new Vertex[buffer_size_];
    for (unsigned int index = 0; index < buffer_size_; index++) {
      bool vertex_valid = face_vertices[index] < vertices.size();

      if (!vertex_valid) {
        delete[] buffer;
        return false;
      }

      Vector<3>& location = vertices[face_vertices[index]];
      triangle[index % 3].setValue(location.At(0), location.At(1),
                                   location.At(2));
      if (index % 3 == 2) {
        triangle_mesh_.addTriangle(triangle[0], triangle[1], triangle[2]);
      }

      buffer[index] = Vertex(location);
    }

    buffer_ = reinterpret_cast<void *>(buffer);
    buffer_type_ = kVertex;
  }

  loaded_ = true;

  return true;
}

bool Model::IsLoaded() const {
  return loaded_;
}

void Model::Render() const {
  if (!loaded_) {
    return;
  }

  switch (buffer_type_) {
    case kVertex:
      DrawVertexBatch(reinterpret_cast<Vertex *>(buffer_), buffer_size_);
      break;

    case kVertexColor:
      DrawVertexBatch(reinterpret_cast<VertexColor *>(buffer_), buffer_size_);
      break;

    case kVertexNormal:
      DrawVertexBatch(reinterpret_cast<VertexNormal *>(buffer_), buffer_size_);
      break;

    case kVertexNormalColor:
      DrawVertexBatch(reinterpret_cast<VertexNormalColor *>(buffer_),
                      buffer_size_);
      break;

    case kVertexNormalTexture:
      DrawVertexBatch(reinterpret_cast<VertexNormalTexture *>(buffer_),
                      buffer_size_);
      break;

    case kVertexTexture:
      DrawVertexBatch(reinterpret_cast<VertexTexture *>(buffer_), buffer_size_);
      break;
  }
}

void Model::Render(Matrix<4, 4> const& transformations) const {
  glPushMatrix();
  glLoadMatrixf(transformations.Data());
  Render();
  glPopMatrix();
}

btTriangleMesh *Model::GetTriangleMesh() {
  return &triangle_mesh_;
}

} // namespace skylib
