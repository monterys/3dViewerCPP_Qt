#ifndef CPP4_3DVIEWER_V2_0_2_GL_WIDGET_H
#define CPP4_3DVIEWER_V2_0_2_GL_WIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include "controller.h"
#include "settings.h"

class GL_Widget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT

 public:
  GL_Widget(QWidget* parent = nullptr);
  ~GL_Widget();

  s21::Controller contr;

  // Process new obj
  void initObj(QString qFileDir);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  // Get settings data
  Settings& settings = Settings::getInstance();

  // Auxiliary methods for render
  void updateProjectionMatrix(int w, int h);
  int screenWidth{}, screenHeight{};
  void drawLines();
  void drawPoints();
};
#endif  // CPP4_3DVIEWER_V2_0_2_GL_WIDGET_H
