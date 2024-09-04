
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t *hal_init(int32_t w, int32_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int main(int argc, char **argv)
{
   (void)argc; /*Unused*/
   (void)argv; /*Unused*/

   static uint16_t angle = 0;

   /*Initialize LVGL*/
   lv_init();

   /*Initialize the HAL (display, input devices, tick) for LVGL*/
   hal_init(240, 240);

   static lv_style_t style;
   lv_style_init(&style);
   lv_style_set_bg_color(&style, lv_color_hex(0xcc182d));
   lv_style_set_radius(&style, 0);

   lv_obj_t *obj = lv_obj_create(lv_screen_active());
   lv_obj_set_size(obj, 10, 100);
   lv_obj_set_pos(obj, 120, 120);

   lv_obj_add_style(obj, &style, 0);

   while(1)
   {
      /* Periodically call the lv_task handler.
       * It could be done in a timer interrupt or an OS task too.*/
      lv_obj_set_style_transform_rotation(obj, ((angle += 2)), 0);

      lv_timer_handler();
      usleep(5 * 1000);
   }

   return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t *hal_init(int32_t w, int32_t h)
{
   lv_group_set_default(lv_group_create());

   lv_display_t *disp = lv_sdl_window_create(w, h);

   return disp;
}
