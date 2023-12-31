#include "client.hpp"
using namespace std;
using namespace jsoncons;
    Client::Client(renderwindow &w): window(w)
    {
    }
    void Client::initialize()
    {
        if(receivingSocket.bind(15000)!=sf::Socket::Done){
            cout<<"failure binding receiving socket";
        }
        if(dataSocket.bind(8000)!=sf::Socket::Done){
            cout<<"failure binding data socket";
        }
    }
    vector<Player> Client::receivingThread(bool &gs)
    {
        vector<Player> receivedPlayers;
        receivingSocket.setBlocking(false);
        if(receivingSocket.receive(buffer, sizeof(buffer)+1, received, hostIp, senderPort)==sf::Socket::Done)
            {
    
               json receivedJson = json::parse(buffer);
                std::vector<Player> players;
                vector <string> playersArray = receivedJson["players"].as<vector<string>>();
                gs = receivedJson["started"].as_bool();
                for (size_t i = 0; i < playersArray.size(); ++i)
                {
                    string playerName = playersArray[i];
                    Player player(playerName,i);
                    receivedPlayers.push_back(player);
                }
                return receivedPlayers;
            }
            gs = false;
            return receivedPlayers;
    }
    bool Client::scanningThread()
    {
        receivingSocket.setBlocking(false);
        if(!found)
        {

            if(receivingSocket.receive(buffer, sizeof(buffer)+1, received, hostIp, senderPort)==sf::Socket::Done)
            {
    
                recievedJson = json::parse(buffer);

                string host = recievedJson["host"].as<std::string>();
                cout<<"Found "<<host<<"'s game. Join?"<<endl;
                show = "Found " + host + "'s game";
                found = true;
                cout<<hostIp<<endl;
            }
        }
        
        window.rendertext(show,position(300,200));   
        return found;         
    }
void Client::sendconfirmation(string n)

    {
            //dataSocket.setBlocking(false);
            serverIp = hostIp;

            json join;
            join["name"]= n;
            jsonString = join.to_string();
            sf::Socket::Status sendStatus = dataSocket.send(jsonString.c_str(), jsonString.size()+1, hostIp, 10000);
            if (sendStatus != sf::Socket::Done) {
                if(sendStatus == sf::Socket::Error)
            cout << "Socket error: " << sendStatus << endl;
            }
            else
            {
                cout<<"confirmation sent"<<endl;
            }
        }
    json Client::receiveInitialData()
    {
        json receivedJson;
        receivedJson["found"] = false; 
        receivingSocket.setBlocking(false);
        if(receivingSocket.receive(buffer,sizeof(buffer)+1,received,hostIp,senderPort)== sf::Socket::Done)
        {   
            receivedJson = json::parse(buffer);
            receivedJson["found"] = true;
        }
        return receivedJson;
    }
    json Client::receiveData()
    {
        json receivedJson;
        receivedJson["found"] = false; 
        receivingSocket.setBlocking(false);
        if(receivingSocket.receive(buffer,sizeof(buffer)+1,received,hostIp,senderPort)== sf::Socket::Done)
        {   
            receivedJson = json::parse(buffer);
            receivedJson["found"] = true;
        }
        return receivedJson;
    }
    void Client::sendData(Player &p,int dir,bool isfiring,float theta,bool over)
        {
            json dataOut;
            dataOut["id"] = p.getid();
            dataOut["x"] = p.getframe().x;
            dataOut["y"] = p.getframe().y;
            dataOut["dir"] = dir;
            dataOut["isfiring"] = isfiring;
            dataOut["theta"] = theta;
            dataOut["flying"] = p.isFlying;
            dataOut["respawning"] = p.respawning;
            dataOut["died"] = p.died;
            dataOut["gameover"] = over;

            string data = dataOut.to_string();
            if(dataSocket.send(data.c_str(),data.size()+1,serverIp,10000) !=sf::Socket::Done)
            {
                cout<<"error";
            }
        }

