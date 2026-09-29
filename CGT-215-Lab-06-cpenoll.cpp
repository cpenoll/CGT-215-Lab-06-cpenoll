// CGT-215-Lab-06-cpenoll.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {
	string background = "images1/backgrounds/winter.png";
	string foreground = "images1/characters/yoda.png";

	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}
	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	//these lines create an image & fills the image with the picture data from our texture above
	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();
	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();

	//two vector2u types with getSize functions
	Vector2u szb = backgroundImage.getSize();
	Vector2u szf = foregroundImage.getSize();

	Color greenColor = foregroundImage.getPixel(0, 0); //color class for the corner aka greenscreen part of the image (byte sized fields for rgb)


	for (int y = 0; y < szf.y; y++) { //row loop going thru each row of foreground image
		for (int x = 0; x < szf.x; x++) { //col loop going thru each column of foreground image
				Color example = foregroundImage.getPixel(x, y); //getting the color at the particular pixel

				int redDifference = abs(example.r - greenColor.r); //abs (absolute) makes the difference a positive number
				int greenDifference = abs(example.g - greenColor.g);
				int blueDifference = abs(example.b - greenColor.b);

				//this section checks whether a pixel is treated as a greenscreen color or not
				if (redDifference < 30 &&
					greenDifference < 25 &&
					blueDifference < 30) {

					//this is replacing the the foreground greenscreen pixels with the background pixels
					if (x < szb.x && y < szb.y) {
						foregroundImage.setPixel(
							x, y,
							backgroundImage.getPixel(x, y)
						);
					}
			}
		}
	}
	
	//showing the foreground image by default
	RenderWindow window(VideoMode(1024, 768), "Here's the output");
	Sprite sprite1;
	Texture tex1;
	tex1.loadFromImage(foregroundImage);
	sprite1.setTexture(tex1);
	window.clear();
	window.draw(sprite1);
	window.display();
	while (true);
}