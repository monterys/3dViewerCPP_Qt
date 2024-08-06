#include "settings.h"

void Settings::saveSettings() {
  QSettings settings("s21_project", "3DViewer");
  settings.setValue("edgesSize", edgesSize);
  settings.setValue("vertexesSize", vertexesSize);
  settings.setValue("projectionType", projectionType);
  settings.setValue("edgesType", edgesType);
  settings.setValue("vertexesType", vertexesType);
  settings.setValue("backgroundColor", backgroundColor);
  settings.setValue("edgesColor", edgesColor);
  settings.setValue("vertexesColor", vertexesColor);
}

void Settings::loadSettings() {
  QSettings settings("s21_project", "3DViewer");
  edgesSize = settings.value("edgesSize", 1.0).toFloat();
  vertexesSize = settings.value("vertexesSize", 5.0).toFloat();
  projectionType = settings.value("projectionType", 0).toInt();
  edgesType = settings.value("edgesType", 0).toInt();
  vertexesType = settings.value("vertexesType", 0).toInt();
  backgroundColor =
      settings.value("backgroundColor", QColor("#E3E3DE")).value<QColor>();
  edgesColor = settings.value("edgesColor", QColor("#212121")).value<QColor>();
  vertexesColor =
      settings.value("vertexesColor", QColor("#212121")).value<QColor>();
}
