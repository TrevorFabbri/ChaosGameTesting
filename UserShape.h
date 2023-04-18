#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

class UserShape
{
	private:
		ConvexShape userInput;
		RectangleShape fillShape;
		float distance;				// Distance between objects
		Vector2f fillShapeXY;		// Coordinates of where the new shape will be displayed

	public:
		UserShape();									// Default constructor
		UserShape(vector<Vector2f>);					// Constructor for when we have user inputs
		void fillShapeSetPosition(Vector2f , Vector2f);	// Set new position of fill shape
		void update();									
		ConvexShape DrawUserShape();
		RectangleShape DrawFillshape();
		int outputs;
};