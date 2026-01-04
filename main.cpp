#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using namespace Keyboard;

int main()
{
	// Create the main window 
    RenderWindow window(VideoMode({ 800, 600 }), "RED DEATH");
    window.setFramerateLimit(60);

	//player creationan 
    RectangleShape player(Vector2f(50.f, 50.f));
    player.setFillColor(Color(255,215,0));
	player.setPosition({375.f, 275.f});
    
    //settings
    float player_speed = 4.f;

    int maxHp = 100;
    int hp = maxHp;

    float Wall_dmgCooldown = 0.5f;
    float wallTimer = 0.5f;

    //clock
	Clock clock;
    
	// Start the game loop
    while (window.isOpen())
    {
		float deltaTime = clock.restart().asSeconds();
        wallTimer += deltaTime;

        //EVENTS
        while (auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
        }

		//PLAYER MOVEMENT
        if (isKeyPressed(Key::W))
        {
            player.move({ 0.f,-player_speed });
        }
        if (isKeyPressed(Key::S))
        {
            player.move({ 0.f,player_speed });
        }
        if (isKeyPressed(Key::A))
        {
            player.move({ -player_speed,0.f });
        }
        if (isKeyPressed(Key::D))
        {
            player.move({ player_speed,0 });
        }

		//GET POSITION AND SIZE
        Vector2f pos = player.getPosition();
        Vector2f size = player.getSize();


		//WALL DAMAGE AND BOUNDS CHECK
		bool touchingWall = false;
        if (pos.x < 0) {
			pos.x = 0;
			touchingWall = true;
        }
        if (pos.y < 0) {
            pos.y = 0;
			touchingWall = true;
        }
        if (pos.x + size.x > window.getSize().x) {
			pos.x = window.getSize().x - size.x;
			touchingWall = true;
        }
        if (pos.y + size.y > window.getSize().y) {
			pos.y = window.getSize().y - size.y;
			touchingWall = true;
        }
		player.setPosition(pos);

        if(touchingWall && wallTimer >= Wall_dmgCooldown) {
            hp -= 10;
            wallTimer = 0.f;
            
            if (hp < 0) {
				hp = 0;
            }
		}

		float hpPercent = static_cast<float>(hp) / static_cast<float>(maxHp);
        int redValue = static_cast<int>(255 * hpPercent);

        if (redValue < 0)   redValue = 0;
        if (redValue > 255) redValue = 255;

        player.setFillColor(Color(redValue, 0, 0));

        //DRAWING
        window.clear(Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}
