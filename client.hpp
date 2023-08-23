#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <jsoncons/json.hpp>
#include "player.hpp" // Include the appropriate header for Player class
#include "windowrenderer.hpp" // Include the appropriate header for renderwindow class

class Client {
private:
    sf::IpAddress serverIp,hostIp, senderIp, dummyIP;
    sf::UdpSocket receivingSocket,dataSocket;
    std::vector<std::string> playerNames;
    renderwindow window;

    std::string show = "Searching for a Game";
    char buffer[1024];
    size_t received;
    unsigned short senderPort;
    jsoncons::json recievedJson;
    std::string jsonString;
    bool found = false;
public:
    Client(renderwindow &w);
    void initialize();
    std::vector<Player> receivingThread(bool &gs);
    bool scanningThread();
    void sendconfirmation(std::string n);
    jsoncons::json receiveInitialData();
    jsoncons::json receiveData();
    void sendData(Player &p, int dir, bool isfiring, float theta = 0, bool over = false);
};
