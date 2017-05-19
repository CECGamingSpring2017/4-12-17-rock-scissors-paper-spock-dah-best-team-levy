#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5\allegro_image.h>
#include <string>
#include <time.h>
using namespace std;

///////////FUNCTIONS//////////////////
int wallCollide(int x, int y, int dir, int level[20][20], bool isAghost);

/////////////CONSTANTS////////////////
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
const int dir = 0;
const int Buffer1 = 38;
const int Buffer2 = 8;
const int PACSIZE = 30;
const int WALLSIZE = 40;
const int maxFrame = 3;

const int RIGHT = 3;
const int LEFT = 4;
const int UP = 2;
const int DOWN = 1;


class ghost {
public:
	ghost();
	void initGhost(int x, int y, char c, int dir, bool dead, int Gspeed, ALLEGRO_BITMAP *pic);
	bool isdead();
	void drawGhost();
	void printInfo();
	void chase(int x, int y, int map[20][20]); //need 4 eventually
	bool getPacman(int pacman_x, int pacman_y);
private:
	int hitwall;
	int xpos;
	int ypos;
	char color;
	int direction;
	bool dead;
	int speed;
	int width;
	int height;
	ALLEGRO_BITMAP *picture;
};

/////////////KEYS////////////
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ESC, KEY_SPACE
};

