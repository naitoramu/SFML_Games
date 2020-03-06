#include <SFML/Graphics.hpp>
#include <iostream>
#include "SnakeHead.hpp"
#include "SnakeBody.hpp"
#include "Apple.hpp"
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

bool menu(RenderWindow* window, Font* font, Event* event, Texture* tekstura, Sprite* menu_background){
    bool b = 1;
    Text Press_to_start("Press Space to start game", *font, 70);
    Press_to_start.setFillColor(Color(190, 195, 190));
    Press_to_start.setOrigin(Vector2f(Press_to_start.getLocalBounds().width/2, Press_to_start.getLocalBounds().height/2));
    Press_to_start.setPosition(Vector2f(window->getSize().x/2, window->getSize().y*0.8));

    if(!tekstura->loadFromFile("img/menu_background.png")) {
        std::cout << "Cannot load texture" << std::endl;
    }else tekstura->loadFromFile("img/menu_background.png");
    menu_background->setTexture(*tekstura);

    window->draw(*menu_background);
    window->draw(Press_to_start);
    window->display();
    while(b){
        while(window->pollEvent(*event))
        {
            if(event->type == Event::Closed){
                window->close();
                return 0;
            }
            if(event->type == Event::KeyPressed && event->key.code == Keyboard::Escape){
                window->close();
                return 0;
            }
            if(event->type == Event::KeyPressed && event->key.code == Keyboard::Space){
                b = 0;
                return 1;
            }
        }
    }
}
RectangleShape createFrame(int width, int height){
    int size = height - 120;
    RectangleShape frame(Vector2f(size, size));
    frame.setOrigin(Vector2f(size/2, size/2));
    frame.setPosition(Vector2f(width/2, height/2));
    frame.setFillColor(Color::Black);
    frame.setOutlineColor(Color(20, 20, 20));
    frame.setOutlineThickness(20);
    return frame;
}

void drawingWorld(RenderWindow* window, Sprite* snake_board, SnakeHead* head, SnakeBody* body, Apple* apple, int segmenty, Text* your_score, Text* best_score, Text* y_score, Text* b_score, bool* collision){
    window->clear(Color::Black);
    window->draw(*snake_board);
    window->draw(*apple);
    if(!(*collision))window->draw(*head);
    while(segmenty){
        window->draw(body[segmenty - 1]);
        segmenty--;
    }
    window->draw(*your_score);
    window->draw(*best_score);
    window->draw(*y_score);
    window->draw(*b_score);
    window->display();
}

void updatingWorld(int input, int* segmenty, SnakeHead* head, SnakeBody* body, Apple* apple, bool* pause, bool* collision, Text* y_score, Text* b_score,  int* b_score_int){
    head->sterowanie(input);
    if(head->kolizja(body, *segmenty) == 0) {
		for(int i = *segmenty - 1; i >= 0; i--){
			if(i)body[i].move(&body[i - 1]);
			else body[i].move(head);
		}
		head->move();
	}else{
        *pause = true;
        *collision = true;
    }
    
    if(apple->getPosition() == head->getPosition()){
		apple->setNewRandomPosition(head, body, *segmenty);
		(*segmenty)++;
        y_score->setString(to_string(*segmenty));
        if(*b_score_int < *segmenty){
            *b_score_int = *segmenty;
            b_score->setString(to_string(*b_score_int));
        }
    }
}

void createBoard(Sprite* snake_board, Texture* tekstura){
    if(!tekstura->loadFromFile("img/SnakeBoard.png")) {
        std::cout << "Cannot load texture" << std::endl;
    }else tekstura->loadFromFile("img/SnakeBoard.png");
    snake_board->setTexture(*tekstura);
}

int pauseMenu(RenderWindow* window, Event* event, Sprite* pause_background, Font* font, bool* collision){
    bool b = 1;
    Text resume("Press Space to resume game", *font, 30);
    resume.setPosition(Vector2f(window->getSize().x/2, window->getSize().y*0.6));
    Text restart("Press Enter to restart game", *font, 30);
    restart.setPosition(Vector2f(window->getSize().x/2, window->getSize().y*0.7));
    Text exit("Press Escape to quit the game", *font, 30);
    exit.setPosition(Vector2f(window->getSize().x/2, window->getSize().y*0.9));
    pause_background->setColor(Color(255, 255, 255, 100));
    window->draw(*pause_background);
    if(!(*collision)) window->draw(resume);
    window->draw(restart);
    window->draw(exit);
    window->display();
    while(b){
        while(window->pollEvent(*event))
        {
            if(event->type == Event::Closed){
                window->close();
                return 0;
            }
            if(event->type == Event::KeyPressed && event->key.code == Keyboard::Escape){
                window->close();
                return 0;
            }
            if(event->type == Event::KeyPressed && event->key.code == Keyboard::Space){
                b = 0;
                return 1;
            }
            if(event->type == Event::KeyPressed && event->key.code == Keyboard::Return){
                b = 0;
                return 2;
            }
        }
    }
}

