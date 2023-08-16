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
    bool started = false;
    bool gameover = false;
    bool isChange = false;
    char c;
    renderwindow window;
    sf::Clock clock;
    sf::UdpSocket broadcastingSocket;
    sf::IpAddress broadcastAddress = sf::IpAddress::Broadcast;
    sf::UdpSocket dataSocket;
        
public:
    Server(renderwindow &w) : window(w)
    {
        serverIp = sf::IpAddress::getLocalAddress();
        playerIps.push_back(serverIp);
        if (broadcastingSocket.bind(0) != sf::Socket::Done)
        {
            cout << "Binding failure" << endl;
            return;
        }
        


        
    }
    void startgame(){
        started = true;
    }
    void initialize()
    {
        if (dataSocket.bind(5000) != sf::Socket::Done)
        {
            cerr << "Binding failure" << endl;
        }
    }
    json incomingThread()
    {   
        
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
            if (dataSocket.receive(buffer, sizeof(buffer)+1, received, senderIp, senderPort) == sf::Socket::Done)
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
    

    void broadcastingThread(vector<Player> players,bool st= false)
    {
        vector<string> playernames;
        for(Player &p: players)
    {
        playernames.push_back(p.getname());
    }
        json dataOut;
        dataOut["host"] = players[0].getname();
        dataOut["Ip"] = serverIp.toString();
        dataOut["started"] = st;
        dataOut["players"]= json(playernames);
        std::string jsonString;
        
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
    void broadcastingStart(vector<Player> players,bool st= false)
    {
        vector<string> playernames;
        for(Player &p: players)
    {
        playernames.push_back(p.getname());
    }
        json dataOut;
        dataOut["host"] = players[0].getname();
        dataOut["Ip"] = serverIp.toString();
        dataOut["started"] = st;
        dataOut["players"]= json(playernames);
        std::string jsonString;
        
        broadcastingSocket.setBlocking(false);
        jsonString = dataOut.to_string();
        if (broadcastingSocket.send(jsonString.c_str(), jsonString.size() + 1, broadcastAddress, 15000) != sf::Socket::Done)
            {
                cout << "error here" << endl;
                return;
            }
        
    }

        void sendData(Player &p)
        {
            json dataOut;
            dataOut["id"] = p.getid();
            dataOut["x"] = p.getframe().x;
            dataOut["y"] = p.getframe().y;
            string data = dataOut.to_string();
            if(broadcastingSocket.send(data.c_str(),data.size()+1,broadcastAddress,15000) !=sf::Socket::Done)
            {
                cout<<"error";
            }
        }
}
;