int main()
{
	srand(time(NULL));

	int width = 32;
	int height = 32;
	int x = width / 2;
	int y = height / 2;
	int curFrame = 0;
	int frameCount = 3;
	int frameDelay = 5;
	int frameWidth = 32;
	int frameHeight = 32;


	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_BITMAP *bouncer2 = NULL;
	ALLEGRO_BITMAP *platform = NULL;
	ALLEGRO_BITMAP *dot = NULL;
	ALLEGRO_BITMAP *gate = NULL;
	ALLEGRO_BITMAP *blank = NULL;
	ALLEGRO_BITMAP *Inky = NULL;
	ALLEGRO_BITMAP *Pinky = NULL;
	ALLEGRO_BITMAP *Clyde = NULL;
	ALLEGRO_BITMAP *Blinky = NULL;
	ALLEGRO_BITMAP *Medina = NULL;
	ALLEGRO_BITMAP *Mo = NULL;
	ALLEGRO_BITMAP *Moback = NULL;


	//initalize allegro
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	//////FONT//////////
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font = al_load_ttf_font("Butcherman-Regular.ttf", 30, 0);
	ALLEGRO_FONT *barq = al_load_ttf_font("barq.ttf", 100, 0);


	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);
	event_queue = al_create_event_queue();


	//////////////////AUDIO/////////////
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(6);

	ALLEGRO_SAMPLE *sample1 = NULL; //variable to hold the audio file
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE *sample3 = NULL;
	ALLEGRO_SAMPLE *sample4 = NULL;
	ALLEGRO_SAMPLE *sample5 = NULL;
	ALLEGRO_SAMPLE *sample6 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance3 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance4 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance5 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance6 = NULL;

	sample1 = al_load_sample("OMNOM.wav");
	sample2 = al_load_sample("OMNOM2.wav");
	sample3 = al_load_sample("OMNOM3.wav");
	sample4 = al_load_sample("BackgroundMusic2.wav");
	sample5 = al_load_sample("GameOver.wav");
	sample6 = al_load_sample("death.wav");

	instance1 = al_create_sample_instance(sample1);
	instance2 = al_create_sample_instance(sample2);
	instance3 = al_create_sample_instance(sample3);
	instance4 = al_create_sample_instance(sample4);
	instance5 = al_create_sample_instance(sample5);
	instance6 = al_create_sample_instance(sample6);

	al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance3, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance4, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance5, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance6, al_get_default_mixer());

	al_set_sample_instance_playmode(instance4, ALLEGRO_PLAYMODE_LOOP);
	//end audio stuff


	//regular variables
	int level[20][20] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,3,4,3,3,0,1,1,1,1,1,1,3,0,3,0,3,0,1,
		1,0,1,1,1,1,3,4,3,0,3,4,3,4,1,1,3,1,3,1,
		1,3,4,3,0,4,0,1,1,3,1,1,1,3,1,1,0,1,0,1,
		1,0,1,1,3,1,3,1,1,0,1,1,1,0,1,1,4,1,3,1,
		1,4,0,3,0,4,0,1,1,4,1,1,1,3,4,3,0,3,0,1,
		1,1,1,0,1,1,3,0,4,0,3,0,3,0,1,1,4,1,1,1,
		1,1,1,4,1,1,1,3,1,1,0,1,1,4,3,0,3,1,1,1,
		1,1,1,0,1,1,1,0,1,1,4,1,1,0,1,1,0,1,1,1,
		0,3,4,3,0,4,0,3,0,4,0,3,0,3,0,4,0,3,0,0,
		1,1,1,0,1,3,1,1,1,4,1,1,1,1,1,1,4,1,1,1,
		1,1,1,4,1,0,1,1,0,3,4,3,0,4,0,3,0,1,1,1,
		1,1,1,0,1,3,1,1,3,1,1,4,1,1,1,0,1,1,1,1,
		1,4,0,3,4,0,1,1,0,1,1,0,1,0,3,0,3,4,3,1,
		1,0,1,1,1,3,3,0,4,0,3,4,3,0,1,1,0,1,4,1,
		1,3,1,1,1,0,1,1,0,1,1,0,1,0,1,1,4,1,3,1,
		1,4,3,0,4,3,1,1,3,1,1,3,1,3,1,1,0,1,0,1,
		1,1,0,1,1,0,1,1,4,3,0,4,0,3,1,1,3,1,4,1,
		1,1,3,4,3,4,3,0,3,1,1,1,1,3,0,4,0,3,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, };

	////////////VARIABLES
	string input;
	int lives = 3;
	int score = 0;
	int pacspeed = 4;
	int pacman_x = 45;
	int pacman_y = 45;
	bool key[5] = { false, false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	/////////////////SPRITES//////////////
	Inky = al_load_bitmap("Bell.png");
	al_convert_mask_to_alpha(Inky, al_map_rgb(0, 255, 0));
	Clyde = al_load_bitmap("Beck.png");
	al_convert_mask_to_alpha(Clyde, al_map_rgb(0, 255, 0));
	Blinky = al_load_bitmap("Springer.png");
	al_convert_mask_to_alpha(Blinky, al_map_rgb(0, 255, 0));
	Pinky = al_load_bitmap("Lofaro.png");
	al_convert_mask_to_alpha(Pinky, al_map_rgb(0, 255, 0));
	Medina = al_load_bitmap("Medina.png");
	al_convert_mask_to_alpha(Medina, al_map_rgb(0, 255, 0));
	Mo = al_load_bitmap("Mo2.png");
	al_convert_mask_to_alpha(Medina, al_map_rgb(0, 255, 0));
	Moback = al_load_bitmap("Mo.png");
	/////////////////INSTANTIATE////////////////////
	ghost blinky;
	blinky.initGhost(365, 600, 'r', dir, false, 4.0, Blinky);
	ghost pinky;
	pinky.initGhost(365, 300, 'r', dir, false, 4.0, Pinky);
	ghost clyde;
	clyde.initGhost(365, 400, 'r', dir, false, 4.0, Clyde);
	ghost inky;
	inky.initGhost(365, 500, 'r', dir, false, 4.0, Inky); 
	ghost medina;
	medina.initGhost(365, 700, 'r', dir, false, 4.0, Medina);

	//////////DRAWING///////////////
	pacman = al_create_bitmap(PACSIZE, PACSIZE);
	al_set_target_bitmap(pacman);
	al_clear_to_color(al_map_rgb(255, 255, 0));

	platform = al_create_bitmap(WALLSIZE, WALLSIZE);
	al_set_target_bitmap(platform);
	al_clear_to_color(al_map_rgb(0, 20, 200));

	dot = al_create_bitmap(4, 4);
	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	blank = al_create_bitmap(WALLSIZE, WALLSIZE);
	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	//TITLE
	al_draw_text(barq, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Pacman?");
	al_flip_display();
	al_rest(2);

	al_start_timer(timer);




	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		cout << pacman_x << " , " << pacman_y << endl;

		///////////BACKGROUND/////////////////
		al_play_sample(sample4, .35, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

		//////////////////////DEATH/////////////////////
		if (lives == 0) {
			al_destroy_sample(sample4);
			al_destroy_sample_instance(instance4);
			al_rest(1);
			al_play_sample_instance(instance5);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			al_draw_textf(barq, al_map_rgb(255, 255, 255), 130, 0, ALLEGRO_ALIGN_CENTRE, "%d", score);
			al_flip_display();
			al_draw_bitmap(Moback, 0, 0, 0);
			al_flip_display();
			al_rest(1);
			for (int i = 0; i < 20; i++) {
				int rand1 = rand() % 750 + 0;
				int rand2 = rand() % 750 + 0;
				al_draw_bitmap(Mo, rand1, rand2, 0);
			}
			al_draw_text(barq, al_map_rgb(414, 255, 1), SCREEN_W / 2, SCREEN_H / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Game Over");
			al_flip_display();
			al_rest(3);
			doexit = true;
		}

	/////////////////////////////MOVEMENT/////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && !wallCollide(pacman_x, pacman_y, UP, level, 0)) {
				pacman_y -= pacspeed;
				pacman = al_load_bitmap("pacmanUp.png");
				al_convert_mask_to_alpha(pacman, al_map_rgb(255, 255, 255));
				if (++frameCount >= frameDelay)
				{
					//these two lines reset the image to the first after you cycle through all 10
					if (++curFrame >= maxFrame)
						curFrame = 0;

					//as soon as you enter this branch and do the code, reset the "timer"
					frameCount = 0;
				}

			}

			//if the down button is pressed AND we're still above the bottom wall
			//move the bopacman_x "down" by 4 pipacman_xels
			if (key[KEY_DOWN] && !wallCollide(pacman_x, pacman_y, DOWN, level, 0)) {
				pacman_y += pacspeed;
				pacman = al_load_bitmap("pacmanDown.png");
				al_convert_mask_to_alpha(pacman, al_map_rgb(255, 255, 255));
				if (++frameCount >= frameDelay)
				{
					//these two lines reset the image to the first after you cycle through all 10
					if (++curFrame >= maxFrame)
						curFrame = 0;

					//as soon as you enter this branch and do the code, reset the "timer"
					frameCount = 0;
				}

			}
			//if the left button is pressed AND we're still right of the left wall
			//move the bopacman_x left by 4 pipacman_xels
			if (key[KEY_LEFT] && !wallCollide(pacman_x, pacman_y, LEFT, level, 0)) {
				pacman_x -= pacspeed;
				pacman = al_load_bitmap("pacmanLeft.png");
				al_convert_mask_to_alpha(pacman, al_map_rgb(255, 255, 255));
				if (++frameCount >= frameDelay)
				{
					//these two lines reset the image to the first after you cycle through all 10
					if (++curFrame >= maxFrame)
						curFrame = 0;

					//as soon as you enter this branch and do the code, reset the "timer"
					frameCount = 0;
				}

			}

			//if the left button is pressed AND we're still left of the right wall
			//move the bopacman_x right by 4 pipacman_xels
			if (key[KEY_RIGHT] && !wallCollide(pacman_x, pacman_y, RIGHT, level, 0)) {
				pacman_x += pacspeed;
				pacman = al_load_bitmap("pacmanRight.png");
				al_convert_mask_to_alpha(pacman, al_map_rgb(255, 255, 255));
				if (++frameCount >= frameDelay)
				{
					//these two lines reset the image to the first after you cycle through all 10
					if (++curFrame >= maxFrame)
						curFrame = 0;

					//as soon as you enter this branch and do the code, reset the "timer"
					frameCount = 0;
				}
			}


			//////////exit/////////
			if (key[KEY_ESC]) {
				doexit = true;
			}

			/////////////////WARP////////////
			if (pacman_y <= 0) {
				pacman_x = 365; //starting x position
				pacman_y = 765; //starting y position
			}

			if (pacman_y >= 800) {
				pacman_x = 365; //starting x position
				pacman_y = 20; //starting y position
			}
			/////////////////WARP END////////////


			/////////////////GAMEOVER////////////////////
			if (inky.getPacman(pacman_x, pacman_y)) {
				lives--;
				pacman_x = 45;
				pacman_y = 45;
				al_play_sample_instance(instance6);
			}
			if (clyde.getPacman(pacman_x, pacman_y)) {
				lives--;
				pacman_x = 45;
				pacman_y = 45;
				al_play_sample_instance(instance6);
			}
			if (blinky.getPacman(pacman_x, pacman_y)) {
				lives--;
				pacman_x = 45;
				pacman_y = 45;
				al_play_sample_instance(instance6);
			}
			if (pinky.getPacman(pacman_x, pacman_y)) {
				lives--;
				pacman_x = 45;
				pacman_y = 45;
				al_play_sample_instance(instance6);
			}
			if (medina.getPacman(pacman_x, pacman_y)) {
				lives--;
				pacman_x = 45;
				pacman_y = 45;
				al_play_sample_instance(instance6);
			}
			
			/////////////////GAMEOVER////////////////////
			if (score == 180) {
				doexit = true;
			}


			//////////////////DOT COLLECTION//////////////////
			if (level[pacman_x / WALLSIZE][pacman_y / WALLSIZE] == 0) {
				score = score + 1;
				(level[pacman_x / WALLSIZE][pacman_y / WALLSIZE] = 2);
				al_play_sample_instance(instance2);
			}

			if (level[pacman_x / WALLSIZE][pacman_y / WALLSIZE] == 3) {
				score = score + 1;
				(level[pacman_x / WALLSIZE][pacman_y / WALLSIZE] = 2);
				al_play_sample_instance(instance1);
			}

			if (level[pacman_x / WALLSIZE][pacman_y / WALLSIZE] == 4) {
				score = score + 1;
				(level[pacman_x / WALLSIZE][pacman_y / WALLSIZE] = 2);
				al_play_sample_instance(instance3);
			}
			//////////////////DOT COLLECTION END//////////////////




			//////////////CHASE/////////////////////////
			inky.chase(pacman_x, pacman_y, level);
			clyde.chase(pacman_x, pacman_y, level);
			blinky.chase(pacman_x, pacman_y, level);
			pinky.chase(pacman_x, pacman_y, level);
			medina.chase(pacman_x, pacman_y, level);
			//////////////CHASE END////////////////////


			//redraw at every tick of the timer. 
			redraw = true;
		}


		//kill program if window "X" has been clicked
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}




		//update key/key2 if a key has been pressed
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_ESCAPE:
				key[KEY_ESC] = true;
				break;

			}
		}

		//update key/key2 if a key has been released
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {


			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;


			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;


			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;


			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;


			case ALLEGRO_KEY_ESCAPE:
				key[KEY_ESC] = false;
				break;
			}
		}


		//RENDER SECTION
		//clears screen to black
		al_clear_to_color(al_map_rgb(0, 0, 0));


		al_draw_bitmap_region(pacman, curFrame*frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 0);
		al_convert_mask_to_alpha(pacman, al_map_rgb(255, 255, 255));


		///////////////DRAW GHOST///////////////
		clyde.drawGhost();
		inky.drawGhost();
		pinky.drawGhost();
		blinky.drawGhost();
		medina.drawGhost();


		///////////////////////DRAWING TO MAP/////////////////
		for (int j = 0; j<20; j++)
			for (int i = 0; i<20; i++) {
				if (level[i][j] == 1)
					al_draw_bitmap(platform, i * 40, j * 40, 0);
			}


		for (int i = 0; i<20; i++)
			for (int j = 0; j<20; j++) {
				if (level[i][j] == 0)
					al_draw_bitmap(dot, i * 40 + 20, j * 40 + 20, 0);
			}

		for (int i = 0; i<20; i++)
			for (int j = 0; j<20; j++) {
				if (level[i][j] == 3)
					al_draw_bitmap(dot, i * 40 + 20, j * 40 + 20, 0);
			}

		for (int i = 0; i<20; i++)
			for (int j = 0; j<20; j++) {
				if (level[i][j] == 4)
					al_draw_bitmap(dot, i * 40 + 20, j * 40 + 20, 0);
			}

		for (int i = 0; i<20; i++)
			for (int j = 0; j<20; j++) {
				if (level[i][j] == 2)
					al_draw_bitmap(blank, i * 40, j * 40, 0);
			}
		////////////////////////////////DRAWING MAP//////////////////////////



		al_draw_text(font, al_map_rgb(255, 255, 255), 55, 0, ALLEGRO_ALIGN_CENTRE, "Score: ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 130, 0, ALLEGRO_ALIGN_CENTRE, "%d", score);

		al_draw_text(font, al_map_rgb(255, 255, 255), 700, 0, ALLEGRO_ALIGN_CENTRE, "Lives: ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 765, 0, ALLEGRO_ALIGN_CENTRE, "%d", lives);
		al_flip_display();
	}


	al_destroy_sample(sample1);
	al_destroy_sample_instance(instance1);
	al_destroy_sample(sample2);
	al_destroy_sample_instance(instance2);
	al_destroy_sample(sample3);
	al_destroy_sample_instance(instance3);
	al_destroy_sample(sample5);
	al_destroy_sample_instance(instance5);
	al_destroy_sample(sample6);
	al_destroy_sample_instance(instance6);
	al_destroy_bitmap(pacman);
	al_destroy_bitmap(platform);
	al_destroy_bitmap(dot);
	al_destroy_bitmap(blank);
	al_destroy_bitmap(Inky);
	al_destroy_bitmap(Pinky);
	al_destroy_bitmap(Clyde);
	al_destroy_bitmap(Blinky);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}






