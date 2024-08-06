#ifndef CPP4_3DVIEWER_V2_0_2_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_2_CONTROLLER_H

#include <QString>

#include "3dviewer.h"

namespace s21 {

class Controller {
 public:
  Controller() = default;
  Controller(QString path) : facade_(path.toStdString(), true) {}

  float *getVertices() { return facade_.getVertices(); }
  unsigned int *getIndices() { return facade_.getIndices(); }
  unsigned int *getIndicesInFace() { return facade_.getIndicesInFace(); }
  unsigned int *getEdges() { return facade_.getEdges(); }
  int getCountVertices() { return facade_.getCountVertices(); }
  int getCountFaces() { return facade_.getCountFaces(); }
  int getCountIndices() { return facade_.getCountIndices(); }
  int getCountEdges() { return facade_.getCountEdges(); }
  NormalizationParameters getParameters() { return facade_.getParameters(); }

  void draw(QString path) { facade_.renderTheScene(path.toStdString(), true); }
  void moveScene(float x, float y, float z) { facade_.moveScene(x, y, z); }
  void scaleScene(float k) { facade_.scaleScene(k); }
  void xRotateScene(float angle) { facade_.xRotateScene(angle); }
  void yRotateScene(float angle) { facade_.yRotateScene(angle); }
  void zRotateScene(float angle) { facade_.zRotateScene(angle); }

 private:
  Facade facade_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_CONTROLLER_H
