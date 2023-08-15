#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <jsoncons/json.hpp>

using jsoncons::json;
using namespace std;

class Server
{
private:
    sf::IpAddress serverIp;
    vector<sf::IpAddress> playerIps;
    json middleground;
    bool started = false;
    bool gameover = false;
    bool isChange = false;
    char c;
    renderwindow window;
    sf::Clock clock;

public:
    Server(renderwindow &w) : window(w)
    {
        serverIp = sf::IpAddress::getLocalAddress();
        playerIps.push_back(serverIp);
    }
    void startgame(){
        started = true;
    }
    json incomingThread()
    {   
        sf::UdpSocket dataSocket;
    
        unsigned short DATA_SOCKET = 10000;

        if (dataSocket.bind(DATA_SOCKET) != sf::Socket::Done)
        {
            cout << "Binding failure" << endl;
            return json();
        }
        // Initializing data in
        char buffer[1024];
        std::size_t received;
        unsigned short senderPort;
        sf::IpAddress senderIp;
        json dataIn;
        dataIn["found"] = false;
        std::string playerName;
        dataSocket.setBlocking(false);
        // cerr<<"gotit";
            if (dataSocket.receive(buffer, sizeof(buffer), received, senderIp, senderPort) == sf::Socket::Done)
            {
                dataIn = json::parse(buffer);
                dataIn["found"] = true;
                playerName = dataIn["name"].as<std::string>();
                cerr << playerName << endl;

                if (std::find(playerIps.begin(), playerIps.end(), senderIp) == playerIps.end() || 1)
                {
                    playerIps.push_back(senderIp);
                    cerr << "Added player IP: " << senderIp << " to the vector." << endl;
                    isChange = true;
                }
            }
            return dataIn;
        }
    

    void broadcastingThread()
    {
        sf::UdpSocket broadcastingSocket;
        
        if (broadcastingSocket.bind(0) != sf::Socket::Done)
        {
            cout << "Binding failure" << endl;
            return;
        }

        json dataOut;
        dataOut["host"] = "Random";
        dataOut["Ip"] = serverIp.toString();
        dataOut["started"] = false;
        std::string jsonString;
        sf::IpAddress broadcastAddress = sf::IpAddress::Broadcast;
        broadcastingSocket.setBlocking(false);
        jsonString = dataOut.to_string();
        if (clock.getElapsedTime().asMilliseconds() >= 5000) // Broadcast every 5 second
        {
        if (broadcastingSocket.send(jsonString.c_str(), jsonString.size() + 1, broadcastAddress, 15000) != sf::Socket::Done)
            {
                cout << "error here" << endl;
                return;
            }

        cout << "Broadcasted. PLayers:" << endl;
            for (const auto &playerIp : playerIps)
            {
                cout << playerIp << endl;
            }
            clock.restart();
        }
        }
}
;
