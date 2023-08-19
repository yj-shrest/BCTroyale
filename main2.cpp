#include<iostream>
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "TEXT", sf::Style::Default);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
    sf::Font font;
    try
    {
        if (!font.loadFromFile("assets/RichuMastRegular.ttf"))
        {
            throw - 1;
        }
    }
        catch(int)
        {
            std::cout << "error couldn't load file" <<std::endl;
            exit (1);
        }
    

    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Hello world");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);



    // inside the main loop, between window.clear() and window.display()
    window.draw(text);
    window.display();
    }
    return 0;
}