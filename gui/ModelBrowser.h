#pragma once

#include <QWidget>

class QListWidget;
class QPushButton;

class ModelBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit ModelBrowser(QWidget* parent = nullptr);

    signals:
        void modelSelected(const QString& fileName);
    void loadModelClicked();

private:
    QListWidget* modelList;
    QPushButton* loadButton;
};
