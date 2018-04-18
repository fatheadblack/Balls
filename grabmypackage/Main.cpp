#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>


int counter = 0;

class myCircleShape : public sf::CircleShape
{

public:
	myCircleShape() : CircleShape(50.0f)
	{

		directionx = 0;
		directiony = 0;
		collided = false;
	}
	bool collided;
	float directionx;
	float directiony;

};


/*struct BoundingCircle
{
	sf::Vector2f centre;
	float radius;

};

sf::Vector2f GetCircleCentre(const myCircleShape& object)
{
	auto dimensions = object.getGlobalBounds();

	return sf::Vector2f(dimensions.left + dimensions.width / 2.0f, dimensions.top + dimensions.height / 2.0f);

}

sf::Vector2f GetCircleSize(const myCircleShape& object)
{
	auto originalSize = object.getTextureRect();
	auto Scale = object.getScale();

	return sf::Vector2f(originalSize.width * Scale.x, originalSize.height * Scale.y);

}

float GetRadiusOfRectangleWithSize(sf::Vector2f size)
{

	return (size.x + size.y) / 4;

}

BoundingCircle GetBoundingCircle(const myCircleShape& object)
{

	auto objsize = GetCircleSize(object);
	auto radius = GetRadiusOfRectangleWithSize(objsize);

	return BoundingCircle({ GetCircleCentre(object), radius });


}*/

bool AreBoundingCirclesIntersecting(myCircleShape& BoundingCircleOne, myCircleShape& BoundingCircleTwo)
{

	auto distanceone = BoundingCircleOne.getPosition();
	auto distancetwo = BoundingCircleTwo.getPosition();
	auto xdist = abs(distanceone.x - distancetwo.x);
	auto ydist = abs(distanceone.y - distancetwo.y);


	auto MagnitudeOfDistanceSquared = (xdist * xdist) + (ydist * ydist);
	
	auto MaximumCollidingDistanceBetweenBoundings = (BoundingCircleOne.getRadius() + BoundingCircleTwo.getRadius());
	//*(BoundingCircleOne.getRadius() + BoundingCircleTwo.getRadius());

	return (sqrt(MagnitudeOfDistanceSquared)  <= MaximumCollidingDistanceBetweenBoundings);
}

/*bool CircleTest(const myCircleShape& object1, const myCircleShape& object2)
{
	//auto boundingCircleOne = GetBoundingCircle(object1);
	//auto boundingCircleTwo = GetBoundingCircle(object2);

	//return AreBoundingCirclesIntersecting(boundingCircleOne, boundingCircleTwo);
}*/


std::vector<myCircleShape> myshapes;

void moveshape(myCircleShape& s, float x, float y);
float bouncex(myCircleShape& s);
float bouncey(myCircleShape& s);





