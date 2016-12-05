#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h> 

int width = 640;
int height = 480;
int fps = 60;

//int unpressedcolor[] = { 255,255,255 };
//int r[] = { 255,0,0 }, g[] = { 0,0,0 }, b[] = { 0,0,0 };
//
//void color(int *r, int *g, int *b, int selection, int max)
//{
//	for (int i = 0; i < max; ++i)
//	{
//		r[i] = unpressedcolor[0]; g[i] = unpressedcolor[1]; b[i] = unpressedcolor[2];
//	}
//	r[selection] = []
//}

int kolor1[] = { 255,255,255 };
int kolor2[] = { 255,255,255 };

int main()
{
	bool game_on = false;
	bool done = false;
	int pointery = height / 2 + 30;

	al_init();

	al_init_image_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_BITMAP *map = al_load_bitmap("960.jpg");
	ALLEGRO_DISPLAY *display = al_create_display(width, height);
	ALLEGRO_FONT *title = al_load_ttf_font("krzysztof.ttf", 42, 0);

		ALLEGRO_FONT *menu = al_load_ttf_font("krzysztof.ttf", 18, 0);
		ALLEGRO_TIMER *timer = al_create_timer(1.0 / fps);
		ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		al_start_timer(timer);

		while (!done)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					if (pointery > height / 2 + 30)
					{
						pointery -= 30;
						kolor1[0] = 255;
						kolor1[1] = 0;
						kolor1[2] = 0;
						kolor2[0] = 255;
						kolor2[1] = 255;
						kolor2[2] = 255;

					}
					break;
				case ALLEGRO_KEY_DOWN:
					if (pointery < height / 2 + 60)
					{
						pointery += 30;
						kolor2[0] = 255;
						kolor2[1] = 0;
						kolor2[2] = 0;
						kolor1[0] = 255;
						kolor1[1] = 255;
						kolor1[2] = 255;
					}
					break;
				case ALLEGRO_KEY_ENTER:
					if (pointery == height / 2 + 30)
					{
						game_on = true;
						done = true;
						//al_draw_text(menu, al_map_rgb(255, 255, 255), width / 2, (height / 2) - 100, ALLEGRO_ALIGN_CENTER, "EXIT");
						//al_draw_bitmap(map, 0, 0, 0);
						//al_flip_display();
					}
					else if (pointery == height / 2 + 60)
					{
						exit(0);
					}
					break;
				}
			}

			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{

				// rendering
				
				al_draw_text(title, al_map_rgb(255, 255, 255), width / 2, (height / 2) - 160, ALLEGRO_ALIGN_CENTER, "MARIAN GAME");
				al_draw_text(menu, al_map_rgb(kolor1[0], kolor1[1], kolor1[2]), width / 2, (height / 2) + 30, ALLEGRO_ALIGN_CENTER, "START GAME");
				al_draw_text(menu, al_map_rgb(kolor1[0], kolor2[1], kolor2[2]), width / 2, (height / 2) + 60, ALLEGRO_ALIGN_CENTER, "EXIT");
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
		al_destroy_font(title);
		al_destroy_font(menu);
		al_destroy_event_queue(event_queue);
		if (game_on)
		{
			done = false;
			while (!done)
			{
				al_draw_bitmap(map, 0, 0, 0);
				al_flip_display();
			}
		}
		al_destroy_bitmap(map);
	return 0;
}