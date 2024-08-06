QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include(QtGifimage/gifimage/qtgifimage.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3dviewer.cc \
    colorpushbutton.cc \
    gl_widget.cc \
    main.cc \
    mainwindow.cc \
    settings.cc

HEADERS += \
    3dviewer.h \
    colorpushbutton.h \
    controller.h \
    gl_widget.h \
    mainwindow.h \
    settings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    3DViewer_v2_0.pro.user \
    QtGifimage/3rdParty/giflib.pri \
    QtGifimage/3rdParty/giflib/AUTHORS \
    QtGifimage/3rdParty/giflib/COPYING \
    QtGifimage/3rdParty/giflib/README \
    QtGifimage/gifimage/doc/qtgifimage.qdocconf \
    QtGifimage/gifimage/doc/src/examples.qdoc \
    QtGifimage/gifimage/doc/src/index.qdoc \
    QtGifimage/gifimage/doc/src/qtgifimage.qdoc \
    QtGifimage/gifimage/doc/src/usage.qdoc \
    QtGifimage/gifimage/qtgifimage.pri

SUBDIRS += \
    QtGifimage/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    QtGifimage/gifimage/gifimage.pro \
    QtGifimage/src.pro
