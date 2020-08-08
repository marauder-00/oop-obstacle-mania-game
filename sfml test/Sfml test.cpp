#include<iostream>
#include<string>
#include<fstream>
#include <SFML/Graphics.hpp>
#include<SFML\Audio.hpp>

using namespace sf;
using namespace std;

const int height = 512, width = 1024;

class player
{
private:
	string name;
	int score;
	
public:
	player()
	{
		score = 0;
	}
	void setname(string nme)
	{
		score = 0;
		name = nme;
	}
	string getname()
	{
		return name;
	}
	void updateScore()
	{
		
		score=score + 4;
		cout << score;
	}
	int getscore()
	{
		
		return score;
	}

};
class motion :public player
{
	float x_velocity, x_position;
	float y_velocity, y_position;
	float direction;
	bool collide;



public:
	motion()
	{
		x_position = 0;
		y_position = 0;
		y_velocity = 0;
		x_velocity = 0;
		collide = false;

	}
	void movement(bool left, bool right)
	{
		if (right)
		{
			x_velocity = 0.5;
		}
		else
		{
			x_velocity = 0;
		}
		if (left)
		{
			x_velocity = -0.5;
		}
		
		y_position = y_position + y_velocity;
		if (left == true || right == true)
		{
			x_position = x_position + x_velocity;
		}

		

	}
	float getXvelocity()
	{
		return x_velocity;
	}
	float getXposition()
	{
		return x_position;
	}
	void edges()
	{
		if (x_position > 850 ||x_position<100)
		{
			x_velocity = 0;
		}

	}
	void Setcollide()
	{
		collide = true;
	}
	bool getcollide()
	{
		return collide;
	}
	friend class platform;
};
class platform
{
	float carSpriteXpos, carSpriteYpos, obstacleXpos, obstacleYpos;
	float obstacleXvel=0, obstacleYvel=-1;
public:
	platform(motion a)
	{
		obstacleXvel = 0;
		obstacleYvel = -0.25;
		carSpriteXpos = a.x_position;
		carSpriteYpos = a.y_position;
	}
	platform()
	{
		obstacleXvel = 0;
		obstacleYvel = -0.25;
	}
	float getObstacleVel()
	{
		return obstacleYvel;
	}

};

