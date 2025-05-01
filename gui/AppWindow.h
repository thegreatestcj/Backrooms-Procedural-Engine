#pragma once

#include <QMainWindow>

class ViewportWidget;
class MaterialPanel;
class ModelBrowser;
class RoomGeneratorPanel;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow(QWidget* parent = nullptr);

private:
    ViewportWidget* viewport;
    MaterialPanel* materialPanel;
    ModelBrowser* modelBrowser;
    RoomGeneratorPanel* roomGeneratorPanel;
};
