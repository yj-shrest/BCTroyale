#pragma once

#include <SFML/Network.hpp>
#include <thread>
#include <jsoncons/json.hpp>
#include "windowrenderer.hpp"
#include "player.hpp"

using jsoncons::json;
using namespace std;

class Server
{
private:
    sf::IpAddress serverIp;
    vector<sf::IpAddress> playerIps;
    bool started = false;
    bool gameover = false;
    bool isChange = false;
    char c;
    renderwindow window;
    sf::Clock clock;
    sf::UdpSocket broadcastingSocket;
    sf::IpAddress broadcastAddress = sf::IpAddress::Broadcast;
    sf::UdpSocket dataSocket;
    char buffer[1024];
    std::size_t received;
    unsigned short senderPort;
    sf::IpAddress senderIp;

public:
    Server(renderwindow &w);

    void startgame();
    void initialize();
    json incomingThread();
    json receiveData();
    void broadcastingThread(vector<Player> players, bool st = false);
    void broadcastingStart(vector<Player> players, bool st = false);
    void sendInitialData(Player &p);
    void sendData(Player &p, int dir, bool isfiring, float theta = 0, bool over = false);
};
