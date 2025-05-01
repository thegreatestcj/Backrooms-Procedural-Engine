#pragma once

#include <QWidget>

class QComboBox;
class QPushButton;
class QLabel;
class QSlider;

class MaterialPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialPanel(QWidget* parent = nullptr);

    signals:
        void materialChanged(const QString& newMaterial);
    void roughnessChanged(float value);
    void metallicChanged(float value);

private:
    QComboBox* materialSelector;
    QSlider* roughnessSlider;
    QSlider* metallicSlider;
};
