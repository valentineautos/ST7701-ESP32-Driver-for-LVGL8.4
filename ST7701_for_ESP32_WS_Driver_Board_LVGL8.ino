/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include "LVGL_Driver.h"
#include <Arduino.h>

void driver_init() {
  I2C_Init();
  TCA9554PWR_Init(0x00);   
  Set_EXIO(EXIO_PIN8,Low);#
  LCD_Init();
  Lvgl_Init();
}

lv_obj_t *main_scr;
lv_obj_t *spinner;

void make_ui() {
  main_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(main_scr, lv_color_black(), 0);
  lv_scr_load(main_scr);

  spinner = lv_spinner_create(main_scr, 1000, 200);
  lv_obj_set_size(spinner, 240, 240);
  lv_obj_center(spinner);
}

void setup() {
  Serial.begin(115200);
  Serial.println("begin");

  driver_init();

  make_ui();
}

void loop() {
  lv_timer_handler();
  vTaskDelay(pdMS_TO_TICKS(5));
}
