#include "MaterialPanel.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

MaterialPanel::MaterialPanel(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Roughness", this);
    auto* slider = new QSlider(Qt::Horizontal, this);

    layout->addWidget(label);
    layout->addWidget(slider);

    connect(slider, &QSlider::valueChanged, this, [=](int value) {
        emit roughnessChanged(value / 100.0f);
    });
}
