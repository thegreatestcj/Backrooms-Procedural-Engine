//
// Created by saki on 4/30/25.
//

#include "RoomGeneratorPanel.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>

RoomGeneratorPanel::RoomGeneratorPanel(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Room Generator", this);
    layout->addWidget(label);

    auto* seedSpin = new QSpinBox(this);
    seedSpin->setRange(0, 99999);
    seedSpin->setValue(1234);
    layout->addWidget(seedSpin);

    auto* sizeSlider = new QSlider(Qt::Horizontal, this);
    sizeSlider->setRange(5, 100);
    sizeSlider->setValue(30);
    layout->addWidget(sizeSlider);

    auto* regenButton = new QPushButton("Regenerate", this);
    layout->addWidget(regenButton);
}
