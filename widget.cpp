#include "widget.h"
#include "ui_widget.h"

#include <QPropertyAnimation>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Создадим группу анимации
    animationGroup = new QSequentialAnimationGroup(this);

    // Создадим анимацию свойства передвижения слева-сверху направо-сверху
    QPropertyAnimation* leftTopToRightTop = new QPropertyAnimation(ui->pushButton, "geometry");
    leftTopToRightTop->setDuration(1000); // Длительность анимации
    leftTopToRightTop->setStartValue(ui->pushButton->geometry()); // Стартовая позиция и геометрия анимации
    leftTopToRightTop->setEndValue(ui->pushButton->geometry().translated(100, 0)); // Конечная позиция и геометрия анимации
    animationGroup->addAnimation(leftTopToRightTop); // Добавим анимацию в группу

    // Справа-сверху вниз-справа
    QPropertyAnimation* rightTopToRightBottom = new QPropertyAnimation(ui->pushButton, "geometry");
    rightTopToRightBottom->setDuration(1000);
    rightTopToRightBottom->setStartValue(leftTopToRightTop->endValue());
    rightTopToRightBottom->setEndValue(leftTopToRightTop->endValue().toRect().translated(0, 100));
    animationGroup->addAnimation(rightTopToRightBottom);

    // Снизу-справа налево-вниз
    QPropertyAnimation* rightBottomToLeftBottom = new QPropertyAnimation(ui->pushButton, "geometry");
    rightBottomToLeftBottom->setDuration(1000);
    rightBottomToLeftBottom->setStartValue(rightTopToRightBottom->endValue());
    rightBottomToLeftBottom->setEndValue(rightTopToRightBottom->endValue().toRect().translated(-100, 0));
    animationGroup->addAnimation(rightBottomToLeftBottom);

    // Слева-снизу наверх-слева
    QPropertyAnimation* leftBottomToLeftTop = new QPropertyAnimation(ui->pushButton, "geometry");
    leftBottomToLeftTop->setDuration(1000);
    leftBottomToLeftTop->setStartValue(rightBottomToLeftBottom->endValue());
    leftBottomToLeftTop->setEndValue(rightBottomToLeftBottom->endValue().toRect().translated(0, -100));
    animationGroup->addAnimation(leftBottomToLeftTop);

    // Подключаем нажатие кнопки к слоту обработчику кнопки
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::onClickButton);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onClickButton()
{
    // Запускаем анимацию
    animationGroup->start();
}