int main()
{
	false;
	motion move;
	string nme;
	cout << "===============Welcome===============\nEnter your name:";
	cin >> nme;
	cout << endl;
	move.setname(nme);
	platform obs(move);
	ofstream Score("score.txt",ios::app);
	

	// Create the main window
	RenderWindow app(VideoMode(width,height), "obstacle mania!!");

	Texture car_texture;
	Texture background;
	Texture obstacle;
	SoundBuffer bkgrnd_music;
	Sound bckgrnd;
	SoundBuffer end;
	Sound destroy;
	
	//car sprite
	car_texture.loadFromFile("data/images/car.png");
	Sprite car_sprite(car_texture);
	car_sprite.setPosition(70, 0);
	
	//background music
	bkgrnd_music.loadFromFile("data/sounds/background.ogg");
	bckgrnd.setBuffer(bkgrnd_music);

	//end sound
	end.loadFromFile("data/sounds/Game Over sound effect.wav");
	destroy.setBuffer(end);
	
	//background
	background.loadFromFile("data/images/road.png");
	Sprite spriteSheet(background);
	
	//obstacles
	obstacle.loadFromFile("data/images/obstacle.png");
	Sprite obstaclesprite1(obstacle);
	obstaclesprite1.scale(2, 1);
	obstaclesprite1.setPosition(70, 320);
	obstaclesprite1.setColor(Color::Red);
	Sprite obstaclesprite2(obstacle);
	obstaclesprite2.scale(2, 1);
	obstaclesprite2.setPosition(270,320);
	Sprite obstaclesprite3(obstacle);
	obstaclesprite3.scale(2, 1);
	obstaclesprite3.setPosition(480, 320);
	Sprite obstaclesprite4(obstacle);
	obstaclesprite4.scale(2, 1);
	obstaclesprite4.setPosition(690, 320);
	obstaclesprite4.setColor(Color::Red);

	Sprite obstaclesprite5(obstacle);
	obstaclesprite5.scale(2, 1);
	obstaclesprite5.setPosition(70, 320);
	obstaclesprite5.setColor(Color::Red);
	Sprite obstaclesprite6(obstacle);
	obstaclesprite6.scale(2, 1);
	obstaclesprite6.setPosition(270, 320);
	Sprite obstaclesprite7(obstacle);
	obstaclesprite7.scale(2, 1);
	obstaclesprite7.setPosition(480, 320);
	Sprite obstaclesprite8(obstacle);
	obstaclesprite8.scale(2, 1);
	obstaclesprite8.setPosition(480, 320);
	obstaclesprite8.setColor(Color::Red);
	Sprite obstaclesprite9(obstacle);
	obstaclesprite9.scale(2, 1);
	obstaclesprite9.setPosition(480, 320);
	Sprite obstaclesprite10(obstacle);
	obstaclesprite10.scale(2, 1);
	obstaclesprite10.setPosition(690, 320);
	obstaclesprite10.setColor(Color::Red);




		bool car_left = false, car_right = false;





	// Start the game loop
	while (app.isOpen())
	{
		if (move.getXposition()<10)
		{
			bckgrnd.play();
		}
		if (move.getcollide() == false)
		{

			// Process events
			Event event;
			while (app.pollEvent(event))
			{
				// Close window : exit
				if (event.type == Event::Closed)
					app.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				car_right = true;
			}
			else
			{

				car_right = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				car_left = true;
			}
			else
			{

				car_left = false;
			}
			//movement of car sprite
			move.movement(car_left, car_right);
			//sets edges of road
			move.edges();

			// Clear screen
			app.clear(Color::Green);
			// Draw the sprite
			app.draw(spriteSheet);
			app.draw(car_sprite);
		
			app.draw(obstaclesprite1);
			app.draw(obstaclesprite4);

			car_sprite.move(Vector2f(move.getXvelocity(), 0));
			obstaclesprite1.move(Vector2f(0, obs.getObstacleVel()));
			obstaclesprite4.move(Vector2f(0, obs.getObstacleVel()));
			if (obstaclesprite1.getPosition().y < 0 && obstaclesprite4.getPosition().y < 0)
			{
				app.draw(obstaclesprite3);

				obstaclesprite3.move(Vector2f(0, obs.getObstacleVel()));
				if (obstaclesprite3.getPosition().y < 0)
				{
					app.draw(obstaclesprite2);
					obstaclesprite2.move(Vector2f(0, obs.getObstacleVel()));
				}
			}
			if (obstaclesprite2.getPosition().y < 0)
			{
				app.draw(obstaclesprite5);
				app.draw(obstaclesprite7);
				obstaclesprite5.move(Vector2f(0, obs.getObstacleVel()));
				obstaclesprite7.move(Vector2f(0, obs.getObstacleVel()));
			}
			if (obstaclesprite5.getPosition().y < 0 && obstaclesprite7.getPosition().y < 0)
			{
				app.draw(obstaclesprite9);

				obstaclesprite9.move(Vector2f(0, obs.getObstacleVel()));
				if (obstaclesprite9.getPosition().y < 0)
				{
					app.draw(obstaclesprite10);
					obstaclesprite10.move(Vector2f(0, obs.getObstacleVel()));
				}
			}
			if (obstaclesprite10.getPosition().y < 0)
			{
				app.draw(obstaclesprite8);
				obstaclesprite8.move(Vector2f(0, obs.getObstacleVel()));
			}

		/*	if (obstaclesprite2.getPosition().y < 1 && obstaclesprite2.getPosition().y >0)
			{
				move.updateScore();
			}*/

			/*if ( car_sprite.getPosition().y == obstaclesprite1.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
				
			}
			else if ( car_sprite.getPosition().y == obstaclesprite2.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}
			else if (car_sprite.getPosition().y == obstaclesprite3.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}
			else if ( car_sprite.getPosition().y == obstaclesprite4.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}
			else if (car_sprite.getPosition().y == obstaclesprite5.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}
			else if (car_sprite.getPosition().y == obstaclesprite6.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}
			else if (car_sprite.getPosition().y == obstaclesprite7.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}*/
			/*else*/ if (car_sprite.getPosition().y == obstaclesprite8.getPosition().y)
			{
				move.Setcollide();
				bckgrnd.pause();
				destroy.play();
				
			}
			/*else if (car_sprite.getPosition().y == obstaclesprite9.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}
			else if (car_sprite.getPosition().y == obstaclesprite10.getPosition().y)
			{
				move.Setcollide();
				destroy.play();
			}

			*/


		
					// Update the window
			app.display();
		}
		else
		{
			system("pause");
			break;
		}
	}

	Score << "\nName:" << move.getname();
	Score << "\nScore:" << move.getscore() % 5;
	Score.close();
	return EXIT_SUCCESS;
}
