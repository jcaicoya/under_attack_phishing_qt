#include "WebSocketServer.h"
#include "AppConfig.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

WebSocketServer::WebSocketServer(QObject* parent)
    : QObject(parent)
    , m_server(new QWebSocketServer("under_attack_phishing_qt", QWebSocketServer::NonSecureMode, this))
{
    m_port = static_cast<quint16>(AppConfig::instance().wsPort);
    if (m_server->listen(QHostAddress::Any, m_port)) {
        qDebug() << "[WS] Server listening on port" << m_port;
        connect(m_server, &QWebSocketServer::newConnection,
                this, &WebSocketServer::onNewConnection);
    } else {
        qWarning() << "[WS] Failed to start server:" << m_server->errorString();
    }

    connect(&m_heartbeatTimer, &QTimer::timeout, this, &WebSocketServer::onHeartbeatTick);
}

WebSocketServer::~WebSocketServer() {
    disconnectClient();
    m_server->close();
}

void WebSocketServer::sendText(const QString& msg) {
    if (m_client) m_client->sendTextMessage(msg);
}

void WebSocketServer::onNewConnection() {
    QWebSocket* pending = m_server->nextPendingConnection();
    if (!pending) return;

    qDebug() << "[WS] Incoming connection from" << pending->peerAddress().toString();

    if (m_client) {
        qDebug() << "[WS] Replacing stale client";
        disconnectClient();
        emit clientConnected(false);
    }

    m_client = pending;
    connect(m_client, &QWebSocket::textMessageReceived,
            this, &WebSocketServer::onTextMessageReceived);
    connect(m_client, &QWebSocket::disconnected,
            this, &WebSocketServer::onClientDisconnected);

    m_lastPongMs = QDateTime::currentMSecsSinceEpoch();
    m_heartbeatTimer.start(AppConfig::instance().heartbeatIntervalMs);
    qDebug() << "[WS] Client accepted";
    emit clientConnected(true);
}

void WebSocketServer::onTextMessageReceived(const QString& msg) {
    const QJsonObject obj = QJsonDocument::fromJson(msg.toUtf8()).object();
    const QString type = obj.value("type").toString();

    if (type == "pong") {
        m_lastPongMs = QDateTime::currentMSecsSinceEpoch();
        return;
    }
    if (type == "link_tapped") {
        qDebug() << "[WS] Link tapped on Android";
        emit linkTapped();
        return;
    }
    qDebug() << "[WS] Unknown message:" << msg;
}

void WebSocketServer::onClientDisconnected() {
    qDebug() << "[WS] Client disconnected";
    disconnectClient();
    emit clientConnected(false);
}

void WebSocketServer::onHeartbeatTick() {
    if (!m_client) return;

    const qint64 silent = QDateTime::currentMSecsSinceEpoch() - m_lastPongMs;
    if (silent > AppConfig::instance().pongTimeoutMs) {
        qDebug() << "[WS] Pong timeout, disconnecting client";
        disconnectClient();
        emit clientConnected(false);
        return;
    }

    m_client->sendTextMessage(R"({"type":"ping"})");
}

void WebSocketServer::disconnectClient() {
    if (!m_client) return;
    m_heartbeatTimer.stop();
    m_client->disconnect(this);
    m_client->close();
    m_client->deleteLater();
    m_client = nullptr;
}
