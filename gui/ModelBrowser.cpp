#include "ModelBrowser.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

ModelBrowser::ModelBrowser(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Model Browser", this);
    layout->addWidget(label);

    auto* list = new QListWidget(this);
    layout->addWidget(list);

    auto* loadButton = new QPushButton("Load Model", this);
    layout->addWidget(loadButton);
}
