#pragma once

#include "cybershow/common/CyberAppMode.h"

#include <QList>
#include <QMainWindow>

class QEvent;
class QGraphicsOpacityEffect;
class QLabel;
class QKeyEvent;
class QPropertyAnimation;
class QResizeEvent;
class QStackedWidget;

class BottomNavBar;
class ScreenPage;
class UdpBeacon;
class WebSocketServer;

class PhishingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhishingWindow(const cybershow::AppLaunchOptions& options, QWidget* parent = nullptr);
    ~PhishingWindow() override = default;

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    struct Screen {
        int number;
        QString id;
        QString navLabel;
        ScreenPage* page = nullptr;
    };

    void buildUi();
    ScreenPage* createPlaceholderPage(const QString& title, const QString& body);
    void wireNavigation();
    void goTo(int index);
    void goToAdjacent(int direction);
    bool handleRuntimeKeyPress(QKeyEvent* event);
    bool focusIsEditable(QWidget* focusWidget) const;

    void setupModeBadge();
    void updateModeBadgeGeometry();
    void updateModeBadgeText();
    void setModeBadgeVisible(bool visible);
    void setBottomNavVisible(bool visible);

    void onClientConnected(bool connected);
    void onLinkTapped();

    cybershow::AppLaunchOptions m_options;
    QList<Screen> m_screens;

    QStackedWidget* m_stack = nullptr;
    BottomNavBar* m_bottomNav = nullptr;

    WebSocketServer* m_wsServer = nullptr;
    UdpBeacon*       m_beacon   = nullptr;

    QLabel* m_modeBadge = nullptr;
    QGraphicsOpacityEffect* m_modeBadgeOpacity = nullptr;
    QPropertyAnimation* m_modeBadgeAnim = nullptr;
    bool m_modeBadgeVisible = false;
    bool m_bottomNavVisible = false;
};
