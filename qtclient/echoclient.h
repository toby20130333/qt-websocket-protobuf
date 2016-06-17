#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>


class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, QObject *parent = Q_NULLPTR);
    ~EchoClient();

    void sendMsg();

    void openWS();
Q_SIGNALS:
    void closed();
    void signalRecieveMessage(const QString& msg);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray message);
private:
    QWebSocket mWebSocket;
    QUrl mUrl;
};

#endif // ECHOCLIENT_H
