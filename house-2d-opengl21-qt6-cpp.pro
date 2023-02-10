QT += core gui openglwidgets widgets
win32: LIBS += -lopengl32
SOURCES += main.cpp main_window.cpp opengl_widget.cpp
HEADERS += main_window.h opengl_widget.h renderable.h
TARGET = app