int wallCollide(int x, int y, int dir, int level[20][20], bool isAghost) {

	//this is such terrible coding :(
	if (((y + Buffer1) / WALLSIZE >= 20) && !isAghost) //check if you've walked off the map, and if so, don't bother with collision
		return 0;

	if (((level[(x + Buffer1) / WALLSIZE][(y) / WALLSIZE] == 1) && dir == RIGHT) || ((level[(x + Buffer1) / 40][(y + 30) / WALLSIZE] == 1) && dir == RIGHT)) {

		return 1;
	}
	else if (((level[(x - Buffer2) / WALLSIZE][(y) / WALLSIZE] == 1) && dir == LEFT) || ((level[(x - Buffer2) / 40][(y + 30) / WALLSIZE] == 1) && dir == LEFT)) {

		return 1;
	}
	else if (((level[(x) / WALLSIZE][(y - Buffer2) / WALLSIZE] == 1) && dir == UP) || ((level[(x + 30) / 40][(y - Buffer2) / WALLSIZE] == 1) && dir == UP)) {

		return 1;
	}
	else if (((level[(x) / WALLSIZE][(y + Buffer1) / WALLSIZE] == 1) && dir == DOWN) || ((level[(x + 30) / 40][(y + Buffer1) / WALLSIZE] == 1) && dir == DOWN)) {
		//cout<<"colliding with "<<(x)/WALLSIZE<<" , "<<(y+Buffer1)/WALLSIZE<<" which holds a "<<(level[(x)/WALLSIZE][(y+Buffer1)/WALLSIZE] == 1)<<endl;
		return 1;
	}
	else
		return 0;

}

