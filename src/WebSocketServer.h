#pragma once

#include <QDateTime>
#include <QObject>
#include <QTimer>
#include <QWebSocket>
#include <QWebSocketServer>

class WebSocketServer : public QObject {
    Q_OBJECT

public:
    explicit WebSocketServer(QObject* parent = nullptr);
    ~WebSocketServer() override;

    bool    isClientConnected() const { return m_client != nullptr; }
    quint16 port()              const { return m_port; }

    void sendText(const QString& msg);

signals:
    void clientConnected(bool connected);
    void linkTapped();

private slots:
    void onNewConnection();
    void onTextMessageReceived(const QString& msg);
    void onClientDisconnected();
    void onHeartbeatTick();

private:
    void disconnectClient();

    quint16           m_port        = 8769;
    QWebSocketServer* m_server      = nullptr;
    QWebSocket*       m_client      = nullptr;
    QTimer            m_heartbeatTimer;
    qint64            m_lastPongMs  = 0;
};
