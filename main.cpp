#include <SFML/Graphics.hpp>
#include <string>
#include <time.h>
#include <list>
#include <bits/stdc++.h>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf ;
// value const
bool gameOver = 0;

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 533;
const int SCREEN_WIDTH_CAR = 33;
const int SCREEN_HEIGHT_CAR = 67;
int speed = 5, score = -1, tmp = 0;
// point
class point
{
public:
    float x, y;
    point ( float  _x, float  _y )
    {
        x = _x;
        y = _y;
    }
};
// get position car
point player ( 133, 450 );
// check collision
bool collision(Sprite &player, Sprite entity)
{
    if(player.getGlobalBounds().intersects(entity.getGlobalBounds()))
        return true;
    return false;
}
// random
int a[5] = { 43, 89, 136, 182, 226 };
//gameover
int gameover();
// MAIN
int main()
{
    // screen start
    RenderWindow start ( VideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT ), "CarRoad", Style::Default );
n:
    SoundBuffer gamesound;
    gamesound.loadFromFile ("sound/game.ogg");
    Sound GameSound;
    GameSound.setBuffer (gamesound);
    GameSound.play();
    GameSound.setLoop(true);
    while (start.isOpen())
    {
        Texture(t);
        t.loadFromFile ( "images/menu.png");
        t.setSmooth (true);
        Sprite menu (t);
        start.clear();
        start.draw (menu);
        start.display();
        Event ev;
        while(start.pollEvent(ev))
        {
            if(ev.type == Event::Closed)
            {
                start.close();
            }
            if ( ev.type == Event:: KeyPressed )
            {
                if ( ev.key.code == Keyboard::Enter )
                    goto a;
                if ( ev.key.code == Keyboard::Escape )
                    start.close();
            }
        }
    }
