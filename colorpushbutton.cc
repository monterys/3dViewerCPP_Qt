#include "colorpushbutton.h"

ColorPushButton::ColorPushButton(QWidget *parent) : QPushButton(parent) {
  connect(this, &ColorPushButton::clicked, this, &ColorPushButton::ChangeColor);
}

void ColorPushButton::updateButtonTitle(const QColor &color) {
  m_hexCode = color.name(QColor::HexRgb).toUpper();
  setText(m_hexCode);
  update();
}

void ColorPushButton::updateData(const QColor &color) {
  m_hexCode = color.name(QColor::HexRgb).toUpper();
  updateButtonTitle(color);
}

void ColorPushButton::paintEvent(QPaintEvent *event) {
  QPushButton::paintEvent(event);
  QRect rect = this->rect();

  int squareSize = rect.height() - 10;
  int x = rect.right() - squareSize - 5;
  int y = rect.top() + 5;

  QPainter painter(this);
  QColor borderColor("#212121");

  painter.setPen(QPen(borderColor, 2));
  painter.setBrush(QColor(m_hexCode));
  painter.drawRect(x, y, squareSize, squareSize);
}

void ColorPushButton::ChangeColor() {
  QColorDialog dialog(QColor(m_hexCode), this);
  dialog.setOption(QColorDialog::ShowAlphaChannel);
  if (dialog.exec()) {
    updateData(dialog.currentColor());
  }
}
