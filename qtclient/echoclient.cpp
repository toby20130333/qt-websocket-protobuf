#include "echoclient.h"
#include <QtCore/QDebug>
#include <QTimer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <string>
#include <QFile>
#include <QTextStream>
#include "Information.RequestMessage.pb.h"
#include "Information.ResponseMessage.pb.h"

QT_USE_NAMESPACE

EchoClient::EchoClient(const QUrl &url, QObject *parent) :
    QObject(parent),
    mUrl(url)
{
    connect(&mWebSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&mWebSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
}

EchoClient::~EchoClient()
{
    mWebSocket.close();
}

void EchoClient::sendMsg()
{
    tutorial::RequestMessage subRequest;
    subRequest.set_service("obj-data-getter-job");
    subRequest.set_token("1212819898BACD3DDD");
    subRequest.set_format("protobuf");
    std::string string;
    if (!subRequest.SerializeToString(&string)) {
        qDebug() << " Serialize Failed";
    }
    QString strmsg = QString("<font color='green'>Send Binary message:<br />"
                             "</font> service: %1<br />  format: %2<br />  token: %3<br />")
            .arg(QString::fromStdString("obj-data-getter-job"))
            .arg(QString::fromStdString("1212819898BACD3DDD"))
            .arg(QString::fromStdString("protobuf"));
    emit signalRecieveMessage(strmsg);
    mWebSocket.sendBinaryMessage(string.data());
}

void EchoClient::openWS()
{
        mWebSocket.open(QUrl(mUrl));
}

void EchoClient::onConnected()
{
    qDebug() << "WebSocket connected";
    emit signalRecieveMessage("<font color='green'>WebSocket Connected:</font>");
    connect(&mWebSocket, &QWebSocket::textMessageReceived,
            this, &EchoClient::onTextMessageReceived);
    connect(&mWebSocket,&QWebSocket::binaryMessageReceived,
            this,&EchoClient::onBinaryMessageReceived);
    //    tutorial::ResponseMessage response
}

void EchoClient::onTextMessageReceived(QString message)
{
    tutorial::ResponseMessage subResult;
    tutorial::ResponseMessage result;
    google::protobuf::Any any;

    if (!result.ParseFromString(message.toStdString()))
        qDebug() << "Parse Failed";

    QString sevice = QString::fromStdString(subResult.service());
    QString format = QString::fromStdString(subResult.format());
    bool success = subResult.issucceeded();

    subResult.mutable_data()->UnpackTo(&any);
    any.UnpackTo(&result);

    qDebug() << sevice << format << success
             <<QString::fromStdString( result.service())
            <<QString::fromStdString( result.format())
           << result.issucceeded();
    QString strmsg = QString("<font color='green'>TextData Recv:</font> service:%1<br />  format: %2<br />  result-service:%3<br />  result-format:%4").arg(sevice).arg(format).arg(QString::fromStdString(result.service())).arg(QString::fromStdString( result.format()));
    emit signalRecieveMessage(strmsg);
}

void EchoClient::onBinaryMessageReceived(QByteArray message)
{
    QString qMessage= QString::fromUtf8(message.data());
    tutorial::ResponseMessage rootResult;
    tutorial::ResponseMessage subResult;
    google::protobuf::Any any;

    if (!subResult.ParseFromString(qMessage.toStdString()))
        qDebug() << "Parse Failed";

    QString sevice = QString::fromStdString(rootResult.service());
    QString format = QString::fromStdString(rootResult.format());
    bool success = rootResult.issucceeded();

    rootResult.mutable_data()->UnpackTo(&any);
    any.UnpackTo(&subResult);

    QString strmsg = QString("<font color='green'>BinaryData Recv:<br />"
                             "</font> service:%1<br />  format: %2<br />  result-service:%3<br />  result-format:%4<br />  result-type_url:%5<br />  result-value:%6<br />")
            .arg(sevice).arg(format)
            .arg(QString::fromStdString(subResult.service()))
            .arg(QString::fromStdString( subResult.format()))
            .arg(QString::fromStdString( subResult.mutable_data()->type_url()))
            .arg(QString::fromStdString( subResult.mutable_data()->value()));
    emit signalRecieveMessage(strmsg);

    qDebug() << sevice << format << success;
    qDebug() <<QString::fromStdString( subResult.service())
            <<QString::fromStdString( subResult.format())
           << subResult.issucceeded();
    qDebug()<< QString::fromStdString(subResult.mutable_data()->type_url());
    qDebug()<< QString::fromStdString(subResult.mutable_data()->value());


    //    mWebSocket.close();
}
