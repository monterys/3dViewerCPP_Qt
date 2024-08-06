#ifndef CPP4_3DVIEWER_V2_0_2_3DVIEWER_H
#define CPP4_3DVIEWER_V2_0_2_3DVIEWER_H

#include <math.h>

#include <set>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES

namespace s21 {

class Point3d {
 public:
  Point3d() : Point3d(0., 0., 0.) {}
  Point3d(float x, float y, float z) : x(x), y(y), z(z) {}

  bool operator==(const Point3d &other) const;

  void setCoordinates(float xNew, float yNew, float zNew);

  float x;
  float y;
  float z;
};

class Vertex {
 public:
  Vertex() : Vertex(Point3d()) {}
  Vertex(Point3d position) : position_(position) {}

  Point3d getPosition() { return position_; }
  void setPosition(Point3d position) { position_ = position; }

  bool operator==(const Vertex &other) const;

 private:
  Point3d position_;
};

class Edge {
 public:
  Edge(unsigned int begin, unsigned int end) : begin_(begin), end_(end) {}

  unsigned int getBegin() { return begin_; }
  unsigned int getEnd() { return end_; }

  bool operator<(const Edge &other) const;
  bool operator==(const Edge &other) const;

 private:
  unsigned int begin_;
  unsigned int end_;
};

class Face {
 public:
  Face() = default;
  Face(std::vector<unsigned int> indices) : indices_(indices) {}

  std::vector<unsigned int> getIndices() { return indices_; }
  unsigned int countIndices() { return indices_.size(); }
  void setIndex(unsigned int index) { indices_.push_back(index); }

  bool operator==(const Face &other) const;

 private:
  std::vector<unsigned int> indices_;
};

class TransformMatrix {
 public:
  Point3d transformPoint(Point3d point);

  float matr[4][4]{};
};

class NormalizationParameters {
 public:
  float min[3];
  float max[3];
};

class Scene {
 public:
  float *getVertices() { return (float *)&(*(vertices_.begin())); }
  std::vector<Face> getFaces() { return faces_; }
  void setVertices(std::vector<Vertex> vertices) { vertices_ = vertices; }
  void setFaces(std::vector<Face> faces) { faces_ = faces; }
  void setNormalizationParameters();
  std::set<Edge> getEdges() { return edges_; }
  unsigned int *getEdgesVector();
  void setEdges();
  void setEdgesVector();
  void setEdge(Edge edge) { edges_.insert(edge); }
  NormalizationParameters getParameters() { return np_; }

  size_t countFaces() { return faces_.size(); }
  size_t countVertices() { return vertices_.size(); }
  size_t countAllIndices();
  size_t countEdges() { return edges_.size(); }
  void normalization();
  void transformScene(TransformMatrix matrix);

 private:
  NormalizationParameters np_{};
  std::vector<Vertex> vertices_;
  std::vector<Face> faces_;
  std::set<Edge> edges_;
  std::vector<Edge> edgesVector_;
};

class TransformMatrixBuilder {
 public:
  static TransformMatrix createMoveMatrix(float x, float y, float z);
  static TransformMatrix createScaleMatrix(float k);
  static TransformMatrix createXRotationMatrix(float angle);
  static TransformMatrix createYRotationMatrix(float angle);
  static TransformMatrix createZRotationMatrix(float angle);

 private:
  static float toRadian(float angle) { return M_PI / 180. * angle; }
};

class FileReader {
 public:
  Scene readScene(std::string path);
};

class Facade {
 public:
  Facade() = default;
  Facade(std::string path, bool useNormalization = false);
  ~Facade();
  float *getVertices() { return scene_.getVertices(); }
  unsigned int *getIndices();
  unsigned int *getIndicesInFace();
  unsigned int *getEdges() { return scene_.getEdgesVector(); }
  size_t getCountVertices() { return scene_.countVertices(); }
  size_t getCountFaces() { return scene_.countFaces(); }
  size_t getCountIndices() { return scene_.countAllIndices(); }
  size_t getCountEdges() { return scene_.countEdges(); }
  NormalizationParameters getParameters() { return scene_.getParameters(); }

  void renderTheScene(std::string path, bool useNormalization = false);
  void moveScene(float x, float y, float z);
  void scaleScene(float k);
  void xRotateScene(float angle);
  void yRotateScene(float angle);
  void zRotateScene(float angle);

 private:
  Scene scene_;
  FileReader fileReader_;
  unsigned int *indices_{};
  unsigned int *indicesInFace_{};
  unsigned int *edges_{};
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_3DVIEWER_H
