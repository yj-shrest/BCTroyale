#include "player.hpp"

    Player::Player(string n,int i)
    {   
        name = n;
        health =100;
        nitro =100;
        weaponwidth = 50;
        weaponheight = 20;
        id =i;
        lives =3;
        flying = false;
        respawning = false;
        died = false;
        firing = false;
    }

    Player::Player():entity(getrandomx(),700,75,100)
    {   
        health =100;
        nitro =100;
        weaponwidth = 50;
        weaponheight = 20;
        lives =3;
        flying = false;
        respawning = false;
        died = false;
        firing = false;
    }
    void Player::setvalues()
    {
        int ran = getrandomx();
        cout<<ran<<endl;
        setval(ran,700);
    }
    void Player::setvalues(int x, int y)
    {
        setval(x,y);
    }
    string Player::getname()
    {
        return name;
    }
    int Player::getid()
    {
        return id;
    }
    int Player::getrandomx()
    {
        // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister engine

    // Define the range of random values
    int minVal = 100;
    int maxVal = 2400;

    // Create a distribution to generate random integers within the specified range
    std::uniform_int_distribution<int> dis(minVal, maxVal);

    // Generate and print a random integer
    int randomNumber = dis(gen);
    return randomNumber;
    }
    position Player::getpos()
    {
        return position(getframe().x,getframe().y);
    }
    position Player::getweaponsize()
    {
        return position(weaponwidth,weaponheight);
    }
    int Player::getlives()
    {
        return lives;
    }
    void Player::refill()
    {
        lives =3;
        health =100;
    }

    void Player::movedown()
    {
        getframe().y+=1;
    }
    void Player::moveSideways(int direction) {
        movementDirection = direction;
        isMovingSideways = true;
    }
    
    void Player::stopMovingSideways() {
        isMovingSideways = false;
    }

    void Player::jump() {
       
        isFlying = true;

    }
    int Player::gethealth()
    {
        return health;
    }
    float Player::getnitro()
    {
        return nitro;
    }
    void Player::stopFlying()
    {
        isFlying = false;
    }

    void Player::damage()
    {
    
        health -=2;
    }
    void Player::nodamage()
    {
        if(health<90) health += 0.2f;    
    }



    bool Player::isOnGround(std::vector<entity>& entities)
    {
        for (entity& e : entities)
        {
            if(e.getframe().y<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x+5<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w-5) )
                {
                return true;
                }
            }
        }
        
        return false;
    }
    std::string Player::sidecollision(std::vector<entity>& entities)
    {
        for (entity& e : entities)
        {
            if(e.getframe().y+5<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w) )
                {
                    if(getframe().x<e.getframe().x )
                    {
                        return "leftside";
                    }
                    if(getframe().x+getframe().w >e.getframe().x+e.getframe().w)
                    {
                        return "rightside";
                    }
                }
            }
        }
        return "nth";
    }
    bool Player::upcollide(std::vector<entity>& entities)
    {
        for (entity& e : entities)
        {
            if(e.getframe().y+5<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x+30<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w-30) )
                {
                    if(-getframe().y<=e.getframe().y +e.getframe().h )
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void Player::updatePosition(int x, int y,int d,float t,bool fi,bool fly,bool res,bool dead)
    {
        getframe().x = x;
        getframe().y = y;
        dir = d;
        theta =t;
        firing = fi;
        flying = fly;
        respawning = res;
        died = dead;
    }
    void Player::update(std::vector<entity>& entities) {
        
        if(health<0 && lives >0)
        {
            getframe().y = 500;
            getframe().x = getrandomx();
            lives -=1;
            if(lives==0)
            {
                died = true;
            }
            health = 100;
            respawning = true;
        }
        if(upcollide(entities))
        {
            isFlying = false;
        }
        if(nitro<=0)
        {
            isFlying = false;
        }
        if(isFlying)
        {
            getframe().y -= getspeed();
            nitro-=0.5f;
        }
        if(isOnGround(entities))
        {   
        if(nitro<100)
        {
            nitro += 0.5f;
        }
               
        }
        if(getframe().y>1500)
        {  
            
            getframe().y = 500;
            getframe().x = getrandomx();
            nitro = 100;
            lives -=1;
            if(lives ==0) died = true;
            respawning = true;

        }
        if(!isFlying && !isOnGround(entities))
        {
            getframe().y+= getspeed();
        }
        if(!isFlying && upcollide(entities))
        {
            getframe() .y += getspeed();
        }
        if (isMovingSideways)
        {
            if(movementDirection ==1 and (sidecollision(entities)!="leftside"))
            {
            getframe().x += movementDirection * getspeed();
            }
            if(movementDirection ==-1 and (sidecollision(entities)!="rightside"))
            {
            getframe().x += movementDirection * getspeed();
            }
        }
    }
bool Player::hit(Bullet &b)
    {
        
    if(b.getframe().y<getframe().y+getframe().h && b.getframe().y+b.getframe().h>getframe().y)
        {

            if ( b.getframe().x+5<getframe().x+getframe().w && getframe().x<(b.getframe().x+b.getframe().w-5) )
                {
                return true;
                }
        }
        
        return false;
    }
    void entity::updateHealth(Player &p)
    {
        currentframe.w = p.gethealth()*2;
    }
    void entity::updatenitro(Player &p)
    {
        currentframe.w = p.getnitro()*2;
    }