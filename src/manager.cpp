#include "manager.h"
#include "ui_manager.h"

#include <QValidator>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QRect>
#include "graphicscell.h"
#include "movescene.h"
#include "configuration.h"

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager),
    validator(new QIntValidator(this)),
    scene(new MoveScene(this))
{
    ui->setupUi(this);

    this->setWindowTitle("FindPath");

    // Set validator for width and height lines edit
    validator->setRange(1, 10);
    this->ui->widthLineEdit->setValidator(validator);
    this->ui->heightLineEdit->setValidator(validator);

    this->ui->graphicsView->resize(300, 300);
    this->ui->graphicsView->setScene(this->scene);

    // Connect signal by generate button with slot
    connect(this->ui->generateButton, &QPushButton::clicked, this, &Manager::generateButtonClicked);
    connect(this, &Manager::generateField, scene, &MoveScene::generatedField);
}

Manager::~Manager()
{
    delete ui;
    delete validator;
    delete scene;
}

void Manager::generateButtonClicked()
{
    qint32 w = this->ui->widthLineEdit->text().toInt();
    qint32 h = this->ui->heightLineEdit->text().toInt();

    if (w == 0 || h == 0)
    {
        handleError(QString::fromUtf8(u8"Количество клеток не может равняться нулю!"));
        return;
    }

    emit generateField(w, h);

    this->ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Manager::handleError(const QString &errorMessage)
{
    QMessageBox messageBox;
    messageBox.critical(this, "Fatal error", errorMessage);
}
