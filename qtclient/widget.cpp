
#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
    ,m_client(NULL)
{
    ui->setupUi(this);
    //EchoClient client(QUrl(QStringLiteral("ws://localhost:8080")), debug);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connLb_clicked()
{
    if(m_client == NULL){
        ui->connLb->setEnabled(false);
        QString wsUrl = QString("ws://%1:%2").arg(ui->hosted->text()).arg(ui->portld->text());
        qDebug()<<Q_FUNC_INFO<<wsUrl;
        m_client = new EchoClient(QUrl(wsUrl));
        connect(m_client,SIGNAL(signalRecieveMessage(QString)),this,SLOT(slotRec(QString)));
        connect(m_client,SIGNAL(closed()),this,SLOT(slotClose()));
    }
    m_client->openWS();
}

void Widget::slotRec(QString str)
{
    ui->msgTd->append(str);
}

void Widget::on_sendLb_clicked()
{
    m_client->sendMsg();
}

void Widget::slotClose()
{
    ui->connLb->setEnabled(true);
    ui->msgTd->append("<font color='red'>remote server is closed</font>");
}
