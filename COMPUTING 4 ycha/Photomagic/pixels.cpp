/***********************************************************************************/
/* pixels.cpp		                                                           */
/* Yoo Min Cha          							   */
/* Linear Feedback Shift Register                                                  */
/* Professor Martin								   */
/* 06 March 2014 					        		   */	
/***********************************************************************************/

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include "LFSR.hpp"

using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{
    // input arguments
  if(argc != 5)
  {
    cerr << "Need source image filename, output image filename, and LFSR seed and tap position.\n";
    return EXIT_FAILURE + 4;
  }
  string sourceFile = argv[1];
  string outputFile = argv[2];
  string seed = argv[3];
  unsigned int tap = atoi(argv[4]);
   
   // load image from file
  Image image;
  if (!image.loadFromFile(sourceFile))
    return EXIT_FAILURE + 6;
  Image image2;
  if (!image2.loadFromFile(sourceFile))
    return EXIT_FAILURE + 7;

   // instantiate a new lfsr object
  LFSR lfsr(seed, tap);
  
   // p is a pixel
  Color p;

  Vector2u size = image.getSize();
  RenderWindow window(VideoMode(size.x *2, size.y), "Image Before/After");
  
    // tranform image using lfsr method generate
  for (int x=0; x < size.x; x++) {
    for (int y= 0; y < size.y; y++) {
      p = image.getPixel(x, y);
      p.r ^= lfsr.generate(tap);
      p.g ^= lfsr.generate(tap);
      p.b ^= lfsr.generate(tap);
      image.setPixel(x, y, p);
    }
  }

  Texture texture;
  texture.loadFromImage(image);
  
  Texture texture2;
  texture2.loadFromImage(image2);

  Sprite sprite;
  sprite.setTexture(texture);
  sprite.setPosition(size.x, 0);
  
  Sprite sprite2;
  sprite2.setTexture(texture2);

  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
        window.close();
    }

    window.clear(Color::White);
    window.draw(sprite);
    window.draw(sprite2);
    window.display();
  }

   //   write to new file
  if (!image.saveToFile(outputFile))
    return EXIT_FAILURE + 8;

  return EXIT_SUCCESS;
}
