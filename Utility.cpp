#include "Utility.h" 
#include <allegro.h>

namespace Utility { 
	int mouseInTheBoundingBox(BoundingBox box) { 

			if (mouse_x > box.x && mouse_x<(box.w + box.x) && mouse_y>box.y && mouse_y < (box.y + box.h))
				return 1;
			return 0;
	}
	BoundingBox textout_magnified(BITMAP* bmp, FONT* font, int x, int y, double multiplier, const char* msg, int color, int bg)
	{
		BoundingBox box = {};
		BITMAP * tmp;
		tmp = create_bitmap(text_length(font, msg), text_height(font));
		if (!tmp)
			return box;
		clear_to_color(tmp, makecol(255, 0, 255));
		textout_ex(tmp, font, msg, 0, 0, color, bg);

		box.x = x;
		box.y = y;
		box.w = (int)(tmp->w * multiplier);
		box.h = (int)(tmp->h * multiplier);

		masked_stretch_blit(tmp, bmp, 0, 0, tmp->w, tmp->h, box.x, box.y, box.w , box.h );
		destroy_bitmap(tmp);

		return box;
		
	}

	BoundingBox textout_centre_scaled(BITMAP* bmp, FONT* font, int x, int y, double multiplier, const char* msg, int color, int bg)
	{	
		BoundingBox box = {};
		BITMAP* tmp;
		tmp = create_bitmap(text_length(font, msg), text_height(font));
		if (!tmp)
			return box;
		clear_to_color(tmp, makecol(255, 0, 255)); 
		textout_ex(tmp, font, msg, 0, 0, color, bg);

		box.x = x - (int)(tmp->w * multiplier) / 2;
		box.y = y - (int)(tmp->h * multiplier) / 2;
		box.w = (int)(tmp->w * multiplier);
		box.h = (int)(tmp->h * multiplier);

		masked_stretch_blit(tmp, bmp, 0, 0, tmp->w, tmp->h, box.x, box.y, box.w, box.h);
		destroy_bitmap(tmp);

		return box;

	}
	
	BoundingBox create_arrow_left(BITMAP* buffer, int x, int y, int size, int color) {
		BoundingBox box = {};
		box.x = x;
		box.y = y;
		box.h = size;
		box.w = sqrt(3) * size / 2;
		triangle(buffer, box.x, box.y+size/2, box.x+box.w, box.y, box.x + box.w, box.y+box.h, color);
		return box;
	}
	BoundingBox create_arrow_right(BITMAP* buffer, int x, int y, int size, int color) {
		BoundingBox box = {};
		box.x = x;
		box.y = y;
		box.h = size;
		box.w = sqrt(3) * size / 2;
		triangle(buffer, box.x, box.y , box.x + box.w, box.y + size / 2, box.x, box.y + box.h, color);
		return box;

	}
	// this function was obtained from Kitty Cat's post in https://www.allegro.cc/forums/thread/581296 
	DIALOG_PLAYER* draw_wrapping_text(BITMAP* bmp, FONT* fontForText, DIALOG* d, char* str, int x, int y, int w, int h, int color)
	{
		FONT* fontOriginal = font;
		font = fontForText;
		

		gui_fg_color = makecol(0, 0, 0);
		gui_mg_color = makecol(128, 128, 128);
		gui_bg_color = makecol(238, 179, 119);
		set_dialog_color(d, gui_fg_color, gui_bg_color);

		d->x = x;
		d->y = y;
		d->w = w;
		d->h = h;
		d->bg = makecol(238, 179, 119);
		d->dp = (char*)(void*)str;


		BITMAP* bmpScreen = gui_get_screen();
		gui_set_screen(bmp);

		DIALOG_PLAYER* player = init_dialog(d, -1);

		if (!update_dialog(player))
		{
			shutdown_dialog(player);
			player = NULL;
		}
		gui_set_screen(bmpScreen);
		font = fontOriginal;
		return player;
	}


	void create_list(BITMAP* bmp, FONT* fontForText, DIALOG* d, void* listGetter, char* selectedElem, int x, int y, int w, int h, int color)
	{
		FONT* fontOriginal = font;
		font = fontForText;


		gui_fg_color = makecol(0, 0, 0);
		gui_mg_color = makecol(128, 128, 128);
		gui_bg_color = makecol(242, 219, 195);
		set_dialog_color(d, gui_fg_color, gui_bg_color);

		d->x = x;
		d->y = y;
		d->w = w;
		d->h = h;
		d->bg = makecol(242, 219, 195);
		d->dp = listGetter;
		d->dp2 = selectedElem;


		BITMAP* bmpScreen = gui_get_screen();
		gui_set_screen(bmp);

		DIALOG_PLAYER* player = init_dialog(d, -1);

		if (!update_dialog(player))
		{
			shutdown_dialog(player);
			player = NULL;
		}
		gui_set_screen(bmpScreen);
		font = fontOriginal;
	}

	void draw_button(BITMAP* buffer, BITMAP* bitmapBg, BoundingBox box) {

		masked_stretch_blit(bitmapBg, buffer, 0, 0, bitmapBg->w, bitmapBg->h, box.x, box.y, box.w, box.h);

	} 		

}
