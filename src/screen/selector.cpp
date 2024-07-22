#include "main.h"
#include "pros/apix.h"
#include "robot/auton.h"
#include "robot/drivetrain.h"

using namespace Robot;

static lv_obj_t * label;
static lv_obj_t * dlabel;



void selector_screen::auton_update(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        Autonomous::AutonSwitcher();

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, Autonomous::autonName.c_str());
    }
}


void selector_screen::drive_update(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * dbtn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        std::string name = Drivetrain::SwitchDrive();

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * dlabel = lv_obj_get_child(dbtn, 0);
        lv_label_set_text_fmt(dlabel, name.c_str());
    }
}


selector_screen::selector_screen() {}

/**
 * Create a slider and write its value on a label.
 */
void selector_screen::selector()
{
    /*Create a slider in the center of the display*/
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 30, 90);                            /*Set its position*/
    lv_obj_set_size(btn, 200, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, auton_update, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/


    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Autonomous");                     /*Set the labels text*/
    lv_obj_center(label);
    
    
    lv_obj_t * dbtn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(dbtn, 250, 90);                            /*Set its position*/
    lv_obj_set_size(dbtn, 200, 50);                          /*Set its size*/
    lv_obj_add_event_cb(dbtn, drive_update, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/


    lv_obj_t * dlabel = lv_label_create(dbtn);          /*Add a label to the button*/
    lv_label_set_text(dlabel, "Drivetrain");                     /*Set the labels text*/
    lv_obj_center(dlabel);      /*Align top of the slider*/

}
