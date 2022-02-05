//Name: Dangnhi Ngoc Ngo
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("sprite.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(10, 130, 40, 68));
    
    //Make the sprite move
    sprite.move(sf::Vector2f(100, 80));	
 
    //Make the sprite rotate 45 degrees
    sprite.setRotation(45);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

	// Right key is pressed: move the sprite
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{ 
        sprite.setRotation(0);
        sprite.move(1, 0);
	    sprite.setTextureRect(sf::IntRect(10, 190, 40, 70));	    
	}
	// Left key is pressed: move the sprite
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        sprite.setRotation(0);
        sprite.move(-1, 0);
   	    sprite.setTextureRect(sf::IntRect(10, 67, 40, 68));
	}
	// Up key is pressed: move the sprite
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{ 
        sprite.setRotation(0);
        sprite.move(0, -1);
	    sprite.setTextureRect(sf::IntRect(10, 8, 40, 68));	    
	}
	// Down key is pressed: move the sprite
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{ 
        sprite.setRotation(0);
        sprite.move(0, 1);
	    sprite.setTextureRect(sf::IntRect(10, 130, 40, 68)); 
	}
		

        //Control the frame rate
        window.setFramerateLimit(60);

        window.clear();
        window.draw(shape);
        //Draw the sprite
        window.draw(sprite);
        window.display();
    }

    return 0;
}
