#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

namespace Ui {
class Manager;
}

class QIntValidator;
class MoveScene;
class GameView;
class QCloseEvent;
class QResizeEvent;

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();

    Q_SIGNAL void generateField(const qint32& w, const qint32& h);
    Q_SLOT void generateButtonClicked();

protected:
    void writeSettings();
    void readSettings();

    Q_SLOT void handleError(const QString& errorMessage);
    Q_SLOT void handleErrorToTextEdit(const QString& error);

    virtual void closeEvent(QCloseEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    Ui::Manager *ui;

    QIntValidator* validator;
    GameView* view;
    MoveScene* scene;
};

#endif // MANAGER_H
