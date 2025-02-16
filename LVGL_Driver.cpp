/*****************************************************************************
  | File        :   LVGL_Driver.c
  
  | help        : 
    The provided LVGL library file must be installed first
******************************************************************************/
#include "LVGL_Driver.h"
#include "Arduino.h"

static lv_disp_draw_buf_t disp_buf;

static lv_color_t* buf1 = (lv_color_t*)heap_caps_aligned_alloc(32, ((480 * 480) * 2) / 10, MALLOC_CAP_DMA);
static lv_color_t* buf2 = (lv_color_t*)heap_caps_aligned_alloc(32, ((480 * 480) * 2) / 10, MALLOC_CAP_DMA);

void flushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    LCD_addWindow(area->x1, area->x2, area->y1, area->y2, ( uint8_t *)&color_p->full);
    lv_disp_flush_ready(disp_drv);
}

void example_increase_lvgl_tick(void *arg)
{
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

void Lvgl_Init(void)
{
  lv_init();
  lv_disp_draw_buf_init(&disp_buf, buf1, buf2, (480 * 480) / 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
  disp_drv.flush_cb = flushDisplay;        /*Set a flush callback to draw to the display*/
  disp_drv.hor_res = 480;                 /*Set the horizontal resolution in pixels*/
  disp_drv.ver_res = 480;                 /*Set the vertical resolution in pixels*/

  lv_disp_drv_register(&disp_drv);

  const esp_timer_create_args_t lvgl_tick_timer_args = {
    .callback = &example_increase_lvgl_tick,
    .name = "lvgl_tick"
  };
  esp_timer_handle_t lvgl_tick_timer = NULL;
  esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
  esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);
}
