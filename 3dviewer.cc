#include "3dviewer.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace s21 {

bool Point3d::operator==(const Point3d &other) const {
  return (x == other.x && y == other.y && z == other.z);
}

void Point3d::setCoordinates(float xNew, float yNew, float zNew) {
  x = xNew;
  y = yNew;
  z = zNew;
}

bool Vertex::operator==(const Vertex &other) const {
  return (position_ == other.position_);
}

bool Face::operator==(const Face &other) const {
  return (indices_ == other.indices_);
}

inline bool Edge::operator<(const Edge &other) const {
  return (begin_ < other.begin_ ||
          (begin_ == other.begin_ && end_ < other.end_));
}

Scene FileReader::readScene(std::string path) {
  std::ifstream objFile(path);
  if (!objFile.is_open()) throw("Error opening file");

  std::vector<Vertex> vertices;
  std::vector<Face> faces;

  std::string line;
  while (std::getline(objFile, line)) {
    size_t start = 2;
    std::string first = line.substr(0, line.find_first_of("\r\t "));
    line.push_back(' ');

    if (first == "v") {
      std::vector<float> coordinates;
      size_t count;
      for (int i = 0; i < 3; ++i) {
        coordinates.push_back(std::stod(line.substr(start), &count));
        start += count;
      }
      auto coordinate = coordinates.begin();
      Vertex vertex(Point3d{*coordinate, *(++coordinate), *(++coordinate)});
      vertices.push_back(vertex);
    } else if (first == "f") {
      Face face;
      size_t end;
      while ((end = line.find_first_of("\r\t ", start)) != std::string::npos) {
        if (start == end) {
          ++start;
          continue;
        }
        int index = std::stoi(line.substr(start));
        if (index < 0) index += vertices.size() + 1;
        face.setIndex(index);
        start = end + 1;
      }
      faces.push_back(face);
    }
  }
  Scene scene;
  scene.setVertices(vertices);
  scene.setFaces(faces);
  scene.setEdges();
  scene.setEdgesVector();

  return scene;
}

void Scene::setEdges() {
  for (auto face : getFaces()) {
    std::vector<unsigned int> indicies = face.getIndices();
    std::vector<unsigned int>::iterator itIndex = indicies.begin();
    unsigned int begin = std::min(*itIndex, *(itIndex + 1));
    unsigned int end = std::max(*itIndex, *(itIndex + 1));
    setEdge(Edge(begin, end));
    for (auto it = itIndex + 1; it < indicies.end() - 1; ++it) {
      begin = std::min(*it, *(it + 1));
      end = std::max(*it, *(it + 1));
      setEdge(Edge(begin, end));
    }
    begin = std::min(*itIndex, *(indicies.end() - 1));
    end = std::max(*itIndex, *(indicies.end() - 1));
    setEdge(Edge(begin, end));
  }
}

void Scene::setEdgesVector() {
  for (auto edge : edges_) {
    edgesVector_.push_back(edge);
  }
}

unsigned int *Scene::getEdgesVector() {
  return (unsigned int *)&(*(edgesVector_.begin()));
}

void Scene::setNormalizationParameters() {
  for (auto &vertex : vertices_) {
    auto point = vertex.getPosition();
    float x = point.x;
    float y = point.y;
    float z = point.z;

    if (x < np_.min[0]) np_.min[0] = x;
    if (x > np_.max[0]) np_.max[0] = x;
    if (y < np_.min[1]) np_.min[1] = y;
    if (y > np_.max[1]) np_.max[1] = y;
    if (z < np_.min[2]) np_.min[2] = z;
    if (z > np_.max[2]) np_.max[2] = z;
  }
}

void Scene::normalization() {
  setNormalizationParameters();

  float centerX = (np_.min[0] + np_.max[0]) / 2;
  float centerY = (np_.min[1] + np_.max[1]) / 2;
  float centerZ = (np_.min[2] + np_.max[2]) / 2;

  transformScene(
      TransformMatrixBuilder::createMoveMatrix(-centerX, -centerY, -centerZ));

  const float x = np_.max[0] - np_.min[0];
  const float y = np_.max[1] - np_.min[1];
  const float z = np_.max[2] - np_.min[2];

  const float max = std::max(std::max(x, y), z);
  float scaleValue = .5;
  float scale = (scaleValue - (scaleValue * (-1))) / max;

  transformScene(TransformMatrixBuilder::createScaleMatrix(scale));
}

void Scene::transformScene(TransformMatrix matrix) {
  for (auto &vertex : vertices_) {
    vertex.setPosition(matrix.transformPoint(vertex.getPosition()));
  }
}

size_t Scene::countAllIndices() {
  size_t count = 0;
  for (auto f : faces_) {
    count += f.countIndices();
  }
  return count;
}

Facade::Facade(std::string path, bool useNormalization) {
  renderTheScene(path, useNormalization);
}

