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
    sf::IpAddress hostIp, senderIp;
    unsigned short senderPort;
    json recievedJson;
    string jsonString;
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
            }
        }
        
        window.rendertext(show,position(300,200));   
        return found;         
    }
    void sendconfirmation(string n)
    {
            serverIp = hostIp;
            json join;
            join["name"]= n;
            jsonString = join.to_string();
            if(dataSocket.send(jsonString.c_str(), jsonString.size()+1, hostIp, 10000)!= sf::Socket::Done)
            {
            cout<<"err"<<endl;
            }
            else
            {
                cout<<"confirmation sent"<<endl;
            }
    }
};
