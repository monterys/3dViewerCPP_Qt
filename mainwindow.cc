#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Load settings
  settings.loadSettings();
  refreshAppSettingsElementsData();

  // Obj button signal
  connect(ui->renderBtn, &QPushButton::clicked, this, &MainWindow::importObj);

  // Img button signal
  connect(ui->snap_btn, &QPushButton::clicked, this, &MainWindow::exportImg);

  //   Gif button signals
  connect(ui->gif_btn, &QPushButton::clicked, this, &MainWindow::exportGif);
  connect(gifTimer, SIGNAL(timeout()), this, SLOT(createGif()));

  // Vector spinboxes signals
  connect(ui->translate_x_val, &QSlider::valueChanged, this,
          &MainWindow::changePositionVector);
  connect(ui->translate_y_val, &QSlider::valueChanged, this,
          &MainWindow::changePositionVector);
  connect(ui->translate_z_val, &QSlider::valueChanged, this,
          &MainWindow::changePositionVector);
  connect(ui->rotate_x_val, &QSlider::valueChanged, this,
          &MainWindow::changeRotationVector);
  connect(ui->rotate_y_val, &QSlider::valueChanged, this,
          &MainWindow::changeRotationVector);
  connect(ui->rotate_z_val, &QSlider::valueChanged, this,
          &MainWindow::changeRotationVector);

  // Scale spinbox signal
  connect(ui->scale_val, &QSlider::valueChanged, this,
          &MainWindow::changeScale);

  // Color buttons signals
  connect(ui->background_color_val, &ColorPushButton::clicked, this,
          &MainWindow::changeColors);
  connect(ui->edge_color_val, &ColorPushButton::clicked, this,
          &MainWindow::changeColors);
  connect(ui->vert_color_val, &ColorPushButton::clicked, this,
          &MainWindow::changeColors);

  // Size spinboxes signals
  connect(ui->edge_thic_val, &QSlider::valueChanged, this,
          &MainWindow::changeSizes);
  connect(ui->vert_size_val, &QSlider::valueChanged, this,
          &MainWindow::changeSizes);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::refreshAppSettingsElementsData() {
  // Refresh type buttons data
  if (settings.getProjectionType() == 0)
    ui->projection_types->setCurrentIndex(0);
  else if (settings.getProjectionType() == 1)
    ui->projection_types->setCurrentIndex(1);
  if (settings.getEdgesType() == 0)
    ui->edge_solid_val->setChecked(true);
  else if (settings.getEdgesType() == 1)
    ui->edge_dashed_val->setChecked(true);
  if (settings.getVertexesType() == 0)
    ui->vert_none_val->setChecked(true);
  else if (settings.getVertexesType() == 1)
    ui->vert_circle_val->setChecked(true);
  else if (settings.getVertexesType() == 2)
    ui->vert_square_val->setChecked(true);

  // Refresh color buttons data
  ui->background_color_val->updateData(settings.getBackgroundColor());
  ui->edge_color_val->updateData(settings.getEdgesColor());
  ui->vert_color_val->updateData(settings.getVertexesColor());

  // Refresh spinboxes data
  ui->edge_thic_val->setValue(static_cast<double>(settings.getEdgesSize()));
  ui->vert_size_val->setValue(static_cast<double>(settings.getVertexesSize()));
}

void MainWindow::clearObjSettings() {
  ui->translate_x_val->setValue(0.0);
  settings.setPositionX(0.0);
  ui->translate_y_val->setValue(0.0);
  settings.setPositionY(0.0);
  ui->translate_z_val->setValue(0.0);
  settings.setPositionZ(0.0);
  ui->rotate_x_val->setValue(0.0);
  settings.setRotationX(0.0);
  ui->rotate_y_val->setValue(0.0);
  settings.setRotationY(0.0);
  ui->rotate_z_val->setValue(0.0);
  settings.setRotationZ(0.0);
}

void MainWindow::refreshObjInfo() {
  QFileInfo fileInfo(settings.getObjDirectory());
  ui->filename_val->setText(fileInfo.fileName());
  ui->vert_numb_val->setText(QString::number(settings.getObjVertexes()));
  ui->edges_numb_val->setText(QString::number(settings.getObjEdges()));
}

void MainWindow::importObj() {
  settings.setObjDirectory((QFileDialog::getOpenFileName(
      this, tr("Pick an obj file"), tr("obj (*.obj)"))));
  if (!settings.getObjDirectory().isEmpty()) {
    clearObjSettings();
    ui->OpenGlWidget->initObj(settings.getObjDirectory());
    refreshObjInfo();
  }
}

void MainWindow::exportImg() {
  QFileDialog dialogConnectImage(this);
  QDateTime currentDate = QDateTime::currentDateTime();
  QString formattedTime = currentDate.toString("yyyy-MM-dd-hh.mm.ss");
  QString namePattern = "screenshot-" + formattedTime + ".jpeg";
  QString imgName = dialogConnectImage.getSaveFileName(
      this, tr("Save a screenshot"), namePattern, tr("image (*.jpeg *.bmp)"));
  if (imgName != "") {
    QImage img = ui->OpenGlWidget->grabFramebuffer();
    img.save(imgName);
  }
}