ghost::ghost() {

	xpos = 0;
	ypos = 0;
	color = 'a';
	direction = 0;
	dead = 0;
	speed = 0;
	width = 0;
	height = 0;
	hitwall = 0;

}
void ghost::initGhost(int x, int y, char c, int dir, bool dead, int Gspeed, ALLEGRO_BITMAP *pic) {

	xpos = x;
	ypos = y;
	color = color;
	direction = dir;
	dead = false;
	speed = Gspeed;
	width = PACSIZE;
	height = PACSIZE;
	hitwall = false;

	picture = pic;

}
bool ghost::isdead() {

	return dead;

}
void ghost::drawGhost() {

	al_draw_bitmap(picture, xpos, ypos, 0);

}
void ghost::printInfo() {

	cout << hitwall << endl;
	cout << xpos << endl;
	cout << ypos << endl;
	cout << color << endl;
	cout << direction << endl;
	cout << dead << endl;
	cout << speed << endl;

}
void ghost::chase(int x, int y, int map[20][20]) {
	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////
	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, map, 1) && y<ypos)
		while (!wallCollide(xpos, ypos, 2, map, 1)) {
			direction = UP;
			ypos -= 5;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, map, 1) && y>ypos)
		while (!wallCollide(xpos, ypos, 4, map, 1)) {
			direction = DOWN;
			ypos += 6;
			return;
		}

	if (direction == LEFT)
		while (!wallCollide(xpos, ypos, LEFT, map, 1)) {
			xpos -= 6;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, map, 1) && x<xpos)
		while (!wallCollide(xpos, ypos, LEFT, map, 1)) {
			direction = LEFT;
			xpos -= 6;
			return;
		}

	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, map, 1) && x>xpos)
		while (!wallCollide(xpos, ypos, 3, map, 1)) {
			direction = RIGHT;
			xpos += 6;
			return;
		}

	if (direction == UP)
		while (!wallCollide(xpos, ypos, 2, map, 1)) {
			ypos -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, map, 1) && y<ypos)
		while (!wallCollide(xpos, ypos, 2, map, 1)) {
			direction = UP;
			ypos -= 6;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, map, 1) && y>ypos)
		while (!wallCollide(xpos, ypos, DOWN, map, 1)) {
			direction = DOWN;
			ypos += 6;
			return;
		}

	if (direction == RIGHT)
		while (!wallCollide(xpos, ypos, RIGHT, map, 1)) {
			xpos += 6;
			return;
		}

	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, map, 1) && x<xpos)
		while (!wallCollide(xpos, ypos, LEFT, map, 1)) {
			direction = LEFT;
			xpos -= 6;
			return;
		}

	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, map, 1) && x>xpos)
		while (!wallCollide(xpos, ypos, RIGHT, map, 1)) {
			direction = RIGHT;
			xpos += 6;
			return;
		}

	if (direction == DOWN)
		while (!wallCollide(xpos, ypos, DOWN, map, 1)) {
			ypos += 6;
			return;
		}

	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y<ypos) && !wallCollide(xpos, ypos, UP, map, 1)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y>ypos) && !wallCollide(xpos, ypos, DOWN, map, 1)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x>xpos) && !wallCollide(xpos, ypos, RIGHT, map, 1)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x<xpos) && !wallCollide(xpos, ypos, LEFT, map, 1)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xpos, ypos, UP, map, 1)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xpos, ypos, DOWN, map, 1)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xpos, ypos, RIGHT, map, 1)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xpos, ypos, LEFT, map, 1)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;
	}

	cout << "x pos " << xpos << "  ypos " << ypos << endl;
}

bool ghost::getPacman(int pacman_x, int pacman_y) {
	if ((pacman_x > xpos + 25) ||
		(pacman_y > ypos + 25) ||
		(pacman_x + 25 < xpos) ||
		(pacman_y + 25 < ypos))
		return 0;

	else
		return 1;

}