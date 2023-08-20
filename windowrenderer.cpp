
#include"windowrenderer.hpp"
using namespace std;

    renderwindow::renderwindow(const char* t, int w, int h)
    {
        char* title = const_cast<char*>(t);
        
        window = sdl.createWindow(title,SDL::WindowPosUndefined,SDL::WindowPosUndefined,w,h,SDL::WindowAllowHighDPI);
        renderer = sdl.createRenderer(window,-1, SDL::RendererAccelerated && SDL::RendererPresentVSync);
        playertexture = loadTexture("assets/char.png");
        playerflyingtexture =loadTexture("assets/charnitro.png");
        playerwtexture = loadTexture("assets/charw.png");
        weapontexture = loadTexture("assets/weapon.png");
        weaponfiretexture = loadTexture("assets/weaponfire.png");
        healthBarRectTexture = loadTexture("assets/healthbarrect.png");
        healthBarTexture = loadTexture("assets/healthbar.png");
    }
    void renderwindow::cleanup()
    {
        sdl.destroyWindow(window);
    }

    SDL::Texture* renderwindow::loadTexture(const char* filepath)
    {
        SDL::Texture *temp =NULL;
        char* fp = const_cast<char*> (filepath);
        temp = sdl.loadTexture(renderer,fp);
        return temp;
    }
    void renderwindow::clear()
    {
        sdl.renderClear(renderer);
    }
    void renderwindow::render(entity &ent,position camerapos, int direction)
    {
        SDL::Rect dst;
        dst.x=ent.getframe().x - camerapos.x;
        dst.y=ent.getframe().y - camerapos.y;
        dst.w= ent.getframe().w;
        dst.h = ent.getframe().h;
        if (direction ==1)
        {
        sdl.renderCopy(renderer,ent.getTxt(),NULL,&dst);
        }
        else{
            sdl.renderCopyEx(renderer,ent.getTxt(), NULL, &dst, 0, NULL, SDL::FlipHorizontal);
        }
    }
    void renderwindow::renderplayer(Player &p,position camerapos,int direction)
    {
        if(!p.respawning){

        SDL::Rect dst;
        SDL::Texture *t;
        dst.x=p.getframe().x - camerapos.x;
        dst.y=p.getframe().y - camerapos.y;
        dst.w= p.getframe().w;
        dst.h = p.getframe().h;
        t = playertexture;
        Uint32 currentTicks = sdl.getTicks();
        Uint32 animationDelay = 150; // Adjust the delay to control the animation speed (milliseconds)
    
    if (p.isMovingSideways && currentTicks - p.lastAnimationUpdateTime > animationDelay)
    {
        if (t == playertexture)
        {
            t = playerwtexture;
        }
        else
        {
             
            t = playertexture;
        }
        p.lastAnimationUpdateTime = currentTicks;
    }
    if(p.isFlying || p.flying)
    {
        dst.h +=10;
        t = playerflyingtexture;
    }
    if (direction ==1)
    {
        sdl.renderCopy(renderer,t,NULL,&dst);
    }
    else{
            sdl.renderCopyEx(renderer,t, NULL, &dst, 0, NULL, SDL::FlipHorizontal);
    }
    //Rendering the weapon
    SDL::Rect dst2;
    dst2.x = dst.x+15;
    dst2.y = dst.y+55;
    dst2.w = p.getweaponsize().x;
    dst2.h = p.getweaponsize().y;
    double angleDegrees = p.theta * (180.0 / M_PI);
    SDL::Texture * wt;
    if(p.firing) 
    {
        wt = weaponfiretexture;
        dst2.w+=20;
    }
    else wt = weapontexture;
    SDL::Point center = { 50 / 2, dst2.h / 2 };
    if (direction ==-1)
    sdl.renderCopyEx(renderer, wt, NULL, &dst2, angleDegrees, &center, SDL::FlipVertical);
    else
    sdl.renderCopyEx(renderer, wt, NULL, &dst2, angleDegrees, &center, SDL::NoFlip);
    ///rendering the name
    TTF_Font* font = TTF_OpenFont("assets/RichuMastRegular.ttf", 40);
    string textInput =p.getname();
    SDL::Color textColor = { 27, 20, 100, 100 };
    SDL::Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
    SDL::Texture* textTexture = sdl.createTextureFromSurface(renderer, textSurface);
    SDL::Rect dst3;
    dst3.x = dst.x - textInput.length()*10+40;
    dst3.y = dst.y - 50;
    dst3.w = textInput.length()*20;
    dst3.h = 40;

    sdl.renderCopy(renderer, textTexture, NULL, &dst3);
    }

    }
    void renderwindow::render(std::vector<entity>& entities,position camerapos) {
    SDL::Rect dst;
    for (entity& e : entities) {
        dst.x = e.getframe().x - camerapos.x;
        dst.y = e.getframe().y - camerapos.y;
        dst.w = e.getframe().w;
        dst.h = e.getframe().h;
        sdl.renderCopy(renderer, e.getTxt(),NULL, &dst);
    }

    }
    void renderwindow::render(std::vector<mob>& entities,position camerapos) {
    SDL::Rect dst;
    SDL::Rect Rdst;
    SDL::Rect hpdst;
    for (mob& m : entities) {
        dst.x = m.getframe().x - camerapos.x;
        dst.y = m.getframe().y - camerapos.y;
        dst.w = m.getframe().w;
        dst.h = m.getframe().h;
        Rdst.x = m.getbigrect().x-camerapos.x; 
        Rdst.y = m.getbigrect().y-camerapos.y;
        Rdst.w = m.getbigrect().w;
        Rdst.h = m.getbigrect().h;
        hpdst.x = m.getsmallrect().x-camerapos.x; 
        hpdst.y = m.getsmallrect().y-camerapos.y;
        hpdst.w = m.getsmallrect().w;
        hpdst.h = m.getsmallrect().h;
        
        sdl.renderCopy(renderer, m.getTxt(),NULL, &dst);
        sdl.renderCopy(renderer, m.getrecttxt(),NULL, &Rdst);
        sdl.renderCopy(renderer, m.gethptxt(),NULL, &hpdst);
        
    }
    }
    void renderwindow::render(std::vector<Bullet>& bull,position cpos) {
    SDL::Rect dst;
    for (Bullet& b : bull) {
        dst.x = b.getframe().x - cpos.x;
        dst.y = b.getframe().y  - cpos.y;
        dst.w = b.getframe().w;
        dst.h = b.getframe().h;
        double angleDegrees = b.gettheta() * (180.0 / M_PI);
        SDL::Point center = { dst.w / 2, dst.h / 2 };
        sdl.renderCopyEx(renderer, b.getTxt(), NULL, &dst, angleDegrees, &center, SDL::NoFlip);
    }
    }

    void renderwindow::renderlives(Player &p, entity &h)
    {
        int l = p.getlives();
        SDL::Rect dst = h.getframe();

        for(int i = 0;i<l;i++)
        {
            dst.x += 50;
            sdl.renderCopy(renderer,h.getTxt(),NULL,&dst);
        }
    }

    void renderwindow::rendername(string name)
    {
        TTF_Font* font = TTF_OpenFont("assets/RichuMastRegular.ttf", 40);
        string textInput =name;
        SDL::Color textColor = { 27, 20, 100, 100 };
        SDL::Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
        SDL::Texture* textTexture = sdl.createTextureFromSurface(renderer, textSurface);

        SDL::Rect dst;
        dst.x = 580- textInput.length()*10;
        dst.y = 305;
        dst.w = textInput.length()*20;
        dst.h = 40;

        sdl.renderCopy(renderer, textTexture, NULL, &dst);
    }

    void renderwindow::inputname(string text)
    {
        TTF_Font* font = TTF_OpenFont("assets/Jost.ttf", 60);
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        string textInput =text;
        SDL::Color textColor = { 27, 20, 100, 150 };
        SDL::Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
        SDL::Texture* textTexture = sdl.createTextureFromSurface(renderer, textSurface);

        SDL::Rect dst;
        dst.x = 575- textInput.length()*20;
        dst.y = 380;
        dst.w = textInput.length()*40;
        dst.h = 60;

        sdl.renderCopy(renderer, textTexture, NULL, &dst);
    }
    void renderwindow::rendertext(string text, position p)
    {
        TTF_Font* font = TTF_OpenFont("assets/Jost.ttf", 60);
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        string textInput =text;
        SDL::Color textColor = { 27, 20, 100, 255 };
        SDL::Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
        SDL::Texture* textTexture = sdl.createTextureFromSurface(renderer, textSurface);

        SDL::Rect dst;
        dst.x = p.x;
        dst.y = p.y;
        dst.w = textInput.length()*25;
        dst.h = 45;

        sdl.renderCopy(renderer, textTexture, NULL, &dst);
    }
    void renderwindow::display()
    {
        sdl.renderPresent(renderer);
    }

