#ifndef CPP4_3DVIEWER_V2_0_2_SETTINGS_H
#define CPP4_3DVIEWER_V2_0_2_SETTINGS_H

#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>
#include <QVector3D>

// extern "C" {
//#include "transform_obj.h"
// }

class Settings {
 public:
  // Settings manipulations
  void saveSettings();
  void loadSettings();
  static Settings& getInstance() {
    static Settings instance;
    return instance;
  }

  // Obj settings setters
  void setPositionX(float x) { positionX = x; };
  void setPositionY(float y) { positionY = y; };
  void setPositionZ(float z) { positionZ = z; };
  void setRotationX(float x) { rotationX = x; };
  void setRotationY(float y) { rotationY = y; };
  void setRotationZ(float z) { rotationZ = z; };
  void setScale(float val) { scale = val; };

  // App settings setters
  void setEdgesSize(float val) { edgesSize = val; };
  void setVertexesSize(float val) { vertexesSize = val; };
  void setProjectionType(int val) { projectionType = val; };
  void setEdgesType(int val) { edgesType = val; };
  void setVertexesType(int val) { vertexesType = val; };
  void setBackgroundColor(QColor color) { backgroundColor = color; };
  void setEdgesColor(QColor color) { edgesColor = color; };
  void setVertexesColor(QColor color) { vertexesColor = color; };

  // Obj info setters
  void setObjDirectory(QString path) { qFileDir = path; };
  void setObjVertexes(int count) { vertexes = count; };
  void setObjEdges(int count) { edges = count; };

  // Obj settings getters
  float getPositionX() { return positionX; };
  float getPositionY() { return positionY; };
  float getPositionZ() { return positionZ; };
  float getRotationX() { return rotationX; };
  float getRotationY() { return rotationY; };
  float getRotationZ() { return rotationZ; };
  float getScale() { return scale; }

  // App settings getters
  float getEdgesSize() { return edgesSize; };
  float getVertexesSize() { return vertexesSize; };
  int getProjectionType() { return projectionType; };
  int getEdgesType() { return edgesType; };
  int getVertexesType() { return vertexesType; };
  QColor getBackgroundColor() { return backgroundColor; };
  QColor getEdgesColor() { return edgesColor; };
  QColor getVertexesColor() { return vertexesColor; };

  // Obj info getters
  QString getObjDirectory() { return qFileDir; };
  int getObjVertexes() { return vertexes; };
  int getObjEdges() { return edges; };

  // Gif global params
  const int gifWidth = 640;
  const int gifHeight = 480;
  const int gifTotalFrames = 50;
  const int gifFrameIntervalMS = 100;
  const int gifDelayMS = 10;

 private:
  // Settings manipulations
  Settings() {}
  ~Settings() {}
  Settings(const Settings&);
  Settings& operator=(const Settings&);

  // Obj settings
  float positionX{};
  float positionY{};
  float positionZ{};
  float rotationX{};
  float rotationY{};
  float rotationZ{};
  float scale = 30.0f;

  // App settings
  float edgesSize = 1.0f;
  float vertexesSize = 5.0f;
  int projectionType{};
  int edgesType{};
  int vertexesType{};
  QColor backgroundColor = "#E3E3DE";
  QColor edgesColor = "#212121";
  QColor vertexesColor = "#212121";

  // Obj info
  QString qFileDir{};
  int vertexes{};
  int edges{};
};
#endif  // CPP4_3DVIEWER_V2_0_2_SETTINGS_H
