#include "manager.h"
#include "ui_manager.h"

#include "graphicscell.h"
#include "gameview.h"
#include "movescene.h"
#include "configuration.h"

#include <QValidator>
#include <QScreen>
#include <QMessageBox>
#include <QSettings>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QRect>
#include <QWidget>
#include <QCloseEvent>
#include <QResizeEvent>


Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager),
    validator(new QIntValidator(this)),
    view(new GameView(this)),
    scene(new MoveScene(this))
{
    ui->setupUi(this);

    // Set config for main window
    this->setWindowTitle("FindPath");
    this->readSettings();

    // Set window icon
    this->setWindowIcon(QIcon(":/icon.png"));

    // Disable frame
    this->ui->lineEdit->setFrame(false);

    // Set validator for width and height lines edit
    validator->setRange(1, 100);
    this->ui->widthLineEdit->setValidator(validator);
    this->ui->heightLineEdit->setValidator(validator);

    // Set to gameLayout GameView
    this->ui->gameLayout->addWidget(this->view);
    this->view->resize(300, 300);
    this->view->setScene(this->scene);
    this->view->setRenderHint(QPainter::HighQualityAntialiasing);

    // Connect signal by generate button with slot
    connect(this->ui->generateButton, &QPushButton::clicked, this, &Manager::generateButtonClicked);
    connect(this, &Manager::generateField, scene, &MoveScene::generatedField);
    connect(scene, &MoveScene::handleError, this, &Manager::handleErrorToTextEdit);
    connect(scene, &MoveScene::clearHandleError, this, [&](){ this->ui->lineEdit->clear(); });
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

    this->view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Manager::writeSettings()
{
    QSettings settings(Configuration::ORGANIZATION, Configuration::APPLICATION);

    settings.beginGroup("Manager");
    settings.setValue("size", this->size());
    settings.setValue("pos", this->pos());
    settings.endGroup();
}

void Manager::readSettings()
{
    QSettings settings(Configuration::ORGANIZATION, Configuration::APPLICATION);

    settings.beginGroup("Manager");
    this->resize(settings.value("size", QSize(400, 400)).toSize());
    this->move(settings.value("pos", QPoint(400, 400)).toPoint());
    settings.endGroup();
}

void Manager::handleError(const QString &errorMessage)
{
    QMessageBox::critical(this, "Fatal error", errorMessage);
}

void Manager::handleErrorToTextEdit(const QString &error)
{
    this->ui->lineEdit->setText(error);
}

void Manager::closeEvent(QCloseEvent *event)
{
    // Save the size and position of window
    writeSettings();
    event->accept();
}

void Manager::resizeEvent(QResizeEvent* event)
{
    this->view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    event->accept();
}
