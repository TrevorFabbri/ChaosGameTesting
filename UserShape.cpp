#include "UserShape.h"

UserShape::UserShape()
{
	// Base Constructor
	srand(time(0));
	distance = 0.45f;
	outputs = 0;
}


UserShape::UserShape(vector<Vector2f> inputs)
{
	srand(time(0));

	// Initialize the shape with user inputted X and Y positions
	userInput.setPointCount(inputs.size() - 1);
	for (int i = 0; i < inputs.size() - 1; i++)
	{
		userInput.setPoint(i, inputs.at(i));
		userInput.setPoint(i, inputs.at(i));
		userInput.setPoint(i, inputs.at(i));
	}
	userInput.setOutlineThickness(5.f);
	userInput.setFillColor(Color::Transparent); // Must be transparent color
	userInput.setOutlineColor(Color::Red);  // CAN CHANGE OUTLINE COLOR HERE IF NEEDED

	// Set starting position of Chaos Game to last user input
	Vector2f fillShapeXY = inputs.at(inputs.size()-1);

	// Initialize the shape that will fill the user inputted shape
	fillShape.setSize(Vector2f(1, 1));
	fillShape.setPosition(fillShapeXY);

	distance = 0.5f;  
	outputs = 0;
}

void UserShape::fillShapeSetPosition(Vector2f first, Vector2f second)
{
	if (outputs = 0) // If 1st output, do it at the user's mouse click
	{
		fillShape.setPosition(fillShapeXY);
	}
	else
	{
		// Set a new position for the fill shape
		float x = (first.x * (1 - distance) + second.x * distance);
		float y = (first.y * (1 - distance) + second.y * distance);
		fillShape.setPosition(x, y);
	}
}


void UserShape::update()
{
	int random = rand() % (userInput.getPointCount() * 2) + 1;

    if (random % 2 == 0) 
    {
		fillShapeSetPosition(userInput.getPoint((random - 2) / 2), fillShapeXY);
    }
    else
    {
		fillShapeSetPosition(userInput.getPoint((random - 1) / 2), fillShapeXY);
	}

    fillShapeXY = fillShape.getPosition();
}

ConvexShape UserShape::DrawUserShape()
{
    return userInput;
}

RectangleShape UserShape::DrawFillshape()
{
    return fillShape;
}