#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <jsoncons/json.hpp>

using jsoncons::json;
using namespace std;

class Client
{
private:
    bool started = false;
    bool gameover = false;
    bool joined = false;
    bool found = false;
    json middleground;
    sf::IpAddress serverIp;
    sf::UdpSocket receivingSocket;
    sf::UdpSocket dataSocket;
    vector<string> playerNames;
    renderwindow window;

    string show = "Searching for a Game";
    char buffer[1024];
    size_t received;
    sf::IpAddress hostIp, senderIp, dummyIP;
    unsigned short senderPort;
    json recievedJson;
    string jsonString;
    sf::Clock clock;
    sf::IpAddress broadcastAddress = sf::IpAddress::Broadcast;
public:
    Client(renderwindow &w): window(w)
    {
    }
    void initialize()
    {
        if(receivingSocket.bind(15000)!=sf::Socket::Done){
            cout<<"failure binding receiving socket";
        }
        if(dataSocket.bind(8000)!=sf::Socket::Done){
            cout<<"failure binding data socket";
        }
    }
    vector<Player> receivingThread()
    {
        vector<Player> receivedPlayers;
        receivingSocket.setBlocking(false);
        if(receivingSocket.receive(buffer, sizeof(buffer)+1, received, hostIp, senderPort)==sf::Socket::Done)
            {
    
               json receivedJson = json::parse(buffer);
                std::vector<Player> players;

                json playersArray = receivedJson["players"];

                for (size_t i = 0; i < playersArray.size(); ++i)
                {
                    json playerJson = playersArray[i];
                    string playerName = playerJson["name"].as<string>();
                    // Extract more attributes as needed
                    Player player(playerName);
                    receivedPlayers.push_back(player);
                }
                return receivedPlayers;
            }
            return receivedPlayers;
    }
    bool scanningThread()
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
void sendconfirmation(string n)

    {
            dataSocket.setBlocking(false);
            receivingSocket.setBlocking(false);
            serverIp = hostIp;
            sf::IpAddress IP = "192.168.1.108";
            sf::UdpSocket sendSocket;
            sendSocket.bind(6000);
            sendSocket.setBlocking(false);
            json join;
            join["name"]= n;
            jsonString = join.to_string();
            sf::Socket::Status sendStatus = sendSocket.send(jsonString.c_str(), jsonString.size()+1, hostIp, 5000);
            if (sendStatus != sf::Socket::Done) {
                if(sendStatus == sf::Socket::Error)
            cout << "Socket error: " << sendStatus << endl;
            }
            else
            {
                cout<<"confirmation sent"<<endl;
            }
        

        }
};
