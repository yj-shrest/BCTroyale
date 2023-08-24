#include "server.hpp"

    Server::Server(renderwindow &w) : window(w)
    {
        serverIp = sf::IpAddress::getLocalAddress();
        playerIps.push_back(serverIp);
        if (broadcastingSocket.bind(0) != sf::Socket::Done)
        {
            cout << "Binding failure" << endl;
            return;
        }
        


        
    }
    void Server::initialize()
    {
        if (dataSocket.bind(10000) != sf::Socket::Done)
        {
            cerr << "Binding failure" << endl;
        }
    }
    json Server::incomingThread()
    {   
        json dataIn;
        dataIn["found"] = false;
        std::string playerName;
        dataSocket.setBlocking(false);
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
                 }
            }
            return dataIn;
        }
    json Server::receiveData()
    {   
        char buffer[1024];
        std::size_t received;
        unsigned short senderPort;
        json receivedJson;
        receivedJson["found"] = false; 
        dataSocket.setBlocking(false);
        if(dataSocket.receive(buffer,sizeof(buffer)+1,received,senderIp,senderPort)== sf::Socket::Done)
        {   
            receivedJson = json::parse(buffer);
            receivedJson["found"] = true;
            if(broadcastingSocket.send(buffer, sizeof(buffer)+1, broadcastAddress, 15000)!=sf::Socket::Done)
            {
                cout<<"error forwarding data";
            }
        }
        return receivedJson;
    }


    void Server::broadcastingThread(vector<Player> players,bool st)
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
            clock.restart();
        }
        }
    void Server::broadcastingStart(vector<Player> players,bool st)
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

        void Server::sendInitialData(Player &p)
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
        void Server::sendData(Player &p,int dir,bool isfiring,float theta,bool over)
        {
            json dataOut;
            dataOut["id"] = p.getid();
            dataOut["x"] = p.getframe().x;
            dataOut["y"] = p.getframe().y;
            dataOut["dir"] = dir;
            dataOut["isfiring"] = isfiring;
            dataOut["flying"] = p.isFlying;
            dataOut["theta"] = theta;
            dataOut["respawning"] = p.respawning;
            dataOut["died"] = p.died;
            dataOut["gameover"] = over;

            string data = dataOut.to_string();
            if(broadcastingSocket.send(data.c_str(),data.size()+1,broadcastAddress,15000) !=sf::Socket::Done)
            {
                cout<<"error";
            }
        }