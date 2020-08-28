#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

namespace Ui {
class Manager;
}

class QIntValidator;
class MoveScene;

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();

    Q_SIGNAL void generateField(const qint32& w, const qint32& h);
    Q_SLOT void generateButtonClicked();

protected:
    void handleError(const QString& errorMessage);

private:
    Ui::Manager *ui;

    QIntValidator* validator;
    MoveScene* scene;
};

#endif // MANAGER_H
