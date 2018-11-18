#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QSequentialAnimationGroup>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onClickButton();

private:
    Ui::Widget *ui;

    // Группа анимации для кнопки
    QSequentialAnimationGroup* animationGroup;
};

#endif // WIDGET_H
