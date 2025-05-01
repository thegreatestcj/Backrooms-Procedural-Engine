#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <memory>
#include <vector>

#include "core/Camera.h"
#include "core/Object.h"
#include "core/Shader.h"

class ViewportWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit ViewportWidget(QWidget* parent = nullptr);
    ~ViewportWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Camera camera;
    std::vector<std::shared_ptr<Object>> sceneObjects;

    Shader* floorShader = nullptr;
    Shader* ceilingShader = nullptr;
    Shader* wallpaperShader = nullptr;

    bool shadersInitialized = false;
    float lastFrameTime = 0.0f;

    void setupScene();
    void lazyInitializeShadersAndScene();
};