bool gameBegin(RenderWindow* window, Event* event, Font* font, int width, int height){
    int scene_size = 600;
    int ilosc_segmentow = 0;
    bool pause = 0;
    bool restart = false;
    bool* collision = new bool;
    *collision = false;
    while (window->isOpen())
    {
        window->setFramerateLimit(8);
        Texture* background_texture = new Texture;
        Sprite* menu_background = new Sprite;
        bool game_is_running = menu(window, font, event, background_texture, menu_background);
        int b_score_int;
        ifstream r_score("src/best_score.txt");
        if(!r_score){
            cout << "Cannot read best score" << endl;
        }else{
            r_score >> b_score_int;
        }
        r_score.close();
        if(game_is_running){
            //createWorld();
            Texture* board_texture = new Texture;
            Sprite* snake_board = new Sprite;
            createBoard(snake_board, board_texture);
            //RectangleShape frame = createFrame(width, height);
            SnakeHead head(40, 40, width/2, height/2, 720, 1280, scene_size);
            SnakeBody body[224];
	        for(int i = 0; i < 224; i++){
		        body[i].konstruktor(&head, -40, -40);
	        }
	        Apple* apple = new Apple(&head);

            Text your_score("Your score:", *font, 30);
            Text y_score;
            y_score.setFont(*font);
            y_score.setCharacterSize(50);
            y_score.setString(to_string(0));
            y_score.setOrigin(Vector2f(y_score.getLocalBounds().width/2, y_score.getLocalBounds().height/2));
            y_score.setPosition(Vector2f(width * 0.13, height * 0.55));
            y_score.setFillColor(Color(35, 45, 20));
            your_score.setFillColor(Color(35, 45, 20));
            your_score.setOrigin(Vector2f(your_score.getLocalBounds().width/2, your_score.getLocalBounds().height/2));
            your_score.setPosition(Vector2f(width * 0.13, height * 0.45));
            Text best_score("Best score:", *font, 30);
            Text b_score;
            b_score.setFont(*font);
            b_score.setCharacterSize(50);
            b_score.setString(to_string(b_score_int));
            b_score.setOrigin(Vector2f(b_score.getLocalBounds().width/2, b_score.getLocalBounds().height/2));
            b_score.setPosition(Vector2f(width * 0.87, height * 0.55));
            b_score.setFillColor(Color(35, 45, 20));
            best_score.setFillColor(Color(35, 45, 20));
            best_score.setOrigin(Vector2f(best_score.getLocalBounds().width/2, best_score.getLocalBounds().height/2));
            best_score.setPosition(Vector2f(width * 0.87, height * 0.45));
            int input = 3;

            while(game_is_running){
                while (window->pollEvent(*event)){
			        if (event->type == sf::Event::Closed){
			    	    window->close();
                        //return 0;
                    }
			        if( event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::W )
			    	    input = 3;
			        if( event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::A )
			    	    input = 2;
			        if( event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::S )
			    	    input = 1;
			        if( event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::D ){
				        input = 4;
		            }
                    if( event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape ){
				        pause = 1;
		            }
                }
                if(!pause){
                    updatingWorld(input, &ilosc_segmentow, &head, body, apple, &pause, collision, &y_score, &b_score, &b_score_int);
                }else{ 
                    int input = pauseMenu(window, event, menu_background, font, collision);
                    if(input == 1){
                        pause = false;
                    }else if(input == 2){
                        restart = true;
                        break;
                    }else game_is_running = false;
                }

                drawingWorld(window, snake_board, &head, body, apple, ilosc_segmentow, &your_score, &best_score, &y_score, &b_score, collision);
                
            }
        }
        ofstream w_score("src/best_score.txt");
        if(!w_score){
            cout << "Cannot write best score" << endl;
        }else{
            w_score << b_score_int;
        }
        w_score.close();
        if(restart){
            gameBegin(window, event, font, width, height);
        }//else return 0;
    }
}

int main(){   
    srand( time( NULL ) );
    int width = 1280;
    int height = 720;
    RenderWindow window(VideoMode(width, height), "Snake_by_NocnyBaran");
    Event* event = new Event;
    Font* font = new Font;
	if (!font->loadFromFile("src/Frijole-Regular.ttf")){
		std::cout << "Cannot load font" << std::endl;
	}else font->loadFromFile("src/Frijole-Regular.ttf");

    gameBegin(&window, event, font, width, height);

    return 0;
}