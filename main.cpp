                                                          

// f12 takes a screenshot
// button "a" takes a screenshot

// bug
//   -- if your in the menus, you can still go in and out of doors
//   -- when there are two platform blocks on top of each other
//      you can not jump onto the bottom one.
//   -- you cannot abort the game with ESC while choosing a level


// this program was compiled with
//  ---- dev-cpp 4
//  ---- mingw32 compiler 2.95.2-1
//  ---- fblend version 0.4
//  ---- alfont v1.9.1
//  ---- allegro version 4.03
//  ---- algif 1.3


#define version_number "Beta v.4"
#define COPYRIGHT_TEXT  "Copyright 2006 - Mark Oates"

//#include "allegro.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>

//#include <algif.h>

#define SCREEN_W 320
#define SCREEN_H 240
#define FONT ALLEGRO_FONT
#define ALFONT_FONT ALLEGRO_FONT

//#include "fblend.h"


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


//#define ALFONT_DLL
//#include <alfont.h>


#define TRUE 1
#define FALSE 0


#define ABS(v) ((v < 0) ? (v*-1) : v)


ALLEGRO_KEYBOARD_STATE keyboard_state;
bool key[ALLEGRO_KEY_MAX];
void poll_keyboard()
{
	al_get_keyboard_state(&keyboard_state);
	for (int i=0; i<ALLEGRO_KEY_MAX; i++)
	{
		key[i] = al_key_down(&keyboard_state, i);
	}
}


float BLEND_ALPHA = 1.0;

void set_multiply_blender(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	BLEND_ALPHA = a / 255.0;
}

void set_trans_blender(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	BLEND_ALPHA = a / 255.0;
}

void draw_trans_sprite(ALLEGRO_BITMAP *target, ALLEGRO_BITMAP *src, int x, int y)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_tinted_bitmap(src, al_map_rgba_f(BLEND_ALPHA, BLEND_ALPHA, BLEND_ALPHA, BLEND_ALPHA), x, y, 0);

	al_restore_state(&prev);	
}

void fblend_rect_trans(ALLEGRO_BITMAP *target, float x, float y, float x2, float y2, ALLEGRO_COLOR primary_color, unsigned char _factor)
{
	float factor = _factor / 255.0;

	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_filled_rectangle(x, y, x2, y2, al_map_rgba_f(primary_color.r * factor, primary_color.g * factor, primary_color.b * factor, primary_color.a * factor));

	al_restore_state(&prev);	
}

#define DRAW_MODE_TRANS 1
void drawing_mode(int mode, ALLEGRO_BITMAP *pattern, int x, int y)
{
	// do nothing
}

void solid_mode()
{
	// also do nothing
}


template<class T>
std::string tostring(T val)
{
	std::ostringstream s;
	s << val;
	return s.str();
}


int text_length(ALLEGRO_FONT *f, std::string message)
{
	return al_get_text_width(f, message.c_str());
}

ALLEGRO_FONT *alfont_load_font(std::string filename)
{
	return al_load_font(filename.c_str(), 15, 0);
}

void alfont_destroy_font(ALLEGRO_FONT *font)
{
	al_destroy_font(font);
}

int alfont_text_length(ALLEGRO_FONT *f, std::string text)
{
	return text_length(f, text);
}

ALLEGRO_SAMPLE *load_sample(std::string filename)
{
	return al_load_sample(filename.c_str());
}

void destroy_sample(ALLEGRO_SAMPLE *sample)
{
	al_destroy_sample(sample);
}

bool keyboard_needs_poll()
{
	return true;
}

void clear_keybuf()
{
	poll_keyboard();
}

void readkey()
{
	ALLEGRO_KEYBOARD_STATE new_state;

	while(true)
	{
		al_get_keyboard_state(&new_state);

		for (int i=0; i<ALLEGRO_KEY_MAX; i++)
		{
			if (!key[i] && al_key_down(&new_state, i)) return;
		}
	}
}


void alfont_set_font_size(ALLEGRO_FONT *font, int size)
{
	// do nothing
}


void draw_sprite_h_flip(ALLEGRO_BITMAP *target, ALLEGRO_BITMAP *src, int x, int y)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_bitmap(src, x, y, ALLEGRO_FLIP_HORIZONTAL);

	al_restore_state(&prev);
}


int text_height(ALLEGRO_FONT *font)
{
	return al_get_font_line_height(font);
}

int alfont_text_height(ALLEGRO_FONT *font)
{
	return text_height(font);
}

void fblend_trans(ALLEGRO_BITMAP *sprite, ALLEGRO_BITMAP *target, int x, int y, unsigned char factor)
{
	float alpha = factor / 255.0;

	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_tinted_bitmap(sprite, al_map_rgba_f(alpha, alpha, alpha, alpha), x, y, 0);

	al_restore_state(&prev);
}


ALLEGRO_JOYSTICK_STATE joy[1];
ALLEGRO_JOYSTICK *joystick = NULL;
void poll_joystick()
{
	if (!joystick) return;

	al_get_joystick_state(joystick, &joy[0]);
}
int get_joy_num_buttons()
{
	if (!joystick) return 0;
	
	return al_get_joystick_num_buttons(joystick);
}


void textprintf(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, const char *format, ...)
{
   char argsbuff[256];
   va_list args;
   va_start(args, format);
   vsprintf(argsbuff, format, args);
   va_end(args);

	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_text(font, color, x, y, 0, argsbuff);

	al_restore_state(&prev);
}


void alfont_textprintf(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, std::string text)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_text(font, color, x, y, 0, text.c_str());

	al_restore_state(&prev);
}

void alfont_textprintf_aa(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, std::string text)
{
	alfont_textprintf(target, font, x, y, color, text);
}

void alfont_textprintf_centre(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, std::string text)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	y -= 2;

	al_draw_text(font, color, x, y, ALLEGRO_ALIGN_CENTER, text.c_str());

	al_restore_state(&prev);
}

void alfont_textprintf_centre(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, std::string text, int val)
{
	std::stringstream ss;
	if (text == "0%i") ss << "0";
	ss << val;

	alfont_textprintf_centre(target, font, x, y, color, ss.str());
}


void alfont_textprintf_centre_aa(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, std::string text)
{
	alfont_textprintf_centre(target, font, x, y, color, text);
}

void alfont_textprintf_centre_aa(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, int x, int y, ALLEGRO_COLOR color, std::string text, int val)
{
	std::stringstream ss;
	if (text == "0%i") ss << "0";
	ss << val;

	alfont_textprintf_centre(target, font, x, y, color, ss.str());
}

   
void ellipsefill(ALLEGRO_BITMAP *target, int cx, int cy, int rx, int ry, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_filled_ellipse(cx, cy, rx, ry, color);

	al_restore_state(&prev);
}


#include <algorithm>
std::string take_screenshot(std::string filename)
{
	ALLEGRO_STATE previous_state;
	al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

	ALLEGRO_DISPLAY *display = al_get_current_display();
	ALLEGRO_BITMAP *target = al_create_bitmap(al_get_display_width(display), al_get_display_height(display));
	al_set_target_bitmap(target);

	al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);

	al_restore_state(&previous_state);

	al_save_bitmap(filename.c_str(), target);
	al_destroy_bitmap(target);

	return filename;
}


void rect(ALLEGRO_BITMAP *target, int x, int y, int x2, int y2, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_rectangle(x+0.5, y+0.5, x2+0.5, y2+0.5, color, 1.0);

	al_restore_state(&prev);
}



ALLEGRO_BITMAP *create_bitmap(int w, int h)
{
	return al_create_bitmap(w, h);
}



void destroy_font(ALLEGRO_FONT *font)
{
	al_destroy_font(font);
}


//ALLEGRO_BITMAP *screen = 0;


int mouse_x = 0;
int mouse_y = 0;
bool mouse_b1 = false;
bool mouse_b2 = false;

ALLEGRO_FONT *font = NULL;

void poll_mouse()
{
	ALLEGRO_MOUSE_STATE mouse_state;
	al_get_mouse_state(&mouse_state);
	mouse_x = mouse_state.x;
	mouse_y = mouse_state.y;
	mouse_b1 = al_mouse_button_down(&mouse_state, 1);
	mouse_b2 = al_mouse_button_down(&mouse_state, 2);
}



void play_sample(ALLEGRO_SAMPLE *spl, int vol, int pan, int freq, int loop)
{
	al_play_sample(spl, vol/255.0, (pan-128)/128.0, freq/1000.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}


void rectfill(ALLEGRO_BITMAP *target, float x1, float y1, float x2, float y2, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_filled_rectangle(x1, y1, x2+1, y2+1, color);

	al_restore_state(&prev);
}


void putpixel(ALLEGRO_BITMAP *target, int x, int y, ALLEGRO_COLOR color)
//void putpixel(b, get_center_int()-(int)camera_x, get_top_edge_int()-(int)camera_y, makecol(100-75, 223-75, 223-75))
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_pixel(x, y, color);

	al_restore_state(&prev);
}


void textprintf_centre(ALLEGRO_BITMAP *target, ALLEGRO_FONT *font, float x, float y, ALLEGRO_COLOR color, std::string text, std::string str2="")
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_textf(font, color, x, y, ALLEGRO_ALIGN_CENTER, text.c_str(), str2.c_str());

	al_restore_state(&prev);
}



void vline(ALLEGRO_BITMAP *target, int x, int y, int y2, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_line(x + 0.5, y+0.5, x + 0.5, y2+0.5, color, 1);

	al_restore_state(&prev);
}


void hline(ALLEGRO_BITMAP *target, int x, int y, int x2, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_line(x + 0.5, y+0.5, x2 + 0.5, y+0.5, color, 1);

	al_restore_state(&prev);
}

void line(ALLEGRO_BITMAP *target, int x, int y, int x2, int y2, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_line(x + 0.5, y+0.5, x2 + 0.5, y2+0.5, color, 1);

	al_restore_state(&prev);
}



void clear_to_color(ALLEGRO_BITMAP *target, ALLEGRO_COLOR color)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_clear_to_color(color);

	al_restore_state(&prev);
}




ALLEGRO_COLOR makecol(unsigned char r, unsigned char g, unsigned char b)
{
	return al_map_rgb(r, g, b);
}



void allegro_message(std::string msg, std::string msg2="")
{
	std::cout << "allegro_message() \"" << msg << "\", \"" << msg2 << "\"" << std::endl;
}



// consequently, any time blit is used in this program, it's equivelent to a flip
void blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *target, int sx, int sy, int dx, int dy, int sw, int sh)
{
	al_flip_display();
}

void masked_blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *target, int sx, int sy, int dx, int dy, int w, int h)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_bitmap_region(source, sx, sy, w, h, dx, dy, 0);

	al_restore_state(&prev);
}


void draw_sprite_FAST(ALLEGRO_BITMAP *src, int x, int y)
{
	al_draw_bitmap(src, x, y, 0);
}



void draw_sprite(ALLEGRO_BITMAP *target, ALLEGRO_BITMAP *src, int x, int y)
{
	ALLEGRO_STATE prev;
	al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(target);

	al_draw_bitmap(src, x, y, 0);

	al_restore_state(&prev);
}


void show_video_bitmap(ALLEGRO_BITMAP *buff)
{
	al_flip_display();
}







using namespace std;

bool no_time_limits = true;
bool no_kills_left = false;
//bool no_one_ups = false;
bool no_killed_em_all = true;
bool no_chain_awards = false;
bool hide_hud = false;
bool F_show_congrats_banner = false;

#define MIN_NUMBER_OF_KILLS_FOR_A_CHAIN 2
#define MIN_NUMBER_OF_SIMULTANIOUS_KILLS 2

//#define YELLOW makecol(255,255,0)

///// program flags
bool F_disable_edits=false;

bool F_draw_map_layer_1=true;
bool F_draw_map_layer_2=true;
bool F_draw_map_layer_3=true;
bool F_draw_boundrys=false;
bool F_debug_mode=false;
bool F_map_maker_mode=false;
bool F_draw_backgrounds=true;

bool blood_censored = false;
bool no_fades_no_rests = true;
void do_logic(void);


ALFONT_FONT *new_font = NULL;

ALLEGRO_BITMAP *poof = NULL;
ALLEGRO_BITMAP *time_bground = NULL;
ALLEGRO_BITMAP *life_icon = NULL;
ALLEGRO_BITMAP *stat_bground = NULL;
ALLEGRO_BITMAP *stat_bground_hearts = NULL;
ALLEGRO_BITMAP *stat_hearts = NULL;
ALLEGRO_BITMAP *clock_icon = NULL;
ALLEGRO_BITMAP *clock_dial = NULL;
ALLEGRO_BITMAP *clock_face_overlay_r = NULL;
ALLEGRO_BITMAP *clock_face_overlay_g = NULL;
ALLEGRO_BITMAP *clock_face_overlay_y = NULL;

#define ADD_ITEM(xx, yy)     ALLEGRO_BITMAP* xx##_img;
#include "item_list.hpp"
#undef ADD_ITEM

ALLEGRO_BITMAP *choose_a_level = NULL;

ALLEGRO_BITMAP *holding_gun = NULL;

ALLEGRO_BITMAP *ready_banner = NULL;
ALLEGRO_BITMAP *go_banner = NULL;
ALLEGRO_BITMAP *paused_banner = NULL;

ALLEGRO_BITMAP *no_bears = NULL;

ALLEGRO_BITMAP *bear1 = NULL;
ALLEGRO_BITMAP *bear2 = NULL;
ALLEGRO_BITMAP *bear3 = NULL;
ALLEGRO_BITMAP *bear4 = NULL;
ALLEGRO_BITMAP *bear_duck = NULL;
ALLEGRO_BITMAP *bear = NULL;
ALLEGRO_BITMAP *bear_climb1 = NULL;
ALLEGRO_BITMAP *bear_climb2 = NULL;
ALLEGRO_BITMAP *bear_in_air = NULL;

ALLEGRO_BITMAP *medal_gold = NULL;
ALLEGRO_BITMAP *medal_silver = NULL;
ALLEGRO_BITMAP *medal_bronze = NULL;

ALLEGRO_BITMAP *bad_bear_pic1 = NULL;
ALLEGRO_BITMAP *bad_bear_pic2 = NULL;
ALLEGRO_BITMAP *bad_bear2_pic1 = NULL;
ALLEGRO_BITMAP *bad_bear2_pic2 = NULL;
ALLEGRO_BITMAP *blue_bear_pic1 = NULL;
ALLEGRO_BITMAP *blue_bear_pic2 = NULL;
ALLEGRO_BITMAP *blue_bear_jump_pic = NULL;
ALLEGRO_BITMAP *purple_bear_pic1 = NULL;
ALLEGRO_BITMAP *purple_bear_pic2 = NULL;

ALLEGRO_SAMPLE *one_up_sample = NULL;
ALLEGRO_SAMPLE *pickup_key_sample = NULL;
ALLEGRO_SAMPLE *use_key_sample = NULL;
ALLEGRO_SAMPLE *pickup_coin_sample = NULL;
ALLEGRO_SAMPLE *door_locked_sample = NULL;
ALLEGRO_SAMPLE *door_open_sample = NULL;
ALLEGRO_SAMPLE *door_close_sample = NULL;

ALLEGRO_BITMAP *sparkle_particle_0 = NULL;
ALLEGRO_BITMAP *sparkle_particle_1 = NULL;
ALLEGRO_BITMAP *sparkle_particle_2 = NULL;
ALLEGRO_BITMAP *sparkle_particle_3 = NULL;

ALLEGRO_SAMPLE *ball_bounce_sample = NULL;


#define ADD_ROCK(x, y) ALLEGRO_SAMPLE* x##y##_sample;
#include "rock_list.hpp"
#undef ADD_ROCK





ALLEGRO_BITMAP *trigger_on = NULL;
ALLEGRO_BITMAP *trigger_off = NULL;


ALLEGRO_SAMPLE *cha_ching = NULL;
ALLEGRO_SAMPLE *jump_sample = NULL;

ALLEGRO_BITMAP *congradulations = NULL;
ALLEGRO_BITMAP *time_up = NULL;

ALLEGRO_BITMAP *title_graphic = NULL;

ALLEGRO_BITMAP *title_options = NULL;
ALLEGRO_BITMAP *title_new_game = NULL;
ALLEGRO_BITMAP *title_load_game = NULL;
ALLEGRO_BITMAP *title_exit = NULL;

ALLEGRO_SAMPLE *menu_move = NULL;
ALLEGRO_SAMPLE *menu_select = NULL;
ALLEGRO_SAMPLE *menu_select2 = NULL;
ALLEGRO_SAMPLE *pause_sample = NULL;
ALLEGRO_SAMPLE *secret_found_sample = NULL;
ALLEGRO_SAMPLE *unpause_sample = NULL;

ALLEGRO_SAMPLE *power_up_sample_heart = NULL;



bool screen_is_black = false;


#define PI 3.14159265f

float get_degrees(float radians)
{
   return (radians * (180 / PI));
}

float get_radians(float degrees)
{
   return (degrees * (PI / 180));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///    SETUP.HPP
//#include "setup.hpp"


#define COLOR_BACKGROUND makecol(212,242,250)
#define EMPTY_BMP                        0        /* BMP  */
#define HELV15                           1        /* FONT */
#define OATUS5                           2        /* FONT */
#define OATUS5_ACC                       3        /* FONT */
#define SMALL7                           4        /* FONT */
#define TEMPO11                          5        /* FONT */
#define TIMES_I_5                        6        /* FONT */
#define X_SMALL                          7        /* FONT */

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define RED makecol(255,0,0)
#define GREEN makecol(0,255,0)
#define BLUE makecol(0,0,255)
#define YELLOW makecol(255, 255, 0)
#define ORANGE makecol(255, 128, 0)
#define VIOLET makecol(128, 0, 128)

#define DGREEN makecol(0, 128, 0)
#define DBLUE makecol(0, 0, 128)

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


#define POWER_UP_BOUNDING_BOX_SIZE  24


char *arg_string;
char buf[256];
char *ptrbuf;

bool page_flipping_on=false;
bool smooth_as_possible=true;
bool abort_game=false;

bool keyboard_available=false;
bool mouse_available=false;
bool joystick_available=false;

//DATAFILE *dat;
FONT *font_med;
FONT *font_small;
FONT *font_x_small;

ALLEGRO_BITMAP *buffer = NULL;
ALLEGRO_BITMAP *page1 = NULL;
ALLEGRO_BITMAP *page2 = NULL;
ALLEGRO_BITMAP *empty = NULL;


ALLEGRO_BITMAP *bullet_img = NULL;

int key_for_button_a = ALLEGRO_KEY_A;
int key_for_button_b = ALLEGRO_KEY_SPACE;
int key_for_button_x = ALLEGRO_KEY_X;
int key_for_button_y = ALLEGRO_KEY_LCTRL;
int key_for_button_up = ALLEGRO_KEY_UP;
int key_for_button_down = ALLEGRO_KEY_DOWN;
int key_for_button_left = ALLEGRO_KEY_LEFT;
int key_for_button_right = ALLEGRO_KEY_RIGHT;

bool button_a_release = false;
bool button_b_release = false;
bool button_x_release = false;
bool button_y_release = false;

bool release_a = false;
bool release_b = false;
bool release_x = false;
bool release_y = false;

void wait_for_press_any_button()
{
    bool get_me_out = false;

    button_a_release = false;
    button_b_release = false;
    button_x_release = false;
    button_y_release = false;

    bool not_pushin_0 = false;
    bool not_pushin_1 = false;
    bool not_pushin_2 = false;
    bool not_pushin_3 = false;

    bool not_pushin_a = false;
    bool not_pushin_b = false;
    bool not_pushin_x = false;
    bool not_pushin_y = false;

    while (!get_me_out)
    {
		poll_keyboard();

      // varify releases
      if (!key[key_for_button_a]) not_pushin_a = true;
      if (!key[key_for_button_b]) not_pushin_b = true;
      if (!key[key_for_button_x]) not_pushin_x = true;
      if (!key[key_for_button_y]) not_pushin_y = true;


      // varify button presses
      if ((key[key_for_button_a] && not_pushin_a)) get_me_out = true;
      if ((key[key_for_button_b] && not_pushin_b)) get_me_out = true;
      if ((key[key_for_button_x] && not_pushin_x)) get_me_out = true;
      if ((key[key_for_button_y] && not_pushin_y)) get_me_out = true;


               poll_joystick();

               int c;
               for (c=0; c<get_joy_num_buttons(); c++)
               {
        	        if (joy[0].button[c])
                    {
                        switch (c)
                        {
                            case 0:
                               if (not_pushin_0) get_me_out = true;
                            break;
                            case 1:
                               if (not_pushin_1) get_me_out = true;
                            break;
                            case 2:
                               if (not_pushin_2) get_me_out = true;
                            break;
                            case 3:
                               if (not_pushin_3) get_me_out = true;
                            break;
                        }
                    }
        	        else if (!joy[0].button[c])
                    {
                        switch (c)
                        {
                            case 0:
                               not_pushin_0 = true;
                            break;
                            case 1:
                               not_pushin_1 = true;
                            break;
                            case 2:
                               not_pushin_2 = true;
                            break;
                            case 3:
                               not_pushin_3 = true;
                            break;
                        }
                    }
               }
    }

    //button_x_release = false;
    //button_y_release = false;

}






//PALETTE screenshot_palette;
ALLEGRO_BITMAP *screenshot;

struct float_coordinate
{
   float x;
   float y;
};
struct int_coordinate
{
   int x;
   int y;
};
float_coordinate coord(float xx, float yy)
{
   float_coordinate f;
   f.x = xx;
   f.y = yy;
   return f;
}
int_coordinate coord(int xx, int yy)
{
   int_coordinate i;
   i.x = xx;
   i.y = yy;
   return i;
}


string make_absolute(string filename)
{
	// takes the filename relative to the executable
	// and produces a full filename

/*
    char name[1024];
    get_executable_name(name, sizeof(name));
    //allegro_message("Running `%s'\n", name);

    string gimp_filename = name;
    int pos = gimp_filename.find_last_of("\\");
    gimp_filename = gimp_filename.substr(0, pos+1);

    filename = gimp_filename + filename;
*/

	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(path, filename.c_str());
	std::string full_filenam = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);
	al_destroy_path(path);


    return full_filenam;
}




const char *full_filename(const char *address)
{
  static std::string buffer;
  buffer = make_absolute(address);
  return buffer.c_str();
    //return replace_filename(buf, arg_string, address, sizeof(buf));
}

ALLEGRO_BITMAP *_load_bitmap(std::string address, void *palette=NULL)
{
    ALLEGRO_BITMAP *b;
    
	//replace_filename(buf, arg_string, address, sizeof(buf));

	//std::string absolute = make_absolute(address).c_str();

    b = al_load_bitmap(address.c_str());
	if (b) al_convert_mask_to_alpha(b, al_map_rgb(255,0, 255));
    //if (!b) allegro_message("%s", address);
    if (!b) std::cout << "could not load \"" << address << "\"" << std::endl;
    return b;
}

#define load_bitmap(x, y) _load_bitmap(x, y)

void destroy_bitmap(ALLEGRO_BITMAP *bitmap)
{
	al_destroy_bitmap(bitmap);
}

/*const char *gimme_a_char(char *format, ...)
{
   char buff[512];

   va_list ap;
   va_start(ap, format);
   uvszprintf(buff, sizeof(buff), format, ap);
   va_end(ap);

   string ret = buff;

   return ret.c_str();   
} 
*/   

/*
string gimme_a_string(char *format, ...)
{
   char buff[512];

   va_list ap;
   va_start(ap, format);
   uvszprintf(buff, sizeof(buff), format, ap);
   va_end(ap);

   string ret = buff;

   return ret;   
} 
*/   

void write_notice(FONT *f, int x, int y, int col, char *format, ...)
{
   char buf[512];

   //va_list ap;
   //va_start(ap, format);
   //uvszprintf(buf, sizeof(buf), format, ap);
   //va_end(ap);

	std::cout << "NOTICE: " << format << std::endl;
//   textprintf(buffer, f, x, y, col, buf);

/*
   if (page_flipping_on) show_video_bitmap(buffer);
   else blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
*/
}




void my_error_message(std::string mess, ...)
{
   //char buf[512];

/*
   va_list ap;
   va_start(ap, mess);
   uvszprintf(buf, sizeof(buf), mess, ap);
   va_end(ap);

     rectfill(screen, SCREEN_W/2-(text_length(font_small, buf) + 40)/2, 100, SCREEN_W/2+(text_length(font_small, buf) + 20)/2, SCREEN_H-100, makecol(64,16,0));
     textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+32,128), buf);
*/
std::cout << "my_error_message(): " << mess << std::endl;
     clear_keybuf();
     readkey();
}


void my_error_message2(std::string mess, ...)
{
   char buf[512];
/*
   va_list ap;
   va_start(ap, mess);
   uvszprintf(buf, sizeof(buf), mess, ap);
   va_end(ap);

     rectfill(screen, SCREEN_W/2-(text_length(font_small, buf) + 40)/2, 100, SCREEN_W/2+(text_length(font_small, buf) + 20)/2, SCREEN_H-100, makecol(64,16,0));
     textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+32,128), buf);
*/
std::cout << "my_error_message2(): " << mess << std::endl;
     clear_keybuf();
     readkey();
}




int ten_mili_seconds = 0;

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// T I M E R S ///////////////////////////////////////////
//////////////////////////////////////////////////////////

/*
volatile int process = 0;			// this is the counter that will increment every x msec.

void process_timer(void)
{
	process++;
} END_OF_FUNCTION (process_timer);

volatile int ten_mili_seconds = 0;			// this is the counter that will increment every x msec.

void seconds_timer(void)
{
	ten_mili_seconds++;
} END_OF_FUNCTION (seconds_timer);

int initialize_timers(void)
{
    ///  TIMERS

	// installs the timer with the incriment variable 'process'

    if (page_flipping_on)
    {
	    int gimp_process_timer = 72;
    	if (smooth_as_possible) gimp_process_timer = 100;

        if (install_int_ex(process_timer, BPS_TO_TIMER(gimp_process_timer)) != 0)
    	{
			printf("unable to initialize timer 1 at 100 bps.\n%s\n", allegro_error);
    	    abort_game = true;
			return 1;
    	}
		LOCK_FUNCTION(process_timer);		//locks the function so not to cause problems while interrupting
		LOCK_VARIABLE(process);			//locks the variable so not to cause problems while interrupting
    }
    else
    {
		if (install_int_ex(process_timer, BPS_TO_TIMER(72)) != 0)
    	{
			printf("unable to initialize timer 1 at 72 bps.\n%s\n", allegro_error);
    	    abort_game = true;
			return 1;
    	}
		LOCK_FUNCTION(process_timer);		//locks the function so not to cause problems while interrupting
		LOCK_VARIABLE(process);			//locks the variable so not to cause problems while interrupting
    }






 	// installs the timer with the incriment variable 'seconds_timer'
	if (install_int_ex(seconds_timer, MSEC_TO_TIMER(10)) != 0)
    {
		printf("unable to initialize timer 2 at 10 msec.\n%s\n", allegro_error);
        abort_game = true;
		return 1;
    }
	LOCK_FUNCTION(seconds_timer);		//locks the function so not to cause problems while interrupting
	LOCK_VARIABLE(ten_mili_seconds);			//locks the variable so not to cause problems while interrupting

    return 0;


}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


int initialize_input_devices(void)
{
	al_install_joystick();
	if (!al_is_joystick_installed()) std::cout << "Joystick not installed" << std::endl;
	else
	{
		joystick_available = true;
		if (al_get_num_joysticks() == 0)
		{
			std::cout << "No joysticks attached.  Expect a crash." << std::endl;
		}
		else
		{
			joystick = al_get_joystick(0);
		}
	}

	al_install_keyboard();
	keyboard_available = true;

	al_install_mouse();
	mouse_available = true;


/*

    // the first thing is to initialise the joystick driver
    if (install_joystick(JOY_TYPE_AUTODETECT) != 0)
    {
       set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
       allegro_message("Error initialising joystick\n%s\n", allegro_error);
       return 1;
    }

    // make sure that we really do have a joystick
    if (!num_joysticks)
    {
       joystick_available = false;
       write_notice(font_small, 10, SCREEN_H-44-14*3, makecol(255-32, 64, 0), "no joystick was found");
       //allegro_message("Cannot find joystick\n");
       //my_error_message2("no joystick");
    }
    else joystick_available = true;

    if (install_keyboard() != 0)
    {
        keyboard_available = false;
        allegro_message("Cannot find keyboard\n");
    }
    else keyboard_available = true;

    install_mouse();
    mouse_available = true;

    if (!keyboard_available && !mouse_available && !joystick_available)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("No form of input available");
        return 1;
    }

    //ALLEGRO_BITMAP *loading_img = _load_bitmap("images/ops/loading.bmp");
    //masked_blit(loading_img, buffer, 0, 0, 10, SCREEN_H-loading_img->h-10, loading_img->w, loading_img->h);

    //if (page_flipping_on) show_video_bitmap(buffer);
    //else blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    //destroy_bitmap(loading_img);
*/
    return 0;
}



	



int initialize_graphics(void)
{
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	font = al_create_builtin_font();

	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W*3, SCREEN_H*3);
	buffer = al_get_backbuffer(display);
	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_scale_transform(&t, 3, 3);
	al_orthographic_transform(&t, 0, 0, -1.0, al_get_bitmap_width(buffer),
                          al_get_bitmap_height(buffer), 1.0);
	al_set_target_bitmap(buffer);
	al_use_projection_transform(&t);

/*
    text_mode(-1);

    set_color_depth(16);

    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_W, SCREEN_H, 0, 0) != 0)
    {
       set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
       allegro_message("Error setting video mode\n%s\n", allegro_error);
       return 1;
    }

	

    if (page_flipping_on)
    {
       page1 = create_video_bitmap(SCREEN_W, SCREEN_H);
       page2 = create_video_bitmap(SCREEN_W, SCREEN_H);
       buffer = page2;

       if (!page1 || !page2)
       {
          allegro_message("unable to allocate video memory.");
          return 1;
       }
    }
    else
    {
        buffer = create_bitmap(SCREEN_W, SCREEN_H);
    }
*/
    clear_to_color(buffer, makecol(0,0,0));
    return 0;
}

int initialize_sound(void)
{
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(32);
	return 0;
/*
    char *argv[1];
    argv[0]="doof";
    // install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, argv[0]) != 0) {
       allegro_message("Error initialising sound system\n%s\n", allegro_error);
       return 1;
    }
*/
    return 0;
}

void show_loading_notice(void)
{
    ALLEGRO_BITMAP *loading_img = _load_bitmap("images/ops/loading.gif");
    masked_blit(loading_img, buffer, 0, 0, 10, SCREEN_H-al_get_bitmap_height(loading_img)-10, al_get_bitmap_width(loading_img), al_get_bitmap_height(loading_img));
    //if (page_flipping_on) show_video_bitmap(buffer);
    //else blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	al_flip_display();
    destroy_bitmap(loading_img);
}

void show_loading_notice__to_screen(void)
{
    ALLEGRO_BITMAP *loading_img = _load_bitmap("images/ops/loading.gif");
    //masked_blit(loading_img, screen, 0, 0, 10, SCREEN_H-al_get_bitmap_height(loading_img)-10, al_get_bitmap_width(loading_img), al_get_bitmap_height(loading_img));
    masked_blit(loading_img, buffer, 0, 0, 10, SCREEN_H-al_get_bitmap_height(loading_img)-10, al_get_bitmap_width(loading_img), al_get_bitmap_height(loading_img));
	al_flip_display();
    destroy_bitmap(loading_img);
}

bool key_shift()
{
    if (key[ALLEGRO_KEY_RSHIFT] || key[ALLEGRO_KEY_LSHIFT]) return true;
    return false;
}    


int load_data(void);

// PREGAME ///////////////////////////////
int initialize(void)
{
	al_init();
   srand(time(NULL));


	ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
	al_destroy_path(resource_path);	


	initialize_graphics();
	show_loading_notice();

	load_data();


	initialize_input_devices();
	


/*
    allegro_init();
    install_timer(); // allegro function
    srand(time(NULL));

    algif_init();

    if (alfont_init() != 0) return 1;
    alfont_text_mode(-1);

    if (initialize_graphics() != 0) return 1;

    show_loading_notice();

    if (load_data() != 0) {abort_game = true; return 1;}


    if (initialize_timers() != 0)
    {
        allegro_message("unable to set timers");
        return 1;
    }    


    if (initialize_input_devices() != 0)
    {
        allegro_message("unable to set input devices");
        return 1;
    }    
*/

/*
    request_refresh_rate(72);

    //int ref_rate = 0;
    int ref_rate = get_refresh_rate();

    if ((ref_rate != 72) && (page_flipping_on == true))
    {
       //allegro_message("alarm!");
       page_flipping_on = false;

       destroy_bitmap(page1);
       destroy_bitmap(page2);
       destroy_bitmap(buffer);

       buffer = create_bitmap(SCREEN_W, SCREEN_H);
       write_notice(font_small, 10, SCREEN_H-44-14*2, makecol(255-32, 64, 0), "refresh rate @ %d - switched to double buffering", ref_rate);
       write_notice(font_small, 10, SCREEN_H-44-14*1, makecol(255-32, 128, 23), "  for best performance, please change your");
       write_notice(font_small, 10, SCREEN_H-44-14*0, makecol(255-32, 128, 23), "  monitor's refresh rate to 72Hz and start again.");
       show_loading_notice();
    }
    else if (!page_flipping_on)
    {
       write_notice(font_small, 10, SCREEN_H-44-14*2, makecol(64, 255-32, 0), "refresh rate @ %d - page flipping failed", ref_rate);
    }
    else
    {
       write_notice(font_small, 10, SCREEN_H-44-14*2, makecol(64, 255-32, 0), "refresh rate @ %d - page flipping available", ref_rate);
    }
*/
    if (initialize_sound() != 0)
    {
        allegro_message("unable to initialze sound");
        return 1;
    }    

/*
    clear_keybuf();
    wait_for_press_any_button();
    clear_keybuf();
*/

//    readkey();
    return 0;
}

void draw_to_buffer();
// buffer flipping
void update_buffer(void);

//////////////////////////////////////////////////////////


int load_data(void)
{
    //char buf[256];
    //replace_filename(buf, arg_string, "dat/data_001.dat", sizeof(buf));
    //dat = load_datafile(buf);
  /*  if (!dat)
    {
        //allegro_message("Error: datafile not found\n");
        clear_to_color(screen, 0);
        textprintf(screen, font, 5, SCREEN_H/2-20, makecol(255,255,255), ": Datafile not found");
        readkey();
        return 1;
    }
	*/



	ALLEGRO_BITMAP *small7 = al_load_bitmap("dat/small7.bmp");
	al_convert_mask_to_alpha(small7, makecol(255, 0, 255));
	int ranges[] = {32, 126};
	font_small = al_grab_font_from_bitmap(small7, 1, ranges);

	ALLEGRO_BITMAP *helv15 = al_load_bitmap("dat/helv15.bmp");
	al_convert_mask_to_alpha(helv15, makecol(255, 0, 255));
	font_med = al_grab_font_from_bitmap(helv15, 1, ranges);

	ALLEGRO_BITMAP *xsmall = al_load_bitmap("dat/xsmall.bmp");
	al_convert_mask_to_alpha(xsmall, makecol(255, 0, 255));
	font_x_small = al_grab_font_from_bitmap(xsmall, 1, ranges);


	//font_med = al_load_bitmap_font("dat/helv15.bmp");//(font *)dat[helv15].dat;
	//font_small = al_load_bitmap_font("dat/small7.bmp");//(FONT *)dat[SMALL7].dat;
	//font_x_small = al_load_bitmap_font("dat/xsmall.bmp");//(FONT *)dat[X_SMALL].dat;
	empty = al_load_bitmap("dat/empty.bmp");//(ALLEGRO_BITMAP *)dat[EMPTY_BMP].dat;



    //replace_filename(buf, arg_string, "images/empty.bmp", sizeof(buf));
    //empty = load_bitmap(buf, NULL);

    if ((!empty) || (!font_med) || (!font_small) || (!font_x_small))
    {
		/*
       clear_to_color(screen, 0);
       textprintf(screen, font, 5, SCREEN_H/2-20, makecol(255,255,255), ": Wrong Datafile");
       readkey();
		*/
		std::cout << "error loading data" << std::endl;
       //my_error_message("cannot find images/empty.bmp");
    }


    return 0;
}

void cleanup(void)
{
   destroy_font(font_med);
   destroy_font(font_small);
   destroy_font(font_x_small);

/*
   destroy_bitmap(buffer);
   destroy_bitmap(page1);
   destroy_bitmap(page2);
   destroy_bitmap(empty);
*/

   //unload_datafile(dat);

   //alfont_exit();
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


bool button_x = false;
bool button_y = false;
bool button_a = false;
bool button_b = false;

bool button_up = false;
bool button_down = false;
bool button_left = false;
bool button_right = false;

//bool release_x = true;
//bool release_y = true;
//bool release_a = true;
//bool release_b = true;

bool release_up = true;
bool release_down = true;
bool release_left = true;
bool release_right = true;


void clear_input()
{
     button_x = false;
     button_y = false;
     button_a = false;
     button_b = false;

     button_up = false;
     button_down = false;
     button_left = false;
     button_right = false;

}


////////////// KEYBOARD INPUT
int check_keyboard()
{
	poll_keyboard();

	if (key[key_for_button_up]) button_up = true;
	if (key[key_for_button_down]) button_down = true;
	if (key[key_for_button_left]) button_left = true;
	if (key[key_for_button_right]) button_right = true;
     
    if (key[key_for_button_a] || key[ALLEGRO_KEY_ENTER] || key[ALLEGRO_KEY_4]) button_a = true;
    if (key[key_for_button_b] || key[ALLEGRO_KEY_2]) button_b = true;
    if (key[key_for_button_x] || key[ALLEGRO_KEY_3]) button_x = true;
    if (key[key_for_button_y] || key[ALLEGRO_KEY_1]) button_y = true;

	if (key_shift() && key[ALLEGRO_KEY_ESCAPE]) abort_game = true;	// press esc to quit

    return 0;
}

////////////// JOYSTICK INPUT
void check_joystick()
{
     poll_joystick();
     int c;

     //for (c=0; c<joy[0].num_buttons; c++)
     for (c=0; c<get_joy_num_buttons(); c++)
     {
	    if (joy[0].button[c])
        {
            switch (c)
            {
                   case 0:
                       button_b = true;
                       break;
                   case 1:
                       button_x = true;
                       break;
                   case 2:
                       button_y = true;
                       break;
                   case 3:
                       button_a = true;
                       break;
            }
        }
     }

     if (joy[0].stick[0].axis[0] < 0) button_left = true;
	 if (joy[0].stick[0].axis[0] > 0) button_right = true;
	 if (joy[0].stick[0].axis[1] < 0) button_up = true;
	 if (joy[0].stick[0].axis[1] > 0) button_down = true;

     if (joy[0].stick[1].axis[0] < 0) button_left = true;
	 if (joy[0].stick[1].axis[0] > 0) button_right = true;
	 if (joy[0].stick[1].axis[1] < 0) button_up = true;
	 if (joy[0].stick[1].axis[1] > 0) button_down = true;

     if (joy[0].stick[2].axis[0] < 0) button_left = true;
	 if (joy[0].stick[2].axis[0] > 0) button_right = true;
	 if (joy[0].stick[2].axis[1] < 0) button_up = true;
	 if (joy[0].stick[2].axis[1] > 0) button_down = true;

     //if (joy[0].stick[0].axis[0].d1) button_left = true;
	 //if (joy[0].stick[0].axis[0].d2) button_right = true;
	 //if (joy[0].stick[0].axis[1].d1) button_up = true;
	 //if (joy[0].stick[0].axis[1].d2) button_down = true;
}

int check_user_input()
{
     if (keyboard_needs_poll()) poll_keyboard();
     if (keyboard_available) check_keyboard();
     if (joystick_available) check_joystick();
     if (mouse_available) poll_mouse();

    if (key[ALLEGRO_KEY_F12]) // f12 takes a screenshot
    {
			take_screenshot("screenshot");
    }

     return 0;
}


void draw_mouse_cursor(ALLEGRO_COLOR col=makecol(255,255,255))
{
     vline(buffer, mouse_x, mouse_y-4, mouse_y+4, col);
     hline(buffer, mouse_x-4, mouse_y, mouse_x+4, col);
}



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// constants

float camera_x;
float camera_y;

int block_type_at(int x, int y);
//int graphic_block_type_at(int x, int y);
int block_left_edge(int horiz);
int block_right_edge(int horiz);
int block_top_edge(int vertic);
int block_bottom_edge(int vertic);
bool is_platform_block(int type);
bool is_ceiling_block(int type);
bool is_right_wall_block(int type);
bool is_left_wall_block(int type);
bool is_passable_platform_block(int type);

int get_on_a_ramp_judge();
//void get_off_a_ramp_judge();

void load_game(void);
void restart_level(void);
int load_level(const char *address);

float point_on_ramp_y(int ramp_index_num, float xx);

int fill_with_boundry(int xx, int yy, int xx2, int yy2, int boundry_tile);

int get_map_width();
int get_map_height();

int get_num_of_ramps();

#define TILE_SIZE 16

#define BOUNDRY_EMPTY 0
#define BOUNDRY_0     BOUNDRY_EMPTY
#define BOUNDRY_1     1
#define BOUNDRY_2     2
#define BOUNDRY_3     3
#define BOUNDRY_4     4
#define BOUNDRY_5     5
#define BOUNDRY_6     6
#define BOUNDRY_7     7
#define BOUNDRY_8     8
#define BOUNDRY_9     9
#define BOUNDRY_10    10
#define BOUNDRY_11    11
#define BOUNDRY_12    12
#define BOUNDRY_13    13
#define BOUNDRY_14    14
#define BOUNDRY_15    15
#define BOUNDRY_16    16


#define BLOCK_EMPTY         0

#define BLOCK_LADDER        17
#define BLOCK_DEATH         18
#define BLOCK_DESTRUCTABLE  19

#define BLOCK_GOAL_1        100


#define BLOCK_SWITCH        200000
#define BLOCK_SWITCH_BLOCK  300000


#define BLOCK_UNLOCK_CAMERA (100000-1)
#define BLOCK_CAMERA 100000


#define BLOCK_SWITCH        200000
#define BLOCK_SWITCH_BLOCK  300000

#define BLOCK_TRIGGER       400000




//#define BLOCK_UNLOCK_CAMERA_X 100001
//#define BLOCK_UNLOCK_CAMERA_Y 100002

//#define BLOCK_LOCK_CAMERA_X 200000
//#define BLOCK_LOCK_CAMERA_Y 300000

//#define BLOCK_CAMERA_MAX_X 400000
//#define BLOCK_CAMERA_MAX_Y 500000
//#define BLOCK_CAMERA_MIN_X 600000
//#define BLOCK_CAMERA_MIN_Y 700000
//
#define BLOCK_DOOR 800000

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define MOVING_UP        8
#define MOVING_DOWN      2
#define MOVING_LEFT      4
#define MOVING_RIGHT     6
#define MOVING_STILL     5

#define ENVIRONMENT_DRAG_AIR 0.0f
#define ENVIRONMENT_DRAG_FLOOR 0.075f   // .075 normal .025f ice
#define ENVIRONMENT_DRAG_ICE 0.000f   // .075 normal .025f ice
#define GRAVITY 0.15f



//////


#define DIRECTORY_TILES "images/tiles/"


float random_float(float min, float max)
{
    return ((float) rand()/RAND_MAX)*(max-min) + min;
}

int random_int(int min, int max)
{
    return rand()%(max-min+1) + min;
}

bool random_bool()
{
    return (rand()%2 == 1);
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int previous_rock_sample_number = 1;
int second_previous_rock_sample_number = 0;
void play_random_rock_sample(int vol, int pan, int freq)
{
    int i = random_int(1, 10);
    while ((i == previous_rock_sample_number) || (i == second_previous_rock_sample_number)) i = random_int(1, 10);

    second_previous_rock_sample_number = previous_rock_sample_number;
    previous_rock_sample_number = i;

    ALLEGRO_SAMPLE *s;

    switch(i)
    {

    #define ADD_ROCK(x, y)    case y:  s = x##y##_sample; break;
    #include "rock_list.hpp"
    #undef ADD_ROCK
        default:
                s = NULL;
                break;


    }

    if (s) play_sample(s, vol, pan, freq, false);
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///    SOUND.HPP
//#include "sound.hpp"


struct splat_sound_struct
{
    ALLEGRO_SAMPLE *sound;
};


int last_played = 0;
int second_to_last_played = 0;
int current_played = 0;


vector<splat_sound_struct> splat;



void play_random_splat_sound()
{
    second_to_last_played = last_played;
    last_played = current_played;
    //current_played = (rand())%(splat.size()-1);

    bool exit_loop = false;
    while (!exit_loop)
    {
        current_played = (rand())%(splat.size());
        if ((current_played != last_played) && (current_played != second_to_last_played)) exit_loop = true;
    }
    play_sample(splat[current_played].sound, 255, 128, 1000, FALSE);
}



int add_splat_sound_to_list(std::string address)
{
    splat_sound_struct gimp_splat_sound_struct;
    
    gimp_splat_sound_struct.sound = load_sample(full_filename(address.c_str()));
    if (!gimp_splat_sound_struct.sound)
    {
		std::stringstream msg;
		msg << "No Sample: " << address;
        //my_error_message2("No Sample: %s", address.c_str());
        my_error_message2(msg.str());
        return -1;
    }    
    
    splat.push_back(gimp_splat_sound_struct);
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



bool start_new_level=false;




#define DRAWING_TO_LAYER_1     9999
#define DRAWING_TO_LAYER_2     9998
#define DRAWING_TO_LAYER_3     9997
#define DRAWING_TO_BOUNDRY     9996
#define DRAWING_TO_ENVIRONMENT 9995

unsigned int drawing_pen_int1 = BOUNDRY_1;
unsigned int drawing_pen_int2 = 0;
unsigned short int drawing_destination = DRAWING_TO_BOUNDRY;
unsigned int pen_from_tile_index = 0;
unsigned int pen_of_boundry = 0;

int current_chain=0;  // the number of bears you killed in the latest chain
int chain_award=0;  // the number of bears you killed in the latest chain
int chain_time_start=0;  // the amount of time you stayed in the air during a chain
int chain_time_finish=0;  //
int chain_award_counter=0;  // the counter that tells you wether or not to display the chain award.
int killed_em_all_counter=0;
int finished_round_counter=0;
int total_enemies_killed=0;

#define FINISHED_ROUND_DURATION 500

int clock_time_suspended_at=0;
bool B_clock_time_suspended=false;

bool first_time_through_fade_in = true;

//ALLEGRO_BITMAP *bg1;
//ALLEGRO_BITMAP *bg2;
//ALLEGRO_BITMAP *bg3;
//ALLEGRO_BITMAP *bg4;

string gimpString;

////////////////////
////////////////////
////////////////////

#define STATE_TITLE_SCREEN -1
#define STATE_WAITING_FOR_LEVEL_START 0
#define STATE_IN_LEVEL 1
#define STATE_FINISH_ROUND 2
#define STATE_PAUSE 3
#define STATE_TIME_UP 4
#define STATE_CHOOSING_LEVEL 5

int game_state = STATE_TITLE_SCREEN;//STATE_WAITING_FOR_LEVEL_START;

int num_of_enemies_left = 0;

int player_score = 0;
int player_lives = 3;
int player_coins = 0;

//int ellapsed_time = 0;

int ellapsed_time = 0;
int time_when_completed = 0;
int time_left_in_round = 0;
int time_to_kill_all_the_bears=-1;
//int level_timer;

void assign_points(int p)
{
    player_score += p;
}


float point_on_a_line_y(int top_x, int top_y, int bottom_x, int bottom_y, float xx)
{
    return ((((float)(top_y - bottom_y))/((float)(top_x - bottom_x))*(xx-bottom_x))+(bottom_y));
}

////////////////////
////////////////////

//char *level_to_start = "Old_Level_3.lev";
#define DEFAULT_BACKGROUND "hill_3.gif"

string title_screen_level = "title_screen_level.lv2";
string level_to_start = title_screen_level;//"levels and maps/Old Level 3.lv2";
//char *level_to_start = "Level_2.lev";

////////////////////

int pre_game_counter=150;
int simultanious_kill=0;
int award_counter=200;
int total_points_in_the_fer=0;


int go_banner_counter=0;



#define ADD_ITEM(xx, yy)    const int xx##_const = yy;
#include "item_list.hpp"
#undef ADD_ITEM



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// HELP MESSAGE
//#include "help_message.hpp"

#define HELP_MESSAGE_DURATION   300


int help_message_counter = 0;
string help_message_text = "";
ALLEGRO_COLOR help_message_color = WHITE;


void start_help_message(string mesg, ALLEGRO_COLOR color=WHITE)
{
    help_message_text = mesg;
    help_message_color = color;
    help_message_counter = HELP_MESSAGE_DURATION;
}    


void draw_help_message()
{
    if (help_message_counter > 0)
    {
        textprintf_centre(buffer, font_small, SCREEN_W/2, SCREEN_H-text_height(font_small)-10, help_message_color, help_message_text.c_str());
    }    
}


void update_help_message()
{
    help_message_counter--;
    if (help_message_counter < 0) help_message_counter = 0;
}    


void clear_help_message()
{
    help_message_text = "";
    help_message_counter = 0;
}        

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// CHANGE LOCKED DOOR GRAPHICS


ALLEGRO_BITMAP *door_normal;
ALLEGRO_BITMAP *door_locked;
ALLEGRO_BITMAP *door_unlocked;
ALLEGRO_BITMAP *door_locked_silver;
ALLEGRO_BITMAP *door_unlocked_silver;
ALLEGRO_BITMAP *door_locked_secret;
ALLEGRO_BITMAP *door_unlocked_secret;
ALLEGRO_BITMAP *door_exit_only;

void load_locked_door_graphics()
{
    door_normal = _load_bitmap("images/doors/door_normal.gif");
    door_locked = _load_bitmap("images/doors/door_locked.gif");
    door_unlocked = _load_bitmap("images/doors/door_unlocked.gif");
    door_locked_silver = _load_bitmap("images/doors/door_locked_silver.gif");
    door_unlocked_silver = _load_bitmap("images/doors/door_unlocked_silver.gif");
    door_locked_secret = _load_bitmap("images/doors/door_locked_secret.gif");
    door_unlocked_secret = _load_bitmap("images/doors/door_unlocked_secret.gif");
    door_exit_only = _load_bitmap("images/doors/door_exit_only.gif");
}

void destroy_locked_door_graphics()
{
    destroy_bitmap(door_normal);
    destroy_bitmap(door_locked);
    destroy_bitmap(door_unlocked);
    destroy_bitmap(door_locked_silver);
    destroy_bitmap(door_unlocked_silver);
    destroy_bitmap(door_locked_secret);
    destroy_bitmap(door_unlocked_secret);
    destroy_bitmap(door_exit_only);
}


#define DOOR_TYPE_NORMAL           1
#define DOOR_TYPE_LOCKED           2
#define DOOR_TYPE_UNLOCKED         3
#define DOOR_TYPE_LOCKED_SILVER    4
#define DOOR_TYPE_UNLOCKED_SILVER  5
#define DOOR_TYPE_LOCKED_SECRET    6
#define DOOR_TYPE_UNLOCKED_SECRET  7
#define DOOR_TYPE_EXIT_ONLY        8




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// LEVEL FILE LIST
//#include "level_file_list.hpp"

#define DIRECTORY_LEVELS_AND_MAPS "levels and maps"
#define DIRECTORY_LEVEL_SNAPSHOTS "images/levels"

ALLEGRO_BITMAP *empty_level_img;

/*
char *path_and_file(const char *directory, const char *filename)
{
    string dir = directory;
    dir.append(filename);
    return replace_filename(buf, arg_string, dir.c_str(), sizeof(buf));
}    
*/


class level_list_item_class
{
public:
    string level_name;
    string file_name;
    ALLEGRO_BITMAP *snapshot;
    
    level_list_item_class()
    {
        level_name = "no name";
        file_name = "no file";
        snapshot = empty_level_img;
    }    
    ~level_list_item_class()
    {
    }    
    int get_snapshot(const char *filename)
    {
        string full_file_name_and_path = "";
        full_file_name_and_path.append(DIRECTORY_LEVELS_AND_MAPS);
        full_file_name_and_path.append("/");
        full_file_name_and_path.append(filename);

        ifstream infile2(full_filename(full_file_name_and_path.c_str()));
        string line_from_file;
        
        if (!infile2)
           {
            infile2.close();
				my_error_message("unable to load file");
            //rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to load level");
            //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), filename);
            readkey();
            return -1;
           }
           
        bool abort_level_input=false;
        bool error = false;   
           
        while ((!infile2.eof()) && (!abort_level_input) && (!error))
        {
           infile2.getline(buf, 256);
           line_from_file = buf;

           if (!line_from_file.empty())
           {
              if (line_from_file.substr(0, 18) == "[////////////////]")
              {
                  abort_level_input = true;
                  error = true;
              }    
              
            //if (line_from_file.substr(0,7) == "title: ")
              else if (line_from_file.substr(0,11) == "levelshot: ")
              {
                  int pos_of_first_par = line_from_file.find_first_of("\"");
                  int pos_of_last_par = line_from_file.find_last_of("\"");
                  string file_name_of_shot;
                  file_name_of_shot = line_from_file.substr(pos_of_first_par+1, pos_of_last_par-(pos_of_first_par+1)); //"whoptie"; //line_from_file.c_str();

                  full_file_name_and_path = "";
                  full_file_name_and_path.append(DIRECTORY_LEVEL_SNAPSHOTS);
                  full_file_name_and_path.append("/");
                  full_file_name_and_path.append(file_name_of_shot);

                  snapshot = _load_bitmap(full_filename(full_file_name_and_path.c_str()), NULL);
                  
                  if (snapshot == NULL)
                  {
                      //allegro_message("could not find level's snapshot\n%s", full_file_name_and_path.c_str());
                      snapshot = empty_level_img;
                      error = true;
                  }    
                  abort_level_input = true;
              }    
           }      
        }    
           
        infile2.close();
        //open file
        //find "levelshot: " 
        // if "[/////////////////]" then abort
        //get shot_file_name
        //see if file is there
        // load picture;
        // close file
        if (error) return -1;
        else return 0;
    }      
    int get_level_name(const char *filename)
    {
        string full_file_name_and_path = "";
        full_file_name_and_path.append(DIRECTORY_LEVELS_AND_MAPS);
        full_file_name_and_path.append("/");
        full_file_name_and_path.append(filename);

        ifstream infile2(full_filename(full_file_name_and_path.c_str()));
        string line_from_file;
        
        if (!infile2)
           {
            infile2.close();
				my_error_message("unable to load file");
            //rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to load level");
            //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), filename);
            readkey();
            return -1;
           }
           
        bool abort_level_input=false;
        bool error = false;   
           
        while ((!infile2.eof()) && (!abort_level_input) && (!error))
        {
           infile2.getline(buf, 256);
           line_from_file = buf;

           if (!line_from_file.empty())
           {
              if (line_from_file.substr(0, 18) == "[////////////////]")
              {
                  abort_level_input = true;
                  error = true;
              }    
              else if (line_from_file.substr(0,7) == "title: ")
              {
                  level_name = line_from_file.substr(7,line_from_file.size()); //"whoptie"; //line_from_file.c_str();
                  abort_level_input = true;
              }    
           }      
        }    
           
        infile2.close();
        if (error) return -1;
        else return 0;
    }    
    int get_info(const char *filename)
    {
        file_name = filename;
        get_level_name(filename);
        get_snapshot(filename);
        //return -1;
        return 0;
    }    
};    


vector<level_list_item_class> level_list;



int add_level_to_list(const char *filename)
{
    if (filename != title_screen_level)
    {
        level_list_item_class llic;
        if (llic.get_info(filename) == -1)
        {
            allegro_message("cannot add level to list: %s", filename);
        }
        else level_list.push_back(llic);
    }
    return 0;
}


/*
void make_level_list()
{
    empty_level_img = load_bitmap(full_filename("images/levels/image_not_available.gif"), NULL);

    al_ffblk found_file;
    string gimp_str;

	std::string pattern = "levels and maps/*.lv2";
    if (al_findfirst(pattern, &found_file, FA_RDONLY | FA_ARCH) != 0)
    //if (al_findfirst(path_and_file(DIRECTORY_LEVELS_AND_MAPS, "/*.lv2"), &found_file, FA_RDONLY | FA_ARCH) != 0)
    {
        textprintf(screen, font, 20, 40, RED, "No level files were found");
        clear_keybuf();
        readkey();
        clear_keybuf();
    }
    else
    {
        gimp_str = found_file.name;
        add_level_to_list(gimp_str.c_str());

        while (al_findnext(&found_file) == 0)
        {
            gimp_str = found_file.name;
            add_level_to_list(gimp_str.c_str());
        }

    }
    al_findclose(&found_file);
}
*/


void destroy_level_list()
{
    for (int k=level_list.size()-1; k>=0; k--)
    {
        if (level_list[k].snapshot != empty_level_img) destroy_bitmap(level_list[k].snapshot);
        level_list.pop_back();
    }    
    
    destroy_bitmap(empty_level_img);
    
}    
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



#define JEWEL_TYPE(xx)    ALLEGRO_BITMAP* xx##_1; ALLEGRO_BITMAP* xx##_2; ALLEGRO_BITMAP* xx##_3;
#include "jewel_list.hpp"
#undef JEWEL_TYPE



void load_jewel_shimmers()
{  
#define JEWEL_TYPE(xx)    xx##_1 = _load_bitmap("images/items/" #xx "_1.gif"); \
                           xx##_2 = _load_bitmap("images/items/" #xx "_2.gif"); \
                           xx##_3 = _load_bitmap("images/items/" #xx "_3.gif");
#include "jewel_list.hpp"
#undef JEWEL_TYPE
}

void destroy_jewel_shimmers()
{
#define JEWEL_TYPE(xx)    destroy_bitmap(xx##_1); \
                          destroy_bitmap(xx##_2); \
                          destroy_bitmap(xx##_3);
#include "jewel_list.hpp"
#undef JEWEL_TYPE
}



bool is_a_jewel(int item_type)
{
#define JEWEL_TYPE(xx)    if (item_type == xx##_const) return true;
#include "jewel_list.hpp"
#undef JEWEL_TYPE
    return false;
}


float jewel_shimmer_x = 0.0f;
float jewel_shimmer_y = 0.0f;
float jewel_padding = 20.0f;
float jewel_shimmer_spacing = SCREEN_W*1.5f;

void update_jewel_shimmer()
{
    jewel_shimmer_spacing = SCREEN_W*1.5f;

    jewel_shimmer_x += 3;
    jewel_shimmer_y += 0.6f;

    while (jewel_shimmer_x > jewel_shimmer_spacing) jewel_shimmer_x -= jewel_shimmer_spacing;
    while (jewel_shimmer_y > jewel_shimmer_spacing) jewel_shimmer_y -= jewel_shimmer_spacing;
}

bool within_x_range(float x, float xx1, float xx2, float padding=0.0f)
{
    if (x+padding < xx1) return false;
    if (x-padding > xx2) return false;
    return true;
}


void draw_jewel_centered(int item_type, float map_x, float map_y)
{
     float x_spot = map_x;
     float y_spot = map_y;

     while (x_spot > jewel_shimmer_spacing) x_spot -= jewel_shimmer_spacing;
     while (y_spot > jewel_shimmer_spacing) y_spot -= jewel_shimmer_spacing;

     ALLEGRO_BITMAP *b;

     switch (item_type)
     {
#define JEWEL_TYPE(xx)    case xx##_const: \
    if (within_x_range(x_spot, jewel_shimmer_x+jewel_padding*0, jewel_shimmer_x+jewel_padding*1, 0)) b = xx##_1;  \
    else if (within_x_range(x_spot, jewel_shimmer_x+jewel_padding*1, jewel_shimmer_x+jewel_padding*2, 0)) b = xx##_2;  \
    else if (within_x_range(x_spot, jewel_shimmer_x+jewel_padding*2, jewel_shimmer_x+jewel_padding*3, 0)) b = xx##_3;  \
    else b = xx##_img;   \
    break;

#include "jewel_list.hpp"
#undef JEWEL_TYPE
     }



     if (b) draw_sprite(buffer, b, (int)map_x-al_get_bitmap_width(b)/2-(int)camera_x, (int)map_y-al_get_bitmap_height(b)/2-(int)camera_y);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool is_trigger_block(int tile_num);
void attempt_to_turn_on_trigger(int trigger_num);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//#include "sprites.hpp"
#define TERMINAL_VELOCITY 6 //TILE_SIZE

#define DEFAULT_MAX_WALK_SPEED         2.0f
#define DEFAULT_MAX_RUN_SPEED          3.0f
#define DEFAULT_ACCEL_RATE             0.15f
#define DEFAULT_JUMP_VELOCITY          4.5f


class character_class
{
public: // this it's high security bank software!!

    float_coordinate map_pos;   // character's location on the current map.
    int_coordinate size;         // character's width and height
    float_coordinate velocity;    // character's velocity

    // speed and drag variables
    float walk_max_speed;   // the maximum walking speed the character can move while walking
    float run_max_speed;    // the maximum speed the character can move while running
    float max_speed;        // the current maximum speed
    float max_climb_speed;
    float jump_velocity;    // the initial force of the jump
    float variable_jump_velocity_decay;   // if you release the jump button before
                                          // the peak of the jump, this value ditermines
                                          // how much velocity you will loose
    float accel_rate;        // how fast the character speeds up when walking or running
    float environment_drag;
    float air_drag;
    float floor_drag;

    // state variables

    bool is_ducking;

    bool has_gun;
    int gun_ammo;

    bool facing_right;      // if the character is facing right
    bool on_ground;         // if the character is on the ground
                               // used for gravity and jumping
    bool released_jump;     // if the character has released his jump
    int on_ramp;           // if the character is on a ramp
    int on_ladder;
    int moving_direction;   // the direction the character is trying to move

    // energy stuff
    float energy;       // the current ammount of energy.. shouldn't be more than max_energy
    int max_energy;     // the maximum energy the player can have.

    // animation
    int anim_counter;
    int anim_rate;

    //bool post_pain;
    int post_pain_counter;
    int bounce_from_pain;

    bool player_alive;

    float strength;
    
    int keys;
    int silver_keys;

    int refire_delay;

    /// functions
    /////////////////////

    character_class(void)
    {
        init();
    }

    void init(void)
    {
        map_pos.x = 20.0f;
        map_pos.y = 20.0f;
        size.x = 14;
        size.y = 37;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        
        keys = 0;
        silver_keys = 0;

        walk_max_speed = DEFAULT_MAX_WALK_SPEED;
        run_max_speed = DEFAULT_MAX_RUN_SPEED; // 3.0f
        max_speed = walk_max_speed;
        max_climb_speed = 1.5f;
        jump_velocity = DEFAULT_JUMP_VELOCITY;
        variable_jump_velocity_decay = 0.15f;
        accel_rate = DEFAULT_ACCEL_RATE;  //0.75f - on crack!   //0.15f normal  // on ice = 0.05f;
        floor_drag = ENVIRONMENT_DRAG_FLOOR;
        air_drag = ENVIRONMENT_DRAG_AIR;
        environment_drag = 0.0f;

        facing_right = true;
        on_ground = false;
        released_jump = true;
        is_ducking = false;

        on_ramp = -1;
        on_ladder = false;
        moving_direction = MOVING_STILL;

        strength = 1.0f;
        energy = 30.0f;
        max_energy = 30;
        anim_counter = 0;
        anim_rate = 0;

        has_gun = false;
        gun_ammo = 0;

        //post_pain = false;
        post_pain_counter = 0;    // 50
        player_alive = true;
        bounce_from_pain = true;

        refire_delay = 0;
    }

    void reset_for_new_level()
    {
//        map_pos.x = 20.0f;
//        map_pos.y = 20.0f;
//        size.x = 14;
//        size.y = 37;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        
        keys = 0;
        silver_keys = 0;

        walk_max_speed = DEFAULT_MAX_WALK_SPEED;
        run_max_speed = DEFAULT_MAX_RUN_SPEED; // 3.0f
        max_speed = walk_max_speed;
        max_climb_speed = 1.5f;
        jump_velocity = DEFAULT_JUMP_VELOCITY;
        variable_jump_velocity_decay = 0.15f;
        accel_rate = DEFAULT_ACCEL_RATE;  //0.75f - on crack!   //0.15f normal  // on ice = 0.05f;
        floor_drag = ENVIRONMENT_DRAG_FLOOR;
        air_drag = ENVIRONMENT_DRAG_AIR;
        environment_drag = 0.0f;

        facing_right = true;
        on_ground = false;
        released_jump = true;
        is_ducking = false;

        on_ramp = -1;
        on_ladder = false;
        moving_direction = MOVING_STILL;

        strength = 1.0f;
        energy = 30.0f;
        max_energy = 30;
        anim_counter = 0;
        anim_rate = 0;

        has_gun = false;
        gun_ammo = 0;

        //post_pain = false;
        post_pain_counter = 0;    // 50
        player_alive = true;
        bounce_from_pain = true;

        refire_delay = 0;
    }


    // find points
    float get_right_edge() {return map_pos.x+size.x;}
    float get_left_edge() {return map_pos.x;}
    float get_top_edge() {return map_pos.y;}
    float get_bottom_edge() {return map_pos.y+size.y;}
    float get_middle() {return map_pos.y+(size.y/2);}
    float get_center() {return map_pos.x+(size.x/2);}
    int get_right_edge_int() {return (int)(map_pos.x+size.x);}
    int get_left_edge_int() {return (int)(map_pos.x);}
    int get_top_edge_int() {return (int)(map_pos.y);}
    int get_bottom_edge_int() {return (int)(map_pos.y+size.y);}
    int get_middle_int() {return (int)(map_pos.y+(size.y/2));}
    int get_center_int() {return (int)(map_pos.x+(size.x/2));}

    // set points
    void set_right_edge(float f) {map_pos.x = f-size.x;}
    void set_left_edge(float f) {map_pos.x = f;}
    void set_top_edge(float f) {map_pos.y = f;}
    void set_bottom_edge(float f) {map_pos.y = f-size.y;}
    void set_center(float f) {map_pos.x = f-(size.x/2);}

    // pushing functions
    void push_horizontal(float f) {velocity.x += f;}
    void push_vertical(float f) {velocity.y += f;}
    void update_environment_drag()
    {
        if (!on_ground) environment_drag = air_drag;
        else environment_drag = air_drag+floor_drag;
    }
    void update_horizontal_velocity(void)
    {
        if (velocity.x > 0.0f)
        {
           velocity.x -= environment_drag;
           if (velocity.x < 0.0f) velocity.x = 0;
        }
        else if (velocity.x < 0.0f)
        {
           velocity.x += environment_drag;
           if (velocity.x > 0.0f) velocity.x = 0;
        }
    }
    void update_vertical_velocity(void)
    {
        if (!on_ground && !on_ladder)
        {
           if (!(velocity.y > TERMINAL_VELOCITY))
           {
               velocity.y += GRAVITY;
           }
           else velocity.y -= environment_drag;
        }
    }

    // character movements
    void run(void) {
        max_speed = run_max_speed;
        }
    void walk(void) {
        max_speed = walk_max_speed;
        }
    void duck(void)
        {
        if (!is_ducking) {size.y = 37-12; map_pos.y+=12;}
        is_ducking = true;
        }
    void stand(void)
        {
        if (is_ducking) {size.y += 12; map_pos.y-=12;}
        is_ducking = false;
        }
    int move_right(void) {
        moving_direction = MOVING_RIGHT;
        facing_right = true;
	return 0;
        }
    int move_left(void) {
        moving_direction = MOVING_LEFT;
        facing_right = false;
	return 0;
        }
    void move_nowhere(void) {
        moving_direction = MOVING_STILL;
        }
    void jump(void)
    {
       if (on_ground && (released_jump == true))
       {
          push_vertical(jump_velocity*(-1));
          on_ground = false;
/////
          get_off_ramp();
          released_jump = false;
       }
    }
    void jump_off_ladder(void)
    {
        on_ladder = false;
        push_vertical(jump_velocity*(-1));
        on_ground = false;
        released_jump = false;
        //map_pos.x = on_ladder - size.x/2;
        //velocity.x = 0.0f;
        //velocity.y = 0.0f;
    }

    void put_on_running_shoes()
    {
        walk_max_speed = DEFAULT_MAX_RUN_SPEED + 0.5f;
        run_max_speed = walk_max_speed + 1.0f;
        accel_rate = DEFAULT_ACCEL_RATE * 1.5f;
    }

    void take_off_running_shoes()
    {
        walk_max_speed = DEFAULT_MAX_WALK_SPEED;
        run_max_speed = DEFAULT_MAX_RUN_SPEED; // 3.0f
        accel_rate = DEFAULT_ACCEL_RATE;
    }

    void pickup_gun()
    {
        has_gun = true;
    }

    void put_on_jumping_shoes()
    {
        jump_velocity = DEFAULT_JUMP_VELOCITY*1.5f;
    }

    void take_off_jumping_shoes()
    {
        jump_velocity = DEFAULT_JUMP_VELOCITY;
    }

    void get_on_ladder(int l)
    {
        on_ladder = l;
        map_pos.x = on_ladder - size.x/2;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        bear = bear_climb1;
    }
    void get_off_ladder()
    {
        on_ladder = false;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }
    void release_jump(void)
    {
       if (velocity.y < 0.0f) push_vertical(variable_jump_velocity_decay);
       if (on_ground) released_jump = true;
    }
    int get_on_ramp(int ramp_index) // max_num_of_ramps = current_map.ramp.size();
    {
       if (ramp_index < 0) return 1;

       velocity.y = 0.0f;
       on_ramp = ramp_index;
       on_ground = true;
       return 0;
    }
    void get_off_ramp()
    {
       on_ramp = -1;
    }
    float take_and_react_to_damage(float damage)
    {
        energy -= damage;
        if (post_pain_counter == 0)
        {
            post_pain_counter = 70;
        }
        if (bounce_from_pain)
        {
            if (facing_right) velocity.x = -2.0f;
            else velocity.x = 2.0f;
        }
        return energy;
    }
    float energy_up(float e)
    {
        energy += e;
        if (energy >= max_energy) energy = max_energy;
        
        return energy;   
    }    
    bool at_platform()
    {
        int dur=0;
        for (dur=0; dur<size.x+1; dur++)
        {
            if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y)+size.y+1)))
            return true;
        }
        return FALSE;
    }

    // don't go off the map
    void prevent_from_going_off_map()
    {
        if (map_pos.x <= 0)
        {
            map_pos.x = 0;
            velocity.x = 0;
        }
        if (get_right_edge() >= ((get_map_width()*TILE_SIZE)-1))
        {
            set_right_edge((get_map_width()*TILE_SIZE)-1);
            velocity.x = 0;
        }
    }

    bool ditect_collision(int x1, int y1, int x2, int y2)
    {
        if ((map_pos.x > x2) == true) return FALSE;
        if ((map_pos.x+size.x < x1) == true) return FALSE;
        if ((map_pos.y+size.y < y1) == true) return FALSE;
        if ((map_pos.y > y2) == true) return FALSE;
        else return true;
    }

    bool ditect_collision_center(int x1, int y1, int x2, int y2)
    {
        if (get_center_int() > x2) return false;
        if (get_center_int() < x1) return false;
        if (map_pos.y+size.y < y1) return false;
        if (map_pos.y > y2) return false;
        else return true;
    }

    bool ditect_collision_center_post_v(int x1, int y1, int x2, int y2)
    {
        if (get_center_int()+velocity.x > x2) return false;
        if (get_center_int()+velocity.x < x1) return false;
        if (map_pos.y+size.y+velocity.y < y1) return false;
        if (map_pos.y+velocity.y > y2) return false;
        else return true;
    }

    int pickup_key()
    {
        keys++;
        return keys;
    }

    int pickup_silver_key()
    {
        silver_keys++;
        return keys;
    }
    
    int use_key()
    {
        keys--;
        if (keys < 0) {keys=0; return -1;}
        return keys;
    }   

    int use_silver_key()
    {
        silver_keys--;
        if (silver_keys < 0) {silver_keys=0; return -1;}
        return silver_keys;
    }

    int get_keys()
    {
        return keys;
    }     

    int get_silver_keys()
    {
        return silver_keys;
    }


    // map collision detections
    int test_map_collision_vertical()
    {
        // return values:
        // 0; no collision
        // 1: collided with a floor
        // 2: collided with a ceiling
        // 3: at the end of a ladder

        #define TRIGGER_Y_OFFSET  6

        if (velocity.y > 0.0f) // falling
        {
            bool char_collides_next = false;
            bool char_collides_now = false;
            int dur=0;
            while(dur<size.x)
            {
                if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y+velocity.y)+size.y+1)))
                {
                    char_collides_next = true;
                }
                if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y)+size.y)))
                {
                    char_collides_now = true;
                }

                dur++;
            }
            if (on_ladder)
            {
                if (block_type_at(get_center_int(), (int)(get_bottom_edge()+velocity.y+1)) == BLOCK_LADDER)
                {
                    char_collides_next=false;
                }
            }

            if (((!char_collides_now) && (char_collides_next)))
            {

                int pos_to_set_to = block_top_edge(((int)(map_pos.y+velocity.y+TILE_SIZE/2)+size.y+1)/TILE_SIZE) - (size.y) - 1;

                int block_player_lands_on_left = block_type_at((int)get_left_edge(), (((int)(map_pos.y+velocity.y+TILE_SIZE/2)+size.y+1+3)));
                int block_player_lands_on_center = block_type_at(get_center_int(), (((int)(map_pos.y+velocity.y+TILE_SIZE/2)+size.y+1+3)));
                int block_player_lands_on_middle = block_type_at((int)get_right_edge(), (((int)(map_pos.y+velocity.y+TILE_SIZE/2)+size.y+1+3)));

                if (is_trigger_block(block_player_lands_on_left) || is_trigger_block(block_player_lands_on_center) || is_trigger_block(block_player_lands_on_middle))
                {
                    attempt_to_turn_on_trigger(block_player_lands_on_left - BLOCK_TRIGGER);
                    attempt_to_turn_on_trigger(block_player_lands_on_center - BLOCK_TRIGGER);
                    attempt_to_turn_on_trigger(block_player_lands_on_middle - BLOCK_TRIGGER);
                    //attempt_to_turn_on_trigger(3);
                    //pos_to_set_to -= TRIGGER_Y_OFFSET;
                }

                map_pos.y = pos_to_set_to;
                on_ground = true;
                velocity.y = 0.0f;
                return 1;
            }
        }
        else if (velocity.y < 0.0f) // jumping (or moving up)
        {
            int dur=0;
            while(dur<size.x)
            {
                if (is_ceiling_block(block_type_at((int)(map_pos.x+1)+dur, (int)(map_pos.y+velocity.y))))
                {
                    if (on_ladder && ((block_type_at(get_center_int(), (int)(map_pos.y+velocity.y)-1) == BLOCK_LADDER)))
                    {
                        dur = size.x+1;
                        //if (block_type_at(get_center_int(), (int)(map_pos.y+velocity.y)-1) == BLOCK_LADDER)
                    }
                    else
                    {
                        dur = size.x+1;
                        velocity.y = 0.0f;
                        map_pos.y = block_bottom_edge(((int)(map_pos.y+velocity.y-TILE_SIZE/2)-1)/TILE_SIZE);
                        return 2;
                    }
                }
                else dur++;
            }
            if (on_ladder)
            {
                if (block_type_at(get_center_int(), (int)(get_middle()+velocity.y)) != BLOCK_LADDER)
                {
                    velocity.y = 0.0f;
                    return 3;
                }
            }
        }
        else if (on_ramp != -1)
        {
            bool going_down_on_ramp = false;
            bool going_up_on_ramp = false;  // not doin this one yet
            float point_to_test_y = point_on_ramp_y(on_ramp, get_center_int());

            if (velocity.x < 0.0f)
            {
                going_down_on_ramp = true;
            }

            if (going_down_on_ramp)
            {
                bool char_collides_next = false;
                //bool char_collides_now = false;
                int dur=0;
                while(dur<size.x)
                {
                    if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(point_to_test_y))))
                    {
                        char_collides_next = true;
                        dur = size.x;
                    }
                    dur++;
                }

                if (char_collides_next)
                {
                    //my_error_message("yup");
                    int pos_to_set_to=block_top_edge(((int)(map_pos.y+velocity.y+TILE_SIZE/2)+size.y+1)/TILE_SIZE) - (size.y) - 1;
                    map_pos.y = pos_to_set_to;
                    on_ground = true;
                    velocity.y = 0.0f;
                    on_ramp = -1;
                    return 1;
                }
             }
             else if (going_up_on_ramp)
             {
                int dur=0;
                while(dur<size.x)
                {
                    if (is_ceiling_block(block_type_at((int)(map_pos.x+1)+dur, (int)(map_pos.y+velocity.y))))
                    {
                        if (on_ladder && ((block_type_at(get_center_int(), (int)(map_pos.y+velocity.y)-1) == BLOCK_LADDER)))
                        {
                            dur = size.x+1;
                            //if (block_type_at(get_center_int(), (int)(map_pos.y+velocity.y)-1) == BLOCK_LADDER)
                        }
                        else
                        {
                            dur = size.x+1;
                            velocity.y = 0.0f;
                            map_pos.y = block_bottom_edge(((int)(map_pos.y+velocity.y-TILE_SIZE/2)-1)/TILE_SIZE);
                            return 2;
                        }
                    }
                    else dur++;
                }
             }
        }
        return 0;
    }
    int test_map_collision_horizontal()
    {
        // return values:
        // 0: no collision
        // 1: collided at the left side of the player
        // 2: collided at the right side of the player

        if (velocity.x > 0.0f)
        {
            int dur=0;
            while(dur<size.y)
            {
                if (is_right_wall_block(block_type_at((int)(map_pos.x+velocity.x)+size.x+1, (int)(map_pos.y)+dur)))
                {
                    dur = size.y+1;
                    velocity.x = 0.0f;
                    map_pos.x = block_left_edge(((int)(map_pos.x+velocity.x+TILE_SIZE/2)+size.x+1)/TILE_SIZE) - (size.x) -1;
                    return 1;
                }
                else dur+=16;
                if (dur > size.y)
                {
                    if (is_right_wall_block(block_type_at((int)(map_pos.x+velocity.x)+size.x+1, (int)(map_pos.y)+size.y)))
                    {
                        dur = size.y+1;
                        velocity.x = 0.0f;
                        map_pos.x = block_left_edge(((int)(map_pos.x+velocity.x+TILE_SIZE/2)+size.x+1)/TILE_SIZE) - (size.x) -1;
                        return 1;
                    }
                }
            }
        }
        else if (velocity.x < 0.0f)
        {
            int dur=0;
            while(dur<size.y)
            {
                if (is_left_wall_block(block_type_at((int)(map_pos.x+velocity.x)-1, (int)(map_pos.y)+dur)))
                {
                    dur = size.y+1;
                    velocity.x = 0.0f;
                    map_pos.x = block_right_edge(((int)(map_pos.x+velocity.x-TILE_SIZE/2)-1)/TILE_SIZE);// + 1;
                    return 2;
                }
                else dur+=16;
                if (dur > size.y)
                {
                    if (is_left_wall_block(block_type_at((int)(map_pos.x+velocity.x)-1, (int)(map_pos.y)+size.y)))
                    {
                        dur = size.y+1;
                        velocity.x = 0.0f;
                        map_pos.x = block_right_edge(((int)(map_pos.x+velocity.x-TILE_SIZE/2)-1)/TILE_SIZE);// + 1;
                        return 2;
                    }
                }
            }
        }
        return 0;
    } // end test_map_collision_horizontal()

    void update_velocity_from_player_movement()
    {
        if (!is_ducking || !on_ground)
        {
            switch (moving_direction)
            {
                case MOVING_RIGHT:
                     if (velocity.x >= max_speed)
                     {

                     }
                     else
                     {
                         push_horizontal(accel_rate);
                         if (velocity.x > max_speed) velocity.x = max_speed;
                     }
                     break;
                     /////////////////////////////////////
                case MOVING_LEFT:
                     if (velocity.x <= max_speed*(-1))
                     {

                     }
                     else
                     {
                         push_horizontal(accel_rate*(-1));
                         if (velocity.x < max_speed*(-1)) velocity.x = max_speed*(-1);
                     }
                     break;
            }
        }
    }

    bool ramp_test()
    {
        int bypass_block_collisions = false;
        if (on_ramp != -1)
        {
            //bypass_block_collisions = true;
            //on_ground=true;
            //map_pos.x += velocity.x;
            //set_bottom_edge(point_on_ramp_y(on_ramp, get_center_int()));
        }
        return bypass_block_collisions;
    }


    bool test_on_death_block()
    {
         if (((block_type_at(get_center_int(), get_middle_int()) == BLOCK_DEATH)))
         {
            return true;
         }

         return false;
    }

    ////////////
    void update_pos(void)
    {
        update_environment_drag();
        update_vertical_velocity();
        update_horizontal_velocity();





        update_velocity_from_player_movement();
        // get_off_a_ramp_judge();



        //if (ramp_test() == false)
        //{

        test_map_collision_horizontal();
        map_pos.x += velocity.x;

        int vert_return_val = test_map_collision_vertical();

        get_on_a_ramp_judge();

        if ((velocity.y == 0.0f) && (on_ramp == -1))
        {
            if (at_platform()) {
                if (!on_ladder) on_ground = true;
                //environment_drag = FLOOR_STONE_DRAG + AIR_DRAG;
            }
            else {
                on_ground = false;
                //environment_drag = AIR_DRAG;
            }
        }
        else if (on_ramp != -1)
        {
            on_ground = true;
        }

        if (on_ramp != -1)
        {
           if ((vert_return_val == 1) || (vert_return_val == 2));
           else set_bottom_edge(point_on_ramp_y(on_ramp, get_center_int()));
        }
        else map_pos.y += velocity.y;
        //}

        if (test_on_death_block() == true)
        {
            energy = 0;
            player_alive = false;
        }

        prevent_from_going_off_map();
    }

    void update_state(void)
    {
        update_pos();
        if (post_pain_counter > 0) post_pain_counter--;
    }



    ////////////
    void draw_bounding_box(ALLEGRO_BITMAP *b = buffer)
    {
			
        rect(b, get_left_edge_int()-(int)camera_x, get_top_edge_int()-(int)camera_y, get_right_edge_int()-(int)camera_x, get_bottom_edge_int()-(int)camera_y, makecol(125, 255, 255));
        if (facing_right) textprintf_centre(b, font_med, get_center_int()-(int)camera_x, get_middle_int()-(text_height(font_med)/2)-2-(int)camera_y, makecol(125, 255, 255), ">>");
        else textprintf_centre(b, font_med, get_center_int()-(int)camera_x, get_middle_int()-(text_height(font_med)/2)-2-(int)camera_y, makecol(125, 255, 255), "<<");
        putpixel(b, get_center_int()-(int)camera_x, get_top_edge_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
        putpixel(b, get_center_int()-(int)camera_x, get_bottom_edge_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
        putpixel(b, get_left_edge_int()-(int)camera_x, get_middle_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
        putpixel(b, get_right_edge_int()-(int)camera_x, get_middle_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
    }
};

character_class player;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class power_up_class
{
public:
    float_coordinate map_pos;   // character's location on the current map.
    int_coordinate size;         // character's width and height
    float_coordinate velocity;    // character's velocity

    bool on_ground;

    int energy;
    int time;
    bool boom;


};

////////////////////////////////////////////////////////////////////////////////


bool is_switch_stick(int tile_num);
void play_switch_sound();
void swap_switch_stick(int index_num);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



class enemy_class
{
public:
    float_coordinate map_pos;
    int_coordinate size;
    float_coordinate velocity;

    float max_velocity;
    bool facing_right;
    bool on_ramp;
    float energy;
    float strength;

    float jump_force;

    int anim_counter;
    int anim_rate;

    ALLEGRO_BITMAP *gimp_pic;
    ALLEGRO_BITMAP *pic;
    ALLEGRO_BITMAP *jump_pic;

    bool on_ground;
    bool will_walk_off_edge;
    bool will_jump_off_edge;
    float jump_x_velocity_boost;

    bool can_be_jumped_on;

    int post_pain_counter;
    float bounce_from_pain;
    int points;

    int on_switch_stick;

    void init()
    {
        map_pos.x=20.0f;
        map_pos.y=20.0f;
        size.x=14;
        size.y=28;
        velocity.x=0.0f;
        velocity.y=0.0f;

        max_velocity=1.5f;
        facing_right=false;
        on_ramp=false;
        energy=1;

        will_walk_off_edge=true;
        will_jump_off_edge=false;
        jump_x_velocity_boost = 0.0f;

        anim_counter=0;
        anim_rate=15;
        strength = 5;

        can_be_jumped_on = true;
        post_pain_counter = 0;
        bounce_from_pain = 0.0f;
        points = 250;

        jump_force = 0.0f;

        pic = bad_bear_pic1;
        jump_pic = NULL;

        on_switch_stick = -1;
    }

    void make_yellow_bear()
    {
        size.x=14;
        size.y=28;
        max_velocity=0.5f;
        facing_right=false;
        on_ramp=false;
        energy=1;

        will_walk_off_edge=false;
        will_jump_off_edge=false;
        jump_x_velocity_boost = 0.0f;

        anim_rate=18;
        anim_counter= (rand() & anim_rate-1);
        strength = 5;

        can_be_jumped_on = true;
        post_pain_counter = 0;
        bounce_from_pain = 0.0f;
        points = 250;

        jump_force = 0.0f;

        pic = bad_bear_pic1;
        jump_pic = NULL;
    }

    void make_blue_bear()
    {
        size.x=12;
        size.y=35;
        max_velocity=1.0f;
        facing_right=false;
        on_ramp=false;
        energy=1;

        will_walk_off_edge=false;
        will_jump_off_edge=true;
        jump_x_velocity_boost = 2.0f;

        anim_rate=18-4;
        anim_counter= (rand() & anim_rate-1);
        strength = 5;

        can_be_jumped_on = true;
        post_pain_counter = 0;
        bounce_from_pain = 0.0f;
        points = 250;

        jump_force = 3.75f;

        pic = blue_bear_pic1;
        jump_pic = blue_bear_jump_pic;
    }

    void make_red_bear()
    {
        max_velocity=1.5f;
        facing_right=false;
        size.x=12;
        size.y=24;
        on_ramp=false;
        energy=2;

        will_walk_off_edge=true;
        will_jump_off_edge=false;
        jump_x_velocity_boost = 0.0f;

        anim_counter=0;
        anim_rate=7;
        strength = 5;

        can_be_jumped_on = true;
        post_pain_counter = 0;
        bounce_from_pain = 0.0f;
        points = 500;

        jump_force = 4.0f;

        pic = bad_bear2_pic1;
        jump_pic = NULL;
    }

    void make_purple_bear()
    {
        max_velocity=1.8f;
        facing_right=false;
        size.x=12;
        size.y=20;
        on_ramp=false;
        energy=2;

        will_walk_off_edge=false;
        will_jump_off_edge=false;
        jump_x_velocity_boost = 0.0f;

        anim_counter=0;
        anim_rate=7;
        strength = 5;

        can_be_jumped_on = true;
        post_pain_counter = 0;
        bounce_from_pain = 0.0f;
        points = 500;

        pic = purple_bear_pic1;
        jump_pic = NULL;
    }

    void turn_around()
    {
        if (!facing_right) facing_right = true;
        else if (facing_right) facing_right = false;
    }
    void set_map_pos(int x, int y)
    {
        map_pos.x = x;
        map_pos.y = y;
    }
    void jump(float x_boost=0.0f)
    {
        if (on_ground || on_ramp)
        {
           if (velocity.x < 0) velocity.x -= x_boost;
           else if (velocity.x > 0) velocity.x += x_boost;
           velocity.y -= jump_force;
           on_ground = false;
           on_ramp = false;
           if (jump_pic) { gimp_pic = pic; pic = jump_pic; }
        }
    }

    bool alive()
    {
        if (energy <= 0) return false;
        else return true;
    }
    bool dead()
    {
        if (energy > 0) return false;
        else return true;
    }

    // find points
    float get_right_edge() {return map_pos.x+size.x;}
    float get_left_edge() {return map_pos.x;}
    float get_top_edge() {return map_pos.y;}
    float get_bottom_edge() {return map_pos.y+size.y;}
    float get_middle() {return map_pos.y+(size.y/2);}
    float get_center() {return map_pos.x+(size.x/2);}
    int get_right_edge_int() {return (int)(map_pos.x+size.x);}
    int get_left_edge_int() {return (int)(map_pos.x);}
    int get_top_edge_int() {return (int)(map_pos.y);}
    int get_bottom_edge_int() {return (int)(map_pos.y+size.y);}
    int get_middle_int() {return (int)(map_pos.y+(size.y/2));}
    int get_center_int() {return (int)(map_pos.x+(size.x/2));}

    // set points
    void set_right_edge(float f) {map_pos.x = f-size.x;}
    void set_left_edge(float f) {map_pos.x = f;}
    void set_top_edge(float f) {map_pos.y = f;}
    void set_bottom_edge(float f) {map_pos.y = f-size.y;}

    void update_vertical_velocity(void)
    {
        if (!on_ground) velocity.y += GRAVITY;
    }

    float take_and_react_to_damage(float damage)
    {
        energy -= damage;
        if (post_pain_counter == 0)
        {
            post_pain_counter = 50;
        }
        if (bounce_from_pain != 0.0f)
        {
            if (facing_right) velocity.x = bounce_from_pain*(-1);
            else velocity.x = bounce_from_pain;
        }
        return energy;
    }

    bool at_platform()
    {
        int dur=-1;
        for (dur=-1; dur<size.x+1; dur++)
        {
            if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y)+size.y+1)))
            return true;
        }
        return FALSE;
    }

    bool at_platform_post_velocity()
    {
        int dur=-1;
        for (dur=-1; dur<size.x+1; dur++)
        {
            if (is_platform_block(block_type_at((int)(map_pos.x+velocity.x)+dur, (int)(map_pos.y)+size.y+1)))
            return true;
        }
        return FALSE;
    }

    bool at_platform_right_edge()
    {
       if (is_platform_block(block_type_at((int)(map_pos.x)+size.x, (int)(map_pos.y)+size.y+1)))
       return true;
       else return false;
    }

    bool at_platform_left_edge()
    {
       if (is_platform_block(block_type_at((int)(map_pos.x), (int)(map_pos.y)+size.y+1)))
       return true;
       else return false;
    }

    // don't go off the map
    void prevent_from_going_off_map()
    {
        if (map_pos.x <= 0)
        {
            map_pos.x = 0;
            velocity.x = 0;
            turn_around();

        }
        if (get_right_edge() >= ((get_map_width()*TILE_SIZE)-1))
        {
            set_right_edge((get_map_width()*TILE_SIZE)-1);
            velocity.x = 0;
            turn_around();
        }
    }
    // map collision detections
    void test_map_collision_vertical()
    {
        if (velocity.y > 0.0f) // falling
        {
            bool char_collides_next = false;
            bool char_collides_now = false;
            int dur=-1;
            while(dur<size.x+1)
            {
                if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y+velocity.y)+size.y+1)))
                {
                    char_collides_next = true;
                }
                if (is_platform_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y)+size.y)))
                {
                    char_collides_now = true;
                }
                dur++;
            }
            if ((!char_collides_now) && (char_collides_next))
            {
                velocity.y = 0.0f;
                map_pos.y = block_top_edge(((int)(map_pos.y+velocity.y+8)+size.y+1)/16) - (size.y) - 1;
                if (pic == jump_pic) pic = gimp_pic;
                on_ground = true;
            }
        }
        else if (velocity.y < 0.0f) // jumping
        {
            int dur=-1;
            while(dur<size.x+1)
            {
                if (is_ceiling_block(block_type_at((int)(map_pos.x)+dur, (int)(map_pos.y+velocity.y)-1)))
                {
                    dur = size.x+1;
                    velocity.y = 0.0f;
                    map_pos.y = block_bottom_edge(((int)(map_pos.y+velocity.y-8)-1)/16) + 1;
                }
                else dur++;
            }
        }
    }

    //bool set_over_switch(int switch_index_num) { on_switch_stick = switch_index_num; }

    bool check_switch_behind_enemy()
    {
        bool good_to_go = false;
        int switch_num = -1;

        int block_behind_player = block_type_at(get_center_int(), get_middle_int()+16+16);
        int block_below_block_behind_player = block_type_at(get_center_int(), get_middle_int()+16);

        //my_error_message2("got here %d, %d", block_behind_player, block_below_block_behind_player);

        if (is_switch_stick(block_behind_player)) { good_to_go = true; switch_num = block_behind_player-BLOCK_SWITCH; }
        if (is_switch_stick(block_below_block_behind_player)) { good_to_go = true; switch_num = block_below_block_behind_player-BLOCK_SWITCH; }

        if (good_to_go)
        {
            if (switch_num != on_switch_stick)
            {
               on_switch_stick = switch_num;
               play_switch_sound();

               swap_switch_stick(switch_num);
            }
        }
        else
        {
            on_switch_stick = -1;
        }
	return good_to_go;
    }


    void test_map_collision_horizontal()
    {
        if (velocity.x > 0.0f)
        {
            int dur=-1;
            while(dur<size.y+1)
            {
                if (is_right_wall_block(block_type_at((int)(map_pos.x+velocity.x)+size.x+1, (int)(map_pos.y)+dur)))
                {
                    dur = size.y+1;
                    velocity.x = 0.0f;
                    map_pos.x = block_left_edge(((int)(map_pos.x+velocity.x+8)+size.x+1)/16) - (size.x) - 1;
                    facing_right = false;
                    //turn_around();
                }
                else dur+=16;
                if (dur > size.y)
                {
                    if (is_right_wall_block(block_type_at((int)(map_pos.x+velocity.x)+size.x+1, (int)(map_pos.y)+size.y)))
                    {
                        dur = size.y+1;
                        velocity.x = 0.0f;
                        map_pos.x = block_left_edge(((int)(map_pos.x+velocity.x+8)+size.x+1)/16) - (size.x) - 1;
                        facing_right = false;
                        //turn_around();
                    }
                }
            }
        }
        else if (velocity.x < 0.0f)
        {
            int dur=-1;
            while(dur<size.y+1)
            {
                if (is_left_wall_block(block_type_at((int)(map_pos.x+velocity.x)-1, (int)(map_pos.y)+dur)))
                {
                    dur = size.y+1;
                    velocity.x = 0.0f;
                    map_pos.x = block_right_edge(((int)(map_pos.x+velocity.x-8)-1)/16) + 1;
                    turn_around();
                }
                else dur+=16;
                if (dur > size.y)
                {
                    if (is_left_wall_block(block_type_at((int)(map_pos.x+velocity.x)-1, (int)(map_pos.y)+size.y)))
                    {
                        dur = size.y+1;
                        velocity.x = 0.0f;
                        map_pos.x = block_right_edge(((int)(map_pos.x+velocity.x-8)-1)/16) + 1;
                        turn_around();
                    }
                }
            }
        }
    } // end test_map_collision_horizontal()

    void test_if_will_fall_off(void)
    {
        if (on_ground)
        {
           if (facing_right)
           {
               if (!at_platform_right_edge())
               {
                   if (will_jump_off_edge) jump(jump_x_velocity_boost);
                   else turn_around();
               }
           }
           else
           {
               if (!at_platform_left_edge())
               {
                   if (will_jump_off_edge) jump(jump_x_velocity_boost);
                   else turn_around();
               }
           }
        }
    }
    ////////////

    #define DRAG 0.2f
    void update_pos(void)
    {
        //#define DRAG 0.02f

        //update_environment_drag();
        update_vertical_velocity();
        //update_horizontal_velocity();

        if (facing_right)
        {
           if ((on_ground) && (velocity.x > max_velocity)) velocity.x = max_velocity;
           else if (!on_ground) { } // do nothing
           else if (velocity.x < max_velocity) velocity.x = max_velocity;
        }
        else
        {
           if ((on_ground) && (velocity.x < max_velocity*(-1))) velocity.x = max_velocity*(-1);
           else if (!on_ground) { } // do nothing
           else if (velocity.x > max_velocity*(-1)) velocity.x = max_velocity*(-1);
        //   velocity.x = max_velocity*(-1);
        }

        if (velocity.y == 0.0f)
        {
            if (at_platform()) {
                on_ground = true;
                //environment_drag = FLOOR_STONE_DRAG + AIR_DRAG;
            }
            else {
                on_ground = false;
                //environment_drag = AIR_DRAG;
            }
        }

        test_map_collision_vertical();
        map_pos.y += velocity.y;
        test_map_collision_horizontal();
        if (!will_walk_off_edge) test_if_will_fall_off();
        map_pos.x += velocity.x;

        prevent_from_going_off_map();

        check_switch_behind_enemy();
    }

    void update_state(void)
    {
        update_pos();
        if (post_pain_counter > 0) post_pain_counter--;
    }


    ////////////
    void draw_bounding_box(ALLEGRO_BITMAP *b = buffer)
    {
        rect(b, get_left_edge_int()-(int)camera_x, get_top_edge_int()-(int)camera_y, get_right_edge_int()-(int)camera_x, get_bottom_edge_int()-(int)camera_y, makecol(125, 255, 255));
        if (facing_right) textprintf_centre(b, font_med, get_center_int()-(int)camera_x, get_middle_int()-(text_height(font_med)/2)-2-(int)camera_y, makecol(125, 255, 255), ">>");
        else textprintf_centre(b, font_med, get_center_int()-(int)camera_x, get_middle_int()-(text_height(font_med)/2)-2-(int)camera_y, makecol(125, 255, 255), "<<");
        putpixel(b, get_center_int()-(int)camera_x, get_top_edge_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
        putpixel(b, get_center_int()-(int)camera_x, get_bottom_edge_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
        putpixel(b, get_left_edge_int()-(int)camera_x, get_middle_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
        putpixel(b, get_right_edge_int()-(int)camera_x, get_middle_int()-(int)camera_y, makecol(100-75, 223-75, 223-75));
    }
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include "map.hpp"

int BIATHCHWHHEHCKS;

#define DIRECTORY_BACKGROUNDS "images/backgrounds/"


void load_map_graphics(void);

struct map_tile_struct
{
    unsigned short int layer[3];
    unsigned int boundry;
    unsigned short int environment;
};

struct tile_refrence_struct
{
    int index_num;
    char *address;
};


#define SECRET_SOLUTION_NONE             0
#define SECRET_SOLUTION_KILL_BEARS       1
#define SECRET_SOLUTION_COLLECT_JEWELS   2
#define SECRET_SOLUTION_TRIGGER_ALL      3
#define SECRET_SOLUTION_TRIGGER_ORDERED  4
#define SECRET_SOLUTION_FER_OF           1000
#define SECRET_SOLUTION_CHAIN_OF         2000


struct door_struct
{
    int index_num;       // the index number of the door (this is the number used for the block in the map
    int type;
    int go_to_new_map;
    std::string map_address;   // the address of the map that needs to be loaded
    int map_spawn_x;
    int map_spawn_y;

    int solution;   // a type of solution for opening a secret door

    float camera_x;
    float camera_y;
    float camera_lock_x;
    float camera_lock_y;
    float camera_min_x;
    float camera_max_x;
    float camera_min_y;
    float camera_max_y;
};

struct camera_struct
{
     int index_num;

     float x;
     float y;

     float lock_x;
     float lock_y;
     float min_x;
     float max_x;
     float min_y;
     float max_y;
};



class ramp_class
{
public:
    int index_num;
    int bottom_x;
    int bottom_y;
    int top_x;
    int top_y;

    ramp_class()
    {
        index_num = -1;
        bottom_x=-1;
        bottom_y=-1;
        top_x=-1;
        top_y=-1;
    }
    int get_left_edge()
    {
       if (get_up_going_right()) return (bottom_x*TILE_SIZE);
       else return (top_x*TILE_SIZE);
    }
    int get_right_edge()
    {
       if (get_up_going_right()) return ((top_x*TILE_SIZE)+TILE_SIZE-1);
       else return (bottom_x*TILE_SIZE)+TILE_SIZE-1;
    }

    // this is always set from the bottom, (x,y) to the top (x2,y2)
    void set_ramp(int x, int y, int x2, int y2)
    {
        if (x < 0) x=0;
        if (y < 0) y=0;
        if (x2 < 0) x2=0;
        if (y2 < 0) y2=0;

        if (x==x2) x2++;

        bottom_x=x;
        bottom_y=y;
        top_x=x2;
        top_y=y2;
    }
    bool get_up_going_right()
    {
        if (bottom_x > top_x) return false;
        else return true;
    }
    bool get_down_going_right()
    {
        if (bottom_x < top_x) return false;
        else return true;
    }
    int get_top_map_x()
    {
        if (get_up_going_right()) return (top_x*TILE_SIZE)+TILE_SIZE-1;
        else return (top_x*TILE_SIZE);
    }
    int get_top_map_y()
    {
        //if (get_up_going_right()) return (top_y*16);
        return (top_y*TILE_SIZE);
    }
    int get_bottom_map_x()
    {
        if (get_up_going_right()) return (bottom_x*TILE_SIZE);
        else return (bottom_x*TILE_SIZE)+TILE_SIZE-1;
    }
    int get_bottom_map_y()
    {
        //if (get_up_going_right()) return (bottom_y*16)+16;
        return (bottom_y*TILE_SIZE)+TILE_SIZE-1;
    }

};

//door_struct door;


struct background_struct
{
    string img_filename;
    ALLEGRO_BITMAP *img;
    int index_num;
    
    bool loop_x;
    bool loop_y;    
    int x_offset;
    int y_offset;
    float x_speed;
    float y_speed;
    float x_disp;    // this one gets incremented with the speed;
    float y_disp;    // and this one too;
    
    float scroll_rate;
};    

void make_door_for_map_to_map()
{
    //fill_with_boundry(34,14,35,16, BLOCK_DOOR+3);
}

void make_door_for_map_to_map2()
{
    //fill_with_boundry(53,9,54,11, BLOCK_DOOR+2);
}



#define MAX_MAP_WIDTH 400
#define MAX_MAP_HEIGHT 300

#define EMPTY                      0

#define PARAMS                     1
#define TILE_INDEX                 2
#define GRAPHICS_LAYER_1           3
#define GRAPHICS_LAYER_2           4
#define GRAPHICS_LAYER_3           5
#define ENEMIES_DUR                6
#define BOUNDRYS                   7
#define ENVIRONMENT                8
#define CAMERA                     9
#define RAMP                       10
#define BACKGROUND                 11

#define ABORT                      99999

// in the game, there are several layers...
// 1. background layers.. any number of multiple scrolling background layers;
// 2. map.tile.layer[0]
// 3. map.tile.layer[1]
// 4. enemies
// 5. effects: blood, poofs, etc
// 6. map.tile.layer[2]
// 7. hud


struct destructable_block_struct
{
    std::string block_address;
    std::string shard_1_address;
	 std::string shard_2_address;
    std::string shard_3_address;
};



class map_class
{
public:
    string title;
    int_coordinate size;
    unsigned int time_limit;
    map_tile_struct tile[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];

    vector<tile_refrence_struct> tile_index;
    destructable_block_struct destructable_tiles;
    std::string switch_block_address;

    int locked_door_index_num;
    int_coordinate spawn;

    int_coordinate camera_start;
    float_coordinate camera_max;
    float_coordinate camera_min;
    float_coordinate camera_lock;

    vector<camera_struct> cam;
    vector<ramp_class> ramp;
    ALLEGRO_COLOR background_color;
    bool start_facing_right;
    vector<background_struct> background;

    float center()
    {
        return (float)(size.x * TILE_SIZE) / 2;
    }
    float middle()
    {
        return (float)(size.y * TILE_SIZE) / 2;
    }

    map_class()
    {
        clear();
    }
    ~map_class() {}

    void clear()
    {
        title = "Empty Map";
        size.x = 20;
        size.y = 15;
        spawn.x = 48;
        spawn.y = 48;

        camera_start.x = 0;
        camera_start.y = 0;
        camera_lock.x = -1;
        camera_lock.y = -1;
        camera_max.x = -1;
        camera_max.y = -1;
        camera_min.x = -1;
        camera_min.y = -1;

        time_limit=99999;
        
        background_color = BLACK;
        start_facing_right = true;


        locked_door_index_num = 1;

        //add_default_background();

        int h=0;
        int k=0;
        for (h=0; h<MAX_MAP_WIDTH; h++)
        {
            for (k=0; k<MAX_MAP_HEIGHT; k++)
            {
                 tile[h][k].layer[0] = EMPTY;
                 tile[h][k].layer[1] = EMPTY;
                 tile[h][k].layer[2] = EMPTY;
                 tile[h][k].boundry = EMPTY;
                 tile[h][k].environment = EMPTY;
            }
        }
        for (k=tile_index.size()-1; k>=0; k--) tile_index.pop_back();
        for (k=background.size()-1; k>=0; k--) {destroy_bitmap(background[k].img); background.pop_back();}
        for (k=cam.size()-1; k>=0; k--) cam.pop_back();
        for (k=ramp.size()-1; k>=0; k--) ramp.pop_back();

        destructable_tiles.block_address = "images/tiles/stone_broken.bmp";
        destructable_tiles.shard_1_address = "images/tiles/stone_shard_1.bmp";
        destructable_tiles.shard_2_address = "images/tiles/stone_shard_2.bmp";
        destructable_tiles.shard_3_address = "images/tiles/stone_shard_3.bmp";

        switch_block_address = "images/tiles/stone12.bmp";
    } // end clear

    int num_of_tiles()
    {
        return tile_index.size();
    }

    int get_num_of_ramps()
    {
        return ramp.size();
    }

    void add_empty_camera()
    {
        camera_struct gimp_camera_struct;

        gimp_camera_struct.index_num = -1;
        gimp_camera_struct.lock_x = -1;
        gimp_camera_struct.lock_y = -1;
        gimp_camera_struct.max_x = -1;
        gimp_camera_struct.max_y = -1;
        gimp_camera_struct.min_x = -1;
        gimp_camera_struct.min_y = -1;

        cam.push_back(gimp_camera_struct);
    }

    void add_empty_ramp()
    {
        ramp_class gimp_ramp_class;
        
        gimp_ramp_class.index_num = -1;
        
        ramp.push_back(gimp_ramp_class);
    }
    
    void add_background(std::string img_filename=DEFAULT_BACKGROUND, bool loop_x=true, bool loop_y=false, int x_offset=0, int y_offset=0, float scroll_rate=0.75f, float x_speed=0.0f, float y_speed=0.0f, int index_num=1)
    {
        string img_and_directory;
        img_and_directory = DIRECTORY_BACKGROUNDS;
        img_and_directory.append(img_filename);
        
        background_struct gimp_background_struct;
        gimp_background_struct.img_filename = img_filename;
        gimp_background_struct.img = load_bitmap(full_filename(img_and_directory.c_str()), NULL);
        gimp_background_struct.loop_x = loop_x;
        gimp_background_struct.loop_y = loop_y;
        gimp_background_struct.x_offset = x_offset;
        gimp_background_struct.y_offset = y_offset;
        gimp_background_struct.x_speed = x_speed;
        gimp_background_struct.y_speed = y_speed;
        gimp_background_struct.x_disp = 0.0f;
        gimp_background_struct.y_disp = 0.0f;
        gimp_background_struct.scroll_rate = scroll_rate;
        gimp_background_struct.index_num = -1;
        background.push_back(gimp_background_struct);
    }    

    void add_empty_background(std::string img_filename=DEFAULT_BACKGROUND, bool loop_x=true, bool loop_y=false, int x_offset=0, int y_offset=0, float scroll_rate=0.75f, float x_speed=0.0f, float y_speed=0.0f, int index_num=1)
    {
        string img_and_directory;
        img_and_directory = "images/backgrounds/";
        img_and_directory.append(img_filename);
        
        background_struct gimp_background_struct;
        gimp_background_struct.img_filename = img_filename;
        gimp_background_struct.img = load_bitmap(full_filename(img_and_directory.c_str()), NULL);
        gimp_background_struct.loop_x = loop_x;
        gimp_background_struct.loop_y = loop_y;
        gimp_background_struct.x_offset = x_offset;
        gimp_background_struct.y_offset = y_offset;
        gimp_background_struct.x_speed = x_speed;
        gimp_background_struct.y_speed = y_speed;
        gimp_background_struct.x_disp = 0.0f;
        gimp_background_struct.y_disp = 0.0f;
        gimp_background_struct.scroll_rate = scroll_rate;
        gimp_background_struct.index_num = -1;
        background.push_back(gimp_background_struct);
    }    

    void update_backgrounds()
    {
        for (int k=0; k<background.size(); k++)
        {
            background[k].x_disp += background[k].x_speed;
            background[k].y_disp += background[k].y_speed;
            //background[k].x_disp = background[k].x_disp % (float)background[k].img->w;
            //background[k].y_disp = background[k].x_disp % (float)background[k].img->h;
        }    
    }    

    int load(const char *filename, int map_num_to_load=1)
    {

        //ptrbuf = full_filename(filename);
        ifstream infile(full_filename(filename));
        string line_from_file;

        if (!infile)
           {
				my_error_message("unable to load map, cannot find .lv2 file");
            //rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to load map, cannot find .lv2 file", filename);
            //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", filename);
            readkey();
            return 1;
           }

        unsigned int data_input_mode = 0;
        int h=0;
        int k=0;
        int gimpInt=0;
        clear();
        // interpret map file
        
        bool abort_map_input = false;

        int dummy_camera_index_num = 0;
        int current_camera_index_num = false;

        int dummy_ramp_index_num = 0;
        int current_ramp_index_num = false;

        int dummy_bg_index_num = 0;
        int current_bg_index_num = false;
                
        bool load_up_the_dang_map = false;
        //const char *looking_for_this_string = gimme_a_char("[map %d]", map_num_to_load);

        int str_length = 7; // 7 if it's a single digit map num         
        if (map_num_to_load > 9999) str_length = 11;
        if (map_num_to_load > 999) str_length = 10;
        if (map_num_to_load > 99) str_length = 9;
        else if (map_num_to_load > 9) str_length = 8;


        // find the beginning of the map in the .lv2 file
        //allegro_message("here");
        
        int num_of_found_map=-1;
        while ((!infile.eof()) && (!load_up_the_dang_map))
        {
           infile.getline(buf, 256);
           line_from_file = buf;

           //char what_we_want_it_to_say[512];
           
           //allegro_message(line_from_file.c_str());

           if (!line_from_file.empty())
           {
					std::stringstream ss;
					ss << "[map " << map_num_to_load << "]";
               if (line_from_file == ss.str())
               {
                   load_up_the_dang_map = true;


                   }
                   }
       }
    
        //allegro_message("ever get here??");
        
        if (infile.eof())
        {
            abort_map_input = true;
            //allegro_error("level segment (map) not found in/n%s", filename);
            allegro_message("map.hpp: map not found in lv2 file\n%s", filename);
        }                       


        while ((!infile.eof()) && (!abort_map_input))
        {
           infile.getline(buf, 256);
           line_from_file = buf;

           if (!line_from_file.empty())
           {
              if (line_from_file.substr(0, 18) == "[////////////////]")
              {
                  data_input_mode = ABORT;
                  abort_map_input = true;
              }    
              if (line_from_file.substr(0,8) == "[params]") data_input_mode = PARAMS;
              else if (line_from_file.substr(0,12) == "[tile_index]")
                  {data_input_mode = TILE_INDEX; infile.getline(buf, 256); line_from_file = buf;}
              else if (line_from_file.substr(0,9) == "[enemies]") data_input_mode = ENEMIES_DUR;
              else if (line_from_file.substr(0,8) == "[layer1]") data_input_mode = GRAPHICS_LAYER_1;
              else if (line_from_file.substr(0,8) == "[layer2]") data_input_mode = GRAPHICS_LAYER_2;
              else if (line_from_file.substr(0,8) == "[layer3]") data_input_mode = GRAPHICS_LAYER_3;
              else if (line_from_file.substr(0,11) == "[boundrys]") data_input_mode = BOUNDRYS;
              else if (line_from_file.substr(0,13) == "[environment]") data_input_mode = ENVIRONMENT;
              else if (line_from_file.substr(0,8) == "[camera ")
                   {
                       data_input_mode = CAMERA;

                      dummy_camera_index_num = atoi(line_from_file.substr(8,line_from_file.size()-1).c_str());
                      //data_input_mode = LEVEL_FILE_INPUT DOOR_INDEX;
                      current_camera_index_num = false;
                      infile.getline(buf, 256);
                      line_from_file = buf;

                   }
              else if (line_from_file.substr(0,6) == "[ramp ")
                   {
                      data_input_mode = RAMP;

                      dummy_ramp_index_num = atoi(line_from_file.substr(6,line_from_file.size()-1).c_str());
                      //data_input_mode = LEVEL_FILE_INPUT DOOR_INDEX;
                      current_ramp_index_num = false;
                      infile.getline(buf, 256);
                      line_from_file = buf;

                   }
              else if (line_from_file.substr(0,12) == "[background ")
                   {
                       data_input_mode = BACKGROUND;
                       
                       dummy_bg_index_num = atoi(line_from_file.substr(12,line_from_file.size()-1).c_str());
                       current_bg_index_num = false;
                       
                       infile.getline(buf, 256);
                       line_from_file = buf;
                   }    
              switch (data_input_mode)
              {
                  case PARAMS:
                      if (line_from_file.substr(0,12) == "time limit: ") time_limit = atoi(line_from_file.substr(12,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,7) == "title: ") title = line_from_file.substr(7,line_from_file.size()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,8) == "height: ") size.y = atoi(line_from_file.substr(8,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,7) == "width: ") size.x = atoi(line_from_file.substr(7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,9) == "spawn x: ") spawn.x = atoi(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,9) == "spawn y: ") spawn.y = atoi(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,16) == "camera start x: ") camera_start.x = atoi(line_from_file.substr(16,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,16) == "camera start y: ") camera_start.y = atoi(line_from_file.substr(16,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,15) == "camera lock x: ") camera_lock.x = atof(line_from_file.substr(15,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,15) == "camera lock y: ") camera_lock.y = atof(line_from_file.substr(15,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,14) == "camera max x: ") camera_max.x = atof(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,14) == "camera max y: ") camera_max.y = atof(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,14) == "camera min x: ") camera_min.x = atof(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,14) == "camera min y: ") camera_min.y = atof(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,10) == "bg color: ")
                      {
                          int rr = 0;
                          int gg = 0;
                          int bb = 0;

                          string bg_color_string = line_from_file.substr(10,line_from_file.size()); //"whoptie"; //line_from_file.c_str();
                          int location_of_first_comma = bg_color_string.find_first_of(",");
                          int location_of_last_comma = bg_color_string.find_last_of(",");
                          
                          rr = atoi(bg_color_string.substr(0,location_of_first_comma).c_str());
                          gg = atoi(bg_color_string.substr(location_of_first_comma+1,location_of_last_comma).c_str());
                          bb = atoi(bg_color_string.substr(location_of_last_comma+1,bg_color_string.size()).c_str());
                          
                          //allegro_message("%s", bg_color_string.c_str());
                          //allegro_message("rr=%d, gg=%d, bb=%d", rr, gg, bb);
                         
                          background_color = makecol(rr,gg,bb);
                      }
                  break;
                  case GRAPHICS_LAYER_1:
                      for (k=0; k<size.y; k++)
                      {
                          for (h=0; h<size.x; h++)
                          {
                               infile >> gimpInt;
                               tile[h][k].layer[0] = gimpInt;
                               //clear_to_color(screen, 0);
                               //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), "(%d, %d) %d", h, k, gimpInt);
                          }
                      }
                      data_input_mode = 0;
                  break;
                  case GRAPHICS_LAYER_2:
                      for (k=0; k<size.y; k++)
                      {
                          for (h=0; h<size.x; h++)
                          {
                              infile >> gimpInt;
                              tile[h][k].layer[1] = gimpInt;
                              //clear_to_color(screen, 0);
                              //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), "(%d, %d) %d", h, k, gimpInt);
                          }
                      }
                      data_input_mode = 0;
                  break;
                  case GRAPHICS_LAYER_3:
                      for (k=0; k<size.y; k++)
                      {
                          for (h=0; h<size.x; h++)
                          {
                              infile >> gimpInt;
                              tile[h][k].layer[2] = gimpInt;
                              //clear_to_color(screen, 0);
                              //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), "(%d, %d) %d", h, k, gimpInt);
                          }
                      }
                      data_input_mode = 0;
                  break;
                  case BOUNDRYS:
                      for (k=0; k<size.y; k++)
                      {
                          for (h=0; h<size.x; h++)
                          {
                              infile >> gimpInt;
                              tile[h][k].boundry = gimpInt;
                              //clear_to_color(screen, 0);
                              //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), "(%d, %d) %d", h, k, gimpInt);
                          }
                      }
                      data_input_mode = 0;
                  break;
                  case ENVIRONMENT:
                      for (k=0; k<size.y; k++)
                      {
                          for (h=0; h<size.x; h++)
                          {
                              infile >> gimpInt;
                              tile[h][k].environment = gimpInt;
                              //clear_to_color(screen, 0);
                              //textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), "(%d, %d) %d", h, k, gimpInt);
                          }
                      }
                      data_input_mode = 0;
                 break;
                 case TILE_INDEX:
                      if (!line_from_file.empty())
                      {
                         int location_of_first_space = line_from_file.find_first_of(" ");
                         int location_of_first_quote = line_from_file.find_first_of("\"");
                         int location_of_last_quote = line_from_file.find_last_of("\"");
                         string string_inside_quotes = line_from_file.substr(location_of_first_quote+1, location_of_last_quote-(location_of_first_quote+1));

                         if (line_from_file.substr(0,22) == "destructable shard 1: ")
                         {
                             string stupid_string = "images/tiles/" + string_inside_quotes;
                             //destructable_tiles.shard_1_address = strdup(stupid_string.c_str());
                             destructable_tiles.shard_1_address = (stupid_string.c_str());
                         }
                         else if (line_from_file.substr(0,22) == "destructable shard 2: ")
                         {
                             string stupid_string = "images/tiles/" + string_inside_quotes;
                             //destructable_tiles.shard_2_address = strdup(stupid_string.c_str());
                             destructable_tiles.shard_2_address = (stupid_string.c_str());
                         }
                         else if (line_from_file.substr(0,22) == "destructable shard 3: ")
                         {
                             string stupid_string = "images/tiles/" + string_inside_quotes;
                             //destructable_tiles.shard_3_address = strdup(stupid_string.c_str());
                             destructable_tiles.shard_3_address = (stupid_string.c_str());
                         }
                         else if (line_from_file.substr(0, 14) == "destructable: ")
                         {
                             string stupid_string = "images/tiles/" + string_inside_quotes;
                             //destructable_tiles.block_address = strdup(stupid_string.c_str());
                             destructable_tiles.block_address = (stupid_string.c_str());
                         }
                         else if (line_from_file.substr(0, 8) == "switch: ")
                         {
                             string stupid_string = "images/tiles/" + string_inside_quotes;
                             //switch_block_address = strdup(stupid_string.c_str());
                             switch_block_address = (stupid_string.c_str());
                         }


                         else
                         {

                         //  should loop as long as there are numbers at the beginning of each line
                         string substring_of__line_from_file___beginning_to__location_of_first_space = line_from_file.substr(0, location_of_first_space);
                         int the_integer_conversion_of_substring = atoi(substring_of__line_from_file___beginning_to__location_of_first_space.c_str());
                         #define MAX_INT_SIZE 7890
                         int i=0;

                         int this_index_number_has_been_used = false;


                         if ((the_integer_conversion_of_substring > 0) && (the_integer_conversion_of_substring < MAX_INT_SIZE))
                         {
                              // test to make sure the index number has not been used
                              for (i=0; i<tile_index.size(); i++)
                              {
                                   if (tile_index[i].index_num == the_integer_conversion_of_substring)
                                   {
                                        this_index_number_has_been_used = i;
                                        // replace the current address with the new one.
                                        tile_index[i].address = strdup(line_from_file.substr(location_of_first_quote+1, location_of_last_quote-(location_of_first_quote+1)).c_str());
                                   }
                              }


                              if (!this_index_number_has_been_used)
                              {
                                   // create a new tile index and fill in the info
                                   tile_refrence_struct gimp_tile_refrence_struct;
                                   
                                   gimp_tile_refrence_struct.index_num = the_integer_conversion_of_substring;
                                   gimp_tile_refrence_struct.address = strdup(line_from_file.substr(location_of_first_quote+1, location_of_last_quote-(location_of_first_quote+1)).c_str());
                                   
                                   //if (gimp_tile_refrence_struct.address == "door2_locked.gif")
                                   //{
                                   //    locked_door_index_num = gimp_tile_refrence_struct.index_num;
                                   //    allegro_message("found locked door graphic: %d", locked_door_index_num);
                                       
                                   //}
                                   
                                   tile_index.push_back(gimp_tile_refrence_struct);
                              }
                         }
                         }
                      }
                 break;
                 case CAMERA:
                       if (!current_camera_index_num)
                       {
                          int i=0;
                          int this_index_number_has_been_used = false;
                          // first, test to see if the index number has been used
                          for (i=0; i<map_class::cam.size(); i++)
                          {
                               if (map_class::cam[i].index_num == dummy_camera_index_num) {this_index_number_has_been_used = i+1;}
                          }

                          if (!this_index_number_has_been_used)
                          {
                              add_empty_camera();
                              map_class::cam[map_class::cam.size()-1].index_num = dummy_camera_index_num;
                              current_camera_index_num = map_class::cam.size()-1 +1;

                          }
                          else current_camera_index_num = this_index_number_has_been_used;

                       }
                       // get the information of the door;
                              //rectfill(screen, 0,0,40,40, makecol(0,0,0));
                              //textprintf(screen, font, 20, 20, makecol(255,255,255), "%d", current_door_index_num);
                              //my_error_message2("yo");
                       if (line_from_file.substr(0,15-7-5) == "x: ") map_class::cam[current_camera_index_num-1].x = atoi(line_from_file.substr(15-7-5,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,15-7-5) == "y: ") map_class::cam[current_camera_index_num-1].y = atoi(line_from_file.substr(15-7-5,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,15-7) == "lock x: ") map_class::cam[current_camera_index_num-1].lock_x = atoi(line_from_file.substr(15-7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,15-7) == "lock y: ") map_class::cam[current_camera_index_num-1].lock_y = atoi(line_from_file.substr(15-7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14-7) == "max x: ") map_class::cam[current_camera_index_num-1].max_x = atoi(line_from_file.substr(14-7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14-7) == "max y: ") map_class::cam[current_camera_index_num-1].max_y = atoi(line_from_file.substr(14-7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14-7) == "min x: ") map_class::cam[current_camera_index_num-1].min_x = atoi(line_from_file.substr(14-7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14-7) == "min y: ") map_class::cam[current_camera_index_num-1].min_y = atoi(line_from_file.substr(14-7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                 break;
                 case RAMP:
                       if (!current_ramp_index_num)
                       {
                          int i=0;
                          int this_index_number_has_been_used = false;
                          // first, test to see if the index number has been used
                          for (i=0; i<map_class::ramp.size(); i++)
                          {
                               if (map_class::ramp[i].index_num == dummy_ramp_index_num) {this_index_number_has_been_used = i+1;}
                          }

                          if (!this_index_number_has_been_used)
                          {
                              add_empty_ramp();
                              map_class::ramp[map_class::ramp.size()-1].index_num = dummy_ramp_index_num;
                              current_ramp_index_num = map_class::ramp.size()-1 +1;

                          }
                          else current_ramp_index_num = this_index_number_has_been_used;

                       }
                       // get the information of the door;
                              //rectfill(screen, 0,0,40,40, makecol(0,0,0));
                              //textprintf(screen, font, 20, 20, makecol(255,255,255), "%d", current_door_index_num);
                              //my_error_message2("yo");
                       if (line_from_file.substr(0,7) == "top x: ") map_class::ramp[current_ramp_index_num-1].top_x = atoi(line_from_file.substr(7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,7) == "top y: ") map_class::ramp[current_ramp_index_num-1].top_y = atoi(line_from_file.substr(7,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,10) == "bottom x: ") map_class::ramp[current_ramp_index_num-1].bottom_x = atoi(line_from_file.substr(10,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,10) == "bottom y: ") map_class::ramp[current_ramp_index_num-1].bottom_y = atoi(line_from_file.substr(10,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                  break;
                 case BACKGROUND:
                       if (!current_bg_index_num)
                       {
                          int i=0;
                          int this_index_number_has_been_used = false;
                          // first, test to see if the index number has been used
                          for (i=0; i<map_class::background.size(); i++)
                          {
                               if (map_class::background[i].index_num == dummy_bg_index_num) {this_index_number_has_been_used = i+1;}
                          }

                          if (!this_index_number_has_been_used)
                          {
                              add_empty_background();
                              map_class::background[map_class::background.size()-1].index_num = dummy_bg_index_num;
                              current_bg_index_num = map_class::background.size()-1 +1;
                          }
                          else current_bg_index_num = this_index_number_has_been_used;

                       }
                       // get the information of the door;
                              //rectfill(screen, 0,0,40,40, makecol(0,0,0));
                              //textprintf(screen, font, 20, 20, makecol(255,255,255), "%d", current_door_index_num);
                              //my_error_message2("yo");

                       if (line_from_file.substr(0,7) == "loop x") map_class::background[current_bg_index_num-1].loop_x = true;
                       else if (line_from_file.substr(0,12) == "don't loop x") map_class::background[current_bg_index_num-1].loop_x = false;
                       else if (line_from_file.substr(0,7) == "loop y") map_class::background[current_bg_index_num-1].loop_y = true;
                       else if (line_from_file.substr(0,12) == "don't loop y") map_class::background[current_bg_index_num-1].loop_y = false;
                       else if (line_from_file.substr(0,5) == "img: ")
                       {
                           int location_of_first_quote = line_from_file.find_first_of("\"");
                           int location_of_last_quote = line_from_file.find_last_of("\"");
                           map_class::background[current_bg_index_num-1].img_filename = line_from_file.substr(location_of_first_quote+1, location_of_last_quote-(location_of_first_quote+1)).c_str();
                           //allegro_message("%s", map_class::background[current_bg_index_num-1].img_filename.c_str());

        string img_and_directory;
        img_and_directory = DIRECTORY_BACKGROUNDS;
        img_and_directory.append(map_class::background[current_bg_index_num-1].img_filename);
        
        //background_struct gimp_background_struct;
        //gimp_background_struct.img_filename = img_filename;
        map_class::background[current_bg_index_num-1].img = load_bitmap(full_filename(img_and_directory.c_str()), NULL);

                       }    
                       else if (line_from_file.substr(0,10) == "x offset: ") map_class::background[current_bg_index_num-1].x_offset = atoi(line_from_file.substr(10,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,10) == "y offset: ") map_class::background[current_bg_index_num-1].y_offset = atoi(line_from_file.substr(10,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,9) == "x speed: ") map_class::background[current_bg_index_num-1].x_speed = atof(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,9) == "y speed: ") map_class::background[current_bg_index_num-1].y_speed = atof(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,6) == "rate: ") map_class::background[current_bg_index_num-1].scroll_rate = atof(line_from_file.substr(6,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                  break;
              }

           }// end if (!line_from_file.empty())
        }// end while !eof

        load_map_graphics();

        return 0;
    }
    int save(const char *filename)
    {
        ofstream outfile(full_filename(filename));

        if (!outfile)
        {
				my_error_message("unable to save map");
				/*
            rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to save map", filename);
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", filename);
				*/
            readkey();
            return 1;
        }

        int h=0;
        int k=0;
        outfile << "[params]" << endl;
        outfile << "title: " << title << endl;
        outfile << "height: " << size.y << endl;
        outfile << "width: " << size.x << endl;
        outfile << "time limit: " << time_limit << endl;
        outfile << "spawn x: " << spawn.x << endl;
        outfile << "spawn y: " << spawn.y << endl;
        outfile << "camera start x: " << camera_start.x << endl;
        outfile << "camera start y: " << camera_start.y << endl;
        outfile << "camera lock x: " << camera_lock.x << endl;
        outfile << "camera lock y: " << camera_lock.y << endl;
        outfile << "camera max x: " << camera_max.x << endl;
        outfile << "camera max y: " << camera_max.y << endl;
        outfile << "camera min x: " << camera_min.x << endl;
        outfile << "camera min y: " << camera_min.y << endl;
        outfile << endl;
        outfile << "[tile_index]" << endl;
        
        for (k=0; k<num_of_tiles(); k++)
        {
            outfile << tile_index[k].index_num << " \"" << tile_index[k].address << "\"" << endl;
        }
        outfile << endl;
        
        for (k=0; k<ramp.size(); k++)
        {
            outfile << "[ramp " << ramp[k].index_num << "]" << endl;
            outfile << "bottom x: " << ramp[k].bottom_x << endl;
            outfile << "bottom y: " << ramp[k].bottom_y << endl;
            outfile << "top x: " << ramp[k].top_x << endl;
            outfile << "top y: " << ramp[k].top_y << endl;
            outfile << endl;
        }
        
        for (k=0; k<cam.size(); k++)
        {
            outfile << "[camera " << cam[k].index_num << "]" << endl;
            outfile << "x: " << cam[k].x << endl;
            outfile << "y: " << cam[k].y << endl;
            outfile << "lock x: " << cam[k].lock_x << endl;
            outfile << "lock y: " << cam[k].lock_y << endl;
            outfile << "max x: " << cam[k].max_x << endl;
            outfile << "max y: " << cam[k].max_y << endl;
            outfile << "min x: " << cam[k].min_x << endl;
            outfile << "min y: " << cam[k].min_y << endl;
            outfile << endl;
        }

        int tile_out_count = 0;
        outfile << "[layer1]" << endl;
        for (k=0; k<size.y; k++)
        {
            for (h=0; h<size.x; h++)
            {
                outfile << tile[h][k].layer[0] << " ";
                tile_out_count++;
                if (tile_out_count%10 == 0) outfile << endl;
                if (tile_out_count == 100) tile_out_count = 0;
            }
        }
        outfile << endl << endl;

        tile_out_count = 0;
        outfile << "[layer2]" << endl;
        for (k=0; k<size.y; k++)
        {
            for (h=0; h<size.x; h++)
            {
                outfile << tile[h][k].layer[1] << " ";
                tile_out_count++;
                if (tile_out_count%10 == 0) outfile << endl;
                if (tile_out_count == 100) tile_out_count = 0;
            }
        }
        outfile << endl << endl;
        
        tile_out_count = 0;
        outfile << "[layer3]" << endl;
        for (k=0; k<size.y; k++)
        {
            for (h=0; h<size.x; h++)
            {
                outfile << tile[h][k].layer[2] << " ";
                tile_out_count++;
                if (tile_out_count%10 == 0) outfile << endl;
                if (tile_out_count == 100) tile_out_count = 0;
            }
        }
        outfile << endl << endl;
        
        tile_out_count = 0;
        outfile << "[boundrys]" << endl;
        for (k=0; k<size.y; k++)
        {
            for (h=0; h<size.x; h++)
            {
                outfile << tile[h][k].boundry << " ";
                tile_out_count++;
                if (tile_out_count%10 == 0) outfile << endl;
                if (tile_out_count == 100) tile_out_count = 0;
            }
        }
        outfile << endl << endl;
        
        tile_out_count = 0;
        outfile << "[environment]" << endl;
        for (k=0; k<size.y; k++)
        {
            for (h=0; h<size.x; h++)
            {
                outfile << tile[h][k].environment << " ";
                tile_out_count++;
                if (tile_out_count%10 == 0) outfile << endl;
                if (tile_out_count == 100) tile_out_count = 0;
            }
        }
        outfile << endl;

        string message = "map \'" + title + "\' saved.";
        
		ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
			int width_of_box = text_length(font_small, message.c_str()) + 40;
        rectfill(screen, SCREEN_W/2-width_of_box/2, SCREEN_H/2-20, SCREEN_W/2+width_of_box/2, SCREEN_H/2+20, makecol(0,64,16));
        textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(128,255,128+32), message.c_str());
        textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", filename);
			al_flip_display();

        readkey();
        return 0;
    }
    void resize(int width, int height)
    {
        if (height < 1) height = 1;
        else if (height > MAX_MAP_HEIGHT-1) height = MAX_MAP_HEIGHT-1;
        if (width < 1) width = 1;
        else if (width > MAX_MAP_WIDTH-1) width = MAX_MAP_WIDTH-1;

        size.x = width;
        size.y = height;
    }
};

map_class current_map;

//#include "__map.hpp"

int get_map_width()
{
   return current_map.size.x;
}
int get_map_height()
{
   return current_map.size.y;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// map construction

int set_boundry_block(int xx, int yy, int boundry_tile)
{
    if ((xx < 0) || (yy < 0) || (xx > MAX_MAP_WIDTH-1) || (yy > MAX_MAP_HEIGHT-1)) return 1;
    current_map.tile[xx][yy].boundry = boundry_tile;
    return 0;
}

int fill_with_boundry(int xx, int yy, int xx2, int yy2, int boundry_tile)
{
    { // test to see if the input is valid
        if (xx < 0) xx = 0;
        if (yy < 0) yy = 0;
        if (xx > MAX_MAP_WIDTH-1) xx = MAX_MAP_WIDTH-1;
        if (yy > MAX_MAP_HEIGHT-1) yy = MAX_MAP_HEIGHT-1;
        if (xx2 < 0) xx2 = 0;
        if (yy2 < 0) yy2 = 0;
        if (xx2 > MAX_MAP_WIDTH-1) xx2 = MAX_MAP_WIDTH-1;
        if (yy2 > MAX_MAP_HEIGHT-1) yy2 = MAX_MAP_HEIGHT-1;
        if (xx > xx2) return 1;
        if (yy > yy2) return 1;
    }

    int h=0;
    int k=0;
    for (k=yy; k<=yy2; k++)
    {
        for (h=xx; h<=xx2; h++)
        {
            current_map.tile[h][k].boundry = boundry_tile;
        }
    }
    return 0;
}


int set_tile(int layer, int xx, int yy, int tile)
{
    layer--;
    if ((xx < 0) || (yy < 0) || (xx > MAX_MAP_WIDTH-1) || (yy > MAX_MAP_HEIGHT-1)) return 1;
    if ((layer < 0) || (layer > 2)) return 1;
    current_map.tile[xx][yy].layer[layer] = tile;
    return 0;
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define LEVEL_FILE_INPUT  (1010+
#define MAP_INDEX         1)
#define DOOR_INDEX        2)
#define ENEMIES           3)
#define POWER_UPS         4)
#define SWITCHES          5)

//define ABORT             99999  // already been defined

#define ENEMY_TYPE        (2020+
#define YELLOW_BEAR       1)
#define RED_BEAR          2)
#define BLUE_BEAR         3)
#define PURPLE_BEAR         4)


struct map_index_struct
{
	std::string address;
    int index_num;
};

struct level_enemy_struct
{
    int map_num;
    int type;
    int start_x;
    int start_y;
    bool facing_right;
    enemy_class params;
};

struct power_up_struct
{
    int map_num;
    float_coordinate map_pos;
    int_coordinate size;
    int type;
    bool alive;
};


struct switch_struct
{
    int index_num;
    bool active;
};


class level_class
{
public:
    string title;
    string snapshot_address;
    vector<map_index_struct> map_index;
    unsigned int time_limit;
    unsigned int gold_time;
    unsigned int silver_time;
    unsigned int bronze_time;
    vector<door_struct> door;
    vector<level_enemy_struct> enemy;
    vector<power_up_struct> power_up;
    int current_map_index;
    int number_of_maps;
    vector<switch_struct> switch_stick;

    level_class()
    {
        clear();
    }
    ~level_class()
    {
    }
    int get_current_map_index()
    {
       return current_map_index;
    }
    void clear()
    {
        title = "Untitled Level";
        time_limit = 999999;
        gold_time = 999999;
        silver_time = 999999;
        bronze_time = 999999;
        current_map_index = 1;
        number_of_maps = 0;
        clear_maps();
        clear_doors();
        clear_switch_sticks();
    }
    void clear_maps()
    {
        int k=0;
        for (k=map_index.size()-1; k>=0; k--) map_index.pop_back();
        number_of_maps = 0;
    }
    void clear_doors()
    {
        int k=0;
        for (k=level_class::door.size()-1; k>=0; k--) level_class::door.pop_back();
    }
    void clear_switch_sticks()
    {
        int k=0;
        for (k=switch_stick.size()-1; k>=0; k--) switch_stick.pop_back();
    }
    void add_empty_map()
    {
        map_index_struct gimp_map_index_struct;
        
        gimp_map_index_struct.address = "";
        gimp_map_index_struct.index_num = -1;
        
        level_class::map_index.push_back(gimp_map_index_struct);
    }
    void add_switch_stick(int index_num, bool active)
    {
        switch_struct gimp_switch_stick;
        gimp_switch_stick.index_num = index_num;
        gimp_switch_stick.active = active;

        switch_stick.push_back(gimp_switch_stick);
    }
    void add_empty_door()
    {
        door_struct gimp_door_struct;

        gimp_door_struct.index_num = -1;
        gimp_door_struct.go_to_new_map = false;
        gimp_door_struct.type = DOOR_TYPE_NORMAL;
        //gimp_door_struct.opened = true;
        gimp_door_struct.map_address = "";
        gimp_door_struct.map_spawn_x = 0;
        gimp_door_struct.map_spawn_y = 0;
        gimp_door_struct.camera_x = 0;
        gimp_door_struct.camera_y = 0;
        gimp_door_struct.camera_lock_x = -1;
        gimp_door_struct.camera_lock_y = -1;
        gimp_door_struct.camera_min_x = -1;
        gimp_door_struct.camera_min_y = -1;
        gimp_door_struct.camera_max_x = -1;
        gimp_door_struct.camera_max_y = -1;

        gimp_door_struct.solution = SECRET_SOLUTION_NONE;

        level_class::door.push_back(gimp_door_struct);
    }
    void add_enemy(int map_num, int type, int xx, int yy, bool face_right)
    {
        level_enemy_struct gimp_level_enemy_struct;

        gimp_level_enemy_struct.params.init();

        gimp_level_enemy_struct.map_num = map_num;
        gimp_level_enemy_struct.type = type;
        if (type == ENEMY_TYPE YELLOW_BEAR) gimp_level_enemy_struct.params.make_yellow_bear();
        else if (type == ENEMY_TYPE RED_BEAR) gimp_level_enemy_struct.params.make_red_bear();
        else if (type == ENEMY_TYPE BLUE_BEAR) gimp_level_enemy_struct.params.make_blue_bear();
        else if (type == ENEMY_TYPE PURPLE_BEAR) gimp_level_enemy_struct.params.make_purple_bear();

        gimp_level_enemy_struct.params.set_left_edge(xx);
        gimp_level_enemy_struct.start_x = xx;
        gimp_level_enemy_struct.params.set_top_edge(yy);
        gimp_level_enemy_struct.start_y = yy;

        if (face_right) gimp_level_enemy_struct.params.facing_right = true;
        else gimp_level_enemy_struct.params.facing_right = false;

        enemy.push_back(gimp_level_enemy_struct);
    }
    void add_power_up(int map_number, float xx=15.0f, float yy=15.0f, int type=heart_const)
    {
        power_up_struct gimp_power_up_struct;
        
        gimp_power_up_struct.map_num = map_number;
        gimp_power_up_struct.map_pos.x = xx;
        gimp_power_up_struct.map_pos.y = yy;

        gimp_power_up_struct.alive=true;

        gimp_power_up_struct.type = type;
        gimp_power_up_struct.size.x = POWER_UP_BOUNDING_BOX_SIZE; // or the size of the heart bitmap        gimp_power_up_struct.size.y=24; // or the size of the heart bitmap
        gimp_power_up_struct.size.y = POWER_UP_BOUNDING_BOX_SIZE; // or the size of the heart bitmap        gimp_power_up_struct.size.y=24; // or the size of the heart bitmap

        power_up.push_back(gimp_power_up_struct);    }


    int load(const char *filename2)
    {
        //ptrbuf = full_filename(filename);
        ifstream infile2(full_filename(filename2));
        string line_from_file;

        if (!infile2)
           {
				ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
            rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to load level", filename2);
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", filename2);
				al_flip_display();
            readkey();
            return 1;
           }

        unsigned int data_input_mode = 0;
        int h=0;
        int k=0;
        int gimpInt=0;
        clear();
        // interpret map file
        
        bool abort_level_input = false;

        int dummy_door_index_num = 0;
        int current_door_index_num = false;

        int dummy_switch_index_num = 0;
        int current_switch_index_num = false;


        while ((!infile2.eof()) && (!abort_level_input))
        {
           infile2.getline(buf, 256);
           line_from_file = buf;

           if (!line_from_file.empty())
           {
              if (line_from_file.substr(0, 18) == "[////////////////]")
              {
                  data_input_mode = ABORT;
                  abort_level_input = true;
              }    

              if (line_from_file.substr(0,8) == "[params]") data_input_mode = PARAMS;
              //else if (line_from_file.substr(0,6) == "[maps]")
              //    {data_input_mode = LEVEL_FILE_INPUT MAP_INDEX; infile2.getline(buf, 256); line_from_file = buf;}
              else if (line_from_file.substr(0,5) == "[door")
                  {
                      dummy_door_index_num = atoi(line_from_file.substr(6,line_from_file.size()-1).c_str());
                      data_input_mode = LEVEL_FILE_INPUT DOOR_INDEX;
                      current_door_index_num = false;
                      infile2.getline(buf, 256);
                      line_from_file = buf;
                  }
              else if (line_from_file.substr(0,7) == "[switch")
                  {
                      dummy_switch_index_num = atoi(line_from_file.substr(8,line_from_file.size()-1).c_str());
                      data_input_mode = LEVEL_FILE_INPUT SWITCHES;
                      current_switch_index_num = false;
                      infile2.getline(buf, 256);
                      line_from_file = buf;
                  }

              else if (line_from_file.substr(0,9) == "[enemies]")
                  {
                      data_input_mode = LEVEL_FILE_INPUT ENEMIES;
                      infile2.getline(buf, 256);
                      line_from_file = buf;
                  }
              else if (line_from_file.substr(0,11) == "[power_ups]")
                  {
                      data_input_mode = LEVEL_FILE_INPUT POWER_UPS;
                      infile2.getline(buf, 256);
                      line_from_file = buf;
                  }

              switch (data_input_mode)
              {
                  case PARAMS:
                      if (line_from_file.substr(0,12) == "time limit: ") time_limit = atoi(line_from_file.substr(12,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,7) == "title: ") title = line_from_file.substr(7,line_from_file.size()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,11) == "gold time: ") gold_time = atoi(line_from_file.substr(11,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,13) == "silver time: ") silver_time = atoi(line_from_file.substr(13,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,13) == "bronze time: ") bronze_time = atoi(line_from_file.substr(13,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,16) == "number of maps: ") number_of_maps = atoi(line_from_file.substr(16,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                      else if (line_from_file.substr(0,11) == "levelshot: ")
                      {
                          int pos_of_first_par = line_from_file.find_first_of("\"");
                          int pos_of_last_par = line_from_file.find_last_of("\"");
                          snapshot_address = line_from_file.substr(pos_of_first_par+1, pos_of_last_par-(pos_of_first_par+1));
                      }
                  break;
                  case LEVEL_FILE_INPUT DOOR_INDEX:
                       if (!current_door_index_num)
                       {
                          int i=0;
                          int this_index_number_has_been_used = false;
                          // first, test to see if the index number has been used
                          for (i=0; i<level_class::door.size(); i++)
                          {
                               if (level_class::door[i].index_num == dummy_door_index_num) {this_index_number_has_been_used = i+1;}
                          }

                          if (!this_index_number_has_been_used)
                          {
                              add_empty_door();
                              level_class::door[level_class::door.size()-1].index_num = dummy_door_index_num;
                              current_door_index_num = level_class::door.size()-1 +1;

                          }
                          else current_door_index_num = this_index_number_has_been_used;

                       }
                       // get the information of the door;
                              //rectfill(screen, 0,0,40,40, makecol(0,0,0));
                              //textprintf(screen, font, 20, 20, makecol(255,255,255), "%d", current_door_index_num);
                              //my_error_message2("yo");
                       if (line_from_file.substr(0,9) == "new map: ") level_class::door[current_door_index_num-1].go_to_new_map = atoi(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,9) == "spawn x: ") level_class::door[current_door_index_num-1].map_spawn_x = atoi(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,9) == "spawn y: ") level_class::door[current_door_index_num-1].map_spawn_y = atoi(line_from_file.substr(9,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,16) == "camera start x: ") level_class::door[current_door_index_num-1].camera_x = atoi(line_from_file.substr(16,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,16) == "camera start y: ") level_class::door[current_door_index_num-1].camera_y = atoi(line_from_file.substr(16,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,15) == "camera lock x: ") level_class::door[current_door_index_num-1].camera_lock_x = atoi(line_from_file.substr(15,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,15) == "camera lock y: ") level_class::door[current_door_index_num-1].camera_lock_y = atoi(line_from_file.substr(15,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14) == "camera max x: ") level_class::door[current_door_index_num-1].camera_max_x = atoi(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14) == "camera max y: ") level_class::door[current_door_index_num-1].camera_max_y = atoi(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14) == "camera min x: ") level_class::door[current_door_index_num-1].camera_min_x = atoi(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();
                       else if (line_from_file.substr(0,14) == "camera min y: ") level_class::door[current_door_index_num-1].camera_min_y = atoi(line_from_file.substr(14,line_from_file.size()).c_str()); //"whoptie"; //line_from_file.c_str();

                       else if (line_from_file.substr(0,19) == "type: locked silver") level_class::door[current_door_index_num-1].type = DOOR_TYPE_LOCKED_SILVER;
                       else if (line_from_file.substr(0,21) == "type: unlocked silver") level_class::door[current_door_index_num-1].type = DOOR_TYPE_UNLOCKED_SILVER;
                       else if (line_from_file.substr(0,19) == "type: locked secret") level_class::door[current_door_index_num-1].type = DOOR_TYPE_LOCKED_SECRET;
                       else if (line_from_file.substr(0,21) == "type: unlocked secret") level_class::door[current_door_index_num-1].type = DOOR_TYPE_UNLOCKED_SECRET;
                       else if (line_from_file.substr(0,15) == "type: exit only") level_class::door[current_door_index_num-1].type = DOOR_TYPE_EXIT_ONLY;
                       else if (line_from_file.substr(0,12) == "type: normal") level_class::door[current_door_index_num-1].type = DOOR_TYPE_NORMAL;
                       else if (line_from_file.substr(0,12) == "type: locked") level_class::door[current_door_index_num-1].type = DOOR_TYPE_LOCKED;
                       else if (line_from_file.substr(0,14) == "type: unlocked") level_class::door[current_door_index_num-1].type = DOOR_TYPE_UNLOCKED;

                       else if (line_from_file.substr(0,20) == "solution: kill bears") level_class::door[current_door_index_num-1].solution = SECRET_SOLUTION_KILL_BEARS;
                       else if (line_from_file.substr(0,24) == "solution: collect jewels") level_class::door[current_door_index_num-1].solution = SECRET_SOLUTION_COLLECT_JEWELS;
                       else if (line_from_file.substr(0,21) == "solution: trigger all") level_class::door[current_door_index_num-1].solution = SECRET_SOLUTION_TRIGGER_ALL;
                       else if (line_from_file.substr(0,25) == "solution: trigger ordered") level_class::door[current_door_index_num-1].solution = SECRET_SOLUTION_TRIGGER_ORDERED;

                       else if (line_from_file.substr(0,19) == "solution: chain of ") level_class::door[current_door_index_num-1].solution = SECRET_SOLUTION_CHAIN_OF + atoi(line_from_file.substr(19,line_from_file.size()).c_str());
                       else if (line_from_file.substr(0,17) == "solution: fer of ") level_class::door[current_door_index_num-1].solution = SECRET_SOLUTION_FER_OF + atoi(line_from_file.substr(17,line_from_file.size()).c_str());

                  break;
                 case LEVEL_FILE_INPUT SWITCHES:
                       if (!current_switch_index_num)
                       {

                       // will load OFF by default

                          int gimp_active = false;

                          int i=0;
                          int this_index_number_has_been_used = false;

                          // first, test to see if the index number has been used
                          for (i=0; i<switch_stick.size(); i++)
                          {
                               if (switch_stick[i].index_num == dummy_switch_index_num) {this_index_number_has_been_used = i+1;}
                          }

                          if (!this_index_number_has_been_used)
                          {
                              if (line_from_file.substr(0,2) == "on") gimp_active = true;
                              else if (line_from_file.substr(0,3) == "off") gimp_active = false;
                              add_switch_stick(dummy_switch_index_num, gimp_active);
                          }
                          else
                          {
                              current_switch_index_num = this_index_number_has_been_used;
                          }

                       }
                 break;
                 case LEVEL_FILE_INPUT ENEMIES:
                      if (!line_from_file.empty())
                      {
                          int enemy_type = -1;
                          int enemy_x = 0;
                          int enemy_y = 0;
                          int enemy_map_index = 0;
                          bool face_right = false;

                          int location_of_first_space = line_from_file.find_first_of(" ");;
                          int location_of_first_parenthesis = line_from_file.find_first_of("(");;
                          int location_of_comma = line_from_file.find_first_of(",");
                          int location_of_last_parenthesis = line_from_file.find_last_of(")");;
                          string enemy_type_string = line_from_file.substr(location_of_first_space+1, (location_of_first_parenthesis-1)-(location_of_first_space+1));

                          enemy_map_index = atoi(line_from_file.substr(0, location_of_first_space).c_str());
                          enemy_x = atoi(line_from_file.substr(location_of_first_parenthesis+1, location_of_comma-location_of_first_parenthesis+1).c_str());
                          enemy_y = atoi(line_from_file.substr(location_of_comma+1, location_of_last_parenthesis-location_of_comma+1).c_str());

                          if (enemy_type_string == "red bear") enemy_type = ENEMY_TYPE RED_BEAR;
                          else if (enemy_type_string == "yellow bear") enemy_type = ENEMY_TYPE YELLOW_BEAR;
                          else if (enemy_type_string == "blue bear") { enemy_type = ENEMY_TYPE BLUE_BEAR;  }
                          else if (enemy_type_string == "brown bear") { enemy_type = ENEMY_TYPE RED_BEAR;  }
                          else if (enemy_type_string == "purple bear") { enemy_type = ENEMY_TYPE PURPLE_BEAR;  }

                          if (enemy_type != -1) add_enemy(enemy_map_index, enemy_type, enemy_x, enemy_y, face_right);
                      }
                 break;
                 case LEVEL_FILE_INPUT POWER_UPS:
                      if (!line_from_file.empty())
                      {
                          int power_up_type = -1;
                          int power_up_x = 0;
                          int power_up_y = 0;
                          int power_up_map_index = 0;

                          int location_of_first_space = line_from_file.find_first_of(" ");;
                          int location_of_first_parenthesis = line_from_file.find_first_of("(");;
                          int location_of_comma = line_from_file.find_first_of(",");
                          int location_of_last_parenthesis = line_from_file.find_last_of(")");;
                          string power_up_type_string = line_from_file.substr(location_of_first_space+1, (location_of_first_parenthesis-1)-(location_of_first_space+1));

                          power_up_map_index = atoi(line_from_file.substr(0, location_of_first_space).c_str());
                          power_up_x = atoi(line_from_file.substr(location_of_first_parenthesis+1, location_of_comma-location_of_first_parenthesis+1).c_str());
                          power_up_y = atoi(line_from_file.substr(location_of_comma+1, location_of_last_parenthesis-location_of_comma+1).c_str());


                          if (false) { } //do nothing

#define ADD_ITEM(xx, yy)     else if (power_up_type_string == "" #xx "") power_up_type = xx##_const;
#include "item_list.hpp"
#undef ADD_ITEM


                          if (power_up_type != -1) add_power_up(power_up_map_index, power_up_x, power_up_y, power_up_type);
                      }
                 break;
              }
           }// end if (!line_from_file.empty())
        }// end while !eof

        load_map_graphics();

        return 0;
    }
    int save(char *filename)
    {
        ofstream outfile(full_filename(filename));

        if (!outfile)
        {
				ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
            rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to save map", filename);
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", filename);
				al_flip_display();
            readkey();
            return 1;
        }

        int h=0;
        int k=0;
        outfile << "//.lev file for Beary's Bash by Mark Oates" << endl;
        outfile << "// questions? comments? euph_boy@hotmail.com" << endl;
        outfile << endl;
        outfile << "[params]" << endl;
        outfile << "title: " << title << endl;
        outfile << "time limit: " << time_limit << endl;
        outfile << "gold time: " << gold_time << endl;
        outfile << "silver time: " << silver_time << endl;
        outfile << "bronze time: " << bronze_time << endl;
        outfile << "number of maps: " << number_of_maps << endl;
        outfile << "levelshot: \"" << snapshot_address << "\"" << endl;
        outfile << endl;
        //outfile << "[maps]" << endl;
        //for (k=0; k<map_index.size(); k++)
        //{
        //    outfile << map_index[k].index_num << " \"" << map_index[k].address << "\"" << endl;
        //}
        //outfile << endl;
        for (k=0; k<door.size(); k++)
        {
            outfile << "[door " << door[k].index_num << "]" << endl;
            outfile << "new map: " << door[k].go_to_new_map << endl;
            outfile << "spawn x: " << door[k].map_spawn_x << endl;
            outfile << "spawn y: " << door[k].map_spawn_y << endl;
            outfile << "camera start x: " << door[k].camera_x << endl;
            outfile << "camera start y: " << door[k].camera_y << endl;
            outfile << "camera lock x: " << door[k].camera_lock_x << endl;
            outfile << "camera lock y: " << door[k].camera_lock_y << endl;
            outfile << "camera max x: " << door[k].camera_max_x << endl;
            outfile << "camera max y: " << door[k].camera_max_y << endl;
            outfile << "camera min x: " << door[k].camera_min_x << endl;
            outfile << "camera min y: " << door[k].camera_min_y << endl;
            outfile << endl;
        }
        outfile << "[enemies]" << endl;
        for (k=0; k<enemy.size(); k++)
        {
            outfile << enemy[k].map_num;
            switch (enemy[k].type)
            {
                   case ENEMY_TYPE RED_BEAR:
                        outfile << " red bear ";
                        break;
                   case ENEMY_TYPE YELLOW_BEAR:
                        outfile << " yellow bear ";
                        break;
                   case ENEMY_TYPE BLUE_BEAR:
                        outfile << " blue bear ";
                        break;
                   default:
                        outfile << " unknown enemy ";
                        break;
            }

            outfile << "(" << enemy[k].start_x << "," << enemy[k].start_y << ")" << endl;
        }
        outfile << endl;


        for (k=0; k<switch_stick.size(); k++)
        {
            outfile << "[switch " << switch_stick[k].index_num << "]" << endl;
            if (switch_stick[k].active) { outfile << "on" << endl; }
            else { outfile << "off" << endl; }
            outfile << endl;
        }

        //outfile << eof;
        
        string message = "level \'" + title + "\' saved.";
        int width_of_box = text_length(font_small, message.c_str()) + 40;
			ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
        rectfill(screen, SCREEN_W/2-width_of_box/2, SCREEN_H/2-20, SCREEN_W/2+width_of_box/2, SCREEN_H/2+20, makecol(0,64,16));
        textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(128,255,128+32), message.c_str());
        textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", filename);
			al_flip_display();

        readkey();
        return 0;
    }


};


    
level_class current_level;





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class level_index_class
{
public:
    int level_number;
    string filename;

    level_index_class(int ln, string fn)
    {
         level_number = ln;
         filename = fn;
    }
};


bool line_is(string prefix, string line)
{
    return (line.substr(0, prefix.size()) == prefix);
}


void attempt_to_extract_data(string prefix, string line, string *var)
{
    if (line_is(prefix, line))
    {
        *var = line.substr(prefix.size(), line.size()-prefix.size());
    }
}


bool attempt_to_extract_level_pair(string line, level_index_class &lic)
{
    int pos_of_first_space = line.find_first_of(" ");
    if (pos_of_first_space == -1) return false;

    int level_number = atoi(line.substr(0, pos_of_first_space).c_str());
    string filename = line.substr(pos_of_first_space+1, line.size());

    lic.filename = filename;
    lic.level_number = level_number;

    return true;
};


class world_class
{
public:
     string title;

     vector<level_index_class> level;
     int current_level_index;

     // ---

     world_class()
     {
         clear();
     }

     void clear()
     {
         for (int i=level.size()-1; i>=0; i--) level.pop_back();
         current_level_index = -1;
     }

     void add_level_listing(int level_number, string filename)
     {
         level.push_back(level_index_class(level_number, filename));
     }

     void add_empty_level_listing()
     {
         level.push_back(level_index_class(0, "this listing should not exist"));
     }

     string get_next_level_filename()
     {
         if ((current_level_index+1 > level.size()) && (current_level_index+1 >= 0)) return "";
         else return level[current_level_index+1].filename;
     }

     string get_current_level_filename()
     {
         if ((level.size() == 0)) return "- no levels -";
         if (!((current_level_index < level.size()) && (current_level_index >= 0))) return "- index out of bounds -";
         else return level[current_level_index].filename;
     }

     void message_dump()
     {
         allegro_message(title.c_str());
         for (int i=0; i<level.size(); i++)
         {
				std::stringstream ss;
             //string str;
             //str = "%d " + level[i].filename;
				ss << level[i].level_number << " " << level[i].filename;
             allegro_message(ss.str());
             //allegro_message(str.c_str(), level[i].level_number);
         }
     }

     int load(const char *filename2)
     {
        // potential errors
        // - there must be a new line at the end of the world file
        // - there must be no extranious spaces -- before, after, or on blank lines
        // - the level list must be the last thing in the file

        ifstream infile(filename2);
        string line_from_file = "";

        if (!infile)
        {
            string message = "unable to load world \"";
            message += filename2;
            message += "\". file not found";
            allegro_message(message.c_str());
            return 1;
        }


        clear();

        bool loading_level_list = false;

        //allegro_message("preparing to parse file");

        while (!infile.eof())
        {
           infile.getline(buf, 256);
           line_from_file = buf;
           string return_string = "";

           if (!line_from_file.empty())
           {
               if (line_is("[levels]", line_from_file))
               {
                   loading_level_list = true;
                   add_empty_level_listing();
               }
               else if (!loading_level_list)
               {
                   attempt_to_extract_data("title: ", line_from_file, &title);
               }
               else if (loading_level_list) // loading level list here
               {
                   if (attempt_to_extract_level_pair(line_from_file, level[level.size()-1])) add_empty_level_listing();
               }
           }
        }

        current_level_index = 0;

        infile.close();

        level.pop_back();

        //message_dump();
        return 0;
     }

     int load_current_level()
     {
         if ((level.size() == 0)) { allegro_message("no levels to load"); return 2; }   // no levels
         if (!((current_level_index < level.size()) && (current_level_index >= 0)))  { allegro_message("current_level_index out of bounds"); return 1; }  // index out of boundes

         level_to_start = level[current_level_index].filename;

         //string message = "starting to level " + level[current_level_index].filename;
         //allegro_message(message.c_str());

         load_level(level_to_start.c_str());

         return 0;
     }

     int load_next_level()
     {
         current_level_index += 1;
         if (current_level_index >= level.size()) current_level_index = level.size()-1;
         return load_current_level();
     }

     int load_previous_level()
     {
         current_level_index -= 1;
         if (current_level_index < 0) current_level_index = 0;
         return load_current_level();
     }

     int start_from_first_level()
     {
         current_level_index = 0;
         return load_current_level();
     }
};

world_class current_world;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



void write_outline_center_alfont_aa_to_destination(ALLEGRO_BITMAP *destination, int x, int y, ALFONT_FONT *f, int size, ALLEGRO_COLOR color, ALLEGRO_COLOR bgcolor, std::string buf, int num)
{
	y -= 1;
	x += 1;
/*
   char buf[512];

   va_list ap;
   va_start(ap, format);
   uvszprintf(buf, sizeof(buf), format, ap);
   va_end(ap);
   
   alfont_set_font_size(f, size);
*/
    //int outline_color = makecol(0,0,0);
    //int text_color = color;

	std::stringstream ss;
	ss << num;
	if (buf == "%d") buf = ss.str();
 
    alfont_textprintf_centre(destination, f, x+1, y, bgcolor, buf);
    alfont_textprintf_centre(destination, f, x-1, y, bgcolor, buf);
    alfont_textprintf_centre(destination, f, x, y+1, bgcolor, buf);
    alfont_textprintf_centre(destination, f, x, y-1, bgcolor, buf);
    alfont_textprintf_centre_aa(destination, f, x, y, color, buf);
}





int get_number_offset(int num)
{
    //if (num == 1) return -1;
    if (num == 7) return 1;
    if (num == 9) return 1;
    return 0;
}



void convert_to_transparent(ALLEGRO_BITMAP *b)
{
   int h; int k;

   bool swap_trigger = true;

   for (k=0; k<al_get_bitmap_height(b); k++)
   {
      if (swap_trigger)
      {
         for (h=0; h<al_get_bitmap_width(b); h+=2)
         {
            putpixel(b, h, k, makecol(255, 0, 255));
         }
      }
      else
      {
         for (h=1; h<al_get_bitmap_width(b); h+=2)
         {
            putpixel(b, h, k, makecol(255, 0, 255));
         }
      }

      swap_trigger = !swap_trigger;
   }
}




ALLEGRO_BITMAP *create_on_switch(string address, int num)
{
    ALLEGRO_BITMAP *original_image = load_bitmap(make_absolute(address).c_str(), NULL);

    ALLEGRO_BITMAP *final_bitmap = create_bitmap(al_get_bitmap_width(original_image), al_get_bitmap_height(original_image)+16+8);
    clear_to_color(final_bitmap, makecol(255, 0, 255));

    ALLEGRO_BITMAP *on_img = load_bitmap(make_absolute("images/on.gif").c_str(), NULL);
	al_convert_mask_to_alpha(on_img, makecol(255, 0, 255));

    ALLEGRO_BITMAP *on_switch = load_bitmap(make_absolute("images/switch_on.gif").c_str(), NULL);
	al_convert_mask_to_alpha(on_switch, makecol(255, 0, 255));

    if (!original_image || !final_bitmap || !on_img || !on_switch) return NULL;

    // --- start makin!


    draw_sprite(final_bitmap, original_image, 0, 16+8);
    draw_sprite(final_bitmap, on_img, al_get_bitmap_width(final_bitmap)/2-al_get_bitmap_width(on_img)/2, 0);
    draw_sprite(final_bitmap, on_switch, 0, 8);
    write_outline_center_alfont_aa_to_destination(final_bitmap, al_get_bitmap_width(final_bitmap)/2+get_number_offset(num), al_get_bitmap_height(final_bitmap)-14, new_font, 12, makecol(255,255,255), makecol(128,128,128), "%d", num);


    // --- clean up

    destroy_bitmap(original_image);
    destroy_bitmap(on_img);
    destroy_bitmap(on_switch);
	al_convert_mask_to_alpha(final_bitmap, makecol(255, 0, 255));

    return final_bitmap;

    return NULL;
}



ALLEGRO_BITMAP *create_off_switch(string address, int num)
{
    ALLEGRO_BITMAP *original_image = load_bitmap(make_absolute(address).c_str(), NULL);

    ALLEGRO_BITMAP *final_bitmap = create_bitmap(al_get_bitmap_width(original_image), al_get_bitmap_height(original_image)+16+8);
    clear_to_color(final_bitmap, makecol(255, 0, 255));

    ALLEGRO_BITMAP *off_img = load_bitmap(make_absolute("images/off.gif").c_str(), NULL);
	al_convert_mask_to_alpha(off_img, makecol(255, 0, 255));

    ALLEGRO_BITMAP *off_switch = load_bitmap(make_absolute("images/switch_off.gif").c_str(), NULL);
	al_convert_mask_to_alpha(off_img, makecol(255, 0, 255));

    if (!original_image || !final_bitmap || !off_img || !off_switch) return NULL;

    // --- start makin!


    draw_sprite(final_bitmap, original_image, 0, 16+8);
    draw_sprite(final_bitmap, off_img, al_get_bitmap_width(final_bitmap)/2-al_get_bitmap_width(off_img)/2, 0);
    draw_sprite(final_bitmap, off_switch, 0, 8);

    // draw switch here


    write_outline_center_alfont_aa_to_destination(final_bitmap, al_get_bitmap_width(final_bitmap)/2+get_number_offset(num), al_get_bitmap_height(final_bitmap)-14, new_font, 12, makecol(255,255,255), makecol(128,128,128), "%d", num);
//    write_outline_center_alfont_aa_to_destination(final_bitmap, final_bitmap->w/2+get_number_offset(num), final_bitmap->h-14, new_font, 12, makecol(0,0,0), makecol(128,128,128), "%d", num);


    // --- clean up

    destroy_bitmap(original_image);
    destroy_bitmap(off_img);
    destroy_bitmap(off_switch);
	al_convert_mask_to_alpha(final_bitmap, makecol(255, 0, 255));

    return final_bitmap;
}


ALLEGRO_BITMAP *create_on_block(string address, int num)
{
    ALLEGRO_BITMAP *final_bitmap = load_bitmap(make_absolute(address).c_str(), NULL);

    if (!final_bitmap) return NULL;

    // --- start makin!

    // draw switch here
    // write text here

    write_outline_center_alfont_aa_to_destination(final_bitmap, al_get_bitmap_width(final_bitmap)/2+get_number_offset(num), al_get_bitmap_height(final_bitmap)-14, new_font, 12, makecol(255,255,255), makecol(128,128,128), "%d", num);


    //convert_to_transparent(final_bitmap);

    // --- clean up

    return final_bitmap;
}

ALLEGRO_BITMAP *create_off_block(string address, int num)
{
    ALLEGRO_BITMAP *final_bitmap = load_bitmap(make_absolute(address).c_str(), NULL);

    if (!final_bitmap) return NULL;

    // --- start makin!

    // draw switch here
    // write text here

    write_outline_center_alfont_aa_to_destination(final_bitmap, al_get_bitmap_width(final_bitmap)/2+get_number_offset(num), al_get_bitmap_height(final_bitmap)-14, new_font, 12, makecol(255,255,255), makecol(128,128,128), "%d", num);
//    write_outline_center_alfont_aa_to_destination(final_bitmap, final_bitmap->w/2+get_number_offset(num), final_bitmap->h-14, new_font, 12, makecol(0,0,0), makecol(128,128,128), "%d", num);

    convert_to_transparent(final_bitmap);
	al_convert_mask_to_alpha(final_bitmap, makecol(255, 0, 255));


    // --- clean up

    return final_bitmap;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////









struct bitmap_struct
{
	ALLEGRO_BITMAP *sub_master;
	ALLEGRO_BITMAP *sub;

    ALLEGRO_BITMAP *bmp;
	std::string image_filename;
    int map_index_number;
};

vector<bitmap_struct> map_graphics;
ALLEGRO_BITMAP *destructable_block;
ALLEGRO_BITMAP *destructable_block_shard_1;
ALLEGRO_BITMAP *destructable_block_shard_2;
ALLEGRO_BITMAP *destructable_block_shard_3;


ALLEGRO_BITMAP *atlas = NULL;



ALLEGRO_BITMAP *create_tile_atlas(vector<bitmap_struct> &graphics)
{
	if (!atlas) atlas = al_create_bitmap(512, 512);

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);

	al_set_target_bitmap(atlas);
	al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));

	int num_rows = 32;
	int num_cols = 32;
	int max_num_indexes = num_rows * num_cols;

	for (unsigned i=0; i<graphics.size(); i++)
	{
		int map_index = graphics[i].map_index_number;
		int tile_x = (map_index % num_cols) * 16;
		int tile_y = (map_index / num_cols) * 16;

		// check the size, warn if its bigger than 16x16
		if (al_get_bitmap_width(graphics[i].bmp) > 16 || al_get_bitmap_height(graphics[i].bmp) > 16)
			std::cout << "warning: tile at index " << graphics[i].map_index_number << " is larger than 16x16" << std::endl;

		// draw the bitmap to the atlas
		al_draw_bitmap(graphics[i].bmp, tile_x, tile_y, 0);

		// create and add the sub-bitmap to the graphics struct, include the atlas, too
		graphics[i].sub = al_create_sub_bitmap(atlas, tile_x, tile_y, 16, 16);
		graphics[i].sub_master = atlas;
	}

	al_restore_state(&state);

	//al_save_bitmap("last_generated_atlas.png", atlas);

	return atlas;
};



struct switch_block_struct
{
    ALLEGRO_BITMAP *switch_on;
    ALLEGRO_BITMAP *switch_off;
    ALLEGRO_BITMAP *block_on;
    ALLEGRO_BITMAP *block_off;
};

switch_block_struct switch_block_1;
switch_block_struct switch_block_2;
switch_block_struct switch_block_3;
switch_block_struct switch_block_4;
switch_block_struct switch_block_5;
switch_block_struct switch_block_6;
switch_block_struct switch_block_7;
switch_block_struct switch_block_8;
switch_block_struct switch_block_9;

void destroy_switch_block_group(switch_block_struct *s)
{
    destroy_bitmap(s->switch_on);
    destroy_bitmap(s->switch_off);
    destroy_bitmap(s->block_on);
    destroy_bitmap(s->block_off);
}

void create_switch_block_group(switch_block_struct *s, int num)
{
    destroy_switch_block_group(s);

    if (current_map.switch_block_address != "")
    {
       s->switch_on = create_on_switch(current_map.switch_block_address, num);
       s->switch_off = create_off_switch(current_map.switch_block_address, num);
       s->block_on = create_on_block(current_map.switch_block_address, num);
       s->block_off = create_off_block(current_map.switch_block_address, num);

       if (!s->switch_on || !s->switch_off || !s->block_on || !s->block_off) { allegro_message("BAM!"); abort_game = true; }
    }


}


void destroy_map_graphics()
{

	for (unsigned i=0; i<map_graphics.size(); i++)
		destroy_bitmap(map_graphics[i].bmp);

	map_graphics.clear();

/*

    int k=0;
    for (k=map_graphics.size()-1; k>=0; k--)
    {
       //if (map_graphics[k].bmp != empty) destroy_bitmap(map_graphics[k].bmp);
       destroy_bitmap(map_graphics[k].bmp);
       //map_graphics.pop_back();
    }
*/

}

void load_map_graphics()
{
    destroy_map_graphics();
    
    string address_with_added_path;

    destroy_bitmap(destructable_block);
    destroy_bitmap(destructable_block_shard_1);
    destroy_bitmap(destructable_block_shard_2);
    destroy_bitmap(destructable_block_shard_3);

    destructable_block = _load_bitmap(current_map.destructable_tiles.block_address);
    destructable_block_shard_1 = _load_bitmap(current_map.destructable_tiles.shard_1_address);
    destructable_block_shard_2 = _load_bitmap(current_map.destructable_tiles.shard_2_address);
    destructable_block_shard_3 = _load_bitmap(current_map.destructable_tiles.shard_3_address);


    create_switch_block_group(&switch_block_1, 1);
    create_switch_block_group(&switch_block_2, 2);
    create_switch_block_group(&switch_block_3, 3);
    create_switch_block_group(&switch_block_4, 4);
    create_switch_block_group(&switch_block_5, 5);
    create_switch_block_group(&switch_block_6, 6);
    create_switch_block_group(&switch_block_7, 7);
    create_switch_block_group(&switch_block_8, 8);
    create_switch_block_group(&switch_block_9, 9);


    int k=0;
    for (k=0; k<current_map.num_of_tiles(); k++)
    {
        bitmap_struct gimp_bitmap_struct;

        address_with_added_path = DIRECTORY_TILES;
        address_with_added_path = address_with_added_path.append(current_map.tile_index[k].address);

        gimp_bitmap_struct.bmp = load_bitmap(full_filename(address_with_added_path.c_str()), NULL);
        gimp_bitmap_struct.image_filename = current_map.tile_index[k].address;
        if ((!gimp_bitmap_struct.bmp) || (gimp_bitmap_struct.bmp == empty))
        {
           //int width_of_box = (text_length(font_small, message.c_str()) + 40);
           //acquire_screen();
           string message = "unable to load graphic";
           //string message2 =
				ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
           rectfill(screen, SCREEN_W/2-(text_length(font_small, message.c_str()) + 40)/2, SCREEN_H/2-20, SCREEN_W/2+(text_length(font_small, message.c_str()) + 40)/2, SCREEN_H/2+20, makecol(64,16,0));
           textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+32,128), message.c_str());
           textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", current_map.tile_index[k].address);
				al_flip_display();
           clear_keybuf();
           readkey();
           //release_screen();
           gimp_bitmap_struct.bmp = empty;
        }
        gimp_bitmap_struct.map_index_number = current_map.tile_index[k].index_num;

        map_graphics.push_back(gimp_bitmap_struct);
    }


		// now push everything into the atlas
		create_tile_atlas(map_graphics);
}








int draw_tile(ALLEGRO_BITMAP *b, int tile_index_num, int xx, int yy)
{
    if ((tile_index_num < 0) || (tile_index_num > map_graphics.size()-1)) return 1;

    draw_sprite(b, map_graphics[tile_index_num].bmp, xx, yy);

    return 0;
}

void draw_tile_index(int xx, int yy)
{
    int m=0;
    for (m=0; m<current_map.tile_index.size(); m++)
    {
        draw_sprite(buffer, map_graphics[m].bmp, xx+126-126, yy+m*12);
        if (map_graphics[m].bmp == empty) textprintf(buffer, font_small, xx-126+150, yy+m*12, makecol(255,128,128), "%d - \"%s\"", current_map.tile_index[m].index_num, current_map.tile_index[m].address);
        else textprintf(buffer, font_small, xx-126+150, yy+m*12, makecol(255,255,255), "%d - \"%s\"", current_map.tile_index[m].index_num, current_map.tile_index[m].address);
    }
}

void draw_map_info(int xx, int yy)
{
    textprintf(buffer, font_small, xx, yy, makecol(255,255,255), "\"%s\"", current_map.title.c_str());
    textprintf(buffer, font_small, xx, yy+10, makecol(255,255,255), "Size: (%d x %d)", current_map.size.x, current_map.size.y);
    textprintf(buffer, font_x_small, xx, yy+23, makecol(255,255,255), "Spawn: (%d,%d)", current_map.spawn.x, current_map.spawn.y);
    textprintf(buffer, font_x_small, xx, yy+30, makecol(255,255,255), "Camera: (%d,%d)", current_map.camera_start.x, current_map.camera_start.y);
    textprintf(buffer, font_x_small, xx, yy+37, makecol(255,255,255), "Time Limit: %d", current_map.time_limit);
    draw_tile_index(xx, yy+55);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


bool is_switch_active(int block_number)
{
    block_number -= BLOCK_SWITCH_BLOCK;

    for (int i=0; i<current_level.switch_stick.size(); i++)
    {
        if (current_level.switch_stick[i].index_num == block_number) return current_level.switch_stick[i].active;
    }
    return false;
}


void swap_switch_stick(int index_num)
{
    for (int i=0; i<current_level.switch_stick.size(); i++)
    {
        if (current_level.switch_stick[i].index_num == index_num)
        {
            if (current_level.switch_stick[i].active == false) current_level.switch_stick[i].active = true;
            else if (current_level.switch_stick[i].active == true) current_level.switch_stick[i].active = false;
            return;
        }
    }
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// CAMERA


class camera_class
{
public:
    float x; // the left
    float y; // the top

    float lock_x;
    float lock_y;
    float min_x;
    float min_y;
    float max_x;
    float max_y;
    float facing_direction_padding;

    float counter_x;
    float counter_y;
    float counter_update_speed;

    float moving_from_x;
    float moving_from_y;

    int camera_block_number;

    bool x_free_beomming_restrained;
    bool y_free_beomming_restrained;

    // ---

    float top(float f) { return y = f; }
    float left(float f) { return x = f; }
    float bottom(float f) { return y = f-SCREEN_H; }
    float right(float f) { return x = f-SCREEN_W; }
    float center(float f) { return x = f-SCREEN_W/2; }
    float middle(float f) { return y = f-SCREEN_H/2; }

    float top() { return y; }
    float left() { return x; }
    float bottom() { return y + SCREEN_H; }
    float right() { return x + SCREEN_W; }
    float center() { return x + SCREEN_W/2; }
    float middle() { return y + SCREEN_H/2; }

    // ---

    camera_class()
    {
        init();
    }

    void init()
    {
        x = 0;
        y = 0;

        facing_direction_padding = 320 * 1.5;

        counter_x = 0.0f;
        counter_y = 0.0f;
        counter_update_speed = 0.025f;

        x_free_beomming_restrained = false;
        y_free_beomming_restrained = false;

        camera_block_number = -1;

        // frees up the camera
        control(-1, -1, -1, -1, -1, -1);
    }

    void start_x_move_from(float xx)
    {
         moving_from_x = xx;
         counter_x = 1.0f;
    }

    void start_y_move_from(float yy)
    {
         moving_from_y = yy;
         counter_y = 1.0f;
    }

    void update_counter()
    {
         counter_x -= counter_update_speed;
         if (counter_x < 0) counter_x = 0.0f;

         counter_y -= counter_update_speed;
         if (counter_y < 0) counter_y = 0.0f;
    }

    bool x_locked() { if (lock_x != -1) return true; return false; }
    bool y_locked() { if (lock_y != -1) return true; return false; }
    bool x_mined() { if (min_x != -1) return true; return false; }
    bool x_maxed() { if (max_x != -1) return true; return false; }
    bool y_mined() { if (min_y != -1) return true; return false; }
    bool y_maxed() { if (max_y != -1) return true; return false; }

    bool camera_is_free()
    {
        if (x_locked()) return false;
        if (y_locked()) return false;
        if (x_mined()) return false;
        if (x_maxed()) return false;
        if (y_mined()) return false;
        if (y_maxed()) return false;
        return true;
    }

    // ---

    bool change_in_xx(float lock_xx, float min_xx, float max_xx)
    {
        if (lock_x != lock_xx) return true;
        if (min_x != min_xx) return true;
        if (max_x != max_xx) return true;

        return false;
    }

    bool change_in_yy(float lock_yy, float min_yy, float max_yy)
    {
        if (lock_y != lock_yy) return true;
        if (min_y != min_yy) return true;
        if (max_y != max_yy) return true;

        return false;
    }

    bool is_no_change(float lock_xx, float lock_yy, float min_xx, float min_yy, float max_xx, float max_yy)
    {
        if (lock_x != lock_xx) return false;
        if (lock_y != lock_yy) return false;
        if (min_x != min_xx) return false;
        if (min_y != min_yy) return false;
        if (max_x != max_xx) return false;
        if (max_y != max_yy) return false;

        return true;
    }

    #define NO_CHANGE      1
    #define RESTRAINED     3
    #define FREED          4
    #define RE_RESTRAINED  2

    int get_change_type(float num1, float num2)
    {
        if (num1 == num2) { return NO_CHANGE; } // no change
        else if ((num1 == -1) && (num2 != -1)) { return RESTRAINED; } // the camera is being restrained
        else if ((num1 != -1) && (num2 == -1)) { return FREED; } // the camera is being freed
        else { return RE_RESTRAINED; } // the camera is being re-restrained
    }


    bool control(float lock_xx, float lock_yy, float min_xx, float min_yy, float max_xx, float max_yy)
    {
        // returns true if there is a change
        if (is_no_change(lock_xx, lock_yy, min_xx, min_yy, max_xx, max_yy)) return false;

        bool x_changed = false;
        bool y_changed = false;

        if (change_in_xx(lock_xx, min_xx, max_xx))
        {
            if ((max_x == -1) && ( min_x == -1) && (lock_x == -1)) { x_free_beomming_restrained = true; }
            else { y_free_beomming_restrained = false; }
            x_changed = true;
        }
        if (change_in_yy(lock_yy, min_yy, max_yy))
        {
            if ((max_y == -1) && ( min_y == -1) && (lock_y == -1)) { y_free_beomming_restrained = true;}
            else { y_free_beomming_restrained = false; }
            y_changed = true;
        }


        lock_x = lock_xx;
        lock_y = lock_yy;

        max_y = max_yy;
        min_y = min_yy;
        max_x = max_xx;
        min_x = min_xx;

        if (x_changed) start_x_move_from(x);
        if (y_changed) start_y_move_from(y);

        return true;
    }

    void lock(float lock_xx, float lock_yy)
    {
        control(lock_xx, lock_yy, -1, -1, -1, -1);
    }

    int set_to_block(int cam_num)
    {
        cam_num -= BLOCK_CAMERA;
        int map_camera_index = -1;

        for (int i=0; i<current_map.cam.size(); i++)
        {
            if (current_map.cam[i].index_num == cam_num) map_camera_index = i;
        }

        if (map_camera_index == -1) return 0;

        control(current_map.cam[map_camera_index].lock_x,
                current_map.cam[map_camera_index].lock_y,
                current_map.cam[map_camera_index].min_x,
                current_map.cam[map_camera_index].min_y,
                current_map.cam[map_camera_index].max_x,
                current_map.cam[map_camera_index].max_y);

        camera_block_number = map_camera_index;

        return 0;
    }

    void prevent_scrolling_off_map()
    {
        if (x < 0) x = 0;
        if (y < 0) y = 0;

        if (right() > current_map.size.x*TILE_SIZE)
        {
            x = current_map.size.x*TILE_SIZE - SCREEN_W;
            if (x < 0) center(current_map.center());
        }
        if (bottom() > current_map.size.y*TILE_SIZE)
        {
            y = current_map.size.y*TILE_SIZE - SCREEN_H;
            if (y < 0) middle(current_map.middle());
        }
    }

    void set_camera_center_to(float xx, float yy)
    {
        x = xx - SCREEN_W/2;
        y = yy - SCREEN_H/2;
    }

    void center_on_player()
    {
        set_camera_center_to(player.get_center(), player.get_middle());
    }

    void update_with_no_grace()
    {
        if (x_mined() && (x < min_x)) x = min_x;
        if (x_maxed() && (x > max_x)) x = max_x;
        if (y_mined() && (y < min_y)) y = min_y;
        if (y_maxed() && (y > max_y)) y = max_y;

        if (x_locked()) x = lock_x;
        if (y_locked()) y = lock_y;

        if (camera_is_free()) center_on_player();

        prevent_scrolling_off_map();
        camera_x = x;
        camera_y = y;
    }

    float distance(float x1, float x2)
    {
        float result = x1 - x2;
        if (result < 0) result *= -1;
        return result;
    }

    void update_with_grace()
    {
        float destination_x;
        float destination_y;

        destination_x = player.get_center() - SCREEN_W/2;
        destination_y = player.get_middle() - SCREEN_H/2;

        if (x_mined() && (destination_x < min_x)) destination_x = min_x;
        if (x_maxed() && (destination_x > max_x)) destination_x = max_x;
        if (y_mined() && (destination_y < min_y)) destination_y = min_y;
        if (y_maxed() && (destination_y > max_y)) destination_y = max_y;

        if (x_locked()) destination_x = lock_x;
        if (y_locked()) destination_y = lock_y;

        if (x_free_beomming_restrained) { if (distance(player.get_center() - SCREEN_W/2, destination_x) < distance(moving_from_x, destination_x)) moving_from_x = player.get_center() - SCREEN_W/2; }
        if (y_free_beomming_restrained) { if (distance(player.get_middle() - SCREEN_H/2, destination_y) < distance(moving_from_y, destination_y)) moving_from_y = player.get_middle() - SCREEN_H/2; }


        x = destination_x + (moving_from_x - destination_x) * counter_x;
        y = destination_y + (moving_from_y - destination_y) * counter_y;

        prevent_scrolling_off_map();

        camera_x = x;
        camera_y = y;
    }

    void update()
    {
        update_counter();
        update_with_grace();
    }
};


camera_class camera;




void draw_door(int door_type, int tile_x, int tile_y)
{
    ALLEGRO_BITMAP *door_img = NULL;

    switch(door_type)
    {
        case DOOR_TYPE_NORMAL:
             door_img = door_normal;
             break;
        case DOOR_TYPE_LOCKED:
             door_img = door_locked;
             break;
        case DOOR_TYPE_UNLOCKED:
             door_img = door_unlocked;
             break;
        case DOOR_TYPE_LOCKED_SILVER:
             door_img = door_locked_silver;
             break;
        case DOOR_TYPE_UNLOCKED_SILVER:
             door_img = door_unlocked_silver;
             break;
        case DOOR_TYPE_LOCKED_SECRET:
             door_img = door_locked_secret;
             break;
        case DOOR_TYPE_UNLOCKED_SECRET:
             door_img = door_unlocked_secret;
             break;
        case DOOR_TYPE_EXIT_ONLY:
             door_img = door_exit_only;
             break;
        default:
             break;
    }

    if (!door_img) { allegro_message("bad door images"); return; }
    draw_sprite(buffer, door_img, tile_x*TILE_SIZE - (int)camera.x, tile_y*TILE_SIZE - (int)camera.y);
}

class door_drawing_class
{
public:
    int tile_x;
    int tile_y;
    int type;
    int map_index;
    int door_index;
    bool top_left_set;

    door_drawing_class(int _door_index, int _map_index, int _type, int _tile_x, int _tile_y)
    {
        door_index = _door_index;
        tile_x = _tile_x;
        tile_y = _tile_y;
        type = _type;
        map_index = _map_index;
        top_left_set = false;
    }

    void draw()
    {
        //allegro_message("tile_x %d\ntile_y%d\nmap_index %d\ncurrent_map_index %d", tile_x, tile_y, map_index, current_level.current_map_index);
        if ((tile_x == -1) || (tile_y == -1)) return;
        if (current_level.current_map_index == map_index)
        {
            draw_door(type, tile_x, tile_y);
        }
    }
};


#include <sstream>
using namespace std;

template< class Type >
std::string ToString( Type value )
{
   std::stringstream s;
   s << value;
   return s.str();
}

class door_drawing_manager_class
{
public:
    vector<door_drawing_class> door;

    door_drawing_manager_class()
    {
        clear_all();
    }

    void clear_all()
    {
        for (int i=door.size()-1; i>=0; i--) door.pop_back();
    }

    void add_door(int door_index, int type, int map_index=-1, int tile_x=-1, int tile_y=-1)
    {
        door.push_back(door_drawing_class(door_index, map_index, type, tile_x, tile_y));
    }

    // ******** call this when loading the level;
    void populate_level_door_data(level_class *lc)
    {
        clear_all();

        string message = "";

        for (int i=0; i<lc->door.size(); i++)
        {
            add_door(lc->door[i].index_num, lc->door[i].type);
        }
    }

    bool top_left_already_set(int index_num)
    {
        for (int i=0; i<door.size(); i++)
        {
           if (index_num == door[i].door_index)
           {
               if (door[i].top_left_set) return true;
               else return false;
           }
        }
        return true;
    }

    void _set_door_coordinates(int index_num, int door_in_map_index_num, int tile_x, int tile_y)
    {
        for (int i=0; i<door.size(); i++)
        {
           if (index_num == door[i].door_index)
           {
                door[i].tile_x = tile_x;
                door[i].tile_y = tile_y;
                door[i].top_left_set = true;
                door[i].map_index = door_in_map_index_num;
           }
        }
    }

    // ******** call this when loading the map
    void set_door_tile_coordinates(map_class *mc)
    {
        //if (door.size() == 0) {allegro_message("empty door list"); return;}

        for (int k=0; k<mc->size.y; k++)
        {
           for (int h=0; h<mc->size.x; h++)
           {
               int tile_num = mc->tile[h][k].boundry;
               if (((tile_num >= BLOCK_DOOR) && (tile_num <= 899999)))
               {
                    int maps_door_index = tile_num - BLOCK_DOOR;
                    if (!top_left_already_set(maps_door_index))
                    {
                        //allegro_message("found a door!\n\nindex: %d\nat %d, %d", maps_door_index, h, k);
                        _set_door_coordinates(maps_door_index, current_level.current_map_index, h, k);
                    }
               }
           }
        }
    }

    void update_door_type(int index_num, int type)
    {
        for (int i=0; i<door.size(); i++)
        {
            if (door[i].door_index == index_num) door[i].type = type;
        }
    }

    void update_doors(level_class *lc)
    {
        for (int i=0; i<lc->door.size(); i++)
        {
            update_door_type(lc->door[i].index_num, lc->door[i].type);
        }
    }

    void draw()
    {
        for (int i=0; i<door.size(); i++) door[i].draw();
    }
};


door_drawing_manager_class door_drawing_manager;

// find the tile_index num for locked door
// if door is unlocked
// draw unlocked graphic
// if door is locked
// draw locked graphic

// make sure map incldes unlocked door graphic if it has locked door graphic



void play_ball_bounce_sound(float screen_pos_x)
{
    float pan;
    pan = (float)screen_pos_x/SCREEN_W;

    pan = (pan) * 255;
    play_sample(ball_bounce_sample, 64, (int)pan, 900+(rand()%201), false);
}


int get_x_location_of_door(int index_num)
{
    for (int i=0; i<door_drawing_manager.door.size(); i++)
    {
       if ((door_drawing_manager.door[i].door_index == index_num) && (door_drawing_manager.door[i].map_index == current_level.get_current_map_index())) return door_drawing_manager.door[i].tile_x*16;
    }

    return -1;
}

int get_y_location_of_door(int index_num)
{
    for (int i=0; i<door_drawing_manager.door.size(); i++)
    {
       if ((door_drawing_manager.door[i].door_index == index_num) && (door_drawing_manager.door[i].map_index == current_level.get_current_map_index())) return door_drawing_manager.door[i].tile_y*16;
    }

    return -1;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




bool is_trigger_block(int tile_num)
{                                                                            
    if ((tile_num >= BLOCK_TRIGGER) && (tile_num < BLOCK_TRIGGER+9999))
    {
        return true;
    }

    return false;
}


class trigger_class
{
public:
    int index_num;
    int map_num;
    int tile_x;
    int tile_y;
    bool active;

    trigger_class(int _index_num, int _map_num, int tile_xx, int tile_yy)
    {
        tile_x = tile_xx;
        tile_y = tile_yy;
        index_num = _index_num;
        map_num = _map_num;
        active = false;
    }

    void turn_on() { active = true; }

    void turn_off() { active = false; }

    void draw()
    {
        if (current_level.current_map_index == map_num)
        {
            if (active) { if (trigger_on) draw_sprite(buffer, trigger_on, tile_x*16 - (int)camera_x, tile_y*16 - (int)camera_y - 10); }
            else { if (trigger_off) draw_sprite(buffer, trigger_off, tile_x*16 - (int)camera_x, tile_y*16 - (int)camera_y - 10); }
        }
    }
};



#include <algorithm>

bool operator< (const trigger_class &tc1, const trigger_class &tc2)
{
   return tc1.index_num < tc2.index_num;
}



class trigger_manger_class
{
public:
   vector<trigger_class> trigger;
   vector<int> push_order;

   trigger_manger_class()
   {
      clear_all();
   }

   void clear_all()
   {
      for (int i=trigger.size()-1; i>=0; i--) trigger.pop_back();
      clear_push_order();
   }

   void clear_push_order()
   {
      for (int i=push_order.size()-1; i>=0; i--) push_order.pop_back();
   }

   void add_trigger_to_list(int index_num, int map_num, int tile_xx, int tile_yy)
   {
      bool number_already_used = false;
      for (int i=0; i<trigger.size(); i++)
      {
         if ((trigger[i].index_num == index_num) && (trigger[i].map_num == map_num)) number_already_used = true;
      }

      if (!number_already_used)
      {
         trigger.push_back(trigger_class(index_num, map_num, tile_xx, tile_yy));
      }
   }


   //*** call this whenever loading a map
   void populate_list(map_class *mc)
   {
      clear_all();

      for (int k=0; k<mc->size.y; k++)
      {
         for (int h=0; h<mc->size.x; h++)
         {
            if (is_trigger_block(mc->tile[h][k].boundry))
            {
                add_trigger_to_list(mc->tile[h][k].boundry-BLOCK_TRIGGER, current_level.current_map_index, h, k); // this last argument is kind of silly
            }
         }
      }

      sort(trigger.begin(), trigger.end());
   }


   void make_all_inactive()
   {
      for (int i=0; i<trigger.size(); i++) trigger[i].turn_off();
   }

   void make_all_active()
   {
      for (int i=0; i<trigger.size(); i++) trigger[i].turn_on();
   }

   void turn_on(int index_num)
   {
      for (int i=0; i<trigger.size(); i++)
      {
         if ((trigger[i].index_num == index_num) && (!trigger[i].active))
         {
             trigger[i].turn_on();
             push_order.push_back(index_num);
         }
      }
   }

   void turn_off(int index_num)
   {
      for (int i=0; i<trigger.size(); i++)
      {
         if ((trigger[i].index_num == index_num)  && (trigger[i].active)) trigger[i].turn_off();
      }
   }


   bool are_all_active()
   {
      for (int i=0; i<trigger.size(); i++) { if (!trigger[i].active) return false; }
      return true;
   }

   // put this in the main layer thing
   void draw()
   {
      for (int i=0; i<trigger.size(); i++) trigger[i].draw();
   }


   bool first_pushed_is_not_least()
   {
      for (int p=0; p<push_order.size(); p++)
      {
          for (int i=0; i<trigger.size(); i++)
          {
              if ((trigger[i].index_num < push_order[p]) && (!trigger[i].active)) return true;
          }
      }

      return false;
   }

   bool triggers_activated_in_order()
   {
      if (first_pushed_is_not_least()) return false;

      if (push_order.size() == 1) return true;

      for (int i=1; i<push_order.size(); i++)
      {
         if (push_order[i-1] > push_order[i]) return false;
      }
      return true;
   }

};


trigger_manger_class trigger_manager;


void attempt_to_turn_on_trigger(int index_num)
{
    trigger_manager.turn_on(index_num);
}


void test_for_incorrect_order()
{
    if (!trigger_manager.triggers_activated_in_order())
    {
       trigger_manager.make_all_inactive();
       trigger_manager.clear_push_order();
       // play_error_sound();
    }
}

////////////////////////////////////////////////////////////////////////////////



class awards_class
{
public:
    vector<int> chain_award;
    vector<int> fer_award;

    awards_class()
    {
       clear_all();
    }

    void clear_all()
    {
       for (int i=chain_award.size()-1; i>=0; i--) chain_award.pop_back();
       for (int i=fer_award.size()-1; i>=0; i--) fer_award.pop_back();
    }

    void add_chain(int i)
    {
       chain_award.push_back(i);
    }

    void add_fer(int i)
    {
       fer_award.push_back(i);
    }

    bool fer_achieved(int num)
    {
       for (int i=0; i<fer_award.size(); i++)  if (fer_award[i] >= num) return true;
       return false;
    }

    bool chain_achieved(int num)
    {
       for (int i=0; i<chain_award.size(); i++)  if (chain_award[i] >= num) return true;
       return false;
    }
};

awards_class awards;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool active_jewels_in_map()
{
    for (int i=0; i<current_level.power_up.size(); i++)
    {
        if (current_level.power_up[i].map_num == current_level.get_current_map_index())
        {
            if (current_level.power_up[i].alive) return true;
        }
    }

    return false;
}


bool live_enemies_in_map()
{
    for (int i=0; i<current_level.enemy.size(); i++)
    {
        if (current_level.enemy[i].map_num == current_level.get_current_map_index())
        {
            if (current_level.enemy[i].params.alive()) return true;
        }
    }

    return false;
}


bool has_solution_been_found(int door_index)
{
    for (int i=0; i<current_level.door.size(); i++)
    {
        if ((current_level.door[i].index_num == door_index) && (current_level.door[i].type == DOOR_TYPE_LOCKED_SECRET))
        {
            switch (current_level.door[i].solution)
            {
                case SECRET_SOLUTION_KILL_BEARS:
                    if (!live_enemies_in_map()) return true;
                    break;
                case SECRET_SOLUTION_COLLECT_JEWELS:
                    if (!active_jewels_in_map()) return true;
                    break;
                case SECRET_SOLUTION_TRIGGER_ALL:
                    if (trigger_manager.are_all_active()) return true;
                    break;
                case SECRET_SOLUTION_TRIGGER_ORDERED:
                    if (trigger_manager.triggers_activated_in_order() && trigger_manager.are_all_active()) return true;
                    break;
                default:
                    break;
            }
            if ((current_level.door[i].solution > SECRET_SOLUTION_FER_OF) && (current_level.door[i].solution <= SECRET_SOLUTION_FER_OF+999))
            {
                if (awards.fer_achieved(current_level.door[i].solution - SECRET_SOLUTION_FER_OF)) return true;
            }
            else if ((current_level.door[i].solution > SECRET_SOLUTION_CHAIN_OF) && (current_level.door[i].solution <= SECRET_SOLUTION_CHAIN_OF+999))
            {
                if (awards.chain_achieved(current_level.door[i].solution - SECRET_SOLUTION_CHAIN_OF)) return true;
            }

        }
    }

    test_for_incorrect_order();

    return false;
}



void play_secret_found_sound();
void start_door_found_animation(float start_xx, float start_yy, float end_xx, float end_yy);

void test_for_solved_secret_door()
{
    bool secret_found = false;

    for (int i=0; i<current_level.door.size(); i++)
    {
       if (has_solution_been_found(current_level.door[i].index_num))
       {
           current_level.door[i].type = DOOR_TYPE_UNLOCKED_SECRET;
           secret_found = true;
           start_door_found_animation(camera_x+SCREEN_W/2, camera_y+SCREEN_H/2, get_x_location_of_door(current_level.door[i].index_num)+16, get_y_location_of_door(current_level.door[i].index_num)+24);
       }
    }

    if (secret_found) play_secret_found_sound();
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
#define DEFAULT_BULLET_X_VELOCITY   4.0f
#define DEFAULT_BULLET_Y_VELOCITY   -1.75f


float f_abs(float f)
{
   if (f < 0.0f) return f * -1.0f;
   return f;
}


class gun_bullet_class
{
public:
    float x;
    float y;

    float velocity_x;
    float velocity_y;

    bool active;

    gun_bullet_class(float xx, float yy, float velocity_xx, float velocity_yy, bool shooting_right)
    {
        x = xx;
        y = yy;
        velocity_x = DEFAULT_BULLET_X_VELOCITY;
        if (!shooting_right) velocity_x *= -1;
        velocity_x += velocity_xx;
        velocity_y = DEFAULT_BULLET_Y_VELOCITY + velocity_yy;

        active = true;
    }

    bool outside_screen()
    {
         if ((int)x-(int)camera.x < 0-64) return true;
         if ((int)x-(int)camera.x > SCREEN_W+64) return true;
         if ((int)y-(int)camera.y < 0-64) return true;
         if ((int)y-(int)camera.y > SCREEN_H+64) return true;
         return false;
    }



    void test_vertical_map_collisions()
    {
        bool char_collides_next = false;
        bool char_collides_now = false;

        if (velocity_y > 0.0f) // falling
        {
            if (block_type_at((int)(x), (int)(y+velocity_y)+1) == BLOCK_DESTRUCTABLE) return;
            if (is_platform_block(block_type_at((int)(x), (int)(y+velocity_y)+1)))
            {
                char_collides_next = true;
            }
            if (is_platform_block(block_type_at((int)(x), (int)y)))
            {
                char_collides_now = true;
            }
        }
        if ((!char_collides_now) && (char_collides_next))
        {
            velocity_y *= -0.8f;
            y = block_top_edge(((int)(y+velocity_y+8)+1)/16) - 1;
            if (velocity_y < -1.0f) play_ball_bounce_sound(x - camera.x);
        }
        else if (velocity_y < 0.0f) // jumping
        {
            if (block_type_at((int)(x), (int)(y+velocity_y)-1) == BLOCK_DESTRUCTABLE) return;
            if (is_ceiling_block(block_type_at((int)(x), (int)(y+velocity_y)-1)))
            {
                velocity_y *= -0.8f;
                y = block_bottom_edge(((int)(y+velocity_y-8)-1)/16) + 1;
                play_ball_bounce_sound(x - camera.x);
            }
        }
    }

    void test_horizontal_map_collisions()
    {
        bool char_collides_next = false;
        bool char_collides_now = false;

        if (velocity_x > 0.0f) // falling
        {
            if (block_type_at((int)(x+velocity_x)+1, (int)(y)) == BLOCK_DESTRUCTABLE) return;
            if (is_left_wall_block(block_type_at((int)(x+velocity_x)+1, (int)(y))))
            {
                char_collides_next = true;
            }
            if (is_left_wall_block(block_type_at((int)(x), (int)y)))
            {
                char_collides_now = true;
            }
        }
        if ((!char_collides_now) && (char_collides_next))
        {
            velocity_x *= -1.0f;
            x = block_left_edge(((int)(x+velocity_x+8)+1)/16) - 1;
            play_ball_bounce_sound(x - camera.x);
        }

        else if (velocity_x < 0.0f) // jumping
        {
            if (block_type_at((int)(x+velocity_x)-1, (int)(y)) == BLOCK_DESTRUCTABLE) return;
            if (is_right_wall_block(block_type_at((int)(x+velocity_x)-1, (int)(y))))
            {
                velocity_x *= -1.0f;
                x = block_right_edge(((int)(x+velocity_x-8)-1)/16) + 1;
                play_ball_bounce_sound(x - camera.x);
            }
        }
    }


    void ricochet()
    {
        velocity_x *= -1.0f;
        velocity_y *= -1.0f;
    }

    void update()
    {
        if (active)
        {
           if (velocity_x > 0) velocity_x -= 0.03f;
           else if (velocity_x < 0) velocity_x += 0.03f;
           velocity_y += GRAVITY;
           if (velocity_y > TERMINAL_VELOCITY) velocity_y = TERMINAL_VELOCITY;

           test_vertical_map_collisions();
           y += velocity_y;
           test_horizontal_map_collisions();
           x += velocity_x;

           float min_motion_range = 0.05f;
           if ((f_abs(velocity_x) < min_motion_range) && (f_abs(velocity_y) < min_motion_range)) active = false;
        }

        if (outside_screen()) active = false;
    }

    void kill()
    {
        active = false;
    }

    void draw()
    {
        if (active) draw_sprite(buffer, bullet_img, (int)x-al_get_bitmap_width(bullet_img)/2-(int)camera.x, (int)y-al_get_bitmap_height(bullet_img)/2-(int)camera.y);
    }
};


class gun_bullet_manager_class
{
public:
    vector<gun_bullet_class> bullet;

    void add_bullet(float x, float y, float velocity_x, float velocity_y, bool shooting_right)
    {
        bullet.push_back(gun_bullet_class(x, y, velocity_x, velocity_y, shooting_right));
    }

    void clear_all()
    {
        bullet.empty();
    }

    void update()
    {
        for (int i=0; i<bullet.size(); i++)
        {
            bullet[i].update();
            if (!bullet[i].active) bullet.erase(bullet.begin()+i);
        }
    }

    void draw()
    {
        for (int i=0; i<bullet.size(); i++) bullet[i].draw();
    }
};


gun_bullet_manager_class bullet_manager;





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void play_use_key_sound();


ALLEGRO_BITMAP *get_random_sparkle()
{
    int num = rand()%4;

    switch(num)
    {
       case 0: return sparkle_particle_0; break;
       case 1: return sparkle_particle_1; break;
       case 2: return sparkle_particle_2; break;
       case 3: return sparkle_particle_3; break;
       default: return sparkle_particle_0; break;
    }

    return NULL;
}


class sparkle_effect_class
{
public:
    float x;
    float y;
    float velocity_x;
    float velocity_y;

    bool on_switch;

    int lifespan;

    bool active;

    ALLEGRO_BITMAP *img;

    // ---

    sparkle_effect_class(float xx, float yy, float velocity_xx, float velocity_yy, int _lifespan, bool _on_switch=true)
    {
       x = xx;
       y = yy;
       velocity_x = velocity_xx;
       velocity_y = velocity_yy;

       lifespan = _lifespan;

       on_switch = _on_switch;
       active = true;
    }

    void set_image(ALLEGRO_BITMAP *b)
    {
        img = b;
    }

    void update_vertical_velocity()
    {
        bool char_collides_next = false;
        bool char_collides_now = false;

        if (velocity_y > 0.0f) // falling
        {
            //if (block_type_at((int)(x), (int)(y+velocity_y)+1) == BLOCK_DESTRUCTABLE) return;
            if (is_platform_block(block_type_at((int)(x), (int)(y+velocity_y)+1)))
            {
                char_collides_next = true;
            }
            if (is_platform_block(block_type_at((int)(x), (int)y)))
            {
                char_collides_now = true;
            }
        }
        if ((!char_collides_now) && (char_collides_next))
        {
            velocity_y *= -0.8f;
            y = block_top_edge(((int)(y+velocity_y+8)+1)/16) - 1;
            //if (velocity_y < -1.0f) play_ball_bounce_sound(x - camera.x);
        }
        else if (velocity_y < 0.0f) // jumping
        {
            //if (block_type_at((int)(x), (int)(y+velocity_y)-1) == BLOCK_DESTRUCTABLE) return;
            if (is_ceiling_block(block_type_at((int)(x), (int)(y+velocity_y)-1)))
            {
                velocity_y *= -0.8f;
                y = block_bottom_edge(((int)(y+velocity_y-8)-1)/16) + 1;
                //play_ball_bounce_sound(x - camera.x);
            }
        }
    }

    bool update()
    {
       if (active)
       {

          velocity_y += GRAVITY/2;
          update_vertical_velocity();

          x += velocity_x;
          y += velocity_y;
          on_switch = !on_switch;

          lifespan -= 1;
          if (lifespan < 0)
          {
            lifespan = 0;
            active = false;
          }
       }

       return active;
    }

    void draw()
    {
       if (active && img) draw_sprite(buffer, img, (int)(x-camera.x), (int)(y-camera.y));
    }
};




class sparkle_effect_manager_class
{
public:
    vector<sparkle_effect_class> sparkle;

    sparkle_effect_manager_class()
    {
        clear_all();
    }

    void clear_all()
    {
        for (int i=sparkle.size()-1; i>=0; i--) sparkle.pop_back();
    }

    void add_sparkle(float x, float y, float velocity_x, float velocity_y, int lifespan, bool on_switch=true)
    {
        sparkle.push_back(sparkle_effect_class(x, y, velocity_x, velocity_y, lifespan, on_switch));
    }

    void add_cluster(float x, float y, float velocity_x, float velocity_y, float padding, float velocity_padding, int density=10, int lifespan_min=10, int lifespan_max=30)
    {
        float particle_x;
        float particle_y;
        float particle_velocity_x;
        float particle_velocity_y;
        bool particle_on;
        int lifespan;

        for (int i=0; i<density; i++)
        {
            particle_x = random_float(0, padding) - padding/2 + x;
            particle_y = random_float(0, padding) - padding/2 + y;

            particle_velocity_x = random_float(0, velocity_padding) - velocity_padding/2 + velocity_x;
            particle_velocity_y = random_float(0, velocity_padding) - velocity_padding/2 + velocity_y - random_float(-1.0, 1.5f);

            particle_on = random_bool();

            lifespan = random_int(lifespan_min, lifespan_max);

            add_sparkle(particle_x, particle_y, particle_velocity_x, particle_velocity_y, lifespan, particle_on);
            sparkle[sparkle.size()-1].set_image(get_random_sparkle());
        }

    }

    void draw()
    {
        for (int i=0; i<sparkle.size(); i++) sparkle[i].draw();
    }

    void update()
    {
        for (int i=0; i<sparkle.size(); i++) { if (!sparkle[i].update()) sparkle.erase(sparkle.begin() + i); }
    }
};


sparkle_effect_manager_class particle_effect_manager;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class block_destruction_particle_class
{
public:
    float x;
    float y;
    float velocity_x;
    float velocity_y;

    int counter;
    bool active;

    int type;  // 1 2 or 3

    block_destruction_particle_class(float xx, float yy, float velocity_xx, float velocity_yy, int particle_type, int _counter=50)
    {
        active = true;
        counter = _counter;

        x = xx;
        y = yy;
        velocity_x = velocity_xx;
        velocity_y = velocity_yy;

        type = particle_type;
    }

    void test_vertical_map_collisions()
    {
        bool char_collides_next = false;
        bool char_collides_now = false;

        if (velocity_y > 0.0f) // falling
        {
            if (is_platform_block(block_type_at((int)(x), (int)(y+velocity_y)+1)))
            {
                char_collides_next = true;
            }
            if (is_platform_block(block_type_at((int)(x), (int)y)))
            {
                char_collides_now = true;
            }
        }
        if ((!char_collides_now) && (char_collides_next))
        {
            if (velocity_y > 0.25f) play_random_rock_sample(64, (int)((float)(x-camera.x)/SCREEN_W*255), random_int(800, 1000));
            velocity_y *= -0.4f;
            y = block_top_edge(((int)(y+velocity_y+8)+1)/16) - 1;
        }
        else if (velocity_y < 0.0f) // jumping
        {
            if (is_ceiling_block(block_type_at((int)(x), (int)(y+velocity_y)-1)))
            {
                play_random_rock_sample(64, (int)((float)(x-camera.x)/SCREEN_W*255), random_int(800, 1000));
                velocity_y *= -0.4f;
                y = block_bottom_edge(((int)(y+velocity_y-8)-1)/16) + 1;
            }
        }
    }

    void test_horizontal_map_collisions()
    {
        bool char_collides_next = false;
        bool char_collides_now = false;

        if (velocity_x > 0.0f) // falling
        {
            if (is_left_wall_block(block_type_at((int)(x+velocity_x)+1, (int)(y))))
            {
                char_collides_next = true;
            }
            if (is_left_wall_block(block_type_at((int)(x), (int)y)))
            {
                char_collides_now = true;
            }
        }
        if ((!char_collides_now) && (char_collides_next))
        {
            velocity_x *= -0.4f;
            x = block_left_edge(((int)(x+velocity_x+8)+1)/16) - 1;
            play_random_rock_sample(64, (int)((float)(x-camera.x)/SCREEN_W*255), random_int(800, 1000));
        }

        else if (velocity_x < 0.0f) // jumping
        {
            if (is_right_wall_block(block_type_at((int)(x+velocity_x)-1, (int)(y))))
            {
                velocity_x *= -0.4f;
                x = block_right_edge(((int)(x+velocity_x-8)-1)/16) + 1;
                play_random_rock_sample(64, (int)((float)(x-camera.x)/SCREEN_W*255), random_int(800, 1000));
            }
        }
    }


    void update()
    {
        counter -= 1;
        if (counter < 0) { counter = 0; active = false; }

        if (active)
        {
            velocity_y += GRAVITY;
            test_vertical_map_collisions();
            y += velocity_y;

            //void apply_drag
            test_horizontal_map_collisions();
            x += velocity_x;
        }
    }

    void draw()
    {
         if (!active) return;

         ALLEGRO_BITMAP *b;

         switch(type)
         {
             case 1:
                  b = destructable_block_shard_1;
                  break;
             case 2:
                  b = destructable_block_shard_2;
                  break;
             case 3:
                  b = destructable_block_shard_3;
                  break;
         }

         draw_sprite(buffer, b, (int)x-al_get_bitmap_width(b)/2-(int)camera.x, (int)y-al_get_bitmap_height(b)/2-(int)camera.y);
    }
};


class block_destruction_class
{
public:
    vector<block_destruction_particle_class> particle;

    block_destruction_class() { clear_all(); }

    void add_particles(float xx, float yy, float velocity_xx=0, float velocity_yy=0)
    {
         int counter = 50;

         velocity_xx /= 2;
         velocity_yy /= 2;

         particle.push_back(block_destruction_particle_class(xx, yy, velocity_xx-1, velocity_yy-3, 1, 30 + rand()%40));
         particle.push_back(block_destruction_particle_class(xx, yy, velocity_xx-1, velocity_yy-1, 2, 20 + rand()%40));
         particle.push_back(block_destruction_particle_class(xx, yy, velocity_xx+1, velocity_yy+2, 3, 20 + rand()%40));
    }

    void clear_all()
    {
        for (int i=particle.size()-1; i>=0; i--) particle.pop_back();
    }

    void update()
    {
        for (int i=0; i<particle.size(); i++) { particle[i].update(); if (!particle[i].active) particle.erase(particle.begin()+i); }
    }

    void draw()
    {
        for (int i=0; i<particle.size(); i++) particle[i].draw();
    }
};

block_destruction_class block_destruction_manager;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void draw_item_centered(int item_type, int x, int y);


#define USE_KEY_START_ANGLE    -90.0f
class use_key_animation_class
{
public:
    float x; float y;
    float center_x; float center_y;
    int item_type;

    float distance;
    float angle;
    float angle_speed;

    bool active;

    use_key_animation_class(float center_xx, float center_yy, bool silver_key=false)
    {
        center_x = center_xx;
        center_y = center_yy;

        active = true;
        angle = USE_KEY_START_ANGLE;
        distance = 40.0f;
        angle_speed = 7.0f;
        if (silver_key) item_type = silver_key_const;
        else item_type = key_const;
    }

   bool update()
   {
       if (active)
       {
          angle += angle_speed;

          x = cos(get_radians(angle)) * distance + center_x;
          y = sin(get_radians(angle)) * distance + center_y;

          //particle_effect_manager.add_cluster(x, y, 0, 0, 20.0f, 3.0f, 3, 20, 50);

          if (angle > (USE_KEY_START_ANGLE+360.0f))
          {
             active = false;
             play_use_key_sound();
             particle_effect_manager.add_cluster(x, y, 0, 0, 30.0f, 4.0f, 70, 30, 100);
             // open_door;
          }
       }

       return active;
   }

   void draw()
   {
       if (active) draw_item_centered(item_type, (int)(x-camera.x), (int)(y-camera.y));
   }
};



class use_key_animation_manager_class
{
public:
   vector<use_key_animation_class> key_object;


   use_key_animation_manager_class()
   {
       clear_all();
   }

   void add_key(float x, float y, bool silver_key=false)
   {
       key_object.push_back(use_key_animation_class(x, y, silver_key));
   }

   void update()
   {
       for (int i=0; i<key_object.size(); i++)
       {
           if (!key_object[i].update()) key_object.erase(key_object.begin() + i);
       }
   }

   void draw()
   {
       for (int i=0; i<key_object.size(); i++) key_object[i].draw();
   }

   void clear_all()
   {
       for (int i=key_object.size()-1; i>=0; i--) key_object.pop_back();
   }

   bool active()
   {
       if (key_object.size() == 0) return false;
       return true;
   }

};

use_key_animation_manager_class use_key_animation_manager;





/////////////////////////////////////



#define SOLVE_DOOR_START_ANGLE    -90.0f

#define START_RADIUS  100
#define END_RADIUS     0

#define SOLVE_DOOR_ANIMATION_DURATION  150
#define SOLVE_DOOR_WAIT_A_SEC_DURATION  50


class solved_door_animation_class
{
public:
    float start_x; float start_y;
    float end_x; float end_y;

    int distance_counter;

    float angle;
    float angle_speed;

    bool active;

    int wait_a_sec_duration;
    bool poped_the_door;

    solved_door_animation_class(float start_xx, float start_yy, float end_xx, float end_yy, int duration=SOLVE_DOOR_ANIMATION_DURATION)
    {
        start_x = start_xx;
        start_y = start_yy;

        end_x = end_xx;
        end_y = end_yy;

        active = true;
        poped_the_door = false;

        angle = SOLVE_DOOR_START_ANGLE;

        distance_counter = duration;

        wait_a_sec_duration = SOLVE_DOOR_WAIT_A_SEC_DURATION;

        //distance = 40.0f;
        angle_speed = 7.0f;
    }

    float get_center_x()
    {
       return (start_x - end_x)*get_distance_normal() + end_x;
    }

    float get_center_y()
    {
       return (start_y - end_y)*get_distance_normal() + end_y;
    }

    float get_distance_normal()
    {
       //return ((float)distance_counter / (float)SOLVE_DOOR_ANIMATION_DURATION)*-1.0f + 1.0f;
       return ((float)distance_counter / (float)SOLVE_DOOR_ANIMATION_DURATION);
    }

   bool update()
   {
       if (active)
       {
          if (poped_the_door)
          {
              wait_a_sec_duration--;

              if (wait_a_sec_duration < 0)
              {
                 wait_a_sec_duration = 0;
                 active = false;
              }
          }
          else
          {
             angle += angle_speed;
             distance_counter--;

             if (distance_counter < 0)
             {
                distance_counter = 0;
                //active = false;
                poped_the_door = true;
                play_use_key_sound();
                particle_effect_manager.add_cluster(end_x, end_y, 0, -2.0f, 30.0f, 4.0f, 100, 30, 100);
                door_drawing_manager.update_doors(&current_level);
             }


             float distance_normal = get_distance_normal();

             float final_radius = (START_RADIUS - END_RADIUS)*distance_normal + END_RADIUS;
             float center_x = (start_x - end_x)*distance_normal + end_x;
             float center_y = (start_y - end_y)*distance_normal + end_y;

             float particle_x = cos(get_radians(angle)) * final_radius + center_x;
             float particle_y = sin(get_radians(angle)) * final_radius + center_y;

             particle_effect_manager.add_cluster(particle_x, particle_y, 0, 0, 0.0f, 4.0f, 2, 20, 50);
          }
       }

       return active;
   }

   void draw()
   {
       //if (active) draw_item_centered(item_type, (int)(x-camera.x), (int)(y-camera.y));
   }
};





class solved_door_animation_manager_class
{
public:
    vector<solved_door_animation_class> animation;

    solved_door_animation_manager_class()
    {
        clear_all();
    }

    void start_effect(float start_xx, float start_yy, float end_xx, float end_yy, int duration=SOLVE_DOOR_ANIMATION_DURATION)
    {
        animation.push_back(solved_door_animation_class(start_xx, start_yy, end_xx, end_yy, duration));
    }

    void clear_all()
    {
        for (int i=animation.size()-1; i>=0; i--) animation.pop_back();
    }

    void update()
    {
        for (int i=animation.size()-1; i>=0; i--) animation[i].update();
    }

    bool active()
    {
        for (int i=animation.size()-1; i>=0; i--)
        {
            if (animation[i].active) return true;
        }

        return false;
    }

    float get_x()
    {
        if (animation.size() > 0) return animation[0].get_center_x();
        return -1.0f;
    }

    float get_y()
    {
        if (animation.size() > 0) return animation[0].get_center_y();
        return -1.0f;
    }
};



solved_door_animation_manager_class solved_door_animation_manager;



void start_door_found_animation(float start_xx, float start_yy, float end_xx, float end_yy)
{
    solved_door_animation_manager.clear_all();
    solved_door_animation_manager.start_effect(start_xx, start_yy, end_xx, end_yy);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


bool is_switch_block(int tile_num)
{                                                                            
    if ((tile_num >= BLOCK_SWITCH_BLOCK) && (tile_num < BLOCK_SWITCH_BLOCK+9999))
    {
        return true;
    }

    return false;
}

bool is_switch_stick(int tile_num)
{
    if ((tile_num >= BLOCK_SWITCH) && (tile_num < BLOCK_SWITCH+9999))
    {
        return true;
    }

    return false;
}





bool player_on_switch_block = false;

bool check_switch_behind_player()
{
     int block_below_block_behind_player = block_type_at(player.get_center_int(), player.get_middle_int()+16);
     int block_behind_player = block_type_at(player.get_center_int(), player.get_middle_int()+16+16);

     bool good_to_go = false;
     int switch_num = -1;

     if (is_switch_stick(block_behind_player)) { good_to_go = true; switch_num = block_behind_player-BLOCK_SWITCH; }
     if (is_switch_stick(block_below_block_behind_player)) { good_to_go = true; switch_num = block_behind_player-BLOCK_SWITCH; }

     if (good_to_go)
     {
         if (!player_on_switch_block)
         {
            player_on_switch_block = true;
            play_switch_sound();
            swap_switch_stick(switch_num);
            //my_error_message2("got here %d", switch_num);
         }
     }
     else
     {
         player_on_switch_block = false;
     }
     return good_to_go;
}






void draw_switch_blocks_and_switches(int tile_num, int tile_h, int tile_k, int xx, int yy)
{
   switch_block_struct *sbs;
   int block_number = tile_num;

   if (is_switch_block(tile_num))
   {
       block_number -= BLOCK_SWITCH_BLOCK;
   }
   else if (is_switch_stick(tile_num))
   {
       block_number -= BLOCK_SWITCH;
   }



   switch (block_number)
   {
       case 1:
            sbs = &switch_block_1;
            break;
       case 2:
            sbs = &switch_block_2;
            break;
       case 3:
            sbs = &switch_block_3;
            break;
       case 4:
            sbs = &switch_block_4;
            break;
       case 5:
            sbs = &switch_block_5;
            break;
       case 6:
            sbs = &switch_block_6;
            break;
       case 7:
            sbs = &switch_block_7;
            break;
       case 8:
            sbs = &switch_block_8;
            break;
       case 9:
            sbs = &switch_block_9;
            break;
       default:
            return;
            break;
   }



   if (is_switch_block(tile_num))
   {
      if (is_switch_active(tile_num))
      {
         if (sbs->block_on) draw_sprite(buffer, sbs->block_on, (tile_h*TILE_SIZE)-xx, (tile_k*TILE_SIZE)-yy);
      }
      else
      {
         if (sbs->block_off) draw_sprite(buffer, sbs->block_off, (tile_h*TILE_SIZE)-xx, (tile_k*TILE_SIZE)-yy);
      }
   }



   if (is_switch_stick(tile_num))
   {
      if (is_switch_active(tile_num+100000))
      {
         if (sbs->switch_on) draw_sprite(buffer, sbs->switch_on, (tile_h*TILE_SIZE)-xx, (tile_k*TILE_SIZE)-yy-16-8);
      }
      else
      {
         if (sbs->switch_off) draw_sprite(buffer, sbs->switch_off, (tile_h*TILE_SIZE)-xx, (tile_k*TILE_SIZE)-yy-16-8);
      }
   }

}



bool is_a_locked_or_unlocked_door(int tile_num);
void draw_locked_or_unlocked_door(int door_num, int x, int y);

int limit(int n, int lower, int upper) {
  return std::max(lower, std::min(n, upper));
}

void draw_map_layer(int layer, int xx=0, int yy=0)
{
     layer--;
     if (layer < 0) layer = 0;
     else if (layer > 2) layer = 2;

     int h=0;
     int k=0;
     int the_number_of_tiles_in_the_maps_index = current_map.num_of_tiles();
     bool done_with_loop = false;


			//al_lock_bitmap(atlas, ALLEGRO_LOCK_READWRITE, ALLEGRO_PIXEL_FORMAT_ANY);

		int padding = -1;

		int minx = xx / 16 + padding;
		int maxx = (xx + SCREEN_W) / 16 - padding;
		int miny = yy / 16 + padding;
		int maxy = (yy + SCREEN_H) / 16 - padding;


		// limit
		minx = limit(minx, 0, current_map.size.x);
		maxx = limit(maxx, 0, current_map.size.x);
		miny = limit(miny, 0, current_map.size.y);
		maxy = limit(maxy, 0, current_map.size.y);


     for (k=miny; k<=maxy; k++)
     {
         for (h=minx; h<=maxx; h++)
         {
             int the_index_of_the_tile_being_drawn = current_map.tile[h][k].layer[layer];

             if (the_index_of_the_tile_being_drawn != 0)
             {
                 done_with_loop = false;
                 int the_map_array_number_of_the_tile_currently_being_tested=0;
                 int the_index_of_the_tile_from_the_map_index=0;

                 while (!done_with_loop)
                 {
                     the_index_of_the_tile_from_the_map_index = current_map.tile_index[the_map_array_number_of_the_tile_currently_being_tested].index_num;
                     if (the_index_of_the_tile_being_drawn == current_map.locked_door_index_num)
                     {
                         if (is_a_locked_or_unlocked_door(current_map.tile[h][k].boundry)) draw_locked_or_unlocked_door(current_map.tile[h][k].boundry-800000, (h*TILE_SIZE)-xx, (k*TILE_SIZE)-yy);
                     }
                     else if (the_index_of_the_tile_being_drawn == the_index_of_the_tile_from_the_map_index)
                     {
                         done_with_loop = true;
                         draw_sprite_FAST(map_graphics[the_map_array_number_of_the_tile_currently_being_tested].bmp, (h*TILE_SIZE)-xx, (k*TILE_SIZE)-yy);
                     }
                     the_map_array_number_of_the_tile_currently_being_tested++;
                     if (the_map_array_number_of_the_tile_currently_being_tested > the_number_of_tiles_in_the_maps_index)
                     {
                         done_with_loop=true;
								// not sure what this is for
                         //draw_sprite(buffer, empty, (h*TILE_SIZE)-xx, (k*TILE_SIZE)-yy);
                     }
                 }
             }



             if (layer == 2)
             {
                 if (current_map.tile[h][k].boundry == BLOCK_DESTRUCTABLE) draw_sprite(buffer, destructable_block, (h*TILE_SIZE)-xx, (k*TILE_SIZE)-yy);
             }

             if (layer == 1)
             {
                 draw_switch_blocks_and_switches(current_map.tile[h][k].boundry, h, k, xx, yy);
             }
         }
     }

		//al_unlock_bitmap(atlas);
}

/*
void old_draw_map_layer(int layer, int xx=0, int yy=0)
{
     layer--;
     if (layer < 0) layer = 0;
     else if (layer > 2) layer = 2;

     int h=0;
     int k=0;
     int the_number_of_tiles_in_the_maps_index = current_map.num_of_tiles();
     bool done_with_loop = false;

     for (k=0; k<current_map.size.y; k++)
     {
         for (h=0; h<current_map.size.x; h++)
         {
             int the_index_of_the_tile_being_drawn = current_map.tile[h][k].layer[layer];

             if (the_index_of_the_tile_being_drawn != 0)
             {
                 done_with_loop = false;
                 int the_map_array_number_of_the_tile_currently_being_tested=0;
                 int the_index_of_the_tile_from_the_map_index=0;

                 while (!done_with_loop)
                 {
                     the_index_of_the_tile_from_the_map_index = current_map.tile_index[the_map_array_number_of_the_tile_currently_being_tested].index_num;
                     if (the_index_of_the_tile_being_drawn == the_index_of_the_tile_from_the_map_index)
                     {
                         done_with_loop = true;
                         draw_sprite(buffer, map_graphics[the_map_array_number_of_the_tile_currently_being_tested].bmp, (h*TILE_SIZE)-xx, (k*TILE_SIZE)-yy);
                     }
                     the_map_array_number_of_the_tile_currently_being_tested++;
                     if (the_map_array_number_of_the_tile_currently_being_tested > the_number_of_tiles_in_the_maps_index)
                     {
                         done_with_loop=true;
                         draw_sprite(buffer, empty, (h*TILE_SIZE)-xx, (k*TILE_SIZE)-yy);
                     }
                 }
             }
         }
     }// end for-next loops
}
*/

void draw_boundry_block(ALLEGRO_BITMAP *b, int x, int y, int boundry_block, ALLEGRO_COLOR col=YELLOW)
{
      switch (boundry_block)
      {
           case BOUNDRY_1:
                hline(b, x, y, x+15, col);  // top
                break;
           case BOUNDRY_2:
                vline(b, x+15, y, y+15, col);  // right
                break;
           case BOUNDRY_3:
                hline(b, x, y+15, x+15, col);  // bottom
                break;
           case BOUNDRY_4:
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_5:
                hline(b, x, y, x+15, col);  // top
                vline(b, x+15, y, y+15, col);  // right
                break;
           case BOUNDRY_6:
                vline(b, x+15, y, y+15, col);  // right
                hline(b, x, y+15, x+15, col);  // bottom
                break;
           case BOUNDRY_7:
                hline(b, x, y+15, x+15, col);  // bottom
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_8:
                hline(b, x, y, x+15, col);  // top
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_9:
                hline(b, x, y, x+15, col);  // top
                hline(b, x, y+15, x+15, col);  // bottom
                break;
           case BOUNDRY_10:
                vline(b, x+15, y, y+15, col);  // right
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_11:
                hline(b, x, y, x+15, col);  // top
                vline(b, x+15, y, y+15, col);  // right
                hline(b, x, y+15, x+15, col);  // bottom
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_12:
                break;
           case BOUNDRY_13:
                vline(b, x+15, y, y+15, col);  // right
                hline(b, x, y+15, x+15, col);  // bottom
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_14:
                hline(b, x, y, x+15, col);  // top
                hline(b, x, y+15, x+15, col);  // bottom
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_15:
                hline(b, x, y, x+15, col);  // top
                vline(b, x+15, y, y+15, col);  // right
                vline(b, x, y, y+15, col);  // left
                break;
           case BOUNDRY_16:
                hline(b, x, y, x+15, col);  // top
                vline(b, x+15, y, y+15, col);  // right
                hline(b, x, y+15, x+15, col);  // bottom
                break;
           case BLOCK_LADDER:
                hline(b, x, y, x+15, makecol(255,128,0));
                hline(b, x, y+4, x+15, makecol(255,128,0));
                hline(b, x, y+8, x+15, makecol(255,128,0));
                hline(b, x, y+12, x+15, makecol(255,128,0));
                break;
           case BLOCK_UNLOCK_CAMERA:
                line(b, x+0, y+0, x+15, y+15, makecol(128,255,128));
                line(b, x+15, y+0, x, y+15, makecol(128,255,128));
                break;
           case BLOCK_GOAL_1:
                hline(b, x, y, x+15, RED);  // top
                vline(b, x+15, y, y+15, RED);  // right
                hline(b, x, y+15, x+15, RED);  // bottom
                vline(b, x, y, y+15, RED);  // left
                break;
           case BLOCK_DEATH:
                line(b, x+0, y+0, x+15, y+15, makecol(255,0,0));
                line(b, x+15, y+0, x, y+15, makecol(255,0,0));
                break;
           case BLOCK_DESTRUCTABLE:
                hline(b, x, y, x+15, makecol(255,0,128));  // top
                vline(b, x+15, y, y+15, makecol(255,0,128));  // right
                hline(b, x, y+15, x+15, makecol(255,0,128));  // bottom
                vline(b, x, y, y+15, makecol(255,0,128));  // left

                hline(b, x, y+4, x+15, makecol(255,0,128));
                hline(b, x, y+12, x+15, makecol(255,0,128));
                break;
           default:
                if ((boundry_block >= BLOCK_CAMERA) && (boundry_block < BLOCK_CAMERA+99999))
                {
                   hline(b, x, y, x+15, makecol(128, 255, 255));  // top
                   vline(b, x+15, y, y+15, makecol(128, 255, 255));  // right
                   hline(b, x, y+15, x+15, makecol(128, 255, 255));  // bottom
                   vline(b, x, y, y+15, makecol(128, 255, 255));  // left
                   textprintf(b, font_x_small, x+2, y+1, makecol(255,255,255), "%d", boundry_block-BLOCK_CAMERA);
                }
                else if ((boundry_block >= BLOCK_SWITCH) && (boundry_block < BLOCK_SWITCH+99999))
                {
                   hline(b, x, y, x+15, makecol(255, 128, 0));  // top
                   vline(b, x+15, y, y+15, makecol(255, 128, 0));  // right
                   hline(b, x, y+15, x+15, makecol(255, 128, 0));  // bottom
                   vline(b, x, y, y+15, makecol(255, 128, 0));  // left
                   //line(b, x, y+10, x+5, y+15, makecol(255, 128, 0));  // bottom left diagonal
                   //textprintf(b, font_x_small, x+2, y+1, makecol(255,255,255), "%d", boundry_block-BLOCK_CAMERA);
                   textprintf(b, font_x_small, x+2, y+1, makecol(255,255,255), "%d", boundry_block-BLOCK_SWITCH);
                }
                else if ((boundry_block >= BLOCK_SWITCH_BLOCK) && (boundry_block < BLOCK_SWITCH_BLOCK+99999))
                {
                   hline(b, x, y, x+15, makecol(255, 64, 0));  // top
                   vline(b, x+15, y, y+15, makecol(255, 64, 0));  // right
                   hline(b, x+5, y+15, x+15, makecol(255, 64, 0));  // bottom
                   vline(b, x, y, y+15-5, makecol(255, 64, 0));  // left
                   line(b, x, y+10, x+5, y+15, makecol(255, 64, 0));  // bottom left diagonal
                   //textprintf(b, font_x_small, x+2, y+1, makecol(255,255,255), "%d", boundry_block-BLOCK_CAMERA);

                }
                else if ((boundry_block >= BLOCK_TRIGGER) && (boundry_block < BLOCK_TRIGGER+99999))
                {
                   hline(b, x, y, x+15, makecol(64, 255, 0));  // top
                   vline(b, x+15, y, y+15, makecol(64, 255, 0));  // right
                   hline(b, x, y+15, x+15, makecol(64, 255, 0));  // bottom
                   vline(b, x, y, y+15, makecol(64, 255, 0));  // left

                   vline(b, x+8, y-6, y, makecol(64, 255, 0)); // stem
                   hline(b, x+3+1, y-6, x+15-3, makecol(64, 255, 0));  // top

                   textprintf(b, font_x_small, x+2, y+1, makecol(255,255,255), "%d", boundry_block-BLOCK_TRIGGER);
                }
                if (boundry_block >= BLOCK_DOOR)
                {
                   hline(b, x, y, x+15, makecol(255, 255, 128));  // top
                   vline(b, x+15, y, y+15, makecol(255, 255, 128));  // right
                   hline(b, x, y+15, x+15, makecol(255, 255, 128));  // bottom
                   vline(b, x, y, y+15, makecol(255, 255, 128));  // left
                   textprintf(b, font_x_small, x+2, y+1, makecol(255,255,255), "%d", boundry_block-BLOCK_DOOR);
                }
                break;
      }

}

void draw_map_boundrys(ALLEGRO_BITMAP *b, int xx, int yy)
{
     int h=0;
     int k=0;

     for (k=0; k<current_map.size.y; k++)
     {
         for (h=0; h<current_map.size.x; h++)
         {
              draw_boundry_block(b, h*TILE_SIZE-xx, k*TILE_SIZE-yy, current_map.tile[h][k].boundry);
         }
     }
}

void draw_map(void)
{
     if (F_draw_map_layer_1) draw_map_layer(1, (int)(camera.x), (int)(camera.y));
     if (F_draw_map_layer_2) draw_map_layer(2, (int)(camera.x), (int)(camera.y));
     door_drawing_manager.draw();
     trigger_manager.draw();
}

void draw_map_front_layer(void)
{
     if (F_draw_map_layer_3) draw_map_layer(3, (int)(camera.x), (int)(camera.y));
     //if (F_draw_boundrys && (drawing_destination != DRAWING_TO_BOUNDRY)) draw_map_boundrys(buffer, (int)(camera.x), (int)(camera.y));

     //draw_big_blocks_layer_mid(1, (int)(((camera.x+SCREEN_W/2)/16)*17)-SCREEN_W/2, (int)(((camera.y+SCREEN_H/2)/16)*17)-SCREEN_H/2);
     //draw_big_blocks_layer(1, (int)(((camera.x+SCREEN_W/2)/16)*18)-SCREEN_W/2, (int)(((camera.y+SCREEN_H/2)/16)*18)-SCREEN_H/2);
}




////////////////////////////////////////////////////////////////////////////////
// TESTING

int block_type_at(int x, int y)
{
     return current_map.tile[x/16][y/16].boundry;
}

int graphic_block_type_at(int x, int y)
{
     return current_map.tile[x/16][y/16].boundry;
}

int block_left_edge(int horiz)
{
     return (horiz*16);
}
int block_right_edge(int horiz)
{
     return ((horiz+1)*16);
}
int block_top_edge(int vertic)
{
     return (vertic*16);
}
int block_bottom_edge(int vertic)
{
     return ((vertic+1)*16);
}




bool is_platform_block(int type)
{
    if (type == BOUNDRY_1) return true;
    if (type == BOUNDRY_5) return true;
    if (type == BOUNDRY_8) return true;
    if (type == BOUNDRY_9) return true;
    if (type == BOUNDRY_11) return true;
    if (type == BOUNDRY_14) return true;
    if (type == BOUNDRY_15) return true;
    if (type == BOUNDRY_16) return true;
    if (type == BLOCK_DESTRUCTABLE) return true;
    if ((type >= BLOCK_SWITCH_BLOCK) && (type < BLOCK_SWITCH_BLOCK+99999) && is_switch_active(type)) return true;
    if ((type >= BLOCK_TRIGGER) && (type < BLOCK_TRIGGER+99999)) return true;
    if (is_switch_stick(type)) return true;
    else return false;
}

bool is_passable_platform_block(int type)
{
    if (type == BOUNDRY_1) return true;
    if (type == BOUNDRY_5) return true;
    if (type == BOUNDRY_8) return true;
    if (type == BOUNDRY_9) return true;
    //if (type == BOUNDRY_11) return true;
    if (type == BOUNDRY_14) return true;
    if (type == BOUNDRY_15) return true;
    if (type == BOUNDRY_16) return true;
    if ((type >= BLOCK_SWITCH_BLOCK) && (type < BLOCK_SWITCH_BLOCK+99999) && is_switch_active(type)) return true;
    if ((type >= BLOCK_TRIGGER) && (type < BLOCK_TRIGGER+99999)) return true;
    if (is_switch_stick(type)) return true;
    else return false;
}

bool is_ceiling_block(int type)
{
    if (type == BOUNDRY_3) return true;
    if (type == BOUNDRY_6) return true;
    if (type == BOUNDRY_7) return true;
    if (type == BOUNDRY_9) return true;
    if (type == BOUNDRY_11) return true;
    if (type == BOUNDRY_13) return true;
    if (type == BOUNDRY_14) return true;
    if (type == BOUNDRY_16) return true;
    if (type == BLOCK_DESTRUCTABLE) return true;
    if ((type >= BLOCK_SWITCH_BLOCK) && (type < BLOCK_SWITCH_BLOCK+99999) && is_switch_active(type)) return true;
    if ((type >= BLOCK_TRIGGER) && (type < BLOCK_TRIGGER+99999)) return true;
    if (is_switch_stick(type)) return true;
    else return false;
}

bool is_right_wall_block(int type)
{
    if (type == BOUNDRY_4) return true;
    if (type == BOUNDRY_7) return true;
    if (type == BOUNDRY_8) return true;
    if (type == BOUNDRY_10) return true;
    if (type == BOUNDRY_11) return true;
    if (type == BOUNDRY_13) return true;
    if (type == BOUNDRY_14) return true;
    if (type == BOUNDRY_15) return true;
    if (type == BLOCK_DESTRUCTABLE) return true;
    if ((type >= BLOCK_SWITCH_BLOCK) && (type < BLOCK_SWITCH_BLOCK+99999) && is_switch_active(type)) return true;
    if ((type >= BLOCK_TRIGGER) && (type < BLOCK_TRIGGER+99999)) return true;
    if (is_switch_stick(type)) return true;
    else return false;
}

bool is_left_wall_block(int type)
{
    if (type == BOUNDRY_2) return true;
    if (type == BOUNDRY_5) return true;
    if (type == BOUNDRY_6) return true;
    if (type == BOUNDRY_10) return true;
    if (type == BOUNDRY_11) return true;
    if (type == BOUNDRY_13) return true;
    if (type == BOUNDRY_15) return true;
    if (type == BOUNDRY_16) return true;
    if (type == BLOCK_DESTRUCTABLE) return true;
    if ((type >= BLOCK_SWITCH_BLOCK) && (type < BLOCK_SWITCH_BLOCK+99999) && is_switch_active(type)) return true;
    if ((type >= BLOCK_TRIGGER) && (type < BLOCK_TRIGGER+99999)) return true;
    if (is_switch_stick(type)) return true;
    else return false;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void clear_picked_up_items(void);


int load_map_from_level(int map_num, const char *address)
{
    if (current_map.load(address, map_num) == 1) return 1;

    player.map_pos.x = current_map.spawn.x;
    player.map_pos.y = current_map.spawn.y;
    player.velocity.x = 0.0f;
    player.velocity.y = 0.0f;

    camera.control(-1, -1, -1, -1, -1, -1);

    clear_picked_up_items();
    bullet_manager.clear_all();
    particle_effect_manager.clear_all();
    block_destruction_manager.clear_all();
    use_key_animation_manager.clear_all();
    awards.clear_all();


    camera.x = current_map.camera_start.x;
    camera.y = current_map.camera_start.y;
    camera.max_x = current_map.camera_max.x;
    camera.max_y = current_map.camera_max.y;
    camera.lock_x = current_map.camera_lock.x;
    camera.lock_y = current_map.camera_lock.y;
    camera.min_x = current_map.camera_min.x;
    camera.min_y = current_map.camera_min.y;

    return 0;
}


int save_lv2_file(const char *fn)
{

        ofstream outfile(full_filename(fn));

        if (!outfile)
        {
				ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
            rectfill(screen, 100, 100, SCREEN_W-100, SCREEN_H-100, makecol(64,16,0));
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(255,128+16,128), "unable to save map", fn);
            textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", fn);
				al_flip_display();
            readkey();
            return 1;
        }

        int h=0;
        int k=0;
        outfile << "//.lv2 file for Beary's Bash by Mark Oates" << endl;
        outfile << "// http://markoates.bafsoft.com" << endl;
        outfile << "// questions? comments? euph_boy@hotmail.com" << endl;
        outfile << endl;
        outfile << "[params]" << endl;
        outfile << "title: " << current_level.title << endl;
        outfile << "time limit: " << current_level.time_limit << endl;
        outfile << "gold time: " << current_level.gold_time << endl;
        outfile << "silver time: " << current_level.silver_time << endl;
        outfile << "bronze time: " << current_level.bronze_time << endl;
        outfile << "number of maps: " << current_level.number_of_maps << endl;
        outfile << "levelshot: \"" << current_level.snapshot_address << "\"" << endl;
        outfile << endl;
        //outfile << "[maps]" << endl;
        //for (k=0; k<map_index.size(); k++)
        //{
        //    outfile << map_index[k].index_num << " \"" << map_index[k].address << "\"" << endl;
        //}
        //outfile << endl;
        for (k=0; k<current_level.door.size(); k++)
        {
            outfile << "[door " << current_level.door[k].index_num << "]" << endl;
            outfile << "new map: " << current_level.door[k].go_to_new_map << endl;
            outfile << "spawn x: " << current_level.door[k].map_spawn_x << endl;
            outfile << "spawn y: " << current_level.door[k].map_spawn_y << endl;
            outfile << "camera start x: " << current_level.door[k].camera_x << endl;
            outfile << "camera start y: " << current_level.door[k].camera_y << endl;
            outfile << "camera lock x: " << current_level.door[k].camera_lock_x << endl;
            outfile << "camera lock y: " << current_level.door[k].camera_lock_y << endl;
            outfile << "camera max x: " << current_level.door[k].camera_max_x << endl;
            outfile << "camera max y: " << current_level.door[k].camera_max_y << endl;
            outfile << "camera min x: " << current_level.door[k].camera_min_x << endl;
            outfile << "camera min y: " << current_level.door[k].camera_min_y << endl;
            outfile << endl;
        }
        outfile << "[enemies]" << endl;
        for (k=0; k<current_level.enemy.size(); k++)
        {
            outfile << current_level.enemy[k].map_num;
            switch (current_level.enemy[k].type)
            {
                   case ENEMY_TYPE RED_BEAR:
                        outfile << " red bear ";
                        break;
                   case ENEMY_TYPE YELLOW_BEAR:
                        outfile << " yellow bear ";
                        break;
                   case ENEMY_TYPE BLUE_BEAR:
                        outfile << " blue bear ";
                        break;
                   default:
                        outfile << " unknown enemy ";
                        break;
            }

            outfile << "(" << current_level.enemy[k].start_x << "," << current_level.enemy[k].start_y << ")" << endl;
        }
        outfile << endl;
        //outfile << eof;


        map_class gimp_map;
        map_class *process_map;
        
        int times_through = 0;


        for (times_through=0; times_through<current_level.number_of_maps; times_through++)
        {
            //times_through++;
            // if the map to be written is the current map
            if (times_through+1 == current_level.get_current_map_index())
            {
                process_map = &current_map;
            }
            // if the map to be written is not the current map
            else
            {
             ////////////!!!!!!!!!!!!!
             ////////////!!!!!!!!!!!!!
             ////////////!!!!!!!!!!!!!
             // this should be the inactive map that has the same map number as times_through
                //process_map = &current_map;
                gimp_map.load(level_to_start.c_str(), times_through+1);
                process_map = &gimp_map;
            }    

            if (!process_map) {allegro_message("error saving map"); return -1;}
            
            //int h=0;
            //int k=0;
            outfile << "[////////////////]" << endl;
            outfile << "[////////////////]" << endl;
            outfile << endl;
            outfile << "[map " << times_through+1 << "]" << endl;
            outfile << endl;
            outfile << "[params]" << endl;
            outfile << "title: " << process_map->title << endl;
            outfile << "height: " << process_map->size.y << endl;
            outfile << "width: " << process_map->size.x << endl;
            outfile << "time limit: " << process_map->time_limit << endl;
            outfile << "spawn x: " << process_map->spawn.x << endl;
            outfile << "spawn y: " << process_map->spawn.y << endl;
            outfile << "camera start x: " << process_map->camera_start.x << endl;
            outfile << "camera start y: " << process_map->camera_start.y << endl;
            outfile << "camera lock x: " << process_map->camera_lock.x << endl;
            outfile << "camera lock y: " << process_map->camera_lock.y << endl;
            outfile << "camera max x: " << process_map->camera_max.x << endl;
            outfile << "camera max y: " << process_map->camera_max.y << endl;
            outfile << "camera min x: " << process_map->camera_min.x << endl;
            outfile << "camera min y: " << process_map->camera_min.y << endl;
            outfile << endl;
            outfile << "[tile_index]" << endl;
            
            for (k=0; k<process_map->num_of_tiles(); k++)
            {
                outfile << process_map->tile_index[k].index_num << " \"" << process_map->tile_index[k].address << "\"" << endl;
            }
            outfile << endl;
            
            for (k=0; k<process_map->ramp.size(); k++)
            {
                outfile << "[ramp " << process_map->ramp[k].index_num << "]" << endl;
                outfile << "bottom x: " << process_map->ramp[k].bottom_x << endl;
                outfile << "bottom y: " << process_map->ramp[k].bottom_y << endl;
                outfile << "top x: " << process_map->ramp[k].top_x << endl;
                outfile << "top y: " << process_map->ramp[k].top_y << endl;
                outfile << endl;
            }
            
            for (k=0; k<process_map->cam.size(); k++)
            {
                outfile << "[camera " << process_map->cam[k].index_num << "]" << endl;
                outfile << "x: " << process_map->cam[k].x << endl;
                outfile << "y: " << process_map->cam[k].y << endl;
                outfile << "lock x: " << process_map->cam[k].lock_x << endl;
                outfile << "lock y: " << process_map->cam[k].lock_y << endl;
                outfile << "max x: " << process_map->cam[k].max_x << endl;
                outfile << "max y: " << process_map->cam[k].max_y << endl;
                outfile << "min x: " << process_map->cam[k].min_x << endl;
                outfile << "min y: " << process_map->cam[k].min_y << endl;
                outfile << endl;
            }
    
            int tile_out_count = 0;
            outfile << "[layer1]" << endl;
            for (k=0; k<process_map->size.y; k++)
            {
                for (h=0; h<process_map->size.x; h++)
                {
                    outfile << process_map->tile[h][k].layer[0] << " ";
                    tile_out_count++;
                    if (tile_out_count%10 == 0) outfile << endl;
                    if (tile_out_count == 100) tile_out_count = 0;
                }
            }
            outfile << endl << endl;
    
            tile_out_count = 0;
            outfile << "[layer2]" << endl;
            for (k=0; k<process_map->size.y; k++)
            {
                for (h=0; h<process_map->size.x; h++)
                {
                    outfile << process_map->tile[h][k].layer[1] << " ";
                    tile_out_count++;
                    if (tile_out_count%10 == 0) outfile << endl;
                    if (tile_out_count == 100) tile_out_count = 0;
                }
            }
            outfile << endl << endl;
            
            tile_out_count = 0;
            outfile << "[layer3]" << endl;
            for (k=0; k<process_map->size.y; k++)
            {
                for (h=0; h<process_map->size.x; h++)
                {
                    outfile << process_map->tile[h][k].layer[2] << " ";
                    tile_out_count++;
                    if (tile_out_count%10 == 0) outfile << endl;
                    if (tile_out_count == 100) tile_out_count = 0;
                }
            }
            outfile << endl << endl;
            
            tile_out_count = 0;
            outfile << "[boundrys]" << endl;
            for (k=0; k<process_map->size.y; k++)
            {
                for (h=0; h<process_map->size.x; h++)
                {
                    outfile << process_map->tile[h][k].boundry << " ";
                    tile_out_count++;
                    if (tile_out_count%10 == 0) outfile << endl;
                    if (tile_out_count == 100) tile_out_count = 0;
                }
            }
            outfile << endl << endl;
            
            tile_out_count = 0;
            outfile << "[environment]" << endl;
            for (k=0; k<process_map->size.y; k++)
            {
                for (h=0; h<process_map->size.x; h++)
                {
                    outfile << process_map->tile[h][k].environment << " ";
                    tile_out_count++;
                    if (tile_out_count%10 == 0) outfile << endl;
                    if (tile_out_count == 100) tile_out_count = 0;
                }
            }
            outfile << endl;

        }    

        outfile.close();
        
        
        string message = "level \'" + current_level.title + "\' saved.";
        int width_of_box = text_length(font_small, message.c_str()) + 40;
			ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
        rectfill(screen, SCREEN_W/2-width_of_box/2, SCREEN_H/2-20, SCREEN_W/2+width_of_box/2, SCREEN_H/2+20, makecol(0,64,16));
        textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2-7, makecol(128,255,128+32), message.c_str());
        textprintf_centre(screen, font_small, SCREEN_W/2, SCREEN_H/2-text_height(font_small)/2+5, makecol(255,255,255), "\"%s\"", fn);
			al_flip_display();

        //textprintf(screen, font, 20, 40, WHITE, "%d", times_through);

        clear_keybuf();
        readkey();
        clear_keybuf();
        return 0;
}    



bool is_a_locked_or_unlocked_door(int tile_num)
{
    if (!((tile_num < BLOCK_DOOR) || (tile_num > 899999))) return false;
    else
    {
        if (tile_num-BLOCK_DOOR >= current_level.door.size()) return false;

        int door_type = current_level.door[tile_num-1].type;

        if ((door_type == DOOR_TYPE_LOCKED)
              || (door_type == DOOR_TYPE_UNLOCKED)
              || (door_type == DOOR_TYPE_LOCKED_SECRET)
              || (door_type == DOOR_TYPE_UNLOCKED_SECRET)
              || (door_type == DOOR_TYPE_LOCKED_SILVER)
              || (door_type == DOOR_TYPE_UNLOCKED_SILVER))
              return true;
    }
    return false;
}


bool OLD_is_a_locked_or_unlocked_door(int tile_num)
{
    if (!((tile_num < BLOCK_DOOR) || (tile_num > 899999))) return false;
    else
    {
        if (tile_num-BLOCK_DOOR >= current_level.door.size()) return false;
        else if ((current_level.door[tile_num-1].type == DOOR_TYPE_LOCKED)
              || (current_level.door[tile_num-1].type == DOOR_TYPE_UNLOCKED))
              return true;
    }
    return false;
}

void draw_locked_or_unlocked_door(int door_num, int x, int y)
{
    ALLEGRO_BITMAP *image_to_draw;

    //if (current_level.door[door_num-1].type == DOOR_TYPE_LOCKED) image_to_draw = door2_locked;
    //else if(current_level.door[door_num-1].type == DOOR_TYPE_UNLOCKED) image_to_draw = door2_unlocked;

    //if (image_to_draw) draw_sprite(buffer, image_to_draw, (int)(x-camera_x), (int)(y-camera_y));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include "effects.hpp"
class draw_one_up_class
{
public:
   float_coordinate map_pos;
   int counter;

   draw_one_up_class()
   {
       map_pos.x =0;
       map_pos.y =0;
       counter = 75;
   }
   void place_here(int xx, int yy)
   {
       map_pos.x = xx;
       map_pos.y = yy;
   }
   void update_pos()
   {
       counter--;
       if (counter < 0) counter = 0;
       else map_pos.y -= 0.25;
   }
};

vector<draw_one_up_class> draw_one_ups;


//make_kill_num()

class poof_class
{
public:
    int counter;
    int_coordinate map_pos;

    void set_coordinates(int xx, int yy)
    {
        counter = 20;
        map_pos.x = xx;
        map_pos.y = yy;
    }
};

vector<poof_class> poofs;

void update_poofs()
{
    int k=0;
    bool there_are_still_poofs = false;
    for (k=poofs.size()-1; k>=0; k--)
    {
        poofs[k].counter--;
        if (poofs[k].counter <= 0)
        {
            poofs[k].counter = 0;
        }
        else there_are_still_poofs = true;
    }

    if (!there_are_still_poofs && (poofs.size() != 0)) poofs.pop_back();
}

void draw_poofs(ALLEGRO_BITMAP *b=buffer)
{
    int k=0;
    for (k=0; k<poofs.size(); k++)
    {
        if (poofs[k].counter != 0)
        {
            draw_sprite(b, poof, poofs[k].map_pos.x-(al_get_bitmap_width(poof)/2)-(int)camera_x, poofs[k].map_pos.y-(al_get_bitmap_height(poof)/2)-(int)camera_y);
        }
    }
}


///////// blood

class blood_drop_class
{
public:
    float_coordinate velocity;
    float_coordinate map_pos;
    int counter;
    bool on_ground;
    //bool size

    blood_drop_class()
    {
        velocity.x=0;
        velocity.y=0;
        map_pos.y=0;
        map_pos.y=0;
        counter = 600;
        on_ground = false;
    }


    void set_coordinate(int xx, int yy)
    {
        map_pos.x = xx;
        map_pos.y = yy;
        on_ground = false;
    }
    void set_velocity(float xx, float yy)
    {
        velocity.x = xx;
        velocity.y = yy;//yy;
        counter = 500; //(int)((rand() * ((velocity.x+velocity.y)/2*100)) + 300);
        on_ground = false;
    }

    void update_vertical_velocity(void)
    {
        if (!on_ground) velocity.y += GRAVITY;
    }
    void update_horizontal_velocity(void)
    {
        if (velocity.x > 0.0f)
        {
           velocity.x -= 0.02f;
           if (velocity.x < 0.0f) velocity.x = 0;
        }
        else if (velocity.x < 0.0f)
        {
           velocity.x += 0.02f;
           if (velocity.x > 0.0f) velocity.x = 0;
        }
    }

    bool at_platform()
    {
        if (is_platform_block(block_type_at((int)(map_pos.x), (int)(map_pos.y)+1))) return true;
        else return false;
    }

    void test_vertical_map_collisions()
    {
        bool char_collides_next = false;
        bool char_collides_now = false;
        if (velocity.y > 0.0f) // falling
        {
            if (is_platform_block(block_type_at((int)(map_pos.x), (int)(map_pos.y+velocity.y)+1)))
            {
                char_collides_next = true;
            }
            if (is_platform_block(block_type_at((int)(map_pos.x), (int)map_pos.y)))
            {
                char_collides_now = true;
            }
        }
        if ((!char_collides_now) && (char_collides_next))
        {
            velocity.y = 0.0f;
            map_pos.y = block_top_edge(((int)(map_pos.y+velocity.y+8)+1)/16) - 1;
            on_ground = true;
        }
        else if (velocity.y < 0.0f) // jumping
        {
            if (is_ceiling_block(block_type_at((int)(map_pos.x), (int)(map_pos.y+velocity.y)-1)))
            {
                velocity.y = 0.0f;
                map_pos.y = block_bottom_edge(((int)(map_pos.y+velocity.y-8)-1)/16) + 1;
            }
        }
    }

    void update_pos()
    {
        if (!at_platform()) on_ground = false;

        update_vertical_velocity();
        test_vertical_map_collisions();
        map_pos.y += velocity.y;
        update_horizontal_velocity();
        map_pos.x += velocity.x;
    }

};

vector<blood_drop_class> blood_drops;

void make_drops(int drops, float xx, float yy)
{
    if (drops < 0) drops = 0;

    int k=0;
    bool there_are_still_drops = false;
    for (k=0; k<drops; k++)
    {
        blood_drop_class gimp_blood_drops_class;
        
        gimp_blood_drops_class.set_coordinate((int)xx, (int)yy);
        gimp_blood_drops_class.set_velocity((rand()%(500))/100.0f - 2.5f, (rand()%(400))/100.0f - 4.0f);
        blood_drops.push_back(gimp_blood_drops_class);
    }
}

void make_drops2(int drops, float xx, float yy)
{
    if (drops < 0) drops = 0;

    int k=0;
    bool there_are_still_drops = false;
    for (k=0; k<drops; k++)
    {
        blood_drop_class gimp_blood_drops_class;
        
        gimp_blood_drops_class.set_coordinate((int)xx, (int)yy);
        gimp_blood_drops_class.set_velocity((rand()%(400))/100.0f - 2.0f, (rand()%(500))/100.0f - 5.0f);
        blood_drops.push_back(gimp_blood_drops_class);
    }
}

void update_blood_drops()
{
    int k=0;

    /// update the counters
    bool there_are_still_drops = false;
    for (k=blood_drops.size()-1; k>=0; k--)
    {
        blood_drops[k].update_pos();

        blood_drops[k].counter--;
        if (blood_drops[k].counter <= 0)
        {
            blood_drops[k].counter = 0;
        }
        else there_are_still_drops = true;
    }

    if (!there_are_still_drops && (blood_drops.size() != 0)) blood_drops.pop_back();
}

void draw_blood_drops(ALLEGRO_BITMAP *b=buffer)
{
    int k=0;

    int size;

    for (k=blood_drops.size()-1; k>=0; k--)
    {
        if (blood_drops[k].counter > 490)
        {
            size = 5;
        }
        else if (blood_drops[k].counter > 480)
        {
            size = 2;
        }
        else if (blood_drops[k].counter > 470)
        {
            size = 1;
        }
        else if (blood_drops[k].counter > 460)
        {
            size = 1;
        }
        else if (blood_drops[k].counter > 450)
        {
            size = 0;
        }
        else size = 0;

        if (blood_drops[k].counter != 0)
        {
            if (!blood_drops[k].on_ground)
            {
               if (ABS((int)blood_drops[k].velocity.y) >= 3.0f)
               {
                   ellipsefill(b, ((int)blood_drops[k].map_pos.x-(int)camera_x), ((int)blood_drops[k].map_pos.y-(int)camera_y),
                                  (((size+1)+1))+size,
                                  (((size+1)+1))+2+size,
                                  makecol(160, 0, 0));

                   // type 2
                   //rectfill(b, (int)(blood_drops[k].map_pos.x-camera_x)-(rand()%(size+1)+(rand()%1)),
                   //            (int)(blood_drops[k].map_pos.y-camera_y)-3-(rand()%(size+1)+(rand()%1)),
                   //            (int)(blood_drops[k].map_pos.x-camera_x)+1,
                   //            (int)(blood_drops[k].map_pos.y-camera_y)+2+(rand()%(size+1)-(rand()%1)), makecol(180, 0, 0));

               }
               else if (ABS((int)blood_drops[k].velocity.y) >= 1.0f)
               {
                   ellipsefill(b, ((int)blood_drops[k].map_pos.x-(int)camera_x), ((int)blood_drops[k].map_pos.y-(int)camera_y),
                                  (((size+1)+(1))+1+size),
                                  (((size+1)+(1))+0+size),
                                  makecol(160, 0, 0));
                   //rectfill(b, (int)(blood_drops[k].map_pos.x-camera_x)-(rand()%(size+1)+(rand()%1)),
                   //            (int)(blood_drops[k].map_pos.y-camera_y)-1-(rand()%(size+1)+(rand()%1)),
                   //            (int)(blood_drops[k].map_pos.x-camera_x)+1,
                   //            (int)(blood_drops[k].map_pos.y-camera_y)+2, makecol(190, 0, 0));
                   //type 2
                   //rectfill(b, (int)(blood_drops[k].map_pos.x-camera_x)-(rand()%(size+1)+(rand()%1)),
                   //            (int)(blood_drops[k].map_pos.y-camera_y)-1-(rand()%(size+1)+(rand()%1)),
                   //            (int)(blood_drops[k].map_pos.x-camera_x)+1,
                   //            (int)(blood_drops[k].map_pos.y-camera_y)+2, makecol(190, 0, 0));

               }
               else
               {
                   putpixel(b, ((int)blood_drops[k].map_pos.x-(int)camera_x), ((int)blood_drops[k].map_pos.y-(int)camera_y), makecol(120, 0, 0));
                   putpixel(b, ((int)blood_drops[k].map_pos.x-(int)camera_x)+1, ((int)blood_drops[k].map_pos.y-(int)camera_y)+1, makecol(120, 0, 0));
                   putpixel(b, ((int)blood_drops[k].map_pos.x-(int)camera_x), ((int)blood_drops[k].map_pos.y-(int)camera_y)+1, makecol(175, 0, 0));
                   putpixel(b, ((int)blood_drops[k].map_pos.x-(int)camera_x)+1, ((int)blood_drops[k].map_pos.y-(int)camera_y), makecol(200, 128, 128));
               }
            }
            else
            {
                //type 1
                hline(b, ((int)blood_drops[k].map_pos.x-(int)camera_x)-3, ((int)blood_drops[k].map_pos.y-(int)camera_y), ((int)blood_drops[k].map_pos.x-(int)camera_x)+3, makecol(120, 0, 0));
                hline(b, ((int)blood_drops[k].map_pos.x-(int)camera_x)-2, ((int)blood_drops[k].map_pos.y-(int)camera_y)-1, ((int)blood_drops[k].map_pos.x-(int)camera_x)+1, makecol(160, 0, 0));
                putpixel(b, ((int)blood_drops[k].map_pos.x-(int)camera_x)+2, ((int)blood_drops[k].map_pos.y-(int)camera_y)-1, makecol(200, 132, 132));

                // type 2
                //putpixel(b, (int)(blood_drops[k].map_pos.x-camera_x)-1, (int)(blood_drops[k].map_pos.y-camera_y), makecol(180, 0, 0));
                //putpixel(b, (int)(blood_drops[k].map_pos.x-camera_x), (int)(blood_drops[k].map_pos.y-camera_y), makecol(180, 0, 0));
                //putpixel(b, (int)(blood_drops[k].map_pos.x-camera_x)+1, (int)(blood_drops[k].map_pos.y-camera_y), makecol(255, 132, 132));
            }
        }
    }
}

class num_of_bears_left_class
{
public:
   float_coordinate map_pos;
   int counter;
   int num;

   num_of_bears_left_class()
   {
       map_pos.x =0;
       map_pos.y =0;
       counter = 75;
       num = 0;
   }
   void place_here(int xx, int yy)
   {
       map_pos.x = xx;
       map_pos.y = yy-10;
   }
   void update_pos()
   {
       counter--;
       if (counter < 0) counter = 0;
       else map_pos.y -= 0.5;
   }
};

vector<num_of_bears_left_class> bears_left_notif;


/*
void write_time(int x, int y, int t)
{
	int min;
	int sec;
	int hunSec;

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

	if (min >= 10) textprintf(buffer, font, x, y, BLACK, "%i", min);
	else textprintf(buffer, font, x, y, BLACK, "0%i", min);

    textprintf(buffer, font, x+15, y, BLACK, ":");

	if (sec >= 10) textprintf(buffer, font, x+22, y, BLACK, "%i", sec);
	else textprintf(buffer, font, x+22, y, BLACK, "0%i", sec);

    textprintf(buffer, font, x+13+18+1+3, y, BLACK, ":");

	if (hunSec >= 10) textprintf(buffer, font, x+37+2+3, y, BLACK, "%i", hunSec);
	else textprintf(buffer, font, x+37+2+3, y, BLACK, "0%i", hunSec);
}
*/

/*
void write_outline(int x, int y, FONT *f, int color, char *format, ...)
{
   char buf[512];

   va_list ap;
   va_start(ap, format);
   uvszprintf(buf, sizeof(buf), format, ap);
   va_end(ap);

    int outline_color = makecol(0,0,0);
    int text_color = color;

    textprintf(buffer, f, x+1, y, outline_color, buf);
    textprintf(buffer, f, x-1, y, outline_color, buf);
    textprintf(buffer, f, x, y+1, outline_color, buf);
    textprintf(buffer, f, x, y-1, outline_color, buf);
    textprintf(buffer, f, x, y, text_color, buf);
}
*/

void write_outline_center(int x, int y, FONT *f, ALLEGRO_COLOR color, const char *format, ...)
{
   char buf[512];

   va_list ap;
   va_start(ap, format);
   //uvszprintf(buf, sizeof(buf), format, ap);
   vsprintf(buf, format, ap);
   va_end(ap);

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = color;

    textprintf_centre(buffer, f, x+1, y, outline_color, buf);
    textprintf_centre(buffer, f, x-1, y, outline_color, buf);
    textprintf_centre(buffer, f, x, y+1, outline_color, buf);
    textprintf_centre(buffer, f, x, y-1, outline_color, buf);
    textprintf_centre(buffer, f, x, y, text_color, buf);
}

// EXCLUSIVE
void write_outline_center_alfont_aa(int x, int y, ALFONT_FONT *f, int size, ALLEGRO_COLOR color, const char *format, int val)
{
   //char buf[512];

/*
   va_list ap;
   va_start(ap, format);
   //uvszprintf(buf, sizeof(buf), format, ap);
   vsprintf(buf, format, ap);
   va_end(ap);
 */  
   alfont_set_font_size(f, size);

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = color;

	std::stringstream ss;
	ss << val;
	std::string buf = ss.str();

    alfont_textprintf_centre(buffer, f, x+1, y, outline_color, buf);
    alfont_textprintf_centre(buffer, f, x-1, y, outline_color, buf);
    alfont_textprintf_centre(buffer, f, x, y+1, outline_color, buf);
    alfont_textprintf_centre(buffer, f, x, y-1, outline_color, buf);
    alfont_textprintf_centre_aa(buffer, f, x, y, text_color, buf);
}

void write_outline_center_alfont_aa__to_screen(int x, int y, ALFONT_FONT *f, int size, ALLEGRO_COLOR color, std::string text)
{
	const char *buf = text.c_str();  
 
   alfont_set_font_size(f, size);

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = color;

	ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());

    alfont_textprintf_centre(screen, f, x+1, y, outline_color, buf);
    alfont_textprintf_centre(screen, f, x-1, y, outline_color, buf);
    alfont_textprintf_centre(screen, f, x, y+1, outline_color, buf);
    alfont_textprintf_centre(screen, f, x, y-1, outline_color, buf);
    alfont_textprintf_centre_aa(screen, f, x, y, text_color, buf);

	al_flip_display();
}



void write_outline_alfont_aa(int x, int y, ALFONT_FONT *f, int size, ALLEGRO_COLOR color, const char *format, ...)
{
   char buf[512];

   va_list ap;
   va_start(ap, format);
   //uvszprintf(buf, sizeof(buf), format, ap);
   vsprintf(buf, format, ap);
   va_end(ap);
   
   alfont_set_font_size(f, size);

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = color;

    alfont_textprintf(buffer, f, x+1, y, outline_color, buf);
    alfont_textprintf(buffer, f, x-1, y, outline_color, buf);
    alfont_textprintf(buffer, f, x, y+1, outline_color, buf);
    alfont_textprintf(buffer, f, x, y-1, outline_color, buf);
    alfont_textprintf_aa(buffer, f, x, y, text_color, buf);
}


void _write_outline_alfont_aa(int x, int y, ALFONT_FONT *f, int size, ALLEGRO_COLOR color, string message)
{
    alfont_set_font_size(f, size);

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = color;

    alfont_textprintf(buffer, f, x+1, y, outline_color, message.c_str());
    alfont_textprintf(buffer, f, x-1, y, outline_color, message.c_str());
    alfont_textprintf(buffer, f, x, y+1, outline_color, message.c_str());
    alfont_textprintf(buffer, f, x, y-1, outline_color, message.c_str());
    alfont_textprintf_aa(buffer, f, x, y, text_color, message.c_str());
}


void write_outline_right_alfont_aa(int x, int y, ALFONT_FONT *f, int size, ALLEGRO_COLOR color, std::string message)
{
	const char *buf = message.c_str();

    alfont_set_font_size(f, size);
    int len = alfont_text_length(f, buf);

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = color;

    alfont_textprintf(buffer, f, x+1-len, y, outline_color, buf);
    alfont_textprintf(buffer, f, x-1-len, y, outline_color, buf);
    alfont_textprintf(buffer, f, x-len, y+1, outline_color, buf);
    alfont_textprintf(buffer, f, x-len, y-1, outline_color, buf);
    alfont_textprintf_aa(buffer, f, x-len, y, text_color, buf);
}


int get_min(int t)
{
    return (int)(((float)t/(float)100)/(float)60);
}    
int get_sec(int t)
{
	return (t - ((int)(((float)t/(float)100)/(float)60))*6000)/100;
}    
int get_hun_sec(int t)
{
    return t%100;
}    

void write_time_outline(int x, int y, int t, ALLEGRO_COLOR col=WHITE)
{
	int min;
	int sec;
	int hunSec;

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = col;

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

	if (min >= 10)
    {
       textprintf(buffer, font, x+1, y, outline_color, "%i", min);
       textprintf(buffer, font, x-1, y, outline_color, "%i", min);
       textprintf(buffer, font, x, y+1, outline_color, "%i", min);
       textprintf(buffer, font, x, y-1, outline_color, "%i", min);
       textprintf(buffer, font, x, y, text_color, "%i", min);
    }
	else
    {
       textprintf(buffer, font, x+1, y, outline_color, "0%i", min);
       textprintf(buffer, font, x-1, y, outline_color, "0%i", min);
       textprintf(buffer, font, x, y+1, outline_color, "0%i", min);
       textprintf(buffer, font, x, y-1, outline_color, "0%i", min);
       textprintf(buffer, font, x, y, text_color, "0%i", min);
    }

    textprintf(buffer, font, x+15+1, y, outline_color, ":");
    textprintf(buffer, font, x+15-1, y, outline_color, ":");
    textprintf(buffer, font, x+15, y+1, outline_color, ":");
    textprintf(buffer, font, x+15, y-1, outline_color, ":");
    textprintf(buffer, font, x+15, y, text_color, ":");

	if (sec >= 10)
    {
        textprintf(buffer, font, x+22+1, y, outline_color, "%i", sec);
        textprintf(buffer, font, x+22-1, y, outline_color, "%i", sec);
        textprintf(buffer, font, x+22, y+1, outline_color, "%i", sec);
        textprintf(buffer, font, x+22, y-1, outline_color, "%i", sec);
        textprintf(buffer, font, x+22, y, text_color, "%i", sec);
    }
	else
    {
        textprintf(buffer, font, x+22+1, y, outline_color, "0%i", sec);
        textprintf(buffer, font, x+22-1, y, outline_color, "0%i", sec);
        textprintf(buffer, font, x+22, y+1, outline_color, "0%i", sec);
        textprintf(buffer, font, x+22, y-1, outline_color, "0%i", sec);
        textprintf(buffer, font, x+22, y, text_color, "0%i", sec);
    }

    textprintf(buffer, font, x+13+18+1+3+1, y, outline_color, ":");
    textprintf(buffer, font, x+13+18+1+3-1, y, outline_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y+1, outline_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y-1, outline_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y, text_color, ":");

	if (hunSec >= 10)
    {
        textprintf(buffer, font, x+37+2+3+1, y, outline_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3-1, y, outline_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y+1, outline_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y-1, outline_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y, text_color, "%i", hunSec);
    }
	else
    {
        textprintf(buffer, font, x+37+2+3+1, y, outline_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3-1, y, outline_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y+1, outline_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y-1, outline_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y, text_color, "0%i", hunSec);
    }
}

/*
void write_time_outline_aa_old(int x, int y, int t, int col=WHITE)
{
    //alfont_textprintf_aa(buffer, new_font, "00:02:37", SCREEN_W / 2, SCREEN_H / 2, makecol(255,255,255));

    ALFONT_FONT *f = new_font;

	int min;
	int sec;
	int hunSec;

    int outline_color = makecol(0,0,0);
    int text_color = col;

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

    y-=6;
    x-=1;

	if (min >= 10)
    {
       alfont_textprintf_aa(buffer, f, x+1, y, outline_color, "%i", min);
       alfont_textprintf_aa(buffer, f, x-1, y, outline_color, "%i", min);
       alfont_textprintf_aa(buffer, f, x, y+1, outline_color, "%i", min);
       alfont_textprintf_aa(buffer, f, x, y-1, outline_color, "%i", min);
       alfont_textprintf_aa(buffer, f, x, y, text_color, "%i", min);
    }
	else
    {
       alfont_textprintf_aa(buffer, f, x+1, y, outline_color, "0%i", min);
       alfont_textprintf_aa(buffer, f, x-1, y, outline_color, "0%i", min);
       alfont_textprintf_aa(buffer, f, x, y+1, outline_color, "0%i", min);
       alfont_textprintf_aa(buffer, f, x, y-1, outline_color, "0%i", min);
       alfont_textprintf_aa(buffer, f, x, y, text_color, "0%i", min);
    }

	if (sec >= 10)
    {
        alfont_textprintf_aa(buffer, f, x+22+1, y, outline_color, "%i", sec);
        alfont_textprintf_aa(buffer, f, x+22-1, y, outline_color, "%i", sec);
        alfont_textprintf_aa(buffer, f, x+22, y+1, outline_color, "%i", sec);
        alfont_textprintf_aa(buffer, f, x+22, y-1, outline_color, "%i", sec);
        alfont_textprintf_aa(buffer, f, x+22, y, text_color, "%i", sec);
    }
	else
    {
        alfont_textprintf_aa(buffer, f, x+22+1, y, outline_color, "0%i", sec);
        alfont_textprintf_aa(buffer, f, x+22-1, y, outline_color, "0%i", sec);
        alfont_textprintf_aa(buffer, f, x+22, y+1, outline_color, "0%i", sec);
        alfont_textprintf_aa(buffer, f, x+22, y-1, outline_color, "0%i", sec);
        alfont_textprintf_aa(buffer, f, x+22, y, text_color, "0%i", sec);
    }

	if (hunSec >= 10)
    {
        alfont_textprintf_aa(buffer, f, x+37+2+3+1, y, outline_color, "%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3-1, y, outline_color, "%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3, y+1, outline_color, "%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3, y-1, outline_color, "%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3, y, text_color, "%i", hunSec);
    }
	else
    {
        alfont_textprintf_aa(buffer, f, x+37+2+3+1, y, outline_color, "0%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3-1, y, outline_color, "0%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3, y+1, outline_color, "0%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3, y-1, outline_color, "0%i", hunSec);
        alfont_textprintf_aa(buffer, f, x+37+2+3, y, text_color, "0%i", hunSec);
    }

    y-=2;
    x+=4;

    alfont_textprintf_aa(buffer, f, x+15+1, y, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+15-1, y, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+15, y+1, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+15, y-1, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+15, y, text_color, ":");

    alfont_textprintf_aa(buffer, f, x+13+18+1+3+1, y, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+13+18+1+3-1, y, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+13+18+1+3, y+1, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+13+18+1+3, y-1, outline_color, ":");
    alfont_textprintf_aa(buffer, f, x+13+18+1+3, y, text_color, ":");

}
*/

/*
void write_time_outline_aa_impact(int x, int y, int t, int col=WHITE)
{
    //alfont_textprintf_aa(buffer, new_font, "00:02:37", SCREEN_W / 2, SCREEN_H / 2, makecol(255,255,255));

    ALFONT_FONT *f = new_font;

	int min;
	int sec;
	int hunSec;

    int outline_color = makecol(0,0,0);
    int text_color = col;

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

    y-=6;
    x-=1;

    int fixie = 5;

	if (min >= 10)
    {
       alfont_textprintf_centre_aa(buffer, f, x+1+fixie, y, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x-1+fixie, y, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y+1, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y-1, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y, text_color, "%i", min);
    }
	else
    {
       alfont_textprintf_centre_aa(buffer, f, x+1+fixie, y, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x-1+fixie, y, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y+1, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y-1, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y, text_color, "0%i", min);
    }

    fixie = 7;

	if (sec >= 10)
    {
        alfont_textprintf_centre_aa(buffer, f, x+22+1+fixie, y, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22-1+fixie, y, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y+1, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y-1, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y, text_color, "%i", sec);
    }
	else
    {
        alfont_textprintf_centre_aa(buffer, f, x+22+1+fixie, y, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22-1+fixie, y, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y+1, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y-1, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y, text_color, "0%i", sec);
    }

    fixie = 11;

	if (hunSec >= 10)
    {
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+1+fixie, y, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3-1+fixie, y, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y+1, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y-1, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y, text_color, "%i", hunSec);
    }
	else
    {
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+1+fixie, y, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3-1+fixie, y, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y+1, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y-1, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y, text_color, "0%i", hunSec);
    }

    y-=2;
    x+=4;

    alfont_textprintf_centre_aa(buffer, f, x+15+1-3, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-1-3, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-3, y+1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-3, y-1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-3, y, text_color, ":");

    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1+1, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3-1+1, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y+1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y-1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y, text_color, ":");
    
    alfont_destroy_font(f);

}
*/

void write_time_outline_aa(int x, int y, int t, ALLEGRO_COLOR col=WHITE)
{
    //alfont_textprintf_aa(buffer, new_font, "00:02:37", SCREEN_W / 2, SCREEN_H / 2, makecol(255,255,255));

    ALFONT_FONT *f = new_font;

	int min;
	int sec;
	int hunSec;

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = col;

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

    y-=5;
    x-=1;
    x+=8;

    int fixie = 5;

	if (min >= 10)
    {
       alfont_textprintf_centre_aa(buffer, f, x+1+fixie, y, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x-1+fixie, y, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y+1, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y-1, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y, text_color, "%i", min);
    }
	else
    {
       alfont_textprintf_centre_aa(buffer, f, x+1+fixie, y, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x-1+fixie, y, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y+1, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y-1, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y, text_color, "0%i", min);
    }

    fixie = 7;

	if (sec >= 10)
    {
        alfont_textprintf_centre_aa(buffer, f, x+22+1+fixie, y, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22-1+fixie, y, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y+1, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y-1, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y, text_color, "%i", sec);
    }
	else
    {
        alfont_textprintf_centre_aa(buffer, f, x+22+1+fixie, y, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22-1+fixie, y, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y+1, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y-1, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y, text_color, "0%i", sec);
    }

    fixie = 11;

	if (hunSec >= 10)
    {
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+1+fixie, y, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3-1+fixie, y, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y+1, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y-1, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y, text_color, "%i", hunSec);
    }
	else
    {
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+1+fixie, y, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3-1+fixie, y, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y+1, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y-1, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y, text_color, "0%i", hunSec);
    }

    y-=1;
    x+=5;

    alfont_textprintf_centre_aa(buffer, f, x+15+1-3, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-1-3, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-3, y+1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-3, y-1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+15-3, y, text_color, ":");

    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1+1, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3-1+1, y, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y+1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y-1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y, text_color, ":");

}



void write_time_outline__half_aa(int x, int y, int t, ALLEGRO_COLOR col=WHITE)
{
    //alfont_textprintf_aa(buffer, new_font, "00:02:37", SCREEN_W / 2, SCREEN_H / 2, makecol(255,255,255));

    ALFONT_FONT *f = new_font;

	int min;
	int sec;
	int hunSec;

    ALLEGRO_COLOR outline_color = makecol(0,0,0);
    ALLEGRO_COLOR text_color = col;

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

    y-=5;
    x-=1;
    x+=8;

    int fixie = 5;

	if (min >= 10)
    {
       alfont_textprintf_centre(buffer, f, x+1+fixie, y, outline_color, "%i", min);
       alfont_textprintf_centre(buffer, f, x-1+fixie, y, outline_color, "%i", min);
       alfont_textprintf_centre(buffer, f, x+fixie, y+1, outline_color, "%i", min);
       alfont_textprintf_centre(buffer, f, x+fixie, y-1, outline_color, "%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y, text_color, "%i", min);
    }
	else
    {
       alfont_textprintf_centre(buffer, f, x+1+fixie, y, outline_color, "0%i", min);
       alfont_textprintf_centre(buffer, f, x-1+fixie, y, outline_color, "0%i", min);
       alfont_textprintf_centre(buffer, f, x+fixie, y+1, outline_color, "0%i", min);
       alfont_textprintf_centre(buffer, f, x+fixie, y-1, outline_color, "0%i", min);
       alfont_textprintf_centre_aa(buffer, f, x+fixie, y, text_color, "0%i", min);
    }

    fixie = 7;

	if (sec >= 10)
    {
        alfont_textprintf_centre(buffer, f, x+22+1+fixie, y, outline_color, "%i", sec);
        alfont_textprintf_centre(buffer, f, x+22-1+fixie, y, outline_color, "%i", sec);
        alfont_textprintf_centre(buffer, f, x+22+fixie, y+1, outline_color, "%i", sec);
        alfont_textprintf_centre(buffer, f, x+22+fixie, y-1, outline_color, "%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y, text_color, "%i", sec);
    }
	else
    {
        alfont_textprintf_centre(buffer, f, x+22+1+fixie, y, outline_color, "0%i", sec);
        alfont_textprintf_centre(buffer, f, x+22-1+fixie, y, outline_color, "0%i", sec);
        alfont_textprintf_centre(buffer, f, x+22+fixie, y+1, outline_color, "0%i", sec);
        alfont_textprintf_centre(buffer, f, x+22+fixie, y-1, outline_color, "0%i", sec);
        alfont_textprintf_centre_aa(buffer, f, x+22+fixie, y, text_color, "0%i", sec);
    }

    fixie = 11;

	if (hunSec >= 10)
    {
        alfont_textprintf_centre(buffer, f, x+37+2+3+1+fixie, y, outline_color, "%i", hunSec);
        alfont_textprintf_centre(buffer, f, x+37+2+3-1+fixie, y, outline_color, "%i", hunSec);
        alfont_textprintf_centre(buffer, f, x+37+2+3+fixie, y+1, outline_color, "%i", hunSec);
        alfont_textprintf_centre(buffer, f, x+37+2+3+fixie, y-1, outline_color, "%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y, text_color, "%i", hunSec);
    }
	else
    {
        alfont_textprintf_centre(buffer, f, x+37+2+3+1+fixie, y, outline_color, "0%i", hunSec);
        alfont_textprintf_centre(buffer, f, x+37+2+3-1+fixie, y, outline_color, "0%i", hunSec);
        alfont_textprintf_centre(buffer, f, x+37+2+3+fixie, y+1, outline_color, "0%i", hunSec);
        alfont_textprintf_centre(buffer, f, x+37+2+3+fixie, y-1, outline_color, "0%i", hunSec);
        alfont_textprintf_centre_aa(buffer, f, x+37+2+3+fixie, y, text_color, "0%i", hunSec);
    }

    y-=1;
    x+=5;

    alfont_textprintf_centre(buffer, f, x+15+1-3, y, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+15-1-3, y, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+15-3, y+1, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+15-3, y-1, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+15-3, y, text_color, ":");

    alfont_textprintf_centre(buffer, f, x+13+18+1+3+1+1, y, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+13+18+1+3-1+1, y, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+13+18+1+3+1, y+1, outline_color, ":");
    alfont_textprintf_centre(buffer, f, x+13+18+1+3+1, y-1, outline_color, ":");
    alfont_textprintf_centre_aa(buffer, f, x+13+18+1+3+1, y, text_color, ":");

}



void write_time_gold(int x, int y, int t)
{
	int min;
	int sec;
	int hunSec;

    //int outline_color = makecol(0,0,0);
    //int text_color = col;
    ALLEGRO_COLOR text_color = makecol(255, 225, 84);

    //int rand_int = rand()%30;
    if ((ten_mili_seconds % 20) <= 10) text_color = makecol(255, 235, 15);
    else text_color = makecol(255, 255, 128); // g=84

    ALLEGRO_COLOR shadow_color = makecol(178, 147, 0);
    ALLEGRO_COLOR hilight_color = makecol(255, 255, 255);

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

	if (min >= 10)
    {
       textprintf(buffer, font, x+1, y, hilight_color, "%i", min);
       textprintf(buffer, font, x-1, y, shadow_color, "%i", min);
       textprintf(buffer, font, x, y+1, shadow_color, "%i", min);
       textprintf(buffer, font, x, y-1, hilight_color, "%i", min);
       textprintf(buffer, font, x, y, text_color, "%i", min);
    }
	else
    {
       textprintf(buffer, font, x+1, y, hilight_color, "0%i", min);
       textprintf(buffer, font, x-1, y, shadow_color, "0%i", min);
       textprintf(buffer, font, x, y+1, shadow_color, "0%i", min);
       textprintf(buffer, font, x, y-1, hilight_color, "0%i", min);
       textprintf(buffer, font, x, y, text_color, "0%i", min);
    }

    textprintf(buffer, font, x+15+1, y, hilight_color, ":");
    textprintf(buffer, font, x+15-1, y, shadow_color, ":");
    textprintf(buffer, font, x+15, y+1, shadow_color, ":");
    textprintf(buffer, font, x+15, y-1, hilight_color, ":");
    textprintf(buffer, font, x+15, y, text_color, ":");

	if (sec >= 10)
    {
        textprintf(buffer, font, x+22+1, y, hilight_color, "%i", sec);
        textprintf(buffer, font, x+22-1, y, shadow_color, "%i", sec);
        textprintf(buffer, font, x+22, y+1, shadow_color, "%i", sec);
        textprintf(buffer, font, x+22, y-1, hilight_color, "%i", sec);
        textprintf(buffer, font, x+22, y, text_color, "%i", sec);
    }
	else
    {
        textprintf(buffer, font, x+22+1, y, hilight_color, "0%i", sec);
        textprintf(buffer, font, x+22-1, y, shadow_color, "0%i", sec);
        textprintf(buffer, font, x+22, y+1, shadow_color, "0%i", sec);
        textprintf(buffer, font, x+22, y-1, hilight_color, "0%i", sec);
        textprintf(buffer, font, x+22, y, text_color, "0%i", sec);
    }

    textprintf(buffer, font, x+13+18+1+3+1, y, hilight_color, ":");
    textprintf(buffer, font, x+13+18+1+3-1, y, shadow_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y+1, shadow_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y-1, hilight_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y, text_color, ":");

	if (hunSec >= 10)
    {
        textprintf(buffer, font, x+37+2+3+1, y, hilight_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3-1, y, shadow_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y+1, shadow_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y-1, hilight_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y, text_color, "%i", hunSec);
    }
	else
    {
        textprintf(buffer, font, x+37+2+3+1, y, hilight_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3-1, y, shadow_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y+1, shadow_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y-1, hilight_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y, text_color, "0%i", hunSec);
    }
}


void write_time_silver(int x, int y, int t)
{
	int min;
	int sec;
	int hunSec;

    //int outline_color = makecol(0,0,0);
    //int text_color = col;
    ALLEGRO_COLOR text_color = makecol(255, 225, 84);

    //int rand_int = rand()%30;
    if ((ten_mili_seconds % 20) <= 10) text_color = makecol(180, 180, 180);
    else text_color = makecol(220, 220, 220); // g=84

    ALLEGRO_COLOR shadow_color = makecol(100, 100, 100);
    ALLEGRO_COLOR hilight_color = makecol(255, 255, 255);

	min = (int)(((float)t/(float)100)/(float)60);
	sec =  (t - min*6000)/100;
	hunSec = t%100;

	if (min >= 10)
    {
       textprintf(buffer, font, x+1, y, hilight_color, "%i", min);
       textprintf(buffer, font, x-1, y, shadow_color, "%i", min);
       textprintf(buffer, font, x, y+1, shadow_color, "%i", min);
       textprintf(buffer, font, x, y-1, hilight_color, "%i", min);
       textprintf(buffer, font, x, y, text_color, "%i", min);
    }
	else
    {
       textprintf(buffer, font, x+1, y, hilight_color, "0%i", min);
       textprintf(buffer, font, x-1, y, shadow_color, "0%i", min);
       textprintf(buffer, font, x, y+1, shadow_color, "0%i", min);
       textprintf(buffer, font, x, y-1, hilight_color, "0%i", min);
       textprintf(buffer, font, x, y, text_color, "0%i", min);
    }

    textprintf(buffer, font, x+15+1, y, hilight_color, ":");
    textprintf(buffer, font, x+15-1, y, shadow_color, ":");
    textprintf(buffer, font, x+15, y+1, shadow_color, ":");
    textprintf(buffer, font, x+15, y-1, hilight_color, ":");
    textprintf(buffer, font, x+15, y, text_color, ":");

	if (sec >= 10)
    {
        textprintf(buffer, font, x+22+1, y, hilight_color, "%i", sec);
        textprintf(buffer, font, x+22-1, y, shadow_color, "%i", sec);
        textprintf(buffer, font, x+22, y+1, shadow_color, "%i", sec);
        textprintf(buffer, font, x+22, y-1, hilight_color, "%i", sec);
        textprintf(buffer, font, x+22, y, text_color, "%i", sec);
    }
	else
    {
        textprintf(buffer, font, x+22+1, y, hilight_color, "0%i", sec);
        textprintf(buffer, font, x+22-1, y, shadow_color, "0%i", sec);
        textprintf(buffer, font, x+22, y+1, shadow_color, "0%i", sec);
        textprintf(buffer, font, x+22, y-1, hilight_color, "0%i", sec);
        textprintf(buffer, font, x+22, y, text_color, "0%i", sec);
    }

    textprintf(buffer, font, x+13+18+1+3+1, y, hilight_color, ":");
    textprintf(buffer, font, x+13+18+1+3-1, y, shadow_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y+1, shadow_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y-1, hilight_color, ":");
    textprintf(buffer, font, x+13+18+1+3, y, text_color, ":");

	if (hunSec >= 10)
    {
        textprintf(buffer, font, x+37+2+3+1, y, hilight_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3-1, y, shadow_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y+1, shadow_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y-1, hilight_color, "%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y, text_color, "%i", hunSec);
    }
	else
    {
        textprintf(buffer, font, x+37+2+3+1, y, hilight_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3-1, y, shadow_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y+1, shadow_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y-1, hilight_color, "0%i", hunSec);
        textprintf(buffer, font, x+37+2+3, y, text_color, "0%i", hunSec);
    }
}


////////////////////////
////////////////////////
////////////////////////
////////////////////////
////////////////////////
////////////////////////
// AWARDS
int this_rand_num1=0;
int this_rand_num2=0;
int this_rand_num3=0;
int this_rand_num4=0;


void draw_fers()
{
    ALLEGRO_COLOR color = makecol(255, 217, 0);

    if (simultanious_kill >= MIN_NUMBER_OF_SIMULTANIOUS_KILLS)
    {
        if (ten_mili_seconds%15 <= 7) color = WHITE;
			std::stringstream ss;
			ss << simultanious_kill << "-fer!";
        //write_outline_alfont_aa(20, 85-18, new_font, 14, color, "%d-fer!", simultanious_kill);
        write_outline_alfont_aa(20, 85-18, new_font, 14, color, ss.str().c_str());
        //write_outline_alfont_aa(20, 85, new_font, 14, makecol(255, 217, 0), "Chain of %d", chain_award);
    }
}


void OLD_draw_fers()
{

            if (simultanious_kill >= MIN_NUMBER_OF_SIMULTANIOUS_KILLS)
            {
                if (ten_mili_seconds%10 <= 5)
                {
                    this_rand_num1 = rand()%3;
                    this_rand_num2 = rand()%3;
                    this_rand_num3 = rand()%4;
                    this_rand_num4 = rand()%4;
                }

                textprintf(buffer, font_med, 20-this_rand_num1, SCREEN_H/3-30+this_rand_num2, makecol(210,0,0), "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20+this_rand_num2+1, SCREEN_H/3-30-this_rand_num1, makecol(120,0,0), "%d-fer!", simultanious_kill);

                textprintf(buffer, font_med, 20+this_rand_num3, SCREEN_H/3-30-this_rand_num4, makecol(210,0,0), "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20-this_rand_num4+1, SCREEN_H/3-30+this_rand_num3, makecol(210,0,0), "%d-fer!", simultanious_kill);

                textprintf(buffer, font_med, 20, SCREEN_H/3-30+1, RED, "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20, SCREEN_H/3-30-1, RED, "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20+2, SCREEN_H/3-30, RED, "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20+2, SCREEN_H/3-30-1, RED, "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20-1, SCREEN_H/3-30+1, RED, "%d-fer!", simultanious_kill);
                textprintf(buffer, font_med, 20-1, SCREEN_H/3-30, RED, "%d-fer!", simultanious_kill);

                if (ten_mili_seconds%15 <= 7)
                {
                    textprintf(buffer, font_med, 20, SCREEN_H/3-30, YELLOW, "%d-fer!", simultanious_kill);
                    textprintf(buffer, font_med, 20+1, SCREEN_H/3-30, YELLOW, "%d-fer!", simultanious_kill);
                }
                else
                {
                    textprintf(buffer, font_med, 20, SCREEN_H/3-30, ORANGE, "%d-fer!", simultanious_kill);
                    textprintf(buffer, font_med, 20+1, SCREEN_H/3-30, ORANGE, "%d-fer!", simultanious_kill);
                }

                //textprintf(buffer, font_small, 40, SCREEN_H/3-30, BLACK, "%d", total_points_in_the_fer);

            }
}

/*
void highcolor_fade_in(ALLEGRO_BITMAP *bmp_orig, int speed)
{
   ALLEGRO_BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;
        
        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    } 

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);

    screen_is_black = false;
}
*/

/*
void highcolor_fade_in__(int speed)
{
    clear_to_color(buffer, COLOR_BACKGROUND);
    draw_to_buffer();

    ALLEGRO_BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;
        
        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, buffer, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    } 

    blit(buffer, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);

    screen_is_black = false;
}


void highcolor_fade_out(int speed)
{
    ALLEGRO_BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;
        
            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));

    screen_is_black = true;
}


/*
void fade_in_flip(int speed)
{
    ALLEGRO_BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;
        
            for (a = 0; a < 256; a+=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                //vsync();
                show_video_bitmap(bmp_buff);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));

    screen_is_black = false;
}  */

/*
void highcolor_fade_in____(int speed)
{
    ALLEGRO_BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;
        
            for (a = 0; a < 256; a+=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));

    screen_is_black = false;
}
*/

/*
void stop_and_fade_out(int speed)
{
    ALLEGRO_BITMAP *orig;
    int a=0;
    
    orig = buffer;
    
    for (a=0; a<256; a+=speed)
    {
        blit(orig, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        fblend_rect_trans(buffer, 0, 0, SCREEN_W, SCREEN_H, BLACK, a);
        if (page_flipping_on)
        {
            //vsync();
            //blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            show_video_bitmap(buffer);
            if (buffer == page1) buffer = page2;
            else buffer = page1;
        }
        else
        {
            vsync();
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }        
    }
    
    //destroy_bitmap(orig);
    screen_is_black = true;
}    
*/
/*
void stop_and_fade_in(int speed)
{
    ALLEGRO_BITMAP *orig;
    int a=0;
    
    draw_to_buffer();
    orig = buffer;
    
    for (a=255; a>=0; a-=speed)
    {
        blit(orig, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        fblend_rect_trans(buffer, 0, 0, SCREEN_W, SCREEN_H, BLACK, a);
        if (page_flipping_on)
        {
            //vsync();
            //blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            show_video_bitmap(buffer);
            if (buffer == page1) buffer = page2;
            else buffer = page1;
        }
        else
        {
            vsync();
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }        
    }
    
    //destroy_bitmap(orig);
    screen_is_black = false;
}    
*/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include "pickup_item.hpp"


#define PICKUP_ITEM_DURATION 40
#define PICKUP_ITEM_GRAVITY 3.4f
#define PICKUP_ITEM_END (PICKUP_ITEM_DURATION*-1+20)

struct picked_up_item_struct
{
    float x_pos;
    float y_pos;
    int counter;
    int item_type;
};

vector<picked_up_item_struct> picked_up_item;



void begin_drawing_picked_up_item(int item_type, float x_pos, float y_pos)
{
    picked_up_item_struct puis;
    puis.counter = PICKUP_ITEM_DURATION;
    puis.item_type = item_type;
    puis.x_pos = x_pos;
    puis.y_pos = y_pos;
    
    puis.y_pos -= 20;
    
    picked_up_item.push_back(puis);
}    


void clear_picked_up_items()
{
    for (int i=picked_up_item.size()-1; i>=0; i--) picked_up_item.pop_back();
}


void _recalc_picked_up_item_pos(picked_up_item_struct *puis)
{
    if (!(puis->counter < 10))
    {
        puis->y_pos -= (puis->counter/(float)6);
        puis->y_pos += PICKUP_ITEM_GRAVITY;
    }    
}    


void update_picked_up_items()
{
    for (int k=0; k<picked_up_item.size(); k++)
    {
        picked_up_item[k].counter--;
        
        _recalc_picked_up_item_pos(&picked_up_item[k]);
        
        // this line will remove the last item from the list if it is finished drawing
        if ((k == picked_up_item.size()-1) && (picked_up_item[k].counter < PICKUP_ITEM_END)) picked_up_item.pop_back();
    }    
}    


void draw_picked_up_items()
{
    int padding = 13;
    int item_spacing = 16;
    int x_cursor = 0;

    ALLEGRO_BITMAP *img;


    for (int k=0; k<picked_up_item.size(); k++)
    {
        if (!(picked_up_item[k].counter < PICKUP_ITEM_END))
        {
            switch (picked_up_item[k].item_type)
            {

#define ADD_ITEM(xx, yy)     case xx##_const: img = xx##_img; break;
#include "item_list.hpp"
#undef ADD_ITEM
            }

            if (img) draw_sprite(buffer, img,
                                 player.get_center_int() - al_get_bitmap_width(img)/2 - (int)camera.x,
                                 player.get_top_edge_int() - padding + x_cursor - al_get_bitmap_height(img)/2 - (int)camera.y);
            x_cursor -= item_spacing;
        }    
    }    
}    



// OLD PICKUP_ITEMS WENT HERE

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include "drawing.hpp"

void draw_clock(int x, int y, int l, int tot)
{
	return;

/*

	int timerAngle;

	timerAngle = (l*256/tot);

	draw_sprite(buffer, clock_icon, x, y);
    if (game_state == STATE_WAITING_FOR_LEVEL_START)
    {
        if (pre_game_counter <= 80) // yellow
        {
           //clock_face_overlay = _load_bitmap("images/ops/clock_face_yellow.bmp");
           set_trans_blender(255,255,255,(255*(pre_game_counter))/80);
           draw_trans_sprite(buffer, clock_face_overlay_y, x, y);
        }
        else if (pre_game_counter <= 160) // yellow
        {
           //clock_face_overlay = _load_bitmap("images/ops/clock_face_yellow.bmp");
           set_trans_blender(255,255,255,(255*(pre_game_counter-80))/80);
           draw_trans_sprite(buffer, clock_face_overlay_y, x, y);
        }
    }
    else if (go_banner_counter > 0)
    {
        if (go_banner_counter > 30)
        {
           //set_trans_blender(255,255,255,255*(go_banner_counter))/30);    // 60 is the max_go_banner_counter
           draw_sprite(buffer, clock_face_overlay_g, x, y);
        }
        else
        {
           set_trans_blender(255,255,255,(255*(go_banner_counter))/30);    // 60 is the max_go_banner_counter
           draw_trans_sprite(buffer, clock_face_overlay_g, x, y);
        }
    }
    else if (time_left_in_round <= 1000)
    {
        bool draw_it = false;

        if (time_left_in_round <= 250)
        {
           if ((time_left_in_round%25 >= 12)) draw_it = true;
        }
        else if (time_left_in_round <= 500)
        {
           if ((time_left_in_round%50 >= 25)) draw_it = true;
        }
        else if (time_left_in_round <= 1500)
        {
           if ((time_left_in_round%100 >= 75)) draw_it = true;
        }


         //if ((time_left_in_round%25 >= 12)) draw_it = true;
        if (time_left_in_round <= 0) draw_it = true;

        if (draw_it)
        {
           draw_sprite(buffer, clock_face_overlay_r, x, y);
        }
    }
	rotate_sprite(buffer, clock_dial, x+5, y+5, itofix(timerAngle));
*/
}


////////////////////////////////////////////////////////////////////////////////


void _draw_ms_background(ALLEGRO_BITMAP *buffer, ALLEGRO_BITMAP *bg, int x_off, int y_off, float rate)
{
    int x_point = x_off - (int)(camera_x*rate);
    int y_point = y_off - (int)(camera_y*rate);

    masked_blit(bg, buffer, 0, 0, x_point, y_point, al_get_bitmap_width(bg), al_get_bitmap_height(bg));
}


void _draw_ms_background_loop_x(ALLEGRO_BITMAP *b, ALLEGRO_BITMAP *bg, int x_off, int y_off, float rate)
{
    x_off = -x_off + (int)(camera_x*rate);
    int y_point = y_off - (int)(camera_y*rate);

    int covered_width = -x_off;
    
    while (covered_width > 0) covered_width -= al_get_bitmap_width(bg);
    while (covered_width < -al_get_bitmap_width(bg)) covered_width += al_get_bitmap_width(bg);
       
    while (covered_width < SCREEN_W)
    {
        masked_blit(bg, buffer, 0, 0, covered_width, y_point, al_get_bitmap_width(bg), al_get_bitmap_height(bg));
        covered_width += al_get_bitmap_width(bg);
    }    
}

void _draw_ms_background_loop_y(ALLEGRO_BITMAP *b, ALLEGRO_BITMAP *bg, int x_off, int y_off, float rate)
{
    y_off = -y_off + (int)(camera_y*rate);
    int x_point = x_off - (int)(camera_x*rate);

    int covered_height = -y_off;
    
    while (covered_height > 0) covered_height -= al_get_bitmap_height(bg);
    while (covered_height < -al_get_bitmap_height(bg)) covered_height += al_get_bitmap_height(bg);
       
    while (covered_height < SCREEN_H)
    {
        masked_blit(bg, buffer, 0, 0, x_point, covered_height, al_get_bitmap_width(bg), al_get_bitmap_height(bg));
        covered_height += al_get_bitmap_height(bg);
    }    
}

void _draw_ms_background_loop_x_y(ALLEGRO_BITMAP *b, ALLEGRO_BITMAP *bg, int x_off, int y_off, float rate)
{
    x_off = -x_off + (int)(camera_x*rate);
    y_off = -y_off + (int)(camera_y*rate);

    int covered_width = -x_off;
    int covered_height = -y_off;
    
    while (covered_width > 0) covered_width -= al_get_bitmap_width(bg);
    while (covered_width < -al_get_bitmap_width(bg)) covered_width += al_get_bitmap_width(bg);
    while (covered_height > 0) covered_height -= al_get_bitmap_height(bg);
    while (covered_height < -al_get_bitmap_height(bg)) covered_height += al_get_bitmap_height(bg);

    int orig_covered_height = covered_height;
       
    while (covered_width < SCREEN_W)
    {
        while (covered_height < SCREEN_H)
        {
            masked_blit(bg, buffer, 0, 0, covered_width, covered_height, al_get_bitmap_width(bg), al_get_bitmap_height(bg));
            covered_height += al_get_bitmap_height(bg);
        }    
        covered_width += al_get_bitmap_width(bg);
        covered_height = orig_covered_height;
    }    
}

void draw_ms_background(ALLEGRO_BITMAP *b, ALLEGRO_BITMAP *bg, int x_off, int y_off, float rate, bool loop_x=false, bool loop_y=false)
{
    if (loop_x && loop_y) _draw_ms_background_loop_x_y(b, bg, x_off, y_off, rate);
    else if (loop_x) _draw_ms_background_loop_x(b, bg, x_off, y_off, rate);
    else if (loop_y) _draw_ms_background_loop_y(b, bg, x_off, y_off, rate);
    else _draw_ms_background(b, bg, x_off, y_off, rate);
}    


void draw_ramps()
{
    int v=0;
    for (v=0; v<current_map.ramp.size(); v++)
    {
        ALLEGRO_COLOR line_col = makecol(255,0,0);

        line(buffer, current_map.ramp[v].get_bottom_map_x()-(int)camera_x, current_map.ramp[v].get_bottom_map_y()-(int)camera_y, current_map.ramp[v].get_top_map_x()-(int)camera_x, current_map.ramp[v].get_top_map_y()-(int)camera_y, line_col);
        rect(buffer, current_map.ramp[v].get_bottom_map_x()-(int)camera_x-1, current_map.ramp[v].get_bottom_map_y()-(int)camera_y+1,
               current_map.ramp[v].get_bottom_map_x()-(int)camera_x+1, current_map.ramp[v].get_bottom_map_y()-(int)camera_y-1, makecol(255, 255, 255));
        rect(buffer, current_map.ramp[v].get_top_map_x()-(int)camera_x-1, current_map.ramp[v].get_top_map_y()-(int)camera_y+1,
               current_map.ramp[v].get_top_map_x()-(int)camera_x+1, current_map.ramp[v].get_top_map_y()-(int)camera_y-1, makecol(255, 255, 255));

        if (current_map.ramp[v].get_up_going_right())
        {
           //draw index num at bottom_left and top_right
           textprintf(buffer, font_x_small, current_map.ramp[v].get_bottom_map_x()-(int)camera_x+3, current_map.ramp[v].get_bottom_map_y()-text_height(font_x_small)-(int)camera_y-1, makecol(255, 196, 196), "%d", current_map.ramp[v].index_num);
           textprintf(buffer, font_x_small, current_map.ramp[v].get_top_map_x()-(int)camera_x-TILE_SIZE+3, current_map.ramp[v].get_top_map_y()-(int)camera_y+1, makecol(255, 196, 196), "%d", current_map.ramp[v].index_num);

        }
        else
        {
           //draw index num at top left and bottom_right
           textprintf(buffer, font_x_small, current_map.ramp[v].get_bottom_map_x()-(int)camera_x-TILE_SIZE+3, current_map.ramp[v].get_bottom_map_y()-text_height(font_x_small)-(int)camera_y-1, makecol(255, 196, 196), "%d", current_map.ramp[v].index_num);
           textprintf(buffer, font_x_small, current_map.ramp[v].get_top_map_x()-(int)camera_x+3, current_map.ramp[v].get_top_map_y()-(int)camera_y+1, makecol(255, 196, 196), "%d", current_map.ramp[v].index_num);
        }
    }

}

////////////////////////////////////////////////////////////////////////////////


void draw_killed_em_all()
{
            textprintf(buffer, font_med, 20-1, SCREEN_H/3-30+15, BLACK, "killed 'em all!");
            textprintf(buffer, font_med, 20+2, SCREEN_H/3-30+15, BLACK, "killed 'em all!");
            textprintf(buffer, font_med, 20, SCREEN_H/3-30+15+1, BLACK, "killed 'em all!");
            textprintf(buffer, font_med, 20+1, SCREEN_H/3-30+15+1, BLACK, "killed 'em all!");
            textprintf(buffer, font_med, 20, SCREEN_H/3-30+15-1, BLACK, "killed 'em all!");
            textprintf(buffer, font_med, 20+1, SCREEN_H/3-30+15-1, BLACK, "killed 'em all!");

            textprintf(buffer, font_med, 20, SCREEN_H/3-30+15, makecol(200-60,80-60,255-60), "killed 'em all!");
            textprintf(buffer, font_med, 20+1, SCREEN_H/3-30+15, makecol(200,80,255), "killed 'em all!");

            //if (killed_all_the_bears <= 2000) clock_col = makecol(255, 232, 84);  // gold
            //else if (killed_all_the_bears <= 2500) clock_col = makecol(200, 200, 200); // silver
            //else if (killed_all_the_bears <= 3000) clock_col = makecol(206, 170, 0);  // bronze

            if (time_to_kill_all_the_bears <= current_level.gold_time)
            {
                 write_time_gold(20+5, SCREEN_H/3-30+1+15+10+2, time_to_kill_all_the_bears);//killed_all_the_bears);
            }
            else if (time_to_kill_all_the_bears <= current_level.silver_time)
            {
                 write_time_silver(20+5, SCREEN_H/3-30+1+15+10+2, time_to_kill_all_the_bears);//killed_all_the_bears);
            }
            else if (time_to_kill_all_the_bears <= current_level.bronze_time)
            {
                 write_time_outline(20+5, SCREEN_H/3-30+1+15+10+2, time_to_kill_all_the_bears, makecol(172,133,28));//killed_all_the_bears);
            }
            else write_time_outline(20+5, SCREEN_H/3-30+1+15+10+2, time_to_kill_all_the_bears, WHITE);//killed_all_the_bears);

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

float smooth_stats_counter = (float)SCREEN_W;
float smooth_stats_counter_helper = 0.5f;

float smooth_stats_counter2 = (float)SCREEN_W;
float smooth_stats_counter_helper2 = 0.5f;
int smooth_stats_counter2_delay = 20;

float smooth_stats_counter3 = (float)SCREEN_W;
float smooth_stats_counter_helper3 = 0.5f;
int smooth_stats_counter3_delay = smooth_stats_counter2_delay*2;

/*
void draw_player_stats_timer(float xx=0.0f)
{
    int time_to_write_on_timer = time_when_completed;

    if (game_state == STATE_IN_LEVEL) time_to_write_on_timer =  ten_mili_seconds;
    else if (game_state == STATE_TIME_UP) time_to_write_on_timer = current_level.time_limit;
    else if (game_state == STATE_PAUSE) time_to_write_on_timer = clock_time_suspended_at;

    draw_trans_sprite(buffer, time_bground, (SCREEN_W/2)-(time_bground->w/2)+25-10+(int)(xx)+10, 6);
    write_time_outline((SCREEN_W/2)-(time_bground->w/2)+25+17-10+(int)(xx)+10+10, 13, time_to_write_on_timer);
    draw_clock((SCREEN_W/2)-clock_icon->w-7-10+(int)(xx)+13+2, 0+2, time_left_in_round, current_level.time_limit);
}
*/

void draw_player_stats_timer_aa(float xx=0.0f)
{
    alfont_set_font_size(new_font, 18);

    draw_trans_sprite(buffer, time_bground, (SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25-10+(int)(xx)+13, 6);
    if (game_state == STATE_IN_LEVEL) write_time_outline_aa((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, ten_mili_seconds);
    //else if (game_state == STATE_IN_LEVEL) write_time_outline((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, ellapsed_time);
    else if (game_state == STATE_TIME_UP) write_time_outline_aa((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, current_level.time_limit);
    else write_time_outline_aa((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, time_when_completed);

    draw_clock((SCREEN_W/2)-al_get_bitmap_width(clock_icon)-7-10+(int)(xx)+13, 0+2, time_left_in_round, current_level.time_limit);

    if (num_of_enemies_left == 0)
    {
       draw_sprite(buffer, no_bears, 260, 3);
    }
}

void draw_player_stats_timer__half_aa(float xx=0.0f)
{
    alfont_set_font_size(new_font, 18);

    draw_trans_sprite(buffer, time_bground, (SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25-10+(int)(xx)+13, 6);
    if (game_state == STATE_IN_LEVEL) write_time_outline__half_aa((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, ten_mili_seconds);
    //else if (game_state == STATE_IN_LEVEL) write_time_outline((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, ellapsed_time);
    else if (game_state == STATE_TIME_UP) write_time_outline__half_aa((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, current_level.time_limit);
    else write_time_outline__half_aa((SCREEN_W/2)-(al_get_bitmap_width(time_bground)/2)+25+17-10+(int)(xx)+13, 13, time_when_completed);

    draw_clock((SCREEN_W/2)-al_get_bitmap_width(clock_icon)-7-10+(int)(xx)+13, 0+2, time_left_in_round, current_level.time_limit);

    //if (num_of_enemies_left == 0)
    //{
    //   draw_sprite(buffer, no_bears, 260, 3);
    //}
}

void draw_player_stats_energy_hearts(float xx=0.0f)
{
    draw_trans_sprite(buffer, stat_bground_hearts, 65-10+3+(int)(xx)-1+13, 10-1);

    int len = (int)(al_get_bitmap_width(stat_hearts)*(player.energy/player.max_energy));
    masked_blit(stat_hearts, buffer, 0, 0, 65-10+3+(int)(xx)-1+13+3, 10-1, len, al_get_bitmap_width(stat_hearts));
}


void draw_player_stats_energy(float xx=0.0f)
{
    draw_trans_sprite(buffer, stat_bground, 65-10+3+(int)(xx)-1+13, 10);

    int bar_length = 4;
    int bar_space = 3;
    int bar_height = 3;
    int num_of_bars = player.max_energy/5;
    int num_of_live_bars = (int)(player.energy/5.0f);
    int dum=0;
    ALLEGRO_COLOR bar_color=makecol(0, 0, 0);

    int orient_x = 65+6-10+(int)(xx)+3-1+13;
    int orient_y = 15+2;

    int percent_of_energy = ((int)((player.energy/((float)player.max_energy))*100.0f));

    ALLEGRO_COLOR dead_bar_color = makecol(96,0,0);
    if (percent_of_energy == 100) bar_color = makecol(255,255,255);
    else if (percent_of_energy >= 60) bar_color = makecol(0, 255, 255);
    else if (percent_of_energy >= 30) bar_color = makecol(0,255,0);
    else if (percent_of_energy >= 0) bar_color = makecol(255, 0, 0);

    for (dum=0; dum<num_of_bars; dum++)
    {
        if (dum >= num_of_live_bars) {
            rectfill(buffer, orient_x+(dum*(bar_length+bar_space)), orient_y, orient_x+bar_length-1+(dum*(bar_length+bar_space)), orient_y-bar_height-1, dead_bar_color);
        }
        else {
            rectfill(buffer, orient_x+(dum*(bar_length+bar_space)), orient_y, orient_x+bar_length-1+(dum*(bar_length+bar_space)), orient_y-bar_height-1, bar_color);
        }

    }

}

void draw_player_stats_lives_aa(float xx=0.0f)
{
    /// draw numer of lives left
    alfont_set_font_size(new_font, 14);

    int space_fixer = 0;
    if (player_lives > 9) space_fixer = 4;
    draw_trans_sprite(buffer, stat_bground, (int)(xx)-1+13, 10);
    draw_sprite(buffer, life_icon, 18-space_fixer-10+(int)(xx)-1+13, 7);
    alfont_textprintf_centre_aa(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+(int)(xx)-1+13, 10+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre_aa(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3-1+9-10+(int)(xx)-1+13, 10+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre_aa(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10+1+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre_aa(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10-1+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre_aa(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10+2-3, WHITE, "x%d", player_lives);
}

void draw_player_stats_lives__half_aa(float xx=0.0f)
{
    /// draw numer of lives left
    alfont_set_font_size(new_font, 14);

    int space_fixer = 0;
    if (player_lives > 9) space_fixer = 4;
    draw_trans_sprite(buffer, stat_bground, (int)(xx)-1+13, 10);
    draw_sprite(buffer, life_icon, 18-space_fixer-10+(int)(xx)-1+13, 7);
    alfont_textprintf_centre(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+(int)(xx)-1+13, 10+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3-1+9-10+(int)(xx)-1+13, 10+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10+1+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10-1+2-3, BLACK, "x%d", player_lives);
    alfont_textprintf_centre_aa(buffer, new_font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10+2-3, WHITE, "x%d", player_lives);
}

/*
void draw_player_stats_lives(float xx=0.0f)
{
    /// draw numer of lives left
    int space_fixer = 0;
    if (player_lives > 9) space_fixer = 4;
    draw_trans_sprite(buffer, stat_bground, (int)(xx)-1+13, 10);
    draw_sprite(buffer, life_icon, 18-space_fixer-10+(int)(xx)-1+13, 7);
    textprintf_centre(buffer, font, 10+6+al_get_bitmap_width(life_icon)+3+(int)(xx)-1+13, 10+2, BLACK, "x%d", player_lives);
    textprintf_centre(buffer, font, 10+6+al_get_bitmap_width(life_icon)+3-1+9-10+(int)(xx)-1+13, 10+2, BLACK, "x%d", player_lives);
    textprintf_centre(buffer, font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10+1+2, BLACK, "x%d", player_lives);
    textprintf_centre(buffer, font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10-1+2, BLACK, "x%d", player_lives);
    textprintf_centre(buffer, font, 10+6+al_get_bitmap_width(life_icon)+3+9-10+(int)(xx)-1+13, 10+2, WHITE, "x%d", player_lives);
}
*/

void draw_player_stats_keys__half_aa(float xx=0.0f)
{
    int y_offset = 0;

    int space_fixer = 0;
    if (player_coins > 9) space_fixer = 4;
    set_multiply_blender(255,255,255,255-128);

    if (player.get_keys() > 0) xx -= 15;
    if (player.get_silver_keys() > 0) xx -= 15;

    draw_trans_sprite(buffer, stat_bground, 244+(int)(xx)-1+13, 10+y_offset);
    if (small_jewel_img)
    {
       draw_sprite(buffer, small_jewel_img, 244+18-space_fixer-10+(int)(xx)-1+13, 7+3+y_offset+1);
       alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(small_jewel_img)+3+(int)(xx)-1+13, 10+2-3+y_offset, BLACK, "x%d", player_coins);
       alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(small_jewel_img)+3-1+9-10+(int)(xx)-1+13, 10+2-3+y_offset, BLACK, "x%d", player_coins);
       alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(small_jewel_img)+3+9-10+(int)(xx)-1+13, 10+1+2-3+y_offset, BLACK, "x%d", player_coins);
       alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(small_jewel_img)+3+9-10+(int)(xx)-1+13, 10-1+2-3+y_offset, BLACK, "x%d", player_coins);
       alfont_textprintf_centre_aa(buffer, new_font, 244+10+6+al_get_bitmap_width(small_jewel_img)+3+9-10+(int)(xx)-1+13, 10+2-3+y_offset, WHITE, "x%d", player_coins);
    }

    if (key[ALLEGRO_KEY_PAD_9]) player.keys++;
    if (key[ALLEGRO_KEY_PAD_3]) player.use_key();
    if (key[ALLEGRO_KEY_PAD_7]) player.silver_keys++;
    if (key[ALLEGRO_KEY_PAD_1]) player.use_silver_key();

    xx += 15;
    y_offset += 17;

    if (player.get_keys() > 0)
    {
        /// draw numer of keys left
        int space_fixer = 0;
        if (player.get_keys() > 9) space_fixer = 4;
        set_multiply_blender(255,255,255,255-128);
        draw_trans_sprite(buffer, stat_bground, 244+(int)(xx)-1+13, 10+y_offset);
        if (key_img)
        {
           draw_sprite(buffer, key_img, 244+18-space_fixer-10+(int)(xx)-1+13, 7+y_offset);
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(key_img)+3+(int)(xx)-1+13, 10+2-3+y_offset, BLACK, "x%d", player.get_keys());
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(key_img)+3-1+9-10+(int)(xx)-1+13, 10+2-3+y_offset, BLACK, "x%d", player.get_keys());
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(key_img)+3+9-10+(int)(xx)-1+13, 10+1+2-3+y_offset, BLACK, "x%d", player.get_keys());
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(key_img)+3+9-10+(int)(xx)-1+13, 10-1+2-3+y_offset, BLACK, "x%d", player.get_keys());
           alfont_textprintf_centre_aa(buffer, new_font, 244+10+6+al_get_bitmap_width(key_img)+3+9-10+(int)(xx)-1+13, 10+2-3+y_offset, WHITE, "x%d", player.get_keys());
        }

        xx += 15;
        y_offset += 17;
    }

    if (player.get_silver_keys() > 0)
    {
        /// draw numer of keys left
        int space_fixer = 0;
        if (player.get_silver_keys() > 9) space_fixer = 4;
        set_multiply_blender(255,255,255,255-128);
        draw_trans_sprite(buffer, stat_bground, 244+(int)(xx)-1+13, 10+y_offset);

        if (silver_key_img)
        {
           draw_sprite(buffer, silver_key_img, 244+18-space_fixer-10+(int)(xx)-1+13, 7+y_offset);
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(silver_key_img)+3+(int)(xx)-1+13, 10+2-3+y_offset, BLACK, "x%d", player.get_silver_keys());
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(silver_key_img)+3-1+9-10+(int)(xx)-1+13, 10+2-3+y_offset, BLACK, "x%d", player.get_silver_keys());
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(silver_key_img)+3+9-10+(int)(xx)-1+13, 10+1+2-3+y_offset, BLACK, "x%d", player.get_silver_keys());
           alfont_textprintf_centre(buffer, new_font, 244+10+6+al_get_bitmap_width(silver_key_img)+3+9-10+(int)(xx)-1+13, 10-1+2-3+y_offset, BLACK, "x%d", player.get_silver_keys());
           alfont_textprintf_centre_aa(buffer, new_font, 244+10+6+al_get_bitmap_width(silver_key_img)+3+9-10+(int)(xx)-1+13, 10+2-3+y_offset, WHITE, "x%d", player.get_silver_keys());
        }
    }
}






void draw_player_stats_aa_fblend(float xx=0.0f)
{
    set_multiply_blender(255,255,255,255-128);

    draw_trans_sprite(buffer, stat_bground_hearts, 65-10+3+(int)((smooth_stats_counter2)*(-1))-1+13, 10-1);

    //fblend_add(stat_bground_hearts, buffer, 65-10+3+(int)(xx)-1+13, 10-1, 255);

    int len = (int)(al_get_bitmap_width(stat_hearts)*(player.energy/player.max_energy));
    masked_blit(stat_hearts, buffer, 0, 0, 65-10+3+(int)((smooth_stats_counter2)*(-1))-1+13+3, 10-1, len, al_get_bitmap_height(stat_hearts));


    draw_player_stats_timer__half_aa((smooth_stats_counter)*(-1));
    set_multiply_blender(255,255,255,255-128);
    draw_player_stats_lives__half_aa((smooth_stats_counter3)*(-1));

    //set_multiply_blender(255,255,255,255-128);

    draw_player_stats_keys__half_aa();

    alfont_set_font_size(new_font, 14);

    //int orient_x = SCREEN_W - 20;
    //int orient_y = 12;
    //alfont_textprintf_right_aa(buffer, new_font, orient_x+1, orient_y, makecol(32,32,32), "%d", player_score);
    //alfont_textprintf_right_aa(buffer, new_font, orient_x-1, orient_y, makecol(32,32,32), "%d", player_score);
    //alfont_textprintf_right_aa(buffer, new_font, orient_x, orient_y+1, makecol(32,32,32), "%d", player_score);
    //alfont_textprintf_right_aa(buffer, new_font, orient_x, orient_y-1, makecol(32,32,32), "%d", player_score);
    //alfont_textprintf_right_aa(buffer, new_font, orient_x, orient_y, makecol(255,255,255), "%d", player_score);
}


void draw_player_stats_aa_fblend_no_timers(float xx=0.0f)
{
    set_multiply_blender(255,255,255,255-128);

    draw_trans_sprite(buffer, stat_bground_hearts, 65-10+3+(int)((smooth_stats_counter2)*(-1))-1+13, 10-1);

    //fblend_add(stat_bground_hearts, buffer, 65-10+3+(int)(xx)-1+13, 10-1, 255);

    int len = (int)(al_get_bitmap_width(stat_hearts)*(player.energy/player.max_energy));
    masked_blit(stat_hearts, buffer, 0, 0, 65-10+3+(int)((smooth_stats_counter2)*(-1))-1+13+3, 10-1, len, al_get_bitmap_height(stat_hearts));


    //draw_player_stats_timer__half_aa((smooth_stats_counter)*(-1));
    set_multiply_blender(255,255,255,255-128);
    draw_player_stats_lives__half_aa((smooth_stats_counter3)*(-1));

    //set_multiply_blender(255,255,255,255-128);
    draw_player_stats_keys__half_aa(smooth_stats_counter3);

//    draw_player_stats_coins__half_aa();
}


/*
void draw_player_stats_aa(float xx=0.0f)
{
    set_multiply_blender(255,255,255,255-128);

    //xx=0;

    //xx = xx*2;


    //xx = xx/2;
    //xx = xx*1.5;

    // draw the player's energy

    draw_player_stats_energy_hearts((smooth_stats_counter2)*(-1));


    //xx = xx/1.5;
    //xx = xx;


    // draw the timers

    draw_player_stats_timer_aa((smooth_stats_counter)*(-1));
    set_multiply_blender(255,255,255,255-128);
    draw_player_stats_lives_aa((smooth_stats_counter3)*(-1));

    set_multiply_blender(255,255,255,255-128);


    // write the score at the bottom of the screen

    //int orient_x = SCREEN_W/2;
    //int orient_y = SCREEN_H - 12;
    //textprintf_centre(buffer, font, orient_x+1, orient_y, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x-1, orient_y, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x, orient_y+1, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x, orient_y-1, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x, orient_y, makecol(255,255,255), "%d", player_score);

   // int orient_x = SCREEN_W - 20;
    //int orient_y = 12;
    //textprintf_right(buffer, font, orient_x+1, orient_y, makecol(32,32,32), "%d", player_score);
    //textprintf_right(buffer, font, orient_x-1, orient_y, makecol(32,32,32), "%d", player_score);
    //textprintf_right(buffer, font, orient_x, orient_y+1, makecol(32,32,32), "%d", player_score);
    //textprintf_right(buffer, font, orient_x, orient_y-1, makecol(32,32,32), "%d", player_score);
   // textprintf_right(buffer, font, orient_x, orient_y, makecol(255,255,255), "%d", player_score);
   ///

    alfont_set_font_size(new_font, 14);

    int orient_x = SCREEN_W - 20;
    int orient_y = 12;
    alfont_textprintf_right_aa(buffer, new_font, orient_x+1, orient_y, makecol(32,32,32), "%d", player_score);
    alfont_textprintf_right_aa(buffer, new_font, orient_x-1, orient_y, makecol(32,32,32), "%d", player_score);
    alfont_textprintf_right_aa(buffer, new_font, orient_x, orient_y+1, makecol(32,32,32), "%d", player_score);
    alfont_textprintf_right_aa(buffer, new_font, orient_x, orient_y-1, makecol(32,32,32), "%d", player_score);
    alfont_textprintf_right_aa(buffer, new_font, orient_x, orient_y, makecol(255,255,255), "%d", player_score);


}
*/

/*
void draw_player_stats(float xx=0.0f)
{
    set_multiply_blender(255,255,255,255-128);

    //xx=0;

    //xx = xx*2;


    //xx = xx/2;
    //xx = xx*1.5;

    // draw the player's energy

    draw_player_stats_energy((smooth_stats_counter2)*(-1));


    //xx = xx/1.5;
    //xx = xx;


    // draw the timers

    draw_player_stats_lives((smooth_stats_counter3)*(-1));
    draw_player_stats_timer((smooth_stats_counter)*(-1));



    // write the score at the bottom of the screen

    //int orient_x = SCREEN_W/2;
    //int orient_y = SCREEN_H - 12;
    //textprintf_centre(buffer, font, orient_x+1, orient_y, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x-1, orient_y, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x, orient_y+1, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x, orient_y-1, makecol(32,32,32), "%d", player_score);
    //textprintf_centre(buffer, font, orient_x, orient_y, makecol(255,255,255), "%d", player_score);

    int orient_x = SCREEN_W - 20;
    int orient_y = 12;
    textprintf_right(buffer, font, orient_x+1, orient_y, makecol(32,32,32), "%d", player_score);
    textprintf_right(buffer, font, orient_x-1, orient_y, makecol(32,32,32), "%d", player_score);
    textprintf_right(buffer, font, orient_x, orient_y+1, makecol(32,32,32), "%d", player_score);
    textprintf_right(buffer, font, orient_x, orient_y-1, makecol(32,32,32), "%d", player_score);
    textprintf_right(buffer, font, orient_x, orient_y, makecol(255,255,255), "%d", player_score);



}
*/

void draw_pen_info()
{
    rectfill(buffer, SCREEN_W-TILE_SIZE*2-6-10, SCREEN_H-TILE_SIZE-6, SCREEN_W-2, SCREEN_H-2, makecol(0,0,0));
    if (drawing_destination == DRAWING_TO_BOUNDRY)
    {
       draw_boundry_block(buffer, SCREEN_W-TILE_SIZE*2-11, SCREEN_H-TILE_SIZE-6+2, drawing_pen_int1, makecol(255,255,0));
       textprintf(buffer, font_x_small, SCREEN_W-TILE_SIZE*2-6+TILE_SIZE/2, SCREEN_H-TILE_SIZE-6-8, makecol(255,255,255), "%d", drawing_pen_int1);
    }
    else
    {
       draw_tile(buffer, pen_from_tile_index, SCREEN_W-TILE_SIZE*2-11, SCREEN_H-TILE_SIZE-6+2);
       textprintf(buffer, font_x_small, SCREEN_W-TILE_SIZE*2-6+TILE_SIZE/2, SCREEN_H-TILE_SIZE-6-8, makecol(255,255,255), "%d", pen_from_tile_index);
    }

    textprintf(buffer, font_x_small, SCREEN_W-50, SCREEN_H-8, makecol(255,255,255), "%d", drawing_destination);
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void draw_debug_info()
{
    rectfill(buffer, 1, 1, 90, 13, makecol(0,0,0));
    textprintf(buffer, font_x_small, 2, 4, makecol(255,128,128), "camera |");
    textprintf(buffer, font_x_small, 35, 1, makecol(255,128,128), "-x=%f", camera.x);
    textprintf(buffer, font_x_small, 35, 7, makecol(255,128,128), "-y=%f", camera.y);

    rectfill(buffer, 1+100, 1, 90+100, 13, makecol(0,0,0));
    textprintf(buffer, font_x_small, 2+100, 4, makecol(128,255,128), "player |");
    textprintf(buffer, font_x_small, 36+96, 1, makecol(128,255,128), "-x=%f", player.map_pos.x);
    textprintf(buffer, font_x_small, 36+96, 7, makecol(128,255,128), "-y=%f", player.map_pos.y);

    textprintf(buffer, font_x_small, SCREEN_W-100, 50, makecol(255,255,255), "bears %d", current_level.enemy.size());

    // shows the level info
    textprintf(buffer, font_x_small, 2, 16, makecol(128,128,255), "Level: %s", current_level.title.c_str());
    textprintf(buffer, font_x_small, 2, 16+10, makecol(128,128,255), "time limit:%d", current_level.time_limit);
    ALLEGRO_COLOR dum_col = makecol(128, 128, 255);
    int pp=0;
    for (pp = 0; pp<current_level.map_index.size(); pp++)
    {
        if (current_level.get_current_map_index() == current_level.map_index[pp].index_num) dum_col = makecol(196,196,255);
        else dum_col = makecol(128, 128, 255);
        textprintf(buffer, font_x_small, 2, 16+20+pp*7, dum_col, "Map %d: %s", current_level.map_index[pp].index_num, current_level.map_index[pp].address.c_str());
    }
    pp=0;
    for (pp = 0; pp<current_level.door.size(); pp++)
    {
        textprintf(buffer, font_x_small, 2, 16+20+pp*7+current_level.map_index.size()*7+3, makecol(128,128,255), "Door %d: (%d,%d) on map %d", current_level.door[pp].index_num, current_level.door[pp].map_spawn_x, current_level.door[pp].map_spawn_y, current_level.door[pp].go_to_new_map);
    }

    if (player.on_ground) textprintf(buffer, font_x_small, SCREEN_W-50, SCREEN_H-10, WHITE, "ON_GROUND");
    textprintf(buffer, font_x_small, SCREEN_W-50, SCREEN_H-18, WHITE, "Ramp: %d", player.on_ramp);


    // show camera lock information
    int spacer = 0;

    if (camera.camera_block_number != -1) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera block: %d", camera.camera_block_number); spacer++; }
    if (camera.y_free_beomming_restrained) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "y_free_beomming_restrained"); spacer++; }
    if (camera.x_free_beomming_restrained) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "x_free_beomming_restrained"); spacer++; }
    if (camera.x_locked()) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera lock_x: %f3", camera.lock_x); spacer++; }
    if (camera.y_locked()) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera lock_y: %f3", camera.lock_y); spacer++; }
    if (camera.x_maxed()) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera max_x: %f3", camera.max_x); spacer++; }
    if (camera.x_mined()) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera min_x: %f3", camera.min_x); spacer++; }
    if (camera.y_maxed()) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera max_y: %f3", camera.max_y); spacer++; }
    if (camera.y_mined()) { textprintf(buffer, font_x_small, 2, SCREEN_H/2+10*spacer, makecol(255,128,128), "camera min_y: %f3", camera.min_y); spacer++; }
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void draw_player_bear()
{
        if ((player.post_pain_counter == 0) || (game_state == STATE_TIME_UP) || (player.post_pain_counter%6 <= 2))
        {
            if (player.facing_right)
            {
               draw_sprite(buffer, bear, (int)player.map_pos.x-(int)camera.x-4, (int)player.map_pos.y-(int)camera.y);
               if (player.has_gun) draw_sprite(buffer, holding_gun, (int)player.map_pos.x-(int)camera.x-4+1, (int)player.map_pos.y-(int)camera.y+14);
            }
            else
            {
               draw_sprite_h_flip(buffer, bear, (int)player.map_pos.x-(int)camera.x-4, (int)player.map_pos.y-(int)camera.y);
               if (player.has_gun) draw_sprite_h_flip(buffer, holding_gun, (int)player.map_pos.x-(int)camera.x-4-7, (int)player.map_pos.y-(int)camera.y+14);
            }
        }
}

void draw_enemy_bears()
{
    int pp=0;
    for (pp=0; pp<current_level.enemy.size(); pp++)
    {
        if ((current_level.enemy[pp].map_num == current_level.get_current_map_index()) && current_level.enemy[pp].params.alive())
        {
            if (current_level.enemy[pp].params.post_pain_counter == 0)
            {
               if (current_level.enemy[pp].params.facing_right) draw_sprite(buffer, current_level.enemy[pp].params.pic, current_level.enemy[pp].params.get_left_edge_int()-(int)camera_x, current_level.enemy[pp].params.get_top_edge_int()-(int)camera_y);
               else draw_sprite_h_flip(buffer, current_level.enemy[pp].params.pic, current_level.enemy[pp].params.get_left_edge_int()-(int)camera_x, current_level.enemy[pp].params.get_top_edge_int()-(int)camera_y);
               if (F_debug_mode) current_level.enemy[pp].params.draw_bounding_box();
            }
            else if ((current_level.enemy[pp].params.post_pain_counter%6 <= 2))
            {
               if (current_level.enemy[pp].params.facing_right) draw_sprite(buffer, current_level.enemy[pp].params.pic, current_level.enemy[pp].params.get_left_edge_int()-(int)camera_x, current_level.enemy[pp].params.get_top_edge_int()-(int)camera_y);
               else draw_sprite_h_flip(buffer, current_level.enemy[pp].params.pic, current_level.enemy[pp].params.get_left_edge_int()-(int)camera_x, current_level.enemy[pp].params.get_top_edge_int()-(int)camera_y);
               if (F_debug_mode) current_level.enemy[pp].params.draw_bounding_box();
            }
        }
    }

}


void draw_kills_left_and_one_ups(void)
{
            int k=0;
            for (k=draw_one_ups.size()-1; k>=0; k--)
            {
                if (draw_one_ups[k].counter != 0)
                {
                   // draw_sprite(buffer, one_up, (int)(draw_one_ups[k].map_pos.x-camera.x-one_up->w/2), (int)(draw_one_ups[k].map_pos.y-camera.y-one_up->h));
                }
            }

            k=0;
            for (k=bears_left_notif.size()-1; k>=0; k--)
            {
                if (bears_left_notif[k].counter != 0)
                {
                    //draw_sprite
                    write_outline_center_alfont_aa((int)(bears_left_notif[k].map_pos.x-camera.x), (int)(bears_left_notif[k].map_pos.y-camera.y),
                                  new_font, 16, makecol(255,255,255), "%d", bears_left_notif[k].num);
                    //write_outline_center((int)(bears_left_notif[k].map_pos.x-camera.x), (int)(bears_left_notif[k].map_pos.y-camera.y),
                                  //font_med, makecol(255,255,255), "%d", bears_left_notif[k].num);
                }
            }
}


void draw_medals(void)
{
    if (time_to_kill_all_the_bears <= current_level.gold_time)
    {
         draw_sprite(buffer, medal_gold, 260, 0);
    }
    else if (time_to_kill_all_the_bears <= current_level.silver_time)
    {
         draw_sprite(buffer, medal_silver, 260, 0);
    }
    else if (time_to_kill_all_the_bears <= current_level.bronze_time)
    {
         draw_sprite(buffer, medal_bronze, 260, 0);
    }
    else
    {
         draw_sprite(buffer, no_bears, 260, 3);
    }

}



void draw_rewards_aa_no_flash(void)
{
       if (award_counter != 0) draw_fers();

       if (time_to_kill_all_the_bears >= 0)
       {
           if ((killed_em_all_counter > 0) && !(no_killed_em_all)) draw_killed_em_all();
           if (!(no_killed_em_all)) draw_medals();
       }

       if ((chain_award_counter != 0) && (chain_award >= MIN_NUMBER_OF_KILLS_FOR_A_CHAIN))
       {
           write_outline_alfont_aa(20, 85, new_font, 14, makecol(255, 217, 0), "Chain of %d", chain_award);
       }
}




void draw_banners(void)
{
    if (((pre_game_counter > 0) && (pre_game_counter < 160)) &&  (game_state != STATE_CHOOSING_LEVEL))
    {
        draw_sprite(buffer, ready_banner, SCREEN_W/2-al_get_bitmap_width(ready_banner)/2, SCREEN_H/2-al_get_bitmap_height(ready_banner)/2);
    }
    if (F_show_congrats_banner)
    {
        if (ten_mili_seconds%40 <= 30)
        {draw_sprite(buffer, congradulations, SCREEN_W/2-al_get_bitmap_width(congradulations)/2, SCREEN_H/3-al_get_bitmap_height(congradulations));}
    }
    if (game_state == STATE_TIME_UP)
    {
          draw_sprite(buffer, time_up, SCREEN_W/2-al_get_bitmap_width(time_up)/2, SCREEN_H/3);
    }
    if (go_banner_counter > 0)
    {
        draw_sprite(buffer, go_banner, SCREEN_W/2-al_get_bitmap_width(go_banner)/2, SCREEN_H/2-al_get_bitmap_height(go_banner)/2);
    }

}



void draw_map_maker_and_debug_stuff(void)
{
    if (F_debug_mode)
    {
        draw_debug_info();
        draw_boundry_block(buffer, ((mouse_x+(int)camera.x)/TILE_SIZE)*TILE_SIZE-(int)camera.x, ((mouse_y+(int)camera.y)/TILE_SIZE)*TILE_SIZE-(int)camera.y, BOUNDRY_11, makecol(128,128,255));
        textprintf(buffer, font_x_small, 2, SCREEN_H-text_height(font_x_small), makecol(128,128,128), "Debug Mode");
        //textprintf(buffer, font_x_small, 2, SCREEN_H-text_height(font_x_small), makecol(128,128,128), "Map Edit Mode (F4-Save)");
    }
    else if (F_map_maker_mode)
    {
        draw_boundry_block(buffer, ((mouse_x+(int)camera.x)/TILE_SIZE)*TILE_SIZE-(int)camera.x, ((mouse_y+(int)camera.y)/TILE_SIZE)*TILE_SIZE-(int)camera.y, BOUNDRY_11, makecol(255,0,0));
        textprintf(buffer, font_x_small, 2, SCREEN_H-text_height(font_x_small), makecol(128,128,128), "Map Edit Mode (F4-Save)");
        draw_pen_info();
    }

    if (F_map_maker_mode || F_debug_mode)
    {
        rectfill(buffer, SCREEN_W-100, 1, SCREEN_W-15, 9, makecol(0,0,0));
        textprintf(buffer, font_x_small, SCREEN_W-100+2+2, 2, makecol(128,128,255), "Mouse + (%d,%d)", (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE);

        draw_mouse_cursor();
    }
    if (F_debug_mode || (F_draw_boundrys || ((drawing_destination == DRAWING_TO_BOUNDRY) && (F_map_maker_mode))))
    {
       draw_map_boundrys(buffer, (int)(camera.x), (int)(camera.y));
       draw_ramps();
    }

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include "logic.hpp"

#define MAX_BLOOD_DROPS 7

void empty_the_bad_bear_vector()
{
    int k=0;
    for (k=current_level.enemy.size()-1; k>=0; k--) {current_level.enemy.pop_back();}
}

void empty_the_blood_drop_vector()
{
    int k=0;
    for (k=blood_drops.size()-1; k>=0; k--) {blood_drops.pop_back();}
}

void empty_the_poofs_vector()
{
    int k=0;
    for (k=poofs.size()-1; k>=0; k--) {poofs.pop_back();}
}

void empty_the_1_ups_vector()
{

}

void empty_the_power_up_vector()
{
    int k=0;
    for (k=current_level.power_up.size()-1; k>=0; k--) {current_level.power_up.pop_back();}
}


void empty_all_the_vectors()
{
     empty_the_bad_bear_vector();
     empty_the_blood_drop_vector();
     empty_the_1_ups_vector();
     empty_the_poofs_vector();
     empty_the_power_up_vector();
}


void empty_the_effects_vectors()
{
     empty_the_blood_drop_vector();
     empty_the_1_ups_vector();
     empty_the_poofs_vector();
     // !!!!! should add empty_num_of_bears_left_vector();
}    



void test_player_enemy_collisions(void)
{


    int k=0;
    int simultanious_kill_counter=0;
    int points_in_fer=0;

    if (player.velocity.y > 0.0f)
    {
       for (k=0; k<current_level.enemy.size(); k++)
       {
          if (current_level.enemy[k].params.alive() && (current_level.enemy[k].map_num == current_level.get_current_map_index()))
          {
             if (player.ditect_collision(current_level.enemy[k].params.get_left_edge_int(), current_level.enemy[k].params.get_top_edge_int(), current_level.enemy[k].params.get_right_edge_int(), current_level.enemy[k].params.get_bottom_edge_int()))
             {
                 current_level.enemy[k].params.take_and_react_to_damage(player.strength);
                 if (current_level.enemy[k].params.dead())
                 {
                    poof_class gimp_poof_class;
                    gimp_poof_class.set_coordinates(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int()); 
                    poofs.push_back(gimp_poof_class);

                    // play sound effect (splat)
                    assign_points(current_level.enemy[k].params.points);
                    points_in_fer += current_level.enemy[k].params.points;
                    //poofs[0].set_coordinates(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int());
                    if (!blood_censored) make_drops((rand()%MAX_BLOOD_DROPS)+2, current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int()+10);
                    //make_drops2((rand()%10)+5, bad_bear[k].get_center_int(), bad_bear[k].get_middle_int());
                    num_of_enemies_left--;


                    num_of_bears_left_class gimp_num_of_bears_left_class;
                    gimp_num_of_bears_left_class.place_here(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int());
                    gimp_num_of_bears_left_class.num = num_of_enemies_left;
                    bears_left_notif.push_back(gimp_num_of_bears_left_class);
                    //bears_left_notif[bears_left_notif.size()-1]
                    //bears_left_notif[bears_left_notif.size()-1]

                    play_random_splat_sound();
                    if (num_of_enemies_left == 0)
                    {
                        time_to_kill_all_the_bears = ellapsed_time;
                        killed_em_all_counter = 300;
                    }
                    simultanious_kill_counter++;
                    if (!(simultanious_kill_counter >= 2))
                    {
                       current_chain++;
                    }
                 }
                 if (player.on_ladder) {player.get_off_ladder();}
                 player.velocity.y = -5.5f;
             }
          }
       }
       if (simultanious_kill_counter >= 2)
       {
           simultanious_kill = simultanious_kill_counter;
           award_counter = 250;
           total_points_in_the_fer = points_in_fer;
           player_score += total_points_in_the_fer*simultanious_kill;
           awards.add_fer(total_points_in_the_fer);
           //player_lives++;
           
           //draw_one_up_class gimp_draw_one_ups_class;
           //gimp_draw_one_ups_class.place_here(player.get_center_int(), player.get_middle_int());
           //draw_one_ups.push_back(gimp_draw_one_ups_class);

           // play sound effect (1up)
           //play_sample(one_up_sample, 64, 128, 1000, false);

       }
       else
       {
           //bears_left_notif.push_back();
           //bears_left_notif[bears_left_notif.size()-1].place_here(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int());
           //bears_left_notif[bears_left_notif.size()-1].num = num_of_enemies_left;
       }
    }
    else if (player.post_pain_counter == 0)
    {
       for (k=0; k<current_level.enemy.size(); k++)
       {
          if (current_level.enemy[k].params.alive() && (current_level.enemy[k].map_num == current_level.get_current_map_index()))
          {
              if (current_level.enemy[k].params.post_pain_counter == 0)
              {
                 if (player.ditect_collision(current_level.enemy[k].params.get_left_edge_int(), current_level.enemy[k].params.get_top_edge_int(), current_level.enemy[k].params.get_right_edge_int(), current_level.enemy[k].params.get_bottom_edge_int()))
                 {
                    player.take_and_react_to_damage(current_level.enemy[k].params.strength);
                 }
              }
          }
       }
    }
}



bool point_box_collision(float x, float y, float xx1, float yy1, float xx2, float yy2, float padding)
{
    if (x+padding < xx1) return false;
    if (x-padding > xx2) return false;
    if (y+padding < yy1) return false;
    if (y-padding > yy2) return false;
    return true;
}



#define BULLET_STRENGTH 1

void test_enemy_bullet_collisions()
{
    if (bullet_manager.bullet.size() == 0) return;

    int simultanious_kill_counter=0;
    int points_in_fer=0;

    for (int i=0; i<bullet_manager.bullet.size(); i++)
    {
      if (bullet_manager.bullet[i].active)
      {
       for (int k=0; k<current_level.enemy.size(); k++)
       {
          if (current_level.enemy[k].params.alive() && (current_level.enemy[k].map_num == current_level.get_current_map_index()))
          {
             if (point_box_collision(bullet_manager.bullet[i].x, bullet_manager.bullet[i].y, current_level.enemy[k].params.get_left_edge_int(), current_level.enemy[k].params.get_top_edge_int(), current_level.enemy[k].params.get_right_edge_int(), current_level.enemy[k].params.get_bottom_edge_int(), 4))
             {

                 if (current_level.enemy[k].params.post_pain_counter == 0)
                 {
                     current_level.enemy[k].params.take_and_react_to_damage(BULLET_STRENGTH);
                     bullet_manager.bullet[i].active = false;
                 }
                 else
                 {
                     bullet_manager.bullet[i].ricochet();
                 }
                 if (current_level.enemy[k].params.dead())
                 {
                    poof_class gimp_poof_class;
                    gimp_poof_class.set_coordinates(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int()); 
                    poofs.push_back(gimp_poof_class);

                    // play sound effect (splat)
                    assign_points(current_level.enemy[k].params.points);
                    points_in_fer += current_level.enemy[k].params.points;
                    //poofs[0].set_coordinates(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int());
                    if (!blood_censored) make_drops((rand()%MAX_BLOOD_DROPS)+2, current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int()+10);
                    //make_drops2((rand()%10)+5, bad_bear[k].get_center_int(), bad_bear[k].get_middle_int());
                    num_of_enemies_left--;


                    num_of_bears_left_class gimp_num_of_bears_left_class;
                    gimp_num_of_bears_left_class.place_here(current_level.enemy[k].params.get_center_int(), current_level.enemy[k].params.get_middle_int());
                    gimp_num_of_bears_left_class.num = num_of_enemies_left;
                    bears_left_notif.push_back(gimp_num_of_bears_left_class);

                    play_random_splat_sound();
                    if (num_of_enemies_left == 0)
                    {
                        time_to_kill_all_the_bears = ellapsed_time;
                        killed_em_all_counter = 300;
                    }
                    //simultanious_kill_counter++;
                    if (!(simultanious_kill_counter >= 2))
                    {
                       //current_chain++;
                    }
                    bullet_manager.bullet[i].active = false;
                 }
             }
          }
       }
      }
    }


}




void test_destructable_block_bullet_collision()
{
    if (bullet_manager.bullet.size() == 0) return;

    for (int i=0; i<bullet_manager.bullet.size(); i++)
    {
//       if (bullet[i].x < 0) || (bullet[i].x > ))
       if (block_type_at((int)bullet_manager.bullet[i].x, (int)bullet_manager.bullet[i].y) == BLOCK_DESTRUCTABLE)
       {
           // change block graphic
           //current_map.tile[(int)bullet_manager.bullet[i].x/16][(int)bullet_manager.bullet[i].y/16].layer[0] = 0;
           //current_map.tile[(int)bullet_manager.bullet[i].x/16][(int)bullet_manager.bullet[i].y/16].layer[1] = 0;
           //current_map.tile[(int)bullet_manager.bullet[i].x/16][(int)bullet_manager.bullet[i].y/16].layer[2] = 0;

           // change block_function
           current_map.tile[(int)bullet_manager.bullet[i].x/16][(int)bullet_manager.bullet[i].y/16].boundry = BOUNDRY_EMPTY;
           block_destruction_manager.add_particles(bullet_manager.bullet[i].x, bullet_manager.bullet[i].y, bullet_manager.bullet[i].velocity_x, bullet_manager.bullet[i].velocity_y);

           bullet_manager.bullet[i].active = false;

           // spawn destruction effect
           // pickup_item_sound();
       }
    }
}



void play_secret_found_sound()
{
    play_sample(secret_found_sample, 200, 128, 1000, false);
}

void play_menu_move_sound()
{
    play_sample(menu_move, 200, 128, 900+(rand()%201), false);
}

void play_menu_select_sound()
{
    play_sample(menu_select, 200, 128, 1000, false); 
}

void play_start_game_sound()
{
    play_sample(menu_select2, 200, 128, 1000, false); 
}    

void play_pause_sound()
{
    play_sample(pause_sample, 200, 128, 1000, false); 
}    

void play_unpause_sound()
{
    play_sample(unpause_sample, 200, 128, 1000, false); 
}    

void play_heart_sound()
{
    play_sample(power_up_sample_heart, 64, 128, 1000, false);
}

void play_switch_sound()
{
    play_sample(menu_move, 200, 128, 900+(rand()%201), false);
}
  
void play_one_up_sound()
{
    play_sample(one_up_sample, 64, 128, 1000, false);
}   

void play_key_sound()
{
    play_sample(pickup_key_sample, 64, 128, 1000, false);
}

void play_use_key_sound()
{
    play_sample(use_key_sample, 196, 128, 1000, false);
}

void play_coin_sound()
{
    play_sample(pickup_coin_sample, 64, 128, 1000, false);
}

void play_locked_door_sound()
{
    play_sample(door_locked_sample, 64, 128, 1000, false);
}

void play_open_door_sound()
{
    play_sample(door_open_sample, 64, 128, 1000, false);
}

void play_close_door_sound()
{
    //play_sample(door_close_sample, 64, 128, 1000, false);
}                 



int adding_coins_counter = 0;
int coins_to_be_added = 0;
bool add_coin = true;

void pickup_coins(int num=1)
{
    coins_to_be_added += num;
}



#define ADDING_COINS_SPEED 3
void adding_coins_update()
{
    if ((coins_to_be_added > 0) && (add_coin))
    {
       player_coins++;
       coins_to_be_added--;
       play_coin_sound();
       add_coin = false;
    }


    adding_coins_counter -= 1;
    if (adding_coins_counter < -1) adding_coins_counter = -1;
    if ((adding_coins_counter < 0) && (!add_coin))
    {
        adding_coins_counter = ADDING_COINS_SPEED;
        add_coin = true;
    }

    while (player_coins >= 100) { player_coins -= 100; player_lives++; play_one_up_sound(); }
}


void test_player_power_up_collisions(void)
{
      int k=0;

       for (k=0; k<current_level.power_up.size(); k++)
       {
           if (current_level.power_up[k].alive && (current_level.power_up[k].map_num == current_level.get_current_map_index()))
           {
              if (player.ditect_collision(
               (int)current_level.power_up[k].map_pos.x-current_level.power_up[k].size.x/2,
               (int)current_level.power_up[k].map_pos.y-current_level.power_up[k].size.y/2,
               (int)current_level.power_up[k].map_pos.x+current_level.power_up[k].size.x/2,
               (int)current_level.power_up[k].map_pos.y+current_level.power_up[k].size.y/2))
              {
                  if (current_level.power_up[k].type == heart_const)
                  {
                     play_heart_sound();
                     current_level.power_up[k].alive = false;
                     player_score += 100;
                     player.energy_up(5.0f);
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                  }
                  else if (current_level.power_up[k].type == key_const)
                  {
                     play_key_sound();
                     current_level.power_up[k].alive = false;
                     player_score += 100;
                     player.pickup_key();
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                  }
                  else if (current_level.power_up[k].type == one_up_const)
                  {
                     play_one_up_sound();
                     current_level.power_up[k].alive = false;
                     player_score += 100;
                     player_lives++;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
                  else if (current_level.power_up[k].type == small_jewel_const)
                  {
                     player_score += 100;
                     pickup_coins(1);
                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
                  else if (current_level.power_up[k].type == medium_jewel_const)
                  {
                     player_score += 100;
                     pickup_coins(5);
                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
                  else if (current_level.power_up[k].type == large_jewel_const)
                  {
                     player_score += 100;
                     pickup_coins(10);
                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
                  else if (current_level.power_up[k].type == silver_key_const)
                  {
                     play_heart_sound();

                     player.pickup_silver_key();

                     player_score += 100;
                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
                  else if (current_level.power_up[k].type == turbo_jump_const)
                  {
                     play_heart_sound();
                     player_score += 100;

                     player.put_on_jumping_shoes();

                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                  }
                  else if (current_level.power_up[k].type == gun_const)
                  {
                     play_heart_sound();

                     player.pickup_gun();

                     player_score += 100;
                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
                  else if (current_level.power_up[k].type == running_shoes_const)
                  {
                     play_heart_sound();

                     player.put_on_running_shoes();

                     player_score += 100;
                     current_level.power_up[k].alive = false;
                     begin_drawing_picked_up_item(current_level.power_up[k].type, current_level.power_up[k].map_pos.x, current_level.power_up[k].map_pos.y);
                     //player.pickup_key();
                  }
              }
           }
       }
}



void update_player_animation()
{

    if (player.on_ladder)
    {
        player.anim_rate = 10;
        if (player.velocity.y == 0.0f) player.anim_counter = player.anim_rate-1;

        if (player.anim_counter > player.anim_rate)
        {
            if (bear == bear_climb1) bear = bear_climb2;
            else if (bear == bear_climb2) bear = bear_climb1;
            player.anim_counter = 0;
        }
    }
    else
    {
        if (player.velocity.x != 0.0f)
        {
            if (player.anim_counter > player.anim_rate)
            {
                if ((bear == bear_in_air) || (bear == bear_duck)) bear = bear1;
                else if (bear == bear1) bear = bear2;
                else if (bear == bear2) bear = bear3;
                else if (bear == bear3) bear = bear4;
                else if (bear == bear4) bear = bear1;
                player.anim_counter = 0;
            }
        }
        else if (player.velocity.x == 0.0f)
        {
            bear = bear1;
            player.anim_counter = 0;
        }

        if (ABS(player.velocity.x) < 1.5f) player.anim_rate = 10;
        else if (ABS(player.velocity.x) < 2.75f) player.anim_rate = 7;
        else player.anim_rate = 5;

        if (!player.on_ground)
        {
            bear = bear_in_air;
            player.anim_counter = player.anim_rate-1;
        }
        if (player.is_ducking)
        {
            bear = bear_duck;
            player.anim_counter = player.anim_rate-1;
        }

    }

    player.anim_counter++;
}


void reset_stats_for_scroll_on()
{
        smooth_stats_counter = (float)SCREEN_W;
        smooth_stats_counter_helper = 10.0f; //7.4f;      // 10

        smooth_stats_counter2 = smooth_stats_counter;
        smooth_stats_counter_helper2 = smooth_stats_counter_helper;
        smooth_stats_counter2_delay = 12;

        smooth_stats_counter3 = smooth_stats_counter;
        smooth_stats_counter_helper3 = smooth_stats_counter_helper;
        smooth_stats_counter3_delay = (int)(smooth_stats_counter2_delay*1.8f);
}

float this_dum_float = 0.155f;
void update_stat_scroll_on()
{
    smooth_stats_counter_helper -= 0.156f; //  0.085f;      //0.155;
    if (smooth_stats_counter_helper < 0.0f) smooth_stats_counter_helper = 0.0f;

    smooth_stats_counter -= (smooth_stats_counter_helper);
    if (smooth_stats_counter < 0.0f) smooth_stats_counter = 0.0f;


    smooth_stats_counter2_delay--;
    if (smooth_stats_counter2_delay < 0)
    {
        smooth_stats_counter2_delay = 0;
        smooth_stats_counter_helper2 -= this_dum_float; //  0.085f;      //0.155;
        if (smooth_stats_counter_helper2 < 0.0f) smooth_stats_counter_helper2 = 0.0f;

        smooth_stats_counter2 -= (smooth_stats_counter_helper2);
        if (smooth_stats_counter2 < 0.0f) smooth_stats_counter2 = 0.0f;
    }


    smooth_stats_counter3_delay--;
    if (smooth_stats_counter3_delay < 0)
    {
        smooth_stats_counter3_delay = 0;
        smooth_stats_counter_helper3 -= this_dum_float; //  0.085f;      //0.155;
        if (smooth_stats_counter_helper3 < 0.0f) smooth_stats_counter_helper3 = 0.0f;

        smooth_stats_counter3 -= (smooth_stats_counter_helper3);
        if (smooth_stats_counter3 < 0.0f) smooth_stats_counter3 = 0.0f;
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//bool release_a = false;
//bool release_b = false;
bool release_plus = false;
bool release_minus = false;
//bool release_up = false;

void drawing_mode()
{

    //if (key[KEY_F6]) drawing_destination = DRAWING_TO_LAYER_1;
    //if (key[KEY_F7]) drawing_destination = DRAWING_TO_LAYER_2;
    //if (key[KEY_F8]) drawing_destination = DRAWING_TO_LAYER_3;
    //if (key[KEY_F9]) drawing_destination = DRAWING_TO_BOUNDRY;
    //if (key[KEY_F10]) drawing_destination = DRAWING_TO_ENVIRONMENT;

    if (drawing_destination != DRAWING_TO_BOUNDRY)
    {
        if (key[ALLEGRO_KEY_PAD_PLUS] && release_plus) {pen_from_tile_index++; release_plus=false;}
        else if (!key[ALLEGRO_KEY_PAD_PLUS]) release_plus = true;
        if (key[ALLEGRO_KEY_PAD_MINUS] && release_minus)
        {
            //if (pen_from_tile_index == 0) pen_from_tile_index = current_map.num_of_tiles()-1;
            //else
            if (pen_from_tile_index == 0) pen_from_tile_index = current_map.tile_index.size()-1;
            else pen_from_tile_index--;
            release_minus = false;
        }
        else if (!key[ALLEGRO_KEY_PAD_MINUS]) release_minus = true;

        if (pen_from_tile_index > current_map.num_of_tiles()-1) pen_from_tile_index = 0;

        drawing_pen_int1 = current_map.tile_index[pen_from_tile_index].index_num;
    }
    else if (drawing_destination == DRAWING_TO_BOUNDRY)
    {
        if (key[ALLEGRO_KEY_PAD_PLUS] && release_plus) {pen_of_boundry++; release_plus=false;}
        else if (!key[ALLEGRO_KEY_PAD_PLUS]) release_plus = true;
        if (key[ALLEGRO_KEY_PAD_MINUS] && release_minus)
        {
            //if (pen_from_tile_index == 0) pen_from_tile_index = current_map.num_of_tiles()-1;
            //else
            if (pen_of_boundry == 0) pen_of_boundry = 17;
            else pen_of_boundry--;
            release_minus = false;
        }
        else if (!key[ALLEGRO_KEY_PAD_MINUS]) release_minus = true;

        if (pen_of_boundry > 19) pen_of_boundry = 0;

        drawing_pen_int1 = pen_of_boundry;

    }


    switch (drawing_destination)
    {
        case DRAWING_TO_BOUNDRY:
             if (mouse_b1) set_boundry_block((mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int1);
             if (mouse_b2) set_boundry_block((mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int2);
             break;
        case DRAWING_TO_LAYER_1:
             if (mouse_b1) set_tile(1, (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int1);
             if (mouse_b2) set_tile(1, (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int2);
             break;
        case DRAWING_TO_LAYER_2:
             if (mouse_b1) set_tile(2, (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int1);
             if (mouse_b2) set_tile(2, (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int2);
             break;
        case DRAWING_TO_LAYER_3:
             if (mouse_b1) set_tile(3, (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int1);
             if (mouse_b2) set_tile(3, (mouse_x+(int)camera.x)/TILE_SIZE, (mouse_y+(int)camera.y)/TILE_SIZE, drawing_pen_int2);
             break;
        case DRAWING_TO_ENVIRONMENT:
             break;
   }

}


int get_door_array_from_door_num(int door_num)
{
    door_num -= BLOCK_DOOR;
    int jj=0;
    for (jj=0; jj<current_level.door.size(); jj++)
    {
        if (current_level.door[jj].index_num == door_num) {return jj;}
    }
    return -1;
}    

int go_in_door(int door_num)
{
    show_loading_notice();

    int map_num_to_load = -1;

    int the_array_index_number_of_the_door_with_the___index_num__equal_to__door_num = get_door_array_from_door_num(door_num);
    

    if (the_array_index_number_of_the_door_with_the___index_num__equal_to__door_num == -1)
    {
        allegro_message("the door leads nowhere");
        my_error_message("the door leads nowhere");
        return 1; // the door leads nowhere
    }


    map_num_to_load = current_level.door[the_array_index_number_of_the_door_with_the___index_num__equal_to__door_num].go_to_new_map;

    if (map_num_to_load)
    {
        int the_array_index_number_of_the_map_with_the__index_num__equal_to_the_new_map_of_the_door = -1;

        if (map_num_to_load > current_level.number_of_maps)
        {
             allegro_message("this door points to a map that is not there");   
             return 1;
        }
        else if (map_num_to_load <= 0)
        {
             allegro_message("the door does not point to a map");
             return 1; // the door does not point to a map
        }

        string fix_me_gimp_string = "";
        fix_me_gimp_string.append("levels and maps/");
        fix_me_gimp_string.append(level_to_start);


        if (load_map_from_level(map_num_to_load, fix_me_gimp_string.c_str()) == 1)
        {
            allegro_message("the door can not find the destination");
            return 1;
        }

        current_level.current_map_index = map_num_to_load;

        door_drawing_manager.set_door_tile_coordinates(&current_map);
    }

    empty_the_effects_vectors();

    int smaller_var = the_array_index_number_of_the_door_with_the___index_num__equal_to__door_num;

    player.set_left_edge(current_level.door[smaller_var].map_spawn_x);
    player.set_top_edge(current_level.door[smaller_var].map_spawn_y);

    if (current_level.door[smaller_var].camera_x != -1) { camera.x = current_level.door[smaller_var].camera_x; }
    else { camera.start_x_move_from(camera.x); }
    if (current_level.door[smaller_var].camera_y != -1) { camera.y = current_level.door[smaller_var].camera_y; }
    else { camera.start_y_move_from(camera.y); }

    camera.lock_x = current_level.door[smaller_var].camera_lock_x;
    camera.lock_y = current_level.door[smaller_var].camera_lock_y;
    camera.min_x = current_level.door[smaller_var].camera_min_x;
    camera.max_x = current_level.door[smaller_var].camera_max_x;
    camera.min_y = current_level.door[smaller_var].camera_min_y;
    camera.max_y = current_level.door[smaller_var].camera_max_y;

    return 0;
}





bool release_f1 = false;
bool release_f2 = false;
bool release_f6 = false;
bool release_f7 = false;
bool release_f8 = false;
bool release_f9 = false;
bool release_f10 = false;
bool release_f11 = false;


bool update_enemy_animations()
{
    bool still_some_bears = false;

    int k=0;
    for (k=0; k<current_level.enemy.size(); k++)
    {
        if (current_level.enemy[k].params.alive() && (current_level.enemy[k].map_num == current_level.get_current_map_index()))
        {
            still_some_bears = true;

            current_level.enemy[k].params.update_state();
            if (current_level.enemy[k].params.anim_counter > current_level.enemy[k].params.anim_rate)
            {
                // if its a red bad bear:
                if (current_level.enemy[k].params.pic == bad_bear2_pic1) current_level.enemy[k].params.pic = bad_bear2_pic2;
                else if (current_level.enemy[k].params.pic == bad_bear2_pic2) current_level.enemy[k].params.pic = bad_bear2_pic1;
                // if its a yellow bad bear:
                if (current_level.enemy[k].params.pic == bad_bear_pic1) current_level.enemy[k].params.pic = bad_bear_pic2;
                else if (current_level.enemy[k].params.pic == bad_bear_pic2) current_level.enemy[k].params.pic = bad_bear_pic1;
                // if its a blue bear:
                if (current_level.enemy[k].params.pic == blue_bear_pic1) current_level.enemy[k].params.pic = blue_bear_pic2;
                else if (current_level.enemy[k].params.pic == blue_bear_pic2) current_level.enemy[k].params.pic = blue_bear_pic1;
                // if its a purple bear:
                if (current_level.enemy[k].params.pic == purple_bear_pic1) current_level.enemy[k].params.pic = purple_bear_pic1;
                else if (current_level.enemy[k].params.pic == purple_bear_pic2) current_level.enemy[k].params.pic = purple_bear_pic2;

                current_level.enemy[k].params.anim_counter = 0;
            }
            current_level.enemy[k].params.anim_counter++;

        }
    }

    return still_some_bears;
}




int stupid_play_counter = 100;
void fake_play_game()
{
    if (pre_game_counter <= 40)
    {  player.move_right();
       stupid_play_counter--;
       if (stupid_play_counter < 0) {stupid_play_counter = (rand() % 200); player.jump();}
       if (stupid_play_counter <= 100 -20) player.release_jump();
       if ((player.velocity.x == 0.0f) && (pre_game_counter != 40)) player.jump();
    }
}



int hilight_transparency = 64;
bool hilight_fade_direction = true; // true = increase, false = decrease;
float hilight_fade_rate = 0.05f;

void update_hilight_transparency()
{
    if (hilight_fade_direction == true) // the hilight is increasing
    {
         hilight_transparency += (int)(hilight_transparency*hilight_fade_rate);
         if (hilight_transparency > 255) {hilight_fade_direction = false; hilight_transparency=255;}
    }
    else
    {
         hilight_transparency -= (int)(hilight_transparency*hilight_fade_rate);
         if (hilight_transparency < 64) {hilight_fade_direction = true; hilight_transparency=64;}
    }

}


#define MENU_TITLE 25583
#define MENU_PAUSE 34820
#define MENU_CHOOSE_LEVEL 448156

int menu_focus=1;
int menu_number=MENU_TITLE;

bool button_down_release=false;
bool button_up_release=false;

void figure_out_title_screen_user_input()
{
    if (button_down && button_down_release) {menu_focus++; button_down_release=false; play_menu_move_sound();}
    else if (!button_down) button_down_release=true;

    if (button_up && button_up_release) {menu_focus--; button_up_release=false; play_menu_move_sound();}
    else if (!button_up) button_up_release=true;

    if (menu_number == MENU_TITLE)
    {
        if (menu_focus == 5) menu_focus = 1;
        if (menu_focus == 0) menu_focus = 4;
    }

    if ((button_a && button_a_release) || (button_b && button_b_release))
    {
       button_a_release=false;
       button_b_release=false;

       if ((menu_number == MENU_TITLE) && (menu_focus == 1))
       {
           /////////////// START THE GAME RIGHT HERE ////////////////
           /////////////// START THE GAME RIGHT HERE ////////////////
           /////////////// START THE GAME RIGHT HERE ////////////////

           current_world.start_from_first_level();

           //game_state == STATE_WAITING_FOR_LEVEL_START;

           //make_level_list();
           //game_state = STATE_CHOOSING_LEVEL;
           //menu_number = MENU_CHOOSE_LEVEL;
           //menu_focus = 1;
       }
       else if ((menu_number == MENU_TITLE) && (menu_focus == 4))
       {
           abort_game=true;
       }
    }

    if (!button_a) button_a_release = true;
    if (!button_b) button_b_release = true;
}

int pre_pause_gamestate = 0;

void figure_out_pause_screen_user_input(void)
{
    if (button_down && button_down_release) {menu_focus++; button_down_release=false; play_menu_move_sound();}
    else if (!button_down) button_down_release=true;

    if (button_up && button_up_release) {menu_focus--; button_up_release=false; play_menu_move_sound();}
    else if (!button_up) button_up_release=true;

    if (menu_number == MENU_PAUSE)
    {
        if (menu_focus == 4) menu_focus = 1;
        else if (menu_focus == 0) menu_focus = (4)-1;
    }


    if ((button_a && button_a_release) || (button_b && button_b_release))
    {
       button_a_release=false;
       button_b_release=false;

       if (menu_number == MENU_PAUSE)
       {
           if (menu_focus == 1)  // unpause
           {
              //play_menu_select_sound();
                 play_unpause_sound();
                 if (pre_game_counter > 0)
                 {
                     pre_pause_gamestate = game_state;
                     game_state = STATE_WAITING_FOR_LEVEL_START;
                 }
                 else
                 {
                     game_state = pre_pause_gamestate;
                     ten_mili_seconds = clock_time_suspended_at;
                     B_clock_time_suspended = false;
                 }        
              //game_state = 0;
              
              //highcolor_fade_out(5);
              //show_loading_notice__to_screen();

              //restart_level();
           }
           else if (menu_focus == 2)  // restart level
           {
              game_state = 0;
              play_unpause_sound();
              
              //highcolor_fade_out(5);
              show_loading_notice__to_screen();

              restart_level();
           }
           else if (menu_focus == 3)  // exit to title
           {
              play_unpause_sound();

              //highcolor_fade_out(5);
              show_loading_notice__to_screen();

              load_game();
              menu_number = MENU_TITLE;
              menu_focus = 1;
           }

       }
    }

    if (!button_a) button_a_release = true;
    if (!button_b) button_b_release = true;

}

char *char_ptr(const char *c)
{
    string st;
    st = c;
    char *cc = strdup(st.c_str());
    return cc;
}    

void figure_out_choose_level_screen_user_input(void)
{
    if (button_down && button_down_release) {menu_focus++; button_down_release=false; play_menu_move_sound();}
    else if (!button_down) button_down_release=true;

    if (button_up && button_up_release) {menu_focus--; button_up_release=false; play_menu_move_sound();}
    else if (!button_up) button_up_release=true;

    if (menu_number == MENU_CHOOSE_LEVEL)
    {
        if (menu_focus == level_list.size()+1) menu_focus = 1;
        else if (menu_focus == 0) menu_focus = level_list.size();
    }


    if ((button_a && button_a_release) || (button_b && button_b_release))
    {
        button_a_release=false;
        button_b_release=false;

        if (menu_number == MENU_CHOOSE_LEVEL)
        {
            game_state = 0;
            play_start_game_sound();

            level_to_start = level_list[menu_focus-1].file_name;
              
            show_loading_notice__to_screen();

            destroy_level_list();
            //destroy_bitmap(choose_a_level);
            load_level(level_to_start.c_str());
        }
    }

    if (!button_a) button_a_release = true;
    if (!button_b) button_b_release = true;

}


void old_figure_out_choose_level_screen_user_input(void)
{
    if (button_down && button_down_release) {menu_focus++; button_down_release=false; play_menu_move_sound();}
    else if (!button_down) button_down_release=true;

    if (button_up && button_up_release) {menu_focus--; button_up_release=false; play_menu_move_sound();}
    else if (!button_up) button_up_release=true;

    if (menu_number == MENU_CHOOSE_LEVEL)
    {
        if (menu_focus == 3) menu_focus = 1;
        else if (menu_focus == 0) menu_focus = 2;
    }


    if ((button_a && button_a_release) || (button_b && button_b_release))
    {
       button_a_release=false;
       button_b_release=false;

       if (menu_number == MENU_CHOOSE_LEVEL)
       {
           if (menu_focus == 1)
           {
              game_state = 0;
              play_start_game_sound();
              level_to_start = "levels and maps/Level_1.lv2";
 
              //highcolor_fade_out(5);
              show_loading_notice__to_screen();

              destroy_level_list();
              load_level(level_to_start.c_str());
           }
           else if (menu_focus == 2)
           {
              game_state = 0;
              play_start_game_sound();
              level_to_start = "levels and maps/Level_2.lv2";

              //highcolor_fade_out(5);
              show_loading_notice__to_screen();

              destroy_level_list();
              load_level(level_to_start.c_str());
           }

       }
    }

    if (!button_a) button_a_release = true;
    if (!button_b) button_b_release = true;

}



void update_award_timers(void)
{
        int k=0;
        for (k=draw_one_ups.size()-1; k>=0; k--)
        {
            if (draw_one_ups[k].counter != 0)
            {
                draw_one_ups[k].update_pos();
            }
        }

        k=0;
        for (k=bears_left_notif.size()-1; k>=0; k--)
        {
            if (bears_left_notif[k].counter != 0)
            {
                bears_left_notif[k].update_pos();
            }
        }

        award_counter--;
        if (award_counter < 0) award_counter = 0;

        chain_award_counter--;
        if (chain_award_counter < 0) chain_award_counter = 0;
}

void update_pre_game(void)
{
    ///
    go_banner_counter--;
    if (go_banner_counter < 0) go_banner_counter = 0;

    pre_game_counter--;
    if (pre_game_counter < 0) pre_game_counter = 0;

    if (pre_game_counter > 0) player.move_nowhere();

    if ((pre_game_counter == 0) && (game_state == STATE_WAITING_FOR_LEVEL_START))
    {
        game_state = STATE_IN_LEVEL;
        ten_mili_seconds = 0;
        time_left_in_round = current_level.time_limit;
        go_banner_counter = 60;
        //level_timer = current_level.time_limit;
    }
    ///

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////






int get_on_a_ramp_judge()
{

    // test to see if the player is above the ramp line before velocity
    // test to see if the player is below the ramp line after velocity

    // if the player was above before and below after and
    //     the player is within the ramp coords after velocity


    bool player_gets_on_a_ramp = false;

    bool above_ramp_line_before_velocity = false;
    bool below_ramp_line_after_velocity = false;

    int xx=0;
    for (xx=0; xx<current_map.ramp.size(); xx++)
    {
        above_ramp_line_before_velocity = false;
        below_ramp_line_after_velocity = false;
        //float point_before_entering_line =

        if (player.on_ramp == current_map.ramp[xx].index_num)
        {
            if (!player.ditect_collision_center(current_map.ramp[xx].get_left_edge(), current_map.ramp[xx].get_top_map_y(),
                current_map.ramp[xx].get_right_edge(), current_map.ramp[xx].get_bottom_map_y()))
                {
                    player.get_off_ramp();
                }
        }
        else
        {
                // see if above_ramp_line_before_velocity
                if (player.get_bottom_edge() <=
                   ((((float)(current_map.ramp[xx].get_top_map_y()
                   - current_map.ramp[xx].get_bottom_map_y()))
                   /((float)(current_map.ramp[xx].get_top_map_x()
                   - current_map.ramp[xx].get_bottom_map_x()))
                   *(player.get_center_int()
                   -current_map.ramp[xx].get_bottom_map_x()))
                   +(current_map.ramp[xx].get_bottom_map_y())))
                {
                    above_ramp_line_before_velocity = true;
                }
                //else if (player.get_bottom_edge() < point_on_line_before_velocity)
                //current_map.ramp[xx].get_top_map_y())
                //{
                //   above_ramp_line_before_velocity = true;
                //}
                // see if below_ramp_line_after_velocity
                if ((player.get_bottom_edge()+player.velocity.y) >=
                   ((((float)(current_map.ramp[xx].get_top_map_y()
                   - current_map.ramp[xx].get_bottom_map_y()))
                   /((float)(current_map.ramp[xx].get_top_map_x()
                   - current_map.ramp[xx].get_bottom_map_x()))
                   *(player.get_center_int()+player.velocity.x
                   -current_map.ramp[xx].get_bottom_map_x()))
                   +(current_map.ramp[xx].get_bottom_map_y())))
                {
                    below_ramp_line_after_velocity = true;
                }


           // if ((player.ditect_collision_center(current_map.ramp[xx].get_left_edge(), current_map.ramp[xx].get_top_map_y(),
            //    current_map.ramp[xx].get_right_edge(), current_map.ramp[xx].get_bottom_map_y()))

           //     ||

            if (    (player.ditect_collision_center_post_v(current_map.ramp[xx].get_left_edge(), current_map.ramp[xx].get_top_map_y(),
                current_map.ramp[xx].get_right_edge(), current_map.ramp[xx].get_bottom_map_y())))
            {


                if (above_ramp_line_before_velocity && below_ramp_line_after_velocity)
                {
                    player.get_on_ramp(current_map.ramp[xx].index_num);
                    //my_error_message("SNARF");
                    player_gets_on_a_ramp = true;
                    return 1;
                }
            }
         }
    }
    return 0;
}

//float point_on_a_ramp_y_old(ramp_class r, float xx)
//{
//    return ((((float)(r.get_top_map_y() - r.get_bottom_map_y()))/((float)(r.get_top_map_x() - r.get_bottom_map_x()))*(xx-r.get_bottom_map_x()))+(r.get_bottom_map_y()));
//}


float point_on_ramp_y(int ramp_index_num, float xx)
{

    if (ramp_index_num != -1)
    {
        int array_num_of_the_ramp_with_the_ramp_index_num_equal_to__ramp_index_num = -1;

        int jj=0;
        for (jj=0; jj<current_map.ramp.size(); jj++)
        {
            if (current_map.ramp[jj].index_num == ramp_index_num)
            {
               array_num_of_the_ramp_with_the_ramp_index_num_equal_to__ramp_index_num = jj;
               jj = current_map.ramp.size();
            }
        }

        if (array_num_of_the_ramp_with_the_ramp_index_num_equal_to__ramp_index_num == -1)
        {
           my_error_message("cannot find ramp");
           return -1;
        }
        else
        {
           int s = array_num_of_the_ramp_with_the_ramp_index_num_equal_to__ramp_index_num;
           return ((((float)(current_map.ramp[s].get_top_map_y() - current_map.ramp[s].get_bottom_map_y()))/((float)(current_map.ramp[s].get_top_map_x() - current_map.ramp[s].get_bottom_map_x()))*(xx-current_map.ramp[s].get_bottom_map_x()))+(current_map.ramp[s].get_bottom_map_y()));
           //point_on_a_ramp_y_old(current_map.ramp[s], xx);
           //return point_on_a_line_y(current_map.ramp[s].top_x, current_map.ramp[s].top_y, current_map.ramp[s].bottom_x, current_map.ramp[s].bottom_y, xx);
        }
    }
    return -1.0f;
}

//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//#include "load_and_destroy.hpp"


void restart_stats()
{
    empty_all_the_vectors();
    ellapsed_time = 0;
    time_left_in_round = 0;
    //level_timer;
    pre_game_counter=260;
    simultanious_kill=0;
    award_counter=200;
    total_points_in_the_fer=0;
    current_chain = 0;
    chain_award = 0;
    chain_award_counter=0;

    ten_mili_seconds = 0;
    player.keys =0;

    num_of_enemies_left = 0;

    time_when_completed = 0;
    F_show_congrats_banner = false;

    time_to_kill_all_the_bears=-1;

    player.energy = player.max_energy;
}

int load_level(const char *address)
{



    empty_all_the_vectors();
    restart_stats();
    game_state = STATE_WAITING_FOR_LEVEL_START;

    door_drawing_manager.clear_all();
    camera.control(-1,-1,-1,-1,-1,-1);


    string fix_me_gimp_string = "";
    fix_me_gimp_string.append("levels and maps/");
    fix_me_gimp_string.append(address);

    if (current_level.load(fix_me_gimp_string.c_str()) != 0) return 1;



    load_map_from_level(current_level.get_current_map_index(), fix_me_gimp_string.c_str());




    door_drawing_manager.populate_level_door_data(&current_level);
    trigger_manager.populate_list(&current_map);

    time_left_in_round = current_level.time_limit;
    num_of_enemies_left = current_level.enemy.size();

    door_drawing_manager.set_door_tile_coordinates(&current_map);

    player.reset_for_new_level();

    do_logic();



    if (!no_fades_no_rests)
    {
        //rest(500);
        //draw_to_buffer();
        //highcolor_fade_in__(5);
        //fade_in_flip(5);
    }


    return 0;
}



void restart_level(void)
{
    load_level(level_to_start.c_str());
    //my_error_message("workin?");
}



void load_game(void)
{
    //allegro_message("inside loading game function");

    bullet_img = _load_bitmap("images/bullett.gif");

    holding_gun = _load_bitmap("images/holding_gun.gif");

    bear1 = _load_bitmap("images/bears/beary6-2.gif");
    bear2 = _load_bitmap("images/bears/beary6.gif");
    bear3 = _load_bitmap("images/bears/beary6-2.gif");
    bear4 = _load_bitmap("images/bears/beary6-3.gif");
    bear_duck = _load_bitmap("images/bears/beary6-duck.gif");
    bear = bear1;

    sparkle_particle_0 = _load_bitmap("images/effects/sparkle_particle_0.gif");
    sparkle_particle_1 = _load_bitmap("images/effects/sparkle_particle_1.gif");
    sparkle_particle_2 = _load_bitmap("images/effects/sparkle_particle_2.gif");
    sparkle_particle_3 = _load_bitmap("images/effects/sparkle_particle_3.gif");



    bear_climb1 = _load_bitmap("images/bears/beary_climb1.gif");
    bear_climb2 = _load_bitmap("images/bears/beary_climb2.gif");
    bear_in_air = _load_bitmap("images/bears/beary6-in_air.gif");

    bad_bear_pic1 = _load_bitmap("images/bears/yellow_bear_1.gif");
    bad_bear_pic2 = _load_bitmap("images/bears/yellow_bear_2.gif");
    blue_bear_pic1 = _load_bitmap("images/bears/blue_bear_1.gif");
    blue_bear_pic2 = _load_bitmap("images/bears/blue_bear_2.gif");
    blue_bear_jump_pic = _load_bitmap("images/bears/blue_bear_jump.gif");
    purple_bear_pic1 = _load_bitmap("images/bears/purple_bear_1.gif");
    purple_bear_pic2 = _load_bitmap("images/bears/purple_bear_2.gif");
    bad_bear2_pic1 = _load_bitmap("images/bears/brown_bear_1.gif");
    bad_bear2_pic2 = _load_bitmap("images/bears/brown_bear_2.gif");



#define ADD_ITEM(xx, yy)   xx##_img = _load_bitmap("images/items/" #xx ".gif");
#include "item_list.hpp"
#undef ADD_ITEM


    load_jewel_shimmers();


    if (blood_censored)
    {
        poof = _load_bitmap("images/censored_poof.gif");
    }    
    else 
    {
        poof = _load_bitmap("images/bloody_bear.gif");
    }    

    time_bground = _load_bitmap("images/ops/time_bground.gif");
    life_icon = _load_bitmap("images/ops/life_icon.gif");
    stat_hearts = _load_bitmap("images/ops/stat_hearts.gif");
    stat_bground = _load_bitmap("images/ops/stat_bground.gif");
    stat_bground_hearts = _load_bitmap("images/ops/stat_bground_hearts.gif");
    clock_icon = _load_bitmap("images/ops/clock.gif");
    clock_dial = _load_bitmap("images/ops/dial.gif");
    clock_face_overlay_r = _load_bitmap("images/ops/clock_face_red.gif");
    clock_face_overlay_g = _load_bitmap("images/ops/clock_face_green.gif");
    clock_face_overlay_y = _load_bitmap("images/ops/clock_face_yellow.gif");

    ready_banner = _load_bitmap("images/ops/ready_banner.gif");
    go_banner = _load_bitmap("images/ops/go_banner.gif");
    paused_banner = _load_bitmap("images/ops/paused_banner.gif");
    //one_up = _load_bitmap("images/one_up.bmp");

    no_bears = _load_bitmap("images/ops/no_bears3.gif");

    reset_stats_for_scroll_on();

    medal_gold = _load_bitmap("images/ops/medal_gold.gif");
    medal_silver = _load_bitmap("images/ops/medal_silver.gif");
    medal_bronze = _load_bitmap("images/ops/medal_bronze.gif");

    title_graphic = _load_bitmap("images/ops/title.gif");

    title_options = _load_bitmap("images/ops/options.gif");
    title_new_game = _load_bitmap("images/ops/new_game.gif");
    title_load_game = _load_bitmap("images/ops/load_a_saved_game.gif");
    title_exit = _load_bitmap("images/ops/exit.gif");





#define ADD_ROCK(x, y) x##y##_sample = load_sample(full_filename("sounds/" #x "_" #y ".ogg"));
#include "rock_list.hpp"
#undef ADD_ROCK




    congradulations = _load_bitmap("images/ops/congradulations.gif");
    time_up = _load_bitmap("images/ops/time_up.gif");

    load_locked_door_graphics();


    if (!blood_censored)
    {
        add_splat_sound_to_list("sounds/splat1.ogg");
        add_splat_sound_to_list("sounds/splat2.ogg");
        add_splat_sound_to_list("sounds/splat3.ogg");
        add_splat_sound_to_list("sounds/splat4.ogg");    //
        add_splat_sound_to_list("sounds/splat5.ogg");
        add_splat_sound_to_list("sounds/splat6.ogg");    //
        add_splat_sound_to_list("sounds/splat7.ogg");    //
        add_splat_sound_to_list("sounds/splat8.ogg");
    }    
    else
    {
        //add_splat_sound_to_list("sounds/destroy.ogg");
        //add_splat_sound_to_list("sounds/destroy.ogg");
        //add_splat_sound_to_list("sounds/destroy.ogg");
    }    


    // trigger

    trigger_on = _load_bitmap("images/trigger_on.gif");
    trigger_off = _load_bitmap("images/trigger_off.gif");


    // sounds

    menu_move = load_sample(full_filename("sounds/pop.ogg"));
    menu_select = load_sample(full_filename("sounds/pause.ogg"));
    pause_sample = load_sample(full_filename("sounds/pause.ogg"));
    secret_found_sample = load_sample(full_filename("sounds/enchant.ogg"));

    menu_select2 = load_sample(full_filename("sounds/start_game.ogg"));
    unpause_sample = load_sample(full_filename("sounds/unpause.ogg"));
    one_up_sample = load_sample(full_filename("sounds/1-up.ogg"));
    pickup_key_sample = load_sample(full_filename("sounds/pickup_key.ogg"));
    use_key_sample = load_sample(full_filename("sounds/use_key.ogg"));
    pickup_coin_sample = load_sample(full_filename("sounds/pickup_coin.ogg"));
    door_open_sample = load_sample(full_filename("sounds/door_open.ogg"));
    //door_close_sample = load_sample(full_filename("sounds/door_close.ogg"));
    door_locked_sample = load_sample(full_filename("sounds/door_locked.ogg"));
    ball_bounce_sample = load_sample(full_filename("sounds/ball_bounce.ogg"));
    //cha_ching = load_sample(full_filename("sounds/ching.ogg"));
    power_up_sample_heart = load_sample(full_filename("sounds/crappy_heart_sound.ogg"));
    //jump_sample = load_sample(full_filename("sounds/jump.ogg"));


    // fonts

    new_font = alfont_load_font(full_filename("fonts/arialbd.ttf"));

    if (new_font == NULL)
    {
       my_error_message2("Cannot load the font");
    }
    alfont_set_font_size(new_font, 18);




    // game prep

    current_world.load("levels and maps/world1.bw2");

    level_to_start = title_screen_level;

    load_level(level_to_start.c_str());
    game_state = STATE_TITLE_SCREEN;
}

void destroy_game(void)
{


    destroy_bitmap(bear1);
    destroy_bitmap(bear2);
    destroy_bitmap(bear3);
    destroy_bitmap(bear4);
    destroy_bitmap(bear_duck);
    //destroy_bitmap(bear);
    destroy_bitmap(bear_climb1);
    destroy_bitmap(bear_climb2);
    destroy_bitmap(bear_in_air);



    destroy_bitmap(bad_bear_pic1);
    destroy_bitmap(bad_bear_pic2);
    destroy_bitmap(blue_bear_pic1);
    destroy_bitmap(blue_bear_pic2);
    destroy_bitmap(blue_bear_jump_pic);
    destroy_bitmap(purple_bear_pic1);
    destroy_bitmap(purple_bear_pic2);
    destroy_bitmap(bad_bear2_pic1);
    destroy_bitmap(bad_bear2_pic2);

    destroy_jewel_shimmers();


    //destroy_bitmap(bg1);
    //destroy_bitmap(bg2);
    //destroy_bitmap(bg3);
    //destroy_bitmap(bg4);

    destroy_bitmap(congradulations);
    destroy_bitmap(paused_banner);
    destroy_bitmap(time_up);



#define ADD_ITEM(xx, yy)   destroy_bitmap( xx##_img );
#include "item_list.hpp"
#undef ADD_ITEM


    destroy_bitmap(poof);
    destroy_bitmap(time_bground);
    destroy_bitmap(life_icon);
    destroy_bitmap(stat_hearts);
    destroy_bitmap(stat_bground);
    destroy_bitmap(stat_bground_hearts);
    destroy_bitmap(clock_icon);
    destroy_bitmap(clock_dial);
    destroy_bitmap(clock_face_overlay_r);
    destroy_bitmap(clock_face_overlay_g);
    destroy_bitmap(clock_face_overlay_y);
    destroy_bitmap(no_bears);

    destroy_bitmap(ready_banner);
    destroy_bitmap(go_banner);

    //destroy_bitmap(power_up_gun);
    //destroy_bitmap(power_up_turbo_jump);

    destroy_bitmap(medal_gold);
    destroy_bitmap(medal_silver);
    destroy_bitmap(medal_bronze);

    destroy_bitmap(title_graphic);

    destroy_bitmap(title_options);
    destroy_bitmap(title_new_game);
    destroy_bitmap(title_load_game);

    destroy_bitmap(empty_level_img);


#define ADD_ROCK(x, y) destroy_sample( x##y##_sample );
#include "rock_list.hpp"
#undef ADD_ROCK


    destroy_sample(menu_move);
    destroy_sample(menu_select);
    destroy_sample(menu_select2);
    destroy_sample(pause_sample);
    destroy_sample(unpause_sample);


    int m=0;
    for (m=splat.size()-1; m>=0; m--)
    {
        destroy_sample(splat[m].sound);
        splat.pop_back();
    }



    destroy_locked_door_graphics();

    destroy_sample(one_up_sample);
    destroy_sample(pickup_key_sample);
    destroy_sample(pickup_coin_sample);
    destroy_sample(door_locked_sample);
    destroy_sample(door_open_sample);
    destroy_sample(door_close_sample);
    destroy_sample(cha_ching);
    destroy_sample(power_up_sample_heart);
    destroy_sample(jump_sample);

    alfont_destroy_font(new_font);
}







////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void draw_menus()
{

        // draw the version number
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5, SCREEN_H-text_height(font_x_small)-3+1, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5, SCREEN_H-text_height(font_x_small)-3-1, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5+1, SCREEN_H-text_height(font_x_small)-3, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5-1, SCREEN_H-text_height(font_x_small)-3, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5, SCREEN_H-text_height(font_x_small)-3, WHITE, version_number);

        // !!!!
        // !!!!
        // for some reason, don't ask me why, but this_x_var translates along
        // the y axis, and this_y_var translates along the x axis.

        int this_x_var = 110;
        int this_y_var = 220;

        //set_trans_blender(255,255,255,64);

        if (menu_number == MENU_TITLE)
        {
            if (menu_focus == 1)
            {
                draw_sprite(buffer, title_new_game, this_y_var-al_get_bitmap_width(title_new_game)/2, this_x_var);
                fblend_trans(title_load_game, buffer, this_y_var-al_get_bitmap_width(title_load_game)/2, this_x_var+al_get_bitmap_height(title_load_game) + 5, 64);
                fblend_trans(title_options, buffer, this_y_var-al_get_bitmap_width(title_options)/2, this_x_var+(al_get_bitmap_height(title_options)*2) + 10, 64);
                fblend_trans(title_exit, buffer, this_y_var-al_get_bitmap_width(title_exit)/2, this_x_var+(al_get_bitmap_height(title_exit)*3) + 15, 64);

                // the inside rect
                drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                set_trans_blender(255,255,255,hilight_transparency);
                rect(buffer, this_y_var-al_get_bitmap_width(title_new_game)/2-2, this_x_var-2, this_y_var+al_get_bitmap_width(title_new_game)/2+2, this_x_var+al_get_bitmap_height(title_new_game)+1, YELLOW);
                // the outside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_new_game)/2-3, this_x_var-3, this_y_var+al_get_bitmap_width(title_new_game)/2+3, this_x_var+al_get_bitmap_height(title_new_game)+2, YELLOW);
                solid_mode();
            }
            else if (menu_focus == 2)
            {
                fblend_trans(title_new_game, buffer, this_y_var-al_get_bitmap_width(title_new_game)/2, this_x_var, 64);
                draw_sprite(buffer, title_load_game, this_y_var-al_get_bitmap_width(title_load_game)/2, this_x_var+al_get_bitmap_height(title_load_game) + 5);
                fblend_trans(title_options, buffer, this_y_var-al_get_bitmap_width(title_options)/2, this_x_var+(al_get_bitmap_height(title_options)*2) + 10, 64);
                fblend_trans(title_exit, buffer, this_y_var-al_get_bitmap_width(title_exit)/2, this_x_var+(al_get_bitmap_height(title_exit)*3) + 15, 64);

                // top left to bottom right
                line(buffer, this_y_var-al_get_bitmap_width(title_load_game)/2-3+5, this_x_var-3+(al_get_bitmap_height(title_load_game)+5)+5, this_y_var+al_get_bitmap_width(title_load_game)/2+3-5, this_x_var+al_get_bitmap_height(title_load_game)+2+(al_get_bitmap_height(title_load_game)+5)-6, RED);
                line(buffer, this_y_var-al_get_bitmap_width(title_load_game)/2-3+5, this_x_var-3+(al_get_bitmap_height(title_load_game)+5)+6, this_y_var+al_get_bitmap_width(title_load_game)/2+3-5, this_x_var+al_get_bitmap_height(title_load_game)+2+(al_get_bitmap_height(title_load_game)+5)-5, RED);
                // bottom left to top right
                line(buffer, this_y_var+al_get_bitmap_width(title_load_game)/2+3-5, this_x_var-3+(al_get_bitmap_height(title_load_game)+5)+5, this_y_var-al_get_bitmap_width(title_load_game)/2-3+5, this_x_var+al_get_bitmap_height(title_load_game)+2+(al_get_bitmap_height(title_load_game)+5)-6, RED);
                line(buffer, this_y_var+al_get_bitmap_width(title_load_game)/2+3-5, this_x_var-3+(al_get_bitmap_height(title_load_game)+5)+6, this_y_var-al_get_bitmap_width(title_load_game)/2-3+5, this_x_var+al_get_bitmap_height(title_load_game)+2+(al_get_bitmap_height(title_load_game)+5)-5, RED);
                drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                set_trans_blender(255,255,255,hilight_transparency);
                // the inside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_load_game)/2-2, this_x_var-2+al_get_bitmap_height(title_load_game)+5, this_y_var+al_get_bitmap_width(title_load_game)/2+2, this_x_var+al_get_bitmap_height(title_load_game)+1+al_get_bitmap_height(title_load_game)+5, YELLOW);
                // the outside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_load_game)/2-3, this_x_var-3+al_get_bitmap_height(title_load_game)+5, this_y_var+al_get_bitmap_width(title_load_game)/2+3, this_x_var+al_get_bitmap_height(title_load_game)+2+al_get_bitmap_height(title_load_game)+5, YELLOW);
                solid_mode();
            }
            else if (menu_focus == 3)
            {
                fblend_trans(title_new_game, buffer, this_y_var-al_get_bitmap_width(title_new_game)/2, this_x_var, 64);
                fblend_trans(title_load_game, buffer, this_y_var-al_get_bitmap_width(title_load_game)/2, this_x_var+al_get_bitmap_height(title_load_game) + 5, 64);
                draw_sprite(buffer, title_options, this_y_var-al_get_bitmap_width(title_options)/2, this_x_var+(al_get_bitmap_height(title_options)*2) + 10);
                fblend_trans(title_exit, buffer, this_y_var-al_get_bitmap_width(title_exit)/2, this_x_var+(al_get_bitmap_height(title_exit)*3) + 15, 64);

                // !!!!!!!!!!!!
                // !!!!!!!!!!!!
                // uncomment this section when this menu option is available
                // !!!!!!!!!!!!
                //drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                //set_trans_blender(255,255,255,hilight_transparency);
                //rect(buffer, this_y_var-title_options->w/2-2, this_x_var-2+(title_options->h+5)*2, this_y_var+title_options->w/2+2, this_x_var+title_options->h+1+(title_options->h+5)*2, YELLOW);
                //rect(buffer, this_y_var-title_options->w/2-3, this_x_var-3+(title_options->h+5)*2, this_y_var+title_options->w/2+3, this_x_var+title_options->h+2+(title_options->h+5)*2, YELLOW);
                //solid_mode();
                // !!!!!!!!!!!!
                // !!!!!!!!!!!!


                // top left to bottom right
                line(buffer, this_y_var-al_get_bitmap_width(title_options)/2-3+5, this_x_var-3+(al_get_bitmap_height(title_options)+5)*2+5, this_y_var+al_get_bitmap_width(title_options)/2+3-5, this_x_var+al_get_bitmap_height(title_options)+2+(al_get_bitmap_height(title_options)+5)*2-6, RED);
                line(buffer, this_y_var-al_get_bitmap_width(title_options)/2-3+5, this_x_var-3+(al_get_bitmap_height(title_options)+5)*2+6, this_y_var+al_get_bitmap_width(title_options)/2+3-5, this_x_var+al_get_bitmap_height(title_options)+2+(al_get_bitmap_height(title_options)+5)*2-5, RED);
                // bottom left to top right
                line(buffer, this_y_var+al_get_bitmap_width(title_options)/2+3-5, this_x_var-3+(al_get_bitmap_height(title_options)+5)*2+5, this_y_var-al_get_bitmap_width(title_options)/2-3+5, this_x_var+al_get_bitmap_height(title_options)+2+(al_get_bitmap_height(title_options)+5)*2-6, RED);
                line(buffer, this_y_var+al_get_bitmap_width(title_options)/2+3-5, this_x_var-3+(al_get_bitmap_height(title_options)+5)*2+6, this_y_var-al_get_bitmap_width(title_options)/2-3+5, this_x_var+al_get_bitmap_height(title_options)+2+(al_get_bitmap_height(title_options)+5)*2-5, RED);
                drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                set_trans_blender(255,255,255,hilight_transparency);
                // the inside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_options)/2-2, this_x_var-2+(al_get_bitmap_height(title_options)+5)*2, this_y_var+al_get_bitmap_width(title_options)/2+2, this_x_var+al_get_bitmap_height(title_options)+1+(al_get_bitmap_height(title_options)+5)*2, YELLOW);
                // the outside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_options)/2-3, this_x_var-3+(al_get_bitmap_height(title_options)+5)*2, this_y_var+al_get_bitmap_width(title_options)/2+3, this_x_var+al_get_bitmap_height(title_options)+2+(al_get_bitmap_height(title_options)+5)*2, YELLOW);
                solid_mode();
            }
            else if (menu_focus == 4)
            {
                //draw_trans_sprite(buffer, title_new_game, this_y_var-title_new_game->w/2, this_x_var);
                //draw_trans_sprite(buffer, title_load_game, this_y_var-title_load_game->w/2, this_x_var+al_get_bitmap_height(title_load_game) + 5);
                //draw_sprite(buffer, title_options, this_y_var-al_get_bitmap_width(title_options)/2, this_x_var+(al_get_bitmap_height(title_options)*2) + 10);

                fblend_trans(title_new_game, buffer, this_y_var-al_get_bitmap_width(title_new_game)/2, this_x_var, 64);
                fblend_trans(title_load_game, buffer, this_y_var-al_get_bitmap_width(title_load_game)/2, this_x_var+al_get_bitmap_height(title_load_game) + 5, 64);
                fblend_trans(title_options, buffer, this_y_var-al_get_bitmap_width(title_options)/2, this_x_var+(al_get_bitmap_height(title_options)*2) + 10, 64);
                draw_sprite(buffer, title_exit, this_y_var-al_get_bitmap_width(title_exit)/2, this_x_var+(al_get_bitmap_height(title_exit)*3) + 15);

                drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                set_trans_blender(255,255,255,hilight_transparency);
               // the inside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_exit)/2-2, this_x_var-2+(al_get_bitmap_height(title_exit)+5)*3, this_y_var+al_get_bitmap_width(title_exit)/2+2, this_x_var+al_get_bitmap_height(title_exit)+1+(al_get_bitmap_height(title_exit)+5)*3, YELLOW);
                // the outside rect
                rect(buffer, this_y_var-al_get_bitmap_width(title_exit)/2-3, this_x_var-3+(al_get_bitmap_height(title_exit)+5)*3, this_y_var+al_get_bitmap_width(title_exit)/2+3, this_x_var+al_get_bitmap_height(title_exit)+2+(al_get_bitmap_height(title_exit)+5)*3, YELLOW);
                solid_mode();
            }

            write_outline_center(SCREEN_W/2, SCREEN_H-17, font_small, WHITE, COPYRIGHT_TEXT);
        }
}

// pause menu item color
ALLEGRO_COLOR pmit(int menu_focus, int this_menu_num)
{
    if (menu_focus == this_menu_num) return YELLOW;
    return WHITE;
}    

void draw_pause_menu(void)
{
        //ALFONT_FONT *f = new_font;
        
        // draw the version number
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5, SCREEN_H-text_height(font_x_small)-3+1, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5, SCREEN_H-text_height(font_x_small)-3-1, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5+1, SCREEN_H-text_height(font_x_small)-3, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5-1, SCREEN_H-text_height(font_x_small)-3, BLACK, version_number);
        textprintf(buffer, font_x_small, SCREEN_W-text_length(font_x_small, version_number)-5, SCREEN_H-text_height(font_x_small)-3, WHITE, version_number);

        int this_x_var = 115;
        int this_y_var = 220;
        

        //fblend_rect_trans(buffer, 80, 60, SCREEN_W-80*2, SCREEN_H-60*2, BLACK, 255/2);
        fblend_rect_trans(buffer, 0, 0, SCREEN_W, SCREEN_H, BLACK, 255/2);
        draw_sprite(buffer, paused_banner, (SCREEN_W/2)-(al_get_bitmap_width(paused_banner)/2), (SCREEN_H/3)-5);

        alfont_set_font_size(new_font, 12);



        int x_orient = SCREEN_W/2;
        int y_orient = SCREEN_H/3 + 30;
        
        int max_width_of_text = 170;
        
        rectfill(buffer, x_orient-max_width_of_text/2, y_orient, x_orient+max_width_of_text/2, y_orient+alfont_text_height(new_font), BLACK);
        alfont_textprintf_centre_aa(buffer, new_font, x_orient, y_orient+2, pmit(menu_focus, 1), "Back to the game");

        y_orient += (alfont_text_height(new_font)+5);
        
        rectfill(buffer, x_orient-max_width_of_text/2, y_orient, x_orient+max_width_of_text/2, y_orient+alfont_text_height(new_font), BLACK);
        alfont_textprintf_centre_aa(buffer, new_font, x_orient, y_orient+2, pmit(menu_focus, 2), "Restart this Level");

        y_orient += (alfont_text_height(new_font)+5);

        rectfill(buffer, x_orient-max_width_of_text/2, y_orient, x_orient+max_width_of_text/2, y_orient+alfont_text_height(new_font), BLACK);
        alfont_textprintf_centre_aa(buffer, new_font, x_orient, y_orient+2, pmit(menu_focus, 3), "Exit to Title Screen");
        //rectfill(buffer, (80)+9, SCREEN_H/3+30, (SCREEN_W-80)-9, SCREEN_H/3+30+alfont_text_height(new_font), BLACK);

        //rectfill(buffer, (80)+9, SCREEN_H/3+30+(alfont_text_height(new_font)+5), (SCREEN_W-80)-9, SCREEN_H/3+30+alfont_text_height(new_font), BLACK);
        //alfont_textprintf_centre_aa(buffer, new_font, SCREEN_W/2, SCREEN_H/3+30+(alfont_text_height(new_font)*2+5), WHITE, "Restart Level");

        //rectfill(buffer, (80)+9, SCREEN_H/3+30+(alfont_text_height(new_font)*2+5), (SCREEN_W-80)-9, SCREEN_H/3+30+(alfont_text_height(new_font)*3)+5, BLACK);
        //alfont_textprintf_centre_aa(buffer, new_font, SCREEN_W/2, SCREEN_H/3+30+(alfont_text_height(new_font)+5)*2, WHITE, "Exit to Title Screen");
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void change_door_graphic_to_unlocked()
{
}    
//bool release_x = true;

void check_function_behind_player(int block_behind_player)
{
    /// judgement of the block behind the player


    if ((block_behind_player > BLOCK_DOOR) && (block_behind_player < BLOCK_DOOR+1000) && button_up && release_up)
    {
       // this says: "if all 4 corners of the character's box are in the door, then go in the door.
       if ((block_type_at(player.get_left_edge_int(), player.get_top_edge_int()) == block_behind_player)
        && (block_type_at(player.get_right_edge_int(), player.get_top_edge_int()) == block_behind_player)
        && (block_type_at(player.get_left_edge_int(), player.get_bottom_edge_int()) == block_behind_player)
        && (block_type_at(player.get_right_edge_int(), player.get_bottom_edge_int()) == block_behind_player))
        {
            int door_array_num = get_door_array_from_door_num(block_behind_player);

            if (door_array_num != -1)
            {
                if (current_level.door[door_array_num].type == DOOR_TYPE_LOCKED)
                {
                    if (player.use_key() == -1)
                    {
                        // player has no keys
                        start_help_message("You need a gold key to get in this door");
                        play_locked_door_sound();
                    }
                    else    
                    {
                        // player used a key
                        current_level.door[door_array_num].type = DOOR_TYPE_UNLOCKED;
                        change_door_graphic_to_unlocked();
                        play_key_sound();
                        use_key_animation_manager.add_key(player.get_center_int(), player.get_middle_int());
                    }
                }
                else if (current_level.door[door_array_num].type == DOOR_TYPE_LOCKED_SILVER)
                {
                    if (player.use_silver_key() == -1)
                    {
                        // player has no keys
                        start_help_message("You need a silver key to get in this door");
                        play_locked_door_sound();
                    }
                    else    
                    {
                        // player used a key
                        current_level.door[door_array_num].type = DOOR_TYPE_UNLOCKED_SILVER;
                        change_door_graphic_to_unlocked();
                        play_key_sound();

                        use_key_animation_manager.add_key(player.get_center_int(), player.get_middle_int(), true);
                    }
                }
                else if (current_level.door[door_array_num].type == DOOR_TYPE_EXIT_ONLY)
                {
                    start_help_message("This door is exit only.  Try comming from the other side.");
                    play_locked_door_sound();
                }
                else if (current_level.door[door_array_num].type == DOOR_TYPE_LOCKED_SECRET)
                {
                    start_help_message("This is a secret door.  I wonder how you can get in?");
                    play_locked_door_sound();
                }
                else
                {
                    clock_time_suspended_at = ten_mili_seconds;
                    B_clock_time_suspended = true;
                    play_open_door_sound();

                    go_in_door(block_behind_player);
                    //rest(100);
                    
                    play_close_door_sound();
                    ten_mili_seconds = clock_time_suspended_at;
                    B_clock_time_suspended = false;
                }        
            }    
        }

       release_up = false;

       door_drawing_manager.update_doors(&current_level);
    }

    switch (block_behind_player)
    {
        case BLOCK_UNLOCK_CAMERA:
             camera.control(-1, -1, -1, -1, -1, -1);
             camera.camera_block_number = -1;
             break;
    }

    if ((block_behind_player >= BLOCK_CAMERA) && (block_behind_player <= BLOCK_CAMERA+(100000-1)))
    {
        camera.set_to_block(block_behind_player);
    }
}


void debug_and_edits()
{
    if (key[ALLEGRO_KEY_F4]) current_map.save("saved_map.map");
    //if (key[KEY_F5]) current_level.save("saved_level.lev");
    //if (key[KEY_F5]) save_lv2_file("saved_level.lv2");

    if (key[ALLEGRO_KEY_F1] && release_f1) {F_debug_mode=!F_debug_mode; F_map_maker_mode=false; release_f1=false;}
    else if (!key[ALLEGRO_KEY_F1]) release_f1=true;

    if (key[ALLEGRO_KEY_F2] && release_f2) {F_map_maker_mode=!F_map_maker_mode; F_debug_mode=false; release_f2=false;}
    else if (!key[ALLEGRO_KEY_F2]) release_f2=true;
}    

void update_clocks()
{
    ellapsed_time = ten_mili_seconds;
    if (!no_time_limits) { time_left_in_round = current_level.time_limit-ellapsed_time; }    
}



// this function is for testing purposes only
bool key_c_release = false;
bool key_d_release = false;
bool key_j_release = false;
void spawn_key_thing()
{
    if (key[ALLEGRO_KEY_C] && key_c_release)
    {
       use_key_animation_manager.add_key(player.get_center_int(), player.get_middle_int());
       key_c_release = false;
    }
    else if (!key[ALLEGRO_KEY_C]) key_c_release = true;

    if (key[ALLEGRO_KEY_D] && key_d_release)
    {
       use_key_animation_manager.add_key(player.get_center_int(), player.get_middle_int(), true);
       key_d_release = false;
    }
    else if (!key[ALLEGRO_KEY_D]) key_d_release = true;

    if (key[ALLEGRO_KEY_J] && key_j_release)
    {
       particle_effect_manager.add_cluster(player.get_center_int(), player.get_middle_int(), 0, 0, 20.0f, 3.0f, 10, 20, 50);
       key_j_release = false;
    }
    else if (!key[ALLEGRO_KEY_J]) key_j_release = true;

}



void do_logic(void)
{
  use_key_animation_manager.update();
  solved_door_animation_manager.update();
  if (solved_door_animation_manager.active())
  {
      camera.x = solved_door_animation_manager.get_x()-SCREEN_W/2;
      camera.y = solved_door_animation_manager.get_y()-SCREEN_H/2;
      camera.prevent_scrolling_off_map();
      camera_x = camera.x;
      camera_y = camera.y;

      particle_effect_manager.update();
  }

  if (!use_key_animation_manager.active() && !solved_door_animation_manager.active())
  {


     if (key[ALLEGRO_KEY_U]) attempt_to_turn_on_trigger(1);
     if (key[ALLEGRO_KEY_I]) attempt_to_turn_on_trigger(2);
     if (key[ALLEGRO_KEY_O]) attempt_to_turn_on_trigger(3);
     if (key[ALLEGRO_KEY_P]) attempt_to_turn_on_trigger(4);


    update_jewel_shimmer();

    test_for_solved_secret_door();


    if (key[ALLEGRO_KEY_PAD_0]) player.has_gun = true;

    if (game_state == STATE_CHOOSING_LEVEL)
    {
        figure_out_choose_level_screen_user_input();
    }

    current_map.update_backgrounds();
    update_help_message();
    test_player_power_up_collisions();
    update_picked_up_items();

    if (!F_disable_edits) debug_and_edits();

    // graphic options and toggles
    if (key[ALLEGRO_KEY_F6] && release_f6)
    {
        F_draw_backgrounds =! F_draw_backgrounds;
        if (F_draw_backgrounds) start_help_message("Background On");
        else start_help_message("Background Off");
        release_f6=false;
    }
    else if (!key[ALLEGRO_KEY_F6]) release_f6=true;



    spawn_key_thing();



    adding_coins_update();

    // gameplay

    int block_behind_player = block_type_at(player.get_center_int(), player.get_middle_int());

    if (!button_up) release_up = true;
    if (!button_a) release_a = true;
    if (!button_b) release_b = true;

    /// user control of the player during the game
    if ((game_state == STATE_IN_LEVEL) || ((game_state == STATE_FINISH_ROUND) && (finished_round_counter > 0)))
    {
        check_function_behind_player(block_behind_player);

        check_switch_behind_player();


        if (button_y)
        {
            player.run();
            if (player.has_gun && release_y)
            {
                float y_force = 0.0f;
                if (button_up) y_force = -2.0f;
                if (button_down) y_force = 2.0f;
                bullet_manager.add_bullet(player.get_center(), player.get_middle(), player.velocity.x, y_force, player.facing_right);
                play_menu_move_sound();
            }
            release_y = false;
        }
        else if (!button_y)
        {
             player.walk();
             release_y = true;
        }


             if   ((block_type_at(player.get_left_edge_int(),  player.get_top_edge_int())    == BLOCK_GOAL_1)
                || (block_type_at(player.get_right_edge_int(), player.get_top_edge_int())    == BLOCK_GOAL_1)
                || (block_type_at(player.get_left_edge_int(),  player.get_bottom_edge_int()) == BLOCK_GOAL_1)
                || (block_type_at(player.get_right_edge_int(), player.get_bottom_edge_int()) == BLOCK_GOAL_1)
                || (block_type_at(player.get_center_int(),     player.get_middle_int())      == BLOCK_GOAL_1))
             {
                 if (game_state != STATE_FINISH_ROUND)
                 {
                     game_state = STATE_FINISH_ROUND;
                     player.velocity.x = 0.0f;
                     player.velocity.y = 0.0f;
                     time_when_completed = ellapsed_time;
                     F_show_congrats_banner = true;
                     finished_round_counter = FINISHED_ROUND_DURATION;
                     total_enemies_killed = current_level.enemy.size()-num_of_enemies_left;
                 }
             }    


        //if (button_b && release_b) player.jump();

        if (button_right) player.move_right();
        if (button_left) player.move_left();
        else if (!button_right && !button_left) player.move_nowhere();

        bullet_manager.update();
        block_destruction_manager.update();
        particle_effect_manager.update();

        test_enemy_bullet_collisions();
        test_destructable_block_bullet_collision();

        if (!player.on_ladder)
        {
           if (button_b && !player.on_ladder) {player.jump();}
           else if (!button_b && !player.on_ladder) {player.release_jump();}

           if (button_down) player.duck();
           else player.stand();
        }

        if (!player.on_ladder && (button_up || button_down) && (block_behind_player == BLOCK_LADDER))
        {
           int center_of_ladder_x = ((player.get_center_int()/TILE_SIZE)*TILE_SIZE)+(TILE_SIZE/2-1);
           player.get_on_ladder(center_of_ladder_x);
        }


        if (player.on_ladder)
        {
            if (button_down)
            {
               player.velocity.y = player.max_climb_speed;
               player.velocity.x = 0.0f;
               if (player.on_ground) player.get_off_ladder();
            }
            else if (button_up)
            {
               player.velocity.y = player.max_climb_speed*(-1);
               player.velocity.x = 0.0f;
            }
            else
            {
               player.velocity.x = 0.0f;
               player.velocity.y = 0.0f;
            }

            // if the block below him isn't a ladder.
            if (block_behind_player != BLOCK_LADDER) player.get_off_ladder();

            // if the user pushes the jump button.
            if (button_b && (release_b==true)) {player.jump_off_ladder(); release_b=false;}
        }
    }/// END user control of the player during the game
    
    else if ((game_state == STATE_TITLE_SCREEN) || (game_state == STATE_CHOOSING_LEVEL))
    {
        figure_out_title_screen_user_input();
        update_hilight_transparency();
        fake_play_game();
        player.energy = player.max_energy;
    }

    if (button_x && release_x)
    {
        switch (game_state)
        {
            case STATE_IN_LEVEL:
                 play_pause_sound();
                 pre_pause_gamestate = game_state;
                 game_state = STATE_PAUSE;
                 menu_number = MENU_PAUSE;
                 menu_focus = 1;
                 clock_time_suspended_at = ten_mili_seconds;
                 B_clock_time_suspended = true;
            break;
            case STATE_PAUSE:
                 play_unpause_sound();
                 if (pre_game_counter > 0)
                 {
                     pre_pause_gamestate = game_state;
                     game_state = STATE_WAITING_FOR_LEVEL_START;
                 }
                 else
                 {
                     game_state = pre_pause_gamestate;
                     ten_mili_seconds = clock_time_suspended_at;
                     B_clock_time_suspended = false;
                 }        
            break;
            case STATE_WAITING_FOR_LEVEL_START:
                 //pre_pause_gamestate = game_state;
                 //game_state = STATE_PAUSE;
                 //menu_number = MENU_PAUSE;
                 //menu_focus = 1;
            break;
            case STATE_FINISH_ROUND:
                 play_pause_sound();
                 if (finished_round_counter <= 0)
                 {
                     pre_pause_gamestate = game_state;
                     game_state = STATE_PAUSE;
                     menu_number = MENU_PAUSE;
                     menu_focus = 1;
                 }    
            break;
        } 
           
        release_x = false;
    } // end if (button_x && release_x)
    
    
    if (!button_x) release_x = true;


    // update-clocks
    if (game_state == STATE_IN_LEVEL) update_clocks();

    if ((game_state == STATE_FINISH_ROUND) && (finished_round_counter <=0))
    {
        player.move_nowhere();
    }    

    if (player.energy <= 0)
    {
        player_lives--;
        // you lost !
        load_level(level_to_start.c_str());
    }

    if ((time_left_in_round <=0) && (game_state != STATE_TIME_UP) && (!no_time_limits))
    {
       game_state = STATE_TIME_UP;
       player_lives--;
    }

    if (player_lives < 0)
    {
       player_lives = 0;
       // game_over
    }

    test_player_enemy_collisions();
    if (player.on_ground)
    {
        if (!no_chain_awards)
        {
            if (current_chain >= 2)
            {
                chain_award = current_chain;
                chain_award_counter = 150;
                awards.add_chain(current_chain);
                //play_sample(cha_ching, 128, 128, 1000, false); //play sound effect (cash register)
            }
            current_chain = 0;
        }    
    }

    if (!F_disable_edits) {if (F_map_maker_mode) drawing_mode();}



    if (game_state != STATE_IN_LEVEL)
    {
        //player.move_nowhere();
    }

    if (game_state == STATE_WAITING_FOR_LEVEL_START)
    {
         update_stat_scroll_on();
    }

    if ((game_state != STATE_TIME_UP) && (game_state != STATE_PAUSE))
    {
        update_pre_game();

        update_award_timers();

        player.update_state();

        update_player_animation();
        update_poofs();
        if (!blood_censored)
        {
            update_blood_drops();
        }    
        update_enemy_animations();

        //keep_camera_in_map(); /// :)
        camera.update();
    }
    if (game_state == STATE_PAUSE)
    {
        figure_out_pause_screen_user_input();
    }

    if (game_state == STATE_TIME_UP)
    {
        if ((button_a && release_a) || (button_b && release_b)) { player_lives--; //reload_level();
        }
    }


    if (!no_killed_em_all)
    {
        if (killed_em_all_counter > 0) killed_em_all_counter--;
    }    


    if (game_state != STATE_PAUSE)
    {
        update_help_message();
    }    

    if (game_state == STATE_FINISH_ROUND) finished_round_counter--;
    if (finished_round_counter < 0) finished_round_counter = 0;



    for (int i=0; i<current_level.enemy.size(); i++)
    {
        if ((current_level.enemy[i].params.get_top_edge() > current_map.size.y*16) && (current_level.enemy[i].params.alive()) && (current_level.enemy[i].map_num == current_level.get_current_map_index()))
        {
            current_level.enemy[i].params.energy = 0;
            num_of_enemies_left--;
            play_random_splat_sound();
        }
    }


  }

}




void draw_item_centered(int item_type, int x, int y)
{
     ALLEGRO_BITMAP *b;

           switch (item_type)
           {

#define ADD_ITEM(xx, yy)   case xx##_const: b = xx##_img; break;
#include "item_list.hpp"
#undef ADD_ITEM

           }

           if (b)
           {
               draw_sprite(buffer, b, x-al_get_bitmap_width(b)/2, y-al_get_bitmap_height(b)/2);
           }
}









void draw_power_ups()
{
    int k=0;

    ALLEGRO_BITMAP *b;

    for (k=0; k<current_level.power_up.size(); k++)
    {
       if (current_level.power_up[k].alive && (current_level.get_current_map_index() == current_level.power_up[k].map_num))
       {
           if (is_a_jewel(current_level.power_up[k].type)) draw_jewel_centered(current_level.power_up[k].type, (int)(current_level.power_up[k].map_pos.x), (int)(current_level.power_up[k].map_pos.y));
           else
           {
               draw_item_centered(current_level.power_up[k].type, (int)(current_level.power_up[k].map_pos.x-camera.x), (int)(current_level.power_up[k].map_pos.y-camera.y));
           }
       }
    }
}


void draw_map_backgrounds()
{
    for (int k=0; k<current_map.background.size(); k++)
    {
        if (current_map.background[k].img)
        {

              draw_ms_background(buffer,
                                 current_map.background[k].img,
                                 current_map.background[k].x_offset+(int)current_map.background[k].x_disp,
                                 current_map.background[k].y_offset+(int)current_map.background[k].y_disp,
                                 current_map.background[k].scroll_rate,
                                 current_map.background[k].loop_x,
                                 current_map.background[k].loop_y
                                 );

            //draw_ms_background(buffer, bg1, 0, 0, 0.0f, true, false);

        }    
    }        
}    

#define HAPPY_YELLOW makecol(255,229,0)

//#include <stdio.h>
#include <stdlib.h>

string convoit_it(int i)
{
/*
  char buffer [33];
  scanf ("%d",&i);
  itoa (i,buffer,10);
string s = buffer;
*/
	std::stringstream ss;
	ss << i;
  return ss.str();
}

string construct_time_string(int time_in_hsec)
{
    int min = get_min(time_in_hsec);
    int sec = get_sec(time_in_hsec);
    int hsec = get_hun_sec(time_in_hsec);

    string str;

    str.append(convoit_it(min));
    str.append(":");
    if (sec < 10) str.append("0");
    str.append(convoit_it(sec));
    str.append(":");
    if (hsec < 10) str.append("0");
    str.append(convoit_it(hsec));

    return str;
}

int draw_finished_round_scores()
{
    if (game_state == STATE_FINISH_ROUND)
    {
        int left_x_pos = 180;
        int initial_y_pos = SCREEN_H/3+20;
        int right_x_pos = 200;
        
        int next_multiplier = 1;
        
        if (finished_round_counter < FINISHED_ROUND_DURATION-(FINISHED_ROUND_DURATION/8)*next_multiplier)
        {
            write_outline_right_alfont_aa(left_x_pos, initial_y_pos, new_font, 18, HAPPY_YELLOW, "Finished time:");
            _write_outline_alfont_aa(right_x_pos, initial_y_pos, new_font, 18, HAPPY_YELLOW, construct_time_string(time_when_completed).c_str());
            initial_y_pos += 20;
            next_multiplier++;
        }
        if (finished_round_counter < FINISHED_ROUND_DURATION-(FINISHED_ROUND_DURATION/8)*next_multiplier)    
        {
            write_outline_right_alfont_aa(left_x_pos, initial_y_pos, new_font, 18, HAPPY_YELLOW, "Enemies killed:");
            write_outline_alfont_aa(right_x_pos, initial_y_pos, new_font, 18, HAPPY_YELLOW, "%d/%d", total_enemies_killed, current_level.enemy.size());
            initial_y_pos += 20;
            next_multiplier++;
        }    
        if (finished_round_counter < FINISHED_ROUND_DURATION-(FINISHED_ROUND_DURATION/8)*next_multiplier)    
        {
            if (num_of_enemies_left == 0)
            {
                write_outline_right_alfont_aa(left_x_pos, initial_y_pos, new_font, 18, HAPPY_YELLOW, "Time to Kill em all:");

                _write_outline_alfont_aa(right_x_pos, initial_y_pos, new_font, 18, HAPPY_YELLOW, construct_time_string(time_to_kill_all_the_bears).c_str());
                initial_y_pos += 20;
                next_multiplier++;
            }    
        }    
        if (finished_round_counter <= 0)    
        {
            write_outline_center_alfont_aa__to_screen(SCREEN_W/2, initial_y_pos+20, new_font, 18, WHITE, "press any button to continue...");

            wait_for_press_any_button();

            current_world.load_next_level();
        }
    }    
    
    return 0;
}    

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void draw_to_buffer(void)
{

    clear_to_color(buffer, current_map.background_color);

    if (F_draw_backgrounds) draw_map_backgrounds();

    draw_map();

    draw_enemy_bears();

    draw_poofs();
    if (!blood_censored)
    {
        draw_blood_drops();
    }    

    draw_power_ups();
    
    bullet_manager.draw();
    particle_effect_manager.draw();
    use_key_animation_manager.draw();

    draw_player_bear();

    //draw_destructable_blocks();

    if (game_state != STATE_TITLE_SCREEN)
    {
        if (F_debug_mode) player.draw_bounding_box();

        draw_map_front_layer();
        block_destruction_manager.draw();
        draw_picked_up_items();

        if (!F_map_maker_mode && !F_debug_mode && (game_state != STATE_TITLE_SCREEN))
        {
            if (no_time_limits) {if (!hide_hud) draw_player_stats_aa_fblend_no_timers();}
            else draw_player_stats_aa_fblend();
           if (!no_chain_awards) draw_rewards_aa_no_flash();
           draw_banners();
           if (!no_kills_left) draw_kills_left_and_one_ups();           
        }

        draw_map_maker_and_debug_stuff();

//        abort_game= true;
//        string alleg_mes_str = "";
//        alleg_mes_str += "\n";
//        alleg_mes_str += "num: %d \n %d\n %d";
//        alleg_mes_str += "\n";
//        alleg_mes_str += "num: %d \n %d\n %d";
//        allegro_message(alleg_mes_str.c_str(),
//                          1, current_level.switch_stick[0].active, current_level.switch_stick[0].index_num,
//                          2, current_level.switch_stick[1].active, current_level.switch_stick[1].index_num);

    }
    else if (game_state == STATE_TITLE_SCREEN)
    {
        draw_map_front_layer();
        draw_sprite(buffer, title_graphic, SCREEN_W/2-al_get_bitmap_width(title_graphic)/2, 2);
        draw_menus();
    }

    draw_help_message();

    if (game_state == STATE_PAUSE)
    {
        draw_pause_menu();
    }
    
    //if (first_time_through_fade_in)
    //{
    //   highcolor_fade_in(buffer, 24);
    //   first_time_through_fade_in = false;
    //}


    if (game_state == STATE_CHOOSING_LEVEL)
    {
        fblend_rect_trans(buffer, 80, 40, SCREEN_W-160, SCREEN_H-80, BLACK, 128);
        //textprintf_centre(buffer, font_med, SCREEN_W/2, SCREEN_W/3-30-60, WHITE, "Choose a level");
        //draw_sprite(buffer, choose_a_level, SCREEN_W/2-choose_a_level->w/2, 20);
        //textprintf_centre(buffer, font_med, SCREEN_W/2, SCREEN_W/3-15-60, WHITE, "Level %d", menu_focus);
        //textprintf_centre(buffer, font_med, SCREEN_W/2, SCREEN_W/3-0 -60, YELLOW, "%s", level_list[menu_focus-1].level_name.c_str());
        alfont_set_font_size(new_font, 16);
        alfont_textprintf_centre_aa(buffer, new_font, SCREEN_W/2, SCREEN_W/3-0 -45, WHITE, level_list[menu_focus-1].level_name.c_str());
        //textprintf_centre(buffer, font_med, SCREEN_W/2, SCREEN_W/3-0 -45, YELLOW, "%s", level_list[menu_focus-1].file_name.c_str());
        draw_sprite(buffer, level_list[menu_focus-1].snapshot, SCREEN_W/2-al_get_bitmap_width(level_list[menu_focus-1].snapshot)/2, 80);
    }

    if (draw_finished_round_scores() == 0)
    {
        // get a keypress to continue on...
    }    




    //textprintf(buffer, font, 110, 50, makecol(255, 0, 0), "current_level in map: %d", current_world.current_level_index);
    //textprintf(buffer, font, 110, 65, makecol(255, 0, 0), current_world.get_current_level_filename().c_str());

}


void update_buffer(void)
{
    if (!screen_is_black)
    {
			/*
        if (page_flipping_on)
        {
				std::cout << page_flipping_on << "S";
           if (buffer == page1) buffer = page2;
           else buffer = page1;
        }
			*/

        clear_to_color(buffer, COLOR_BACKGROUND);
        draw_to_buffer();
			al_flip_display();
        //if (page_flipping_on) show_video_bitmap(buffer);
        //else blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    else
    {
			ALLEGRO_BITMAP *screen = al_get_backbuffer(al_get_current_display());
        clear_to_color(screen, BLACK);
			al_flip_display();
    }            

}


void game_loop()
{
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1/60.0);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	double time_increment = 0.0; // fractional time in hundredths of a second (10ms)
   while (!abort_game)
   {
       if(!al_is_event_queue_empty(event_queue))
       {
	 time_increment += 100.0/60.0;
	 double whole_units = floor(time_increment);
	 ten_mili_seconds += int(whole_units);
	 time_increment -= whole_units;

           //process = 0;
           do_logic();
           clear_input();
				while(!al_is_event_queue_empty(event_queue))
					al_drop_next_event(event_queue);
       }

       check_user_input();

       update_buffer();

   }

	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
   arg_string = argv[0];
   if (initialize() == 1) allegro_message("initialization failed");

   load_game();

   update_buffer();

   game_loop();

   cleanup();
   destroy_game();

   return 0;
//}END_OF_MAIN();
};

