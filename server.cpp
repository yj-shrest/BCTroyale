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
    

    void broadcastingThread(vector<Player> players)
    {
        vector<string> playernames;
        for(Player &p: players)
    {
        playernames.push_back(p.getname());
    }
        json dataOut;
        dataOut["host"] = "Random";
        dataOut["Ip"] = serverIp.toString();
        dataOut["started"] = false;
        dataOut["confirm"] = false;
        json playersArray = json::array(); // Create a JSON array

        for (Player &p : players)
        {
            json playerJson;
            playerJson["name"] = p.getname();
            // Add more attributes as needed
            playersArray.push_back(playerJson);
        }
        dataOut["players"]= playersArray;
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
}
;