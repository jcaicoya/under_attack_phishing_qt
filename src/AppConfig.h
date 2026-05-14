#pragma once

struct AppConfig {
    int wsPort              = 8769;
    int udpBeaconPort       = 8770;
    int heartbeatIntervalMs = 5000;
    int pongTimeoutMs       = 10000;
    int beaconIntervalMs    = 2000;

    static AppConfig& instance();
};
