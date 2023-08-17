#pragma once

#include<random>
class Bullet;
class Player: public entity
{   private:
    const int maxhealth=100; 
    int health;
    float nitro;
    int mouseX, mouseY;
    int weaponwidth, weaponheight;
    int lives = 3;
    int id;
    string name;
    public:
    float theta;
    int dir;
    bool firing;
    Uint32 lastAnimationUpdateTime = 0;

    Player(string n,int i)
    {   
        name = n;
        health =100;
        nitro =100;
        weaponwidth = 50;
        weaponheight = 20;
        id =i;
    }

    Player():entity(getrandomx(),700,75,100)
    {   
        health =100;
        nitro =100;
        weaponwidth = 50;
        weaponheight = 20;
    }
    void setvalues()
    {
        int ran = getrandomx();
        cout<<ran<<endl;
        setval(ran,700);
    }
    void setvalues(int x, int y)
    {
        setval(x,y);
    }
    string getname()
    {
        return name;
    }
    int getid()
    {
        return id;
    }
    int getrandomx()
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
    position getpos()
    {
        return position(getframe().x,getframe().y);
    }
    position getweaponsize()
    {
        return position(weaponwidth,weaponheight);
    }
    int getlives()
    {
        return lives;
    }
    void refill()
    {
        lives =3;
    }

    void movedown()
    {
        getframe().y+=1;
    }
    void moveSideways(int direction) {
        movementDirection = direction;
        isMovingSideways = true;
    }
    
    void stopMovingSideways() {
        isMovingSideways = false;
    }

    void jump() {
       
        isFlying = true;

    }
    int gethealth()
    {
        return health;
    }
    float getnitro()
    {
        return nitro;
    }
    void stopFlying()
    {
        isFlying = false;
    }


    bool hit(Bullet &b);
    void updateHealth()
    {
        health -=2;
    }



    bool isOnGround(std::vector<entity>& entities)
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
    std::string sidecollision(std::vector<entity>& entities)
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
    bool upcollide(std::vector<entity>& entities)
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
    void updatePosition(int x, int y,int d,float t,bool fi)
    {
        getframe().x = x;
        getframe().y = y;
        dir = d;
        theta =t;
        firing = fi;
    }
    void update(std::vector<entity>& entities) {
        
        

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
            //nitro-=0.5f;
        }
        if(isOnGround(entities))
        {   if(nitro<100)
        {
            nitro += 0.5f;
        }
        
        }
        if(getframe().y>1500)
        {  
            getframe().y = 500;
            nitro = 100;
            lives -=1;
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
};
void entity::updateHealth(Player &p)
{
    currentframe.w = p.gethealth()*2;
}
void entity::updatenitro(Player &p)
{
    currentframe.w = p.getnitro()*2;
}