void MainWindow::exportGif() {
  QDateTime currentDate = QDateTime::currentDateTime();
  QString formattedTime = currentDate.toString("yyyy-MM-dd-hh.mm.ss");
  QString namePattern = "screencast-" + formattedTime + ".gif";
  gifName = QFileDialog::getSaveFileName(this, tr("Save a screencast"),
                                         namePattern, tr("gif (*.gif)"));
  if (gifName != "") {
    ui->gif_btn->setDisabled(true);
    gifFrame = new QGifImage;
    gifFrame->setDefaultDelay(settings.gifDelayMS);
    gifTimer->setInterval(settings.gifFrameIntervalMS);
    gifTimer->start();
  }
}

void MainWindow::createGif() {
  QImage img = ui->OpenGlWidget->grabFramebuffer();
  QSize imgSize(settings.gifWidth, settings.gifHeight);
  QImage scaledImg = img.scaled(imgSize);
  gifFrame->addFrame(scaledImg);
  if (frameCounter <= 0) {
    gifTimer->stop();
    gifFrame->save(gifName);
    frameCounter = settings.gifTotalFrames;
    delete gifFrame;
    ui->gif_btn->setText("GIF");
    ui->gif_btn->setEnabled(true);
  }
  frameCounter--;
  if (!ui->gif_btn->isEnabled()) {
    ui->gif_btn->setText(QString::number(frameCounter / 10 + 1) + "S");
  }
}

void MainWindow::changePositionVector(double val) {
  if (QObject::sender() == ui->translate_x_val) {
    ui->OpenGlWidget->contr.moveScene((val - settings.getPositionX()) / 10, 0,
                                      0);
    settings.setPositionX(val);
  } else if (QObject::sender() == ui->translate_y_val) {
    ui->OpenGlWidget->contr.moveScene(0, (val - settings.getPositionY()) / 10,
                                      0);
    settings.setPositionY(val);
  } else if (QObject::sender() == ui->translate_z_val) {
    ui->OpenGlWidget->contr.moveScene(0, 0,
                                      (val - settings.getPositionX()) / 10);
    settings.setPositionZ(val);
  }
  ui->OpenGlWidget->update();
}

void MainWindow::changeRotationVector(double val) {
  if (QObject::sender() == ui->rotate_x_val) {
    ui->OpenGlWidget->contr.xRotateScene(val - settings.getRotationX());
    settings.setRotationX(val);
  } else if (QObject::sender() == ui->rotate_y_val) {
    ui->OpenGlWidget->contr.yRotateScene(val - settings.getRotationY());
    settings.setRotationY(val);
  } else if (QObject::sender() == ui->rotate_z_val) {
    ui->OpenGlWidget->contr.zRotateScene(val - settings.getRotationZ());
    settings.setRotationZ(val);
  }
  ui->OpenGlWidget->update();
}

void MainWindow::changeScale(double val) {
  float floatVal = static_cast<float>(val);
  settings.setScale(floatVal);
  ui->OpenGlWidget->update();
}

void MainWindow::changeProjectionType(int index) {
  if (index == 1) {
    settings.setProjectionType(1);
  } else if (index == 0) {
    settings.setProjectionType(0);
  }
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::changeColors() {
  ColorPushButton* senderButton = qobject_cast<ColorPushButton*>(sender());
  if (senderButton) {
    QString hexCode = senderButton->text();
    if (senderButton == ui->background_color_val) {
      settings.setBackgroundColor(QColor(hexCode));
    } else if (senderButton == ui->edge_color_val) {
      settings.setEdgesColor(QColor(hexCode));
    } else if (senderButton == ui->vert_color_val) {
      settings.setVertexesColor(QColor(hexCode));
    }
  }
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::changeSizes(double val) {
  float floatVal = static_cast<float>(val);
  if (QObject::sender() == ui->edge_thic_val) {
    settings.setEdgesSize(floatVal);
  } else if (QObject::sender() == ui->vert_size_val) {
    settings.setVertexesSize(floatVal);
  }
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::on_projection_types_currentIndexChanged(int index) {
  changeProjectionType(index);
}

void MainWindow::on_edge_solid_val_clicked() {
  settings.setEdgesType(0);
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::on_edge_dashed_val_clicked() {
  settings.setEdgesType(1);
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::on_vert_circle_val_clicked() {
  settings.setVertexesType(1);
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::on_vert_square_val_clicked() {
  settings.setVertexesType(2);
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::on_vert_none_val_clicked() {
  settings.setVertexesType(0);
  settings.saveSettings();
  ui->OpenGlWidget->update();
}

void MainWindow::on_in_btn_clicked() {
  settings.setScale(settings.getScale() + 1);
  ui->OpenGlWidget->update();
}

void MainWindow::on_out_btn_clicked() {
  settings.setScale(settings.getScale() - 1);
  ui->OpenGlWidget->update();
}
