#include "gl_widget.h"

#include <QMessageBox>

#include "controller.h"

GL_Widget::GL_Widget(QWidget* parent) : QOpenGLWidget(parent) {}

GL_Widget::~GL_Widget() {}

void GL_Widget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GL_Widget::resizeGL(int w, int h) {
  screenWidth = w;
  screenHeight = h;
  glViewport(0, 0, w, h);
  updateProjectionMatrix(w, h);
}

void GL_Widget::updateProjectionMatrix(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspectRatio = static_cast<float>(w) / static_cast<float>(h);
  float objAbsVal = 1;
  float halfObjSize = objAbsVal * 0.5f;
  float scaleFactor = settings.getScale();

  if (settings.getProjectionType() == 1) {
    float frustumFactor = scaleFactor * 100;
    float nearPlane = 0.1f;
    float farPlane = 100000.0f;
    float fov = 45.0f;
    float top = halfObjSize * tan(fov * 0.5f * (M_PI / 180.0f)) / frustumFactor;
    float right = top * aspectRatio;
    glFrustum(-right, right, -top, top, nearPlane, farPlane);

  } else if (settings.getProjectionType() == 0) {
    float ortoFactor = halfObjSize / (scaleFactor / 62);
    if (w <= h) {
      glOrtho(-ortoFactor * aspectRatio, ortoFactor * aspectRatio, -ortoFactor,
              ortoFactor, 0.1f, 1000000.0f);
    } else {
      glOrtho(-ortoFactor, ortoFactor, -ortoFactor / aspectRatio,
              ortoFactor / aspectRatio, 0.1f, 1000000.0f);
    }
  }

  glTranslatef(0, 0, -1000);

  glMatrixMode(GL_MODELVIEW);
}

void GL_Widget::paintGL() {
  QColor backgroundColor = settings.getBackgroundColor();
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);

  updateProjectionMatrix(screenWidth, screenHeight);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glVertexPointer(3, GL_FLOAT, 0, contr.getVertices());

  glEnableClientState(GL_VERTEX_ARRAY);

  if (settings.getVertexesType()) {
    drawPoints();
  }
  drawLines();

  glDisableClientState(GL_VERTEX_ARRAY);
}

void GL_Widget::drawLines() {
  if (settings.getEdgesType() == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(settings.getEdgesSize());
  QColor edgesColor = settings.getEdgesColor();
  glColor3f(edgesColor.redF(), edgesColor.greenF(), edgesColor.blueF());
  glDrawElementsBaseVertex(GL_LINES, contr.getCountEdges() * 2, GL_UNSIGNED_INT,
                           contr.getEdges(), -1);
  if (settings.getEdgesType() == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GL_Widget::drawPoints() {
  if (settings.getVertexesType() == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(settings.getVertexesSize());
  QColor vertexesColor = settings.getVertexesColor();
  glColor3f(vertexesColor.redF(), vertexesColor.greenF(),
            vertexesColor.blueF());
  glDrawArrays(GL_POINTS, 0, contr.getCountVertices());
  if (settings.getVertexesType() == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void GL_Widget::initObj(QString qFileDir) {
  try {
    contr.draw(qFileDir);
  } catch (const char* s) {
    QMessageBox box(this);
    box.setWindowTitle("Error");
    box.setText("File not found");
    box.exec();
  } catch (std::exception e) {
    QMessageBox box(this);
    box.setWindowTitle("Error");
    box.setText("Invalid file format");
    box.exec();
  }
  settings.setObjVertexes(contr.getCountVertices());
  settings.setObjEdges(contr.getCountEdges());
  update();
}
