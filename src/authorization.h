#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

namespace Ui {
class authorization;
}

class authorization : public QWidget
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = nullptr);
    ~authorization();

private:
    Ui::authorization *ui;
};

#endif // AUTHORIZATION_H
