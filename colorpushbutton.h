#ifndef CPP4_3DVIEWER_V2_0_2_COLORPUSHBUTTON_H
#define CPP4_3DVIEWER_V2_0_2_COLORPUSHBUTTON_H

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

#include "gl_widget.h"

class ColorPushButton : public QPushButton {
  Q_OBJECT

 public:
  ColorPushButton(QWidget *parent = nullptr);
  void updateButtonTitle(const QColor &color);
  void updateData(const QColor &color);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void ChangeColor();

 private:
  QString m_hexCode;
};

#endif  // CPP4_3DVIEWER_V2_0_2_COLORPUSHBUTTON_H
