#ifndef CPP4_3DVIEWER_V2_0_2_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_MAINWINDOW_H

#include <qgifimage.h>

#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>

#include "controller.h"
#include "gl_widget.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void clearObjSettings();
  void refreshAppSettingsElementsData();
  void importObj();
  void exportImg();
  void exportGif();
  void createGif();
  void changePositionVector(double val);
  void changeRotationVector(double val);
  void changeScale(double val);
  void changeSizes(double val);
  void changeProjectionType(int index);
  void changeColors();

 public:
  void refreshObjInfo();

 private slots:

  void on_projection_types_currentIndexChanged(int index);

  void on_edge_solid_val_clicked();

  void on_edge_dashed_val_clicked();

  void on_vert_circle_val_clicked();

  void on_vert_square_val_clicked();

  void on_vert_none_val_clicked();

  void on_in_btn_clicked();

  void on_out_btn_clicked();

 private:
  Ui::MainWindow *ui;

  // Get settings data
  Settings &settings = Settings::getInstance();

  // Gif local params
  QTimer *gifTimer = new QTimer(0);
  QGifImage *gifFrame;
  QString gifName;
  int frameCounter = 50;
};
#endif  // MAINWINDOW_H