a:
    srand ( time (0) );
    // create the window
    RenderWindow game ( VideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT ), "CarRoad", Style::Default );
    game.setVerticalSyncEnabled(true);
    //load file
    Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    Texture t1, t2, t3, t4;
    t1.loadFromFile ( "images/background.png" );
    t2.loadFromFile ( "images/car.png" );
    t3.loadFromFile ( "images/threat1.png" );
    t4.loadFromFile ( "images/threat2.png" );
    // smooth
    t1.setSmooth(true);
    t2.setSmooth(true);
    t3.setSmooth(true);
    t4.setSmooth(true);
    //sprite
    Sprite background ( t1 ), car ( t2 ), square ( t3 ), square1 ( t3 ), square2 ( t3 ), square3 (t3), square4 (t3), circle (t4);
    // get position
    point sq ( 43, 0 );
    point sq1 ( 89, 0 );
    point sq2 ( 136, 0 );
    point sq3 ( 182, 0 );
    point sq4 ( 226, 0 );
    point cr ( a[rand()%5], 0 );
    // value speed and random
    int speed1 = rand()%5 + 1;
    int speed2 = rand()%5 + 1;
    int speed3 = rand()%5 + 1;
    int speed4 = rand()%5 + 1;
    int speed5 = rand()%5 + 1;
    // music1
    SoundBuffer soundeat;
    soundeat.loadFromFile("sound/collision.ogg");
    Sound SoundEat;
    SoundEat.setBuffer(soundeat);
    //music2
    SoundBuffer musicgameover;
    musicgameover.loadFromFile("sound/crash.ogg");
    Sound MusicGameOver;
    MusicGameOver.setBuffer(musicgameover);
    //music 3
    SoundBuffer musicskip;
    musicskip.loadFromFile("sound/skip.ogg");
    Sound MusicSkip;
    MusicSkip.setBuffer(musicskip);
    //gameOverAsset
    Texture gameOverImage;
    gameOverImage.loadFromFile("images/gameover.png");
    gameOverImage.setSmooth(true);
    Sprite END (gameOverImage);
    Font gameOverFont;
    gameOverFont.loadFromFile("OpenSans-Bold.ttf");


    //start game loop
    while(game.isOpen())
    {
        //check event
        Event event;
        while(game.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                game.close();
            }
        }
        //car move and keyboard
        if(Keyboard::isKeyPressed(Keyboard::Up))
            player.y -= 3.5;
        if(Keyboard::isKeyPressed(Keyboard::Down))
            player.y += 3.5;
        if(Keyboard::isKeyPressed(Keyboard::Right))
            player.x += 4;
        if(Keyboard::isKeyPressed(Keyboard::Left))
            player.x -= 4;
        if(Keyboard::isKeyPressed(Keyboard::Escape))
            game.close();
        if(gameOver && Keyboard::isKeyPressed(Keyboard::Enter))
        {
            gameOver = 0;

            sq.y = sq1.y = sq2.y = sq3.y = sq4.y = 0;

            cr.x = a[rand() % 5];
            cr.y = 0;

            player.x = 133;
            player.y = 450;
            // value speed and random
            int speed1 = rand()%5 + 1;
            int speed2 = rand()%5 + 1;
            int speed3 = rand()%5 + 1;
            int speed4 = rand()%5 + 1;
            int speed5 = rand()%5 + 1;

            score = 0;
        }
        if( player.x + SCREEN_WIDTH_CAR >= 265 )
        {
            player.x -= 4;
        }
        else if( player.x <= 35 )
            player.x += 4;
        if( player.y + SCREEN_HEIGHT_CAR >= SCREEN_HEIGHT )
        {
            player.y -= 3.5;
        }
        else if( player.y <= 0 )
            player.y += 3.5;
        //speed game
        sq.y += speed1 + 1.25 ;
        sq1.y += speed2 + 1.25;
        sq2.y += speed3 + 1.25;
        sq3.y += speed4 + 1.25;
        sq4.y += speed5 + 1.25;
        cr.y += 1.5;
        //collision and end game
        // circle
        if (!gameOver)
        {
            if (collision( car, circle ) )
            {
                GameSound.pause();
                SoundEat.play();
                GameSound.play();
                score++;
                cr.x = a[rand()%5];
                cr.y = 0;
            }
            else
            {
                if ( cr.y > SCREEN_HEIGHT)
                {
                    GameSound.pause();
                    MusicSkip.play();
                    GameSound.play();
                    gameOver = 1;
                }

            }
        }
        //square
        if(sq.y > SCREEN_HEIGHT)
        {
            sq.y = 0;
            sq.x = 43;
            speed1 = rand()%5 + 1;
        }
        //square1
        if(sq1.y > SCREEN_HEIGHT)
        {
            sq1.y = 0;
            sq1.x = 89;
            speed2 = rand()%5 + 1;
        }
        //square2
        if(sq2.y > SCREEN_HEIGHT)
        {
            sq2.y = 0;
            sq2.x = 136;
            speed3 = rand()%5 + 1;
        }
        //square3
        if(sq3.y > SCREEN_HEIGHT)
        {
            sq3.y = 0;
            sq3.x = 182;
            speed4 = rand()%5 + 1;
        }
        //square4
        if(sq4.y > SCREEN_HEIGHT)
        {
            sq4.y = 0;
            sq4.x = 226;
            speed5 = rand()%5 + 1;
        }
        //check collision
        if (!gameOver)
            if(collision(car, square) || collision(car, square1) ||  collision(car, square2) ||  collision(car, square3) ||  collision(car, square4) )
            {
                tmp++;
                if(tmp > 1)
                {
                    GameSound.pause();
                    MusicGameOver.play();
                    GameSound.play();
                    gameOver = 1;
                }
            }
        //score
        string result;
        ostringstream convert;
        convert << score;
        result = convert.str();
        Text mark ( result, font, 25 );
        mark.setOutlineThickness(0.5);
        mark.setOutlineColor(Color::White);
        //game clear
        game.clear();
        //update position
        car.setPosition(player.x, player.y);
        //cout << sq.x <<' '<< sq.y << endl;
        square.setPosition(sq.x, sq.y);
        square1.setPosition(sq1.x, sq1.y);
        square2.setPosition(sq2.x, sq2.y);
        square3.setPosition(sq3.x, sq3.y);
        square4.setPosition(sq4.x, sq4.y);
        circle.setPosition( cr.x, cr.y );
        mark.setPosition(133, 20);
        // draw image
        if (!gameOver)
        {
            game.draw(background);
            game.draw(square);
            game.draw(square1);
            game.draw(square2);
            game.draw(square3);
            game.draw(square4);
            game.draw(circle);
            game.draw(car);
            game.draw(mark);
        }
        else
        {
            string result;
            ostringstream convert;
            convert << score;
            result = "YOUR SCORE : " + convert.str();
            Text mark ( result, font, 25 );
            mark.setOutlineThickness(0.5);
            mark.setOutlineColor(Color::White);
            // mark position
            mark.setPosition(60, 100);
            // draw
            game.draw(END);
            game.draw(mark);
        }
        // screen game
        game.display();
    }
    return EXIT_SUCCESS;
}