Facade::~Facade() {
  delete[] indices_;
  delete[] indicesInFace_;
  delete[] edges_;
}

unsigned int *Facade::getIndices() {
  indices_ = new unsigned int[scene_.countAllIndices()];
  unsigned int i = 0;
  for (auto face : scene_.getFaces()) {
    for (unsigned int index : face.getIndices()) {
      indices_[i++] = index;
    }
  }
  return indices_;
}

unsigned int *Facade::getIndicesInFace() {
  indicesInFace_ = new unsigned int[scene_.countFaces()];
  int f = 0;
  for (auto face : scene_.getFaces()) {
    indicesInFace_[f++] = face.countIndices();
  }
  return indicesInFace_;
}

void Facade::renderTheScene(std::string path, bool useNormalization) {
  scene_ = fileReader_.readScene(path);
  if (useNormalization) scene_.normalization();
}

void Facade::moveScene(float x, float y, float z) {
  scene_.transformScene(TransformMatrixBuilder::createMoveMatrix(x, y, z));
}

void Facade::scaleScene(float k) {
  scene_.transformScene(TransformMatrixBuilder::createScaleMatrix(k));
}

void Facade::xRotateScene(float angle) {
  scene_.transformScene(TransformMatrixBuilder::createXRotationMatrix(angle));
}

void Facade::yRotateScene(float angle) {
  scene_.transformScene(TransformMatrixBuilder::createYRotationMatrix(angle));
}

void Facade::zRotateScene(float angle) {
  scene_.transformScene(TransformMatrixBuilder::createZRotationMatrix(angle));
}

Point3d TransformMatrix::transformPoint(Point3d point) {
  std::vector<float> coordinates{point.x, point.y, point.z, 1.};
  std::vector<float> result;

  for (int i = 0; i < 4; ++i) {
    float sum{};
    for (int j = 0; j < 4; ++j) {
      sum += matr[i][j] * (*(coordinates.begin() + j));
    }
    result.push_back(sum);
  }

  auto coordinate = result.begin();
  return Point3d{*coordinate, *(++coordinate), *(++coordinate)};
}

TransformMatrix TransformMatrixBuilder::createMoveMatrix(float x, float y,
                                                         float z) {
  TransformMatrix moveMatrix{};
  moveMatrix.matr[0][0] = 1.;
  moveMatrix.matr[0][3] = x;
  moveMatrix.matr[1][1] = 1.;
  moveMatrix.matr[1][3] = y;
  moveMatrix.matr[2][2] = 1.;
  moveMatrix.matr[2][3] = z;
  moveMatrix.matr[3][3] = 1.;
  return moveMatrix;
}

TransformMatrix TransformMatrixBuilder::createScaleMatrix(float k) {
  TransformMatrix scaleMatrix;
  scaleMatrix.matr[0][0] = k;
  scaleMatrix.matr[1][1] = k;
  scaleMatrix.matr[2][2] = k;
  scaleMatrix.matr[3][3] = 1.;
  return scaleMatrix;
}

TransformMatrix TransformMatrixBuilder::createXRotationMatrix(float angle) {
  TransformMatrix xRotationMatrix{};
  float radian = toRadian(angle);

  float cosValue = cos(radian);
  float sinValue = sin(radian);

  xRotationMatrix.matr[0][0] = 1.;
  xRotationMatrix.matr[1][1] = cosValue;
  xRotationMatrix.matr[1][2] = -sinValue;
  xRotationMatrix.matr[2][1] = sinValue;
  xRotationMatrix.matr[2][2] = cosValue;
  xRotationMatrix.matr[3][3] = 1.;

  return xRotationMatrix;
}

TransformMatrix TransformMatrixBuilder::createYRotationMatrix(float angle) {
  TransformMatrix yRotationMatrix{};
  float radian = toRadian(angle);

  float cosValue = cos(radian);
  float sinValue = sin(radian);

  yRotationMatrix.matr[0][0] = cosValue;
  yRotationMatrix.matr[1][1] = 1.;
  yRotationMatrix.matr[0][2] = sinValue;
  yRotationMatrix.matr[2][0] = -sinValue;
  yRotationMatrix.matr[2][2] = cosValue;
  yRotationMatrix.matr[3][3] = 1.;

  return yRotationMatrix;
}

TransformMatrix TransformMatrixBuilder::createZRotationMatrix(float angle) {
  TransformMatrix zRotationMatrix{};
  float radian = toRadian(angle);

  float cosValue = cos(radian);
  float sinValue = sin(radian);

  zRotationMatrix.matr[0][0] = cosValue;
  zRotationMatrix.matr[0][1] = -sinValue;
  zRotationMatrix.matr[1][0] = sinValue;
  zRotationMatrix.matr[1][1] = cosValue;
  zRotationMatrix.matr[2][2] = 1.;
  zRotationMatrix.matr[3][3] = 1.;

  return zRotationMatrix;
}

}  // namespace s21