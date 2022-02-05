1 // Student: Phong Hong Vo
2 #include <SFML/Graphics.hpp>
3 
4 int main()
5 {
6     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
7     sf::CircleShape shape(100.f);
8     shape.setFillColor(sf::Color::Green);
9 	
10	// load the sprite
11	sf::Texture texture;
12	if (!texture.loadFromFile("sprite.png")) 
13		return EXIT_FAILURE;
14	sf::Sprite sprite(texture);
15	sprite.setTexture(texture);
16	sprite.setTextureRect(sf::IntRect(1, 1, 32, 32));
17	
18	// sprite's move
19	sprite.move(sf::Vector2f(80,80));
20	
21	// sprite's rotation
22	sprite.setRotation(0);
23
24    while (window.isOpen())
25    {
26        sf::Event event;
27        while (window.pollEvent(event))
28        {
29            if (event.type == sf::Event::Closed)
30                window.close();
31        }
32		
33		// detect arrow key is pressed
34		// right arrow key is pressed
35		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
36		{
37			sprite.setRotation(0);
38			sprite.move(1, 0);
39			sprite.setTextureRect(sf::IntRect(1, 96, 32, 32));
40		}
41		// left arrow key is pressed
42		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
43		{
44			sprite.setRotation(0);
45			sprite.move(-1,0);
46			sprite.setTextureRect(sf::IntRect(1, 64, 32, 32));
47		}
48		// up arrow key is pressed
49		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
50		{
51			sprite.setRotation(0);
52			sprite.move(0,-1);
53			sprite.setTextureRect(sf::IntRect(1, 32, 32, 32));
54		}
55		// down arrow key is pressed
56		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
57		{
58			sprite.setRotation(0);
59			sprite.move(0,1);
60			sprite.setTextureRect(sf::IntRect(1, 1, 32, 32));
61		}
62		
63		// set framerate
64		window.setFramerateLimit(60);
65
66        window.clear();
67        window.draw(shape);
68		// draw the sprite
69		window.draw(sprite);
70        window.display();
71    } // end while
72
73    return 0;
74}