int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

	for (int i = 0; i <= 3; i++)
	{
		 
		myCircleShape shape;
		myshapes.push_back(shape);
	}

	myshapes[0].setFillColor(sf::Color::Red);
	myshapes[1].setFillColor(sf::Color::Blue);
	myshapes[2].setFillColor(sf::Color::Green);
	myshapes[3].setFillColor(sf::Color::Yellow);
	myshapes[0].setPosition(100.f, 100.f);
	myshapes[1].setPosition(200.f, 200.f);
	myshapes[2].setPosition(400.f, 400.f);
	myshapes[3].setPosition(400.f, 100.f);
	myshapes[0].directionx = 0.09;
	myshapes[0].directiony = 0.1;
	myshapes[1].directionx = -0.09;
	myshapes[1].directiony = 0.1;
	myshapes[2].directionx = 0.09;
	myshapes[2].directiony = -0.1;
	myshapes[3].directionx = -0.09;
	myshapes[3].directiony = -0.1;

	myshapes[0].setOrigin(myshapes[0].getRadius() / 2, myshapes[0].getRadius() / 2);
	myshapes[1].setOrigin(myshapes[1].getRadius() / 2, myshapes[1].getRadius() / 2);
	myshapes[2].setOrigin(myshapes[2].getRadius() / 2, myshapes[2].getRadius() / 2);
	myshapes[3].setOrigin(myshapes[3].getRadius() / 2, myshapes[3].getRadius() / 2);

	//myshapes[0].setRadius(50.f);
	//myshapes[1].setRadius(40.f);
	//myshapes[2].setRadius(60.f);


	

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (counter == 2000)
		{
			myshapes[0].collided = false;
			myshapes[1].collided = false;
			myshapes[2].collided = false;
			myshapes[3].collided = false;
			counter = 0;

		}
		
		window.clear();
		myshapes[0].directionx *= bouncex(myshapes[0]);
		myshapes[0].directiony *= bouncey(myshapes[0]);

		moveshape(myshapes[0], myshapes[0].directionx, myshapes[0].directiony);
		

		myshapes[1].directionx *= bouncex(myshapes[1]);
		myshapes[1].directiony *= bouncey(myshapes[1]);
		moveshape(myshapes[1], myshapes[1].directionx, myshapes[1].directiony);
		

		myshapes[2].directionx *= bouncex(myshapes[2]);
		myshapes[2].directiony *= bouncey(myshapes[2]);
		moveshape(myshapes[2], myshapes[2].directionx, myshapes[2].directiony);

		myshapes[3].directionx *= bouncex(myshapes[3]);
		myshapes[3].directiony *= bouncey(myshapes[3]);
		moveshape(myshapes[3], myshapes[3].directionx, myshapes[3].directiony);
		

		if (AreBoundingCirclesIntersecting(myshapes[0], myshapes[1]) && (myshapes[0].collided == false && myshapes[1].collided == false)) 
			{ 
				std::cout << "collsion" << std::endl;
				myshapes[0].directionx *= -1;
				myshapes[1].directionx *= -1;
				myshapes[0].collided = true;
				myshapes[1].collided = true;
				//myshapes[0].directiony *= -1;
				//myshapes[1].directiony *= -1;
			}


		if (AreBoundingCirclesIntersecting(myshapes[0], myshapes[2]) && (myshapes[0].collided == false && myshapes[2].collided == false))
			{ 
				std::cout << "collsion" << std::endl;
				myshapes[0].directionx *= -1;
				myshapes[2].directionx *= -1;
				myshapes[0].collided = true;
				myshapes[2].collided = true;
				//myshapes[0].directiony *= -1;
				//myshapes[2].directiony *= -1;
		
			}

		if (AreBoundingCirclesIntersecting(myshapes[1], myshapes[2]) && (myshapes[1].collided == false && myshapes[2].collided == false))
			{ 
				std::cout << "collsion" << std::endl;
				myshapes[1].directionx *= -1;
				myshapes[2].directionx *= -1;
				myshapes[1].collided = true;
				myshapes[2].collided = true;
				//myshapes[1].directiony *= -1;
				//myshapes[2].directiony *= -1;
		
			}

		if (AreBoundingCirclesIntersecting(myshapes[0], myshapes[3]) && (myshapes[0].collided == false && myshapes[3].collided == false))
		{
			std::cout << "collsion" << std::endl;
			myshapes[0].directionx *= -1;
			myshapes[3].directionx *= -1;
			myshapes[0].collided = true;
			myshapes[3].collided = true;
			//myshapes[0].directiony *= -1;
			//myshapes[1].directiony *= -1;
		}


		if (AreBoundingCirclesIntersecting(myshapes[1], myshapes[3]) && (myshapes[1].collided == false && myshapes[3].collided == false))
		{
			std::cout << "collsion" << std::endl;
			myshapes[1].directionx *= -1;
			myshapes[3].directionx *= -1;
			myshapes[1].collided = true;
			myshapes[3].collided = true;
			//myshapes[0].directiony *= -1;
			//myshapes[2].directiony *= -1;

		}

		if (AreBoundingCirclesIntersecting(myshapes[2], myshapes[3]) && (myshapes[2].collided == false && myshapes[3].collided == false))
		{
			std::cout << "collsion" << std::endl;
			myshapes[2].directionx *= -1;
			myshapes[3].directionx *= -1;
			myshapes[2].collided = true;
			myshapes[3].collided = true;
			//myshapes[1].directiony *= -1;
			//myshapes[2].directiony *= -1;

		}


		//std::cout << "Not colliding " << std::endl;

		window.draw(myshapes[0]);
		window.draw(myshapes[1]);
		window.draw(myshapes[2]);
		window.draw(myshapes[3]);
		
		window.display();
		counter++;
	}

	

	return 0;
}

void moveshape(myCircleShape& s, float x, float y)


{

	s.move(sf::Vector2f(x, y));

}

float bouncex(myCircleShape& s)
{
	sf::Vector2f S = s.getPosition();

	if ((S.x > 950) || (S.x < 0))
	{
		return -1;

	}

	return 1;

}

float bouncey(myCircleShape& s)
{
	sf::Vector2f S = s.getPosition();

	if ((S.y > 950) || (S.y < 10))
	{
		return -1;

	}

	return 1;

}
