/* Create a .pro file:
QT += core gui openglwidgets widgets
win32: LIBS += -lopengl32
SOURCES += main.cpp
TARGET = app
-------------------------------
Build and run commands for CMD:
> qmake -makefile
> mingw32-make
> "./release/app.exe"
*/

#ifdef _WIN32
#include <windows.h>
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
#endif

#include <QtWidgets/QApplication>
#include "main_window.h"

#include <iostream>

int main(int argc, char *argv[])
{
#ifdef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif
    std::cout << std::endl;

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
