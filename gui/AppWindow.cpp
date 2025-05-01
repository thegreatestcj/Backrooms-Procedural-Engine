#include "AppWindow.h"
#include "ViewportWidget.h"
#include "MaterialPanel.h"
#include "ModelBrowser.h"
#include "RoomGeneratorPanel.h"

#include <QDockWidget>
#include <QVBoxLayout>

AppWindow::AppWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Backrooms Engine");
    resize(1280, 720);

    // Viewport
    viewport = new ViewportWidget(this);
    setCentralWidget(viewport);

    // Material Panel
    materialPanel = new MaterialPanel(this);
    auto* materialDock = new QDockWidget("Material", this);
    materialDock->setWidget(materialPanel);
    addDockWidget(Qt::RightDockWidgetArea, materialDock);

    // Model Browser
    modelBrowser = new ModelBrowser(this);
    auto* modelDock = new QDockWidget("Model Browser", this);
    modelDock->setWidget(modelBrowser);
    addDockWidget(Qt::LeftDockWidgetArea, modelDock);

    // Room Generator Panel
    roomGeneratorPanel = new RoomGeneratorPanel(this);
    auto* roomDock = new QDockWidget("Room Generator", this);
    roomDock->setWidget(roomGeneratorPanel);
    addDockWidget(Qt::RightDockWidgetArea, roomDock);
}
