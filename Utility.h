#pragma once
#include "Constants.h"
#include <allegro.h> 
#include <math.h>
/**
 * @brief Utility functions related to UI of the game
 * 
 */
namespace Utility {
	/**
	 * @brief Checks if the mouse is inside a Bounding Box
	 * 
	 * @param box BoundingBox to be checked for mouse over
	 * @return int 1 if the mouse is in the bounding box and 0 if it outside
	 */
	extern int mouseInTheBoundingBox(BoundingBox box);
	/**
	 * @brief Draws a scaled version of text on the bitmap
	 * 
	 * @param bmp Bitmap where the text has to be drawn upon
	 * @param font Font that has to be used for the Text
	 * @param x X-Coordinate where text has to be placed
	 * @param y Y-Coordinate where text has to be placed
	 * @param multiplier Scale of the text
	 * @param msg Pointer to the string that has to be printed on screen
	 * @param color Color(Allegro Colors) of the text
	 * @param bg Color(Allegro Colors) of background
	 * @return BoundingBox The bounding box for the text
	 */
	extern BoundingBox textout_magnified(BITMAP* bmp, FONT* font, int x, int y, double multiplier, const char* msg, int color, int bg);
	/**
	 * @brief Draws a centered and scaled version of text on the bitmap
	 * 
	 * @param bmp Bitmap where the text has to be drawn upon
	 * @param font Font that has to be used for the Text
	 * @param x X-Coordinate where text has to be centered
	 * @param y Y-Coordinate where text has to be centered
	 * @param multiplier Scale of the text
	 * @param msg Pointer to the string that has to be printed on screen
	 * @param color Color(Allegro Colors) of the text
	 * @param bg Color(Allegro Colors) of background
	 * @return BoundingBox The bounding box for the text
	 */
	extern BoundingBox textout_centre_scaled(BITMAP* bmp, FONT* font, int x, int y, double multiplier, const char* msg, int color, int bg); 
	/**
	 * @brief Draws button on a bitmap
	 * 
	 * @param buffer Bitmap where button has to be drawn
	 * @param bitmapBg Bitmap to be used as the button background
	 * @param box Bounding box representing the position and size of the button
	 */
	extern void draw_button(BITMAP* buffer, BITMAP* bitmapBg, BoundingBox box);
	/**
	 * @brief Draws an arrow pointing left
	 * 
	 * @param buffer Bitmap where arrow has to be drawn upon
	 * @param x X-Coordinate of the arrow
	 * @param y Y-Coordinate of the arrow
	 * @param size Size of the arrow in pixels
	 * @param color Color(Allegro Colors)  of the arrow
	 * @return BoundingBox Bounding box for the arrow
	 */
	extern BoundingBox create_arrow_left(BITMAP* buffer, int x, int y, int size, int color);
	/**
	 * @brief Draws an arrow pointing right
	 * 
	 * @param buffer Bitmap where arrow has to be drawn upon
	 * @param x X-Coordinate of the arrow
	 * @param y Y-Coordinate of the arrow
	 * @param size Size of the arrow in pixels
	 * @param color Color(Allegro Colors)  of the arrow
	 * @return BoundingBox Bounding box for the arrow
	 */
	extern BoundingBox create_arrow_right(BITMAP* buffer, int x, int y, int size, int color);
	/**
	 * @brief Draws an uneditable text area on screen with a scrollbar allowing to fit long text on the screen.
	 * 
	 * @param bmp Bitmap where the text area has to be drawn
	 * @param fontForText Font to be used for the contents of the text area
	 * @param d Dialog to use for the text area
	 * @param str String that has to be written to the text area
	 * @param x X-Coordinate where text area has to be positioned
	 * @param y Y-Coordinate where text area has to be positioned
	 * @param w Width of the text area in pixels
	 * @param h Height of the text area in pixels
	 * @param color Color(Allegro Colors) to use for the text area
	 * @return DIALOG_PLAYER Pointer to Dialog player object for the created textarea 
	 */
	extern DIALOG_PLAYER* draw_wrapping_text(BITMAP* bmp, FONT* fontForText, DIALOG* d, char* str, int x, int y, int w, int h, int color);
	/**
	 * @brief Create a selectable list of elements
	 * 
	 * @param bmp Bitmap to draw the list upon
	 * @param fontForText Pointer to the font to be used for the list
	 * @param d Dialog for the creation of the list
	 * @param listGetter Getter method for the list items
	 * @param[out] selectedElem Pointer to the list of selected elements
	 * @param x X-Coordinate where list has to be positioned
	 * @param y Y-Coordinate where list has to be positioned
	 * @param w Width of the list in pixels
	 * @param h Height of the list in pixels
	 * @param color Color(Allegro Color) of the list
	 */ 
	extern void create_list(BITMAP* bmp, FONT* fontForText, DIALOG* d, void* listGetter, char* selectedElem, int x, int y, int w, int h, int color);
}