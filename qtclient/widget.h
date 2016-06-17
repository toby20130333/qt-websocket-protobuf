#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "echoclient.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_connLb_clicked();
    void slotRec(QString);
    void on_sendLb_clicked();
    void slotClose();

private:
    Ui::Widget *ui;
    EchoClient *m_client;
};

#endif // WIDGET_H
