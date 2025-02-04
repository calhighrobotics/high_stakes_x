#include "screen/status.h"
#include "main.h"
#include "pros/apix.h"
#include "robot/drivetrain.h"

lv_obj_t* image;

Robot::status_screen::status_screen() {}

/**
 * Create a slider and write its value on a label.
 */

static void workpls() {
   LV_IMG_DECLARE(text198);
   image = lv_img_create(lv_scr_act());
   lv_img_set_src(image, &text198);
   lv_obj_set_size(image, 480, 240);
   lv_obj_align(image, LV_ALIGN_CENTER, 0, 0); 
}

void Robot::status_screen::status() {
   workpls();
}
