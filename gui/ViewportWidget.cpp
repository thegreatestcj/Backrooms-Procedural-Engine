#include <glad/glad.h>

#include "ViewportWidget.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include "utilities/CreatePlaneMesh.h"
#include "core/MeshComponent.h"
#include "core/MaterialComponent.h"

static void* QtGLGetProcAddress(const char* name)
{
    return reinterpret_cast<void*>(QOpenGLContext::currentContext()->getProcAddress(name));
}

ViewportWidget::ViewportWidget(QWidget* parent)
    : QOpenGLWidget(parent), camera(glm::vec3(0.0f, 2.0f, 5.0f))
{
    setFocusPolicy(Qt::StrongFocus);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&ViewportWidget::update));
    timer->start(16); // ~60fps
}

ViewportWidget::~ViewportWidget()
{
    delete floorShader;
    delete ceilingShader;
    delete wallpaperShader;
}

void ViewportWidget::initializeGL()
{
    qDebug() << "initializeGL called";

    if (!context() || !context()->isValid()) {
        qWarning() << "❌ OpenGL context invalid!";
        return;
    }

    if (!gladLoadGLLoader(QtGLGetProcAddress)) {
        qWarning() << "❌ gladLoadGLLoader failed!";
        return;
    }

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    qDebug() << "🟢 OpenGL initialized";
}

void ViewportWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void ViewportWidget::paintGL()
{
    if (!shadersInitialized) {
        lazyInitializeShadersAndScene();
        shadersInitialized = true;
    }

    float current = static_cast<float>(QDateTime::currentMSecsSinceEpoch()) / 1000.0f;
    float deltaTime = current - lastFrameTime;
    lastFrameTime = current;

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(width()) / height(), 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();

    for (auto& obj : sceneObjects) {
        obj->Render(projection, view, camera.Position);
    }
}

void ViewportWidget::lazyInitializeShadersAndScene()
{
    qDebug() << "🟢 Shader & scene initialization triggered";

    floorShader = new Shader("DefaultFloor.vert", "DefaultFloor.frag");
    ceilingShader = new Shader("DefaultCeiling.vert", "DefaultCeiling.frag");
    wallpaperShader = new Shader("DefaultWallpaper.vert", "DefaultWallpaper.frag");

    setupScene();
}

void ViewportWidget::setupScene()
{
    Mesh plane = CreatePlaneMesh(50.0f, 50.0f, 4.0f);

    auto floor = std::make_shared<Object>();
    floor->AddComponent<MeshComponent>(plane);
    floor->AddComponent<MaterialComponent>(Material(floorShader, glm::vec3(0.4f, 0.35f, 0.3f)));
    floor->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
    sceneObjects.push_back(floor);

    auto ceiling = std::make_shared<Object>();
    ceiling->AddComponent<MeshComponent>(plane);
    ceiling->AddComponent<MaterialComponent>(Material(ceilingShader, glm::vec3(0.95f, 0.95f, 1.0f)));
    ceiling->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    ceiling->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
    sceneObjects.push_back(ceiling);

    glm::vec3 wallPos[4] = {
        glm::vec3(0, 2.5f, -25),
        glm::vec3(0, 2.5f, 25),
        glm::vec3(-25, 2.5f, 0),
        glm::vec3(25, 2.5f, 0)
    };
    float rotY[4] = { 0, 180, 90, -90 };

    for (int i = 0; i < 4; ++i)
    {
        auto wall = std::make_shared<Object>();
        wall->AddComponent<MeshComponent>(plane);
        wall->AddComponent<MaterialComponent>(Material(wallpaperShader, glm::vec3(1.0f, 0.95f, 0.7f)));
        wall->SetPosition(wallPos[i]);
        wall->SetRotation(glm::vec3(0, rotY[i], 0));
        sceneObjects.push_back(wall);
    }
}

void ViewportWidget::mousePressEvent(QMouseEvent* event)
{
    // TODO: implement mouse interaction
}

void ViewportWidget::mouseMoveEvent(QMouseEvent* event)
{
    // TODO: implement mouse interaction
}

void ViewportWidget::keyPressEvent(QKeyEvent* event)
{
    // TODO: implement movement
}
