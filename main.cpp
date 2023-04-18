#include "UserShape.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1600, 900);
	
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);
	
	// Render a canvas here, same size as the window, to draw on
	// Without this, if we just window display it will not keep the previous shape
	RenderTexture background;
	background.create(1600, 900);
	Sprite fill;
	fill.setTexture(background.getTexture(), true);
	fill.setColor(Color::White);
	
	// Create a Text object to display instructions
	Text messageText;

	// Choose a font, color, size, and instructions displayed
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf"); // This will be different on linux
	messageText.setFont(font);
	messageText.setString("Click in 3 places to start the Chaos Game:");
	messageText.setCharacterSize(35);
	messageText.setFillColor(Color::White);

	// Position the text at the top middle of the window
	FloatRect textRect2 = messageText.getLocalBounds();
	messageText.setOrigin(textRect2.left +
		textRect2.width / 2.0f,
		textRect2.top +
		textRect2.height / 2.0f);
	messageText.setPosition(1600 / 2.0f, 35);

	// Variable to store the amount of user inputted coordinates
	int score = 0;

	// Text window to show the user how many inputs they have done
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Points input = 0");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 20);		// Set this text to the top left of the screen

	// To check for furthur input, none needed after first 4 clicks
	bool acceptInput = true;

	// Vector to hold the user inputted coordinates
	vector<Vector2f> inputs;

	// Create an intial shape to modify with user input later on
	UserShape shape;

	while (window.isOpen())
	{

		//******************************
		// BEGIN TAKING INPUTS FROM USER
		//******************************

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				// Close window when the X is pressed or ESC key pressed
				window.close();
			}

			// Input user mouse clicks into a vector of Vector2f's
			if (event.type == Event::MouseButtonReleased )
			{
				if (acceptInput)
				{
					// Display where the mouse inputs occur on the console
					cout << "Input " << score + 1 << ": " << endl;
					cout << "X: " << event.mouseButton.x << endl;
					cout << "Y: " << event.mouseButton.y << endl;
					cout << endl;

					// Create a Vector2f to store the mouse click, then push into the vector to store it
					Vector2f temp;
					temp.x = event.mouseButton.x;
					temp.y = event.mouseButton.y;
					inputs.push_back(temp);
					score++;
				}
			}
			
		}

		// ***************************
		// BEGIN WINDOW DISPLAY UPDATE
		// ***************************
		
		window.clear();
	
		// Update the score text
		std::stringstream ss;
		ss << "Points input = " << score;
		scoreText.setString(ss.str());

		// Draw the score
		window.draw(scoreText);

		// If 4 click have happened, no more need for the 1st prompt
		if (score < 3)
		{		
			window.draw(messageText);
		}
		
		if (score == 3)			// On the 3rd click, change instructions
		{
			// Display new prompt
			messageText.setString("Click on a starting point to begin");
			window.draw(messageText);

			// Create an outline that the user created
			vector<Vector2f> userOutline;
			Vector2f blankPoint;
			userOutline = inputs;
			userOutline.push_back(blankPoint);
			UserShape triangleOutline(userOutline);
			shape = triangleOutline;

			// Draw the outline
			background.draw(shape.DrawFillshape()); // This will start displaying the fill sprite at the last inputted click
			shape.update();							// Then it will update here to a new coordinate
			window.draw(shape.DrawUserShape());		// This is the outline of the shape the user inputted
			background.display();					// Set the fill sprites inside of the original shape		
			window.draw(fill);						// Draws the fill in sprites
		}
		else if(score == 4)		// On the 4th click initialize the shape
		{
			// Re-Initialize the shape here
			UserShape temp(inputs);
			shape = temp;
			window.draw(messageText); 
			score++;	
		}
		else if(score > 4)			// Start to display the shape after initialization
		{	

			background.draw(shape.DrawFillshape()); // This will start displaying the fill sprite at the last inputted click
			shape.update();							// Then it will update here to a new coordinate
			score++;								// To display how many points there are
			window.draw(shape.DrawUserShape());		// This is the outline of the shape the user inputted
			background.display();					// Set the fill sprites inside of the original shape		
			window.draw(fill);						// Draws the fill in sprites
			acceptInput = false;
		}

		window.display();		// Display the frame

	}

	return 0;
}