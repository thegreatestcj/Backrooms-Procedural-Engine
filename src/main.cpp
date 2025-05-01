#include <QApplication>
#include "AppWindow.h"
#include <QDebug>
#include <iostream>


// Cross-platform working directory setup
#ifdef _WIN32
    #include <direct.h>
    #define chdir _chdir
#else
    #include <unistd.h>
#endif

void SetWorkingDirectoryToProjectRoot()
{
    // Assuming executable is launched from bin/Debug or bin/Release
    if (chdir("../../") != 0)
    {
        std::cerr << "❌ Failed to change working directory to project root!" << std::endl;
    }
    else
    {
        std::cout << "✅ Working directory set to project root" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    SetWorkingDirectoryToProjectRoot();

    QApplication app(argc, argv);

    AppWindow window;
    window.show();

    qDebug() << "Main window shown";
    return app.exec();
}
