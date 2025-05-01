//
// Created by saki on 4/30/25.
//

#pragma once

#include <QWidget>

class QSpinBox;
class QSlider;
class QPushButton;

class RoomGeneratorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit RoomGeneratorPanel(QWidget* parent = nullptr);

    signals:
        void seedChanged(int newSeed);
    void roomSizeChanged(int newSize);
    void regenerateRequested();

private:
    QSpinBox* seedSpinBox;
    QSlider* roomSizeSlider;
    QPushButton* regenerateButton;
};

