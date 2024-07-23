#include "main.h"
#include "pros/apix.h"
#include "robot/auton.h"
#include "robot/drivetrain.h"

using namespace Robot;


/**
 * @brief function to update the autonomous routine based on the updates made to
* the dropdown list and skills switch in the UI (See auton_ui_update)
*/
void auton_state_update(lv_event_code_t code, lv_obj_t * dropdown, lv_obj_t * label, lv_obj_t * skillSwitch, lv_obj_t * autonSwitch) {
    // Checks if the dropdown list has been updated, and updates the autonomous routine
    if(code == LV_EVENT_VALUE_CHANGED) {
         char * opt = new char[15];
         std::string auton;
         lv_dropdown_get_selected_str(dropdown, opt, 15);

        if (lv_obj_has_state(skillSwitch, LV_STATE_CHECKED)) {
            Autonomous::AutonSwitcher(5);
        }
        else {
            if(strcmp(opt, "Red Left") == 0) {
                Autonomous::AutonSwitcher(1);
            }
            else if(strcmp(opt, "Red Right") == 0) {
                Autonomous::AutonSwitcher(2);
            }
            else if(strcmp(opt, "Blue Left") == 0) {
                Autonomous::AutonSwitcher(3);
            }
            else if(strcmp(opt, "Blue Right") == 0) {
                Autonomous::AutonSwitcher(4);
            }
            else {
            }
        }
        lv_label_set_text_fmt(label, "Current Auton: %s", Autonomous::autonName.c_str());
    }

}


/**
 * @brief Updates the user interface for autonomous selection.
 *
 * This function is responsible for updating the content of the dropdown list based on the alliance color.
 * It also handles the state of the skill switch and updates the autonomous routine accordingly.
 *
 * @param e Pointer to the event object.
 */
static void auton_ui_update(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * tab1 = lv_event_get_current_target(e);
    lv_obj_t * auton_dd = lv_obj_get_child(tab1, -1);
    lv_obj_t * skillSwitch = lv_obj_get_child(tab1, -2);
    lv_obj_t * autonSwitch = lv_obj_get_child(tab1, -3);
    lv_obj_t * autonLabel = lv_obj_get_child(tab1, -4);

    /* Updates content of the dropdown list based on the alliance color, using
    * the state of the alliance color switch, which is detected through "bubbling"
    */
    if (code == LV_EVENT_VALUE_CHANGED) {
        if(lv_obj_has_state(autonSwitch, LV_STATE_CHECKED)) {
            lv_dropdown_clear_options(auton_dd);
            lv_dropdown_add_option(auton_dd, "Blue Left",0);
            lv_dropdown_add_option(auton_dd, "Blue Right",1);
            lv_obj_set_style_border_color(auton_dd, lv_color_hex(0x0077c8), 0);
        }
        else {
            lv_dropdown_clear_options(auton_dd);
            lv_dropdown_add_option(auton_dd, "Red Left",0);
            lv_dropdown_add_option(auton_dd, "Red Right",1);
            lv_obj_set_style_border_color(auton_dd, lv_color_hex(0xd22730), 0);
        }
    }

    if (lv_obj_has_state(skillSwitch, LV_STATE_CHECKED)) {
        lv_obj_add_state(autonSwitch, LV_STATE_DISABLED);
        lv_obj_add_state(auton_dd, LV_STATE_DISABLED);
        lv_obj_set_style_border_color(auton_dd, lv_color_hex(0x7a7a7a), 0);
    }
    else {
        lv_obj_clear_state(autonSwitch, LV_STATE_DISABLED);
        lv_obj_clear_state(auton_dd, LV_STATE_DISABLED);
    }

    auton_state_update(code, auton_dd, autonLabel, skillSwitch, autonSwitch);
    //Updates the Autonomous routine based on the dropdown list and skills

}


/**
 * @brief Updates the drive mode based on the selected option in the drive roller.
 * 
 * This function is called when the value of the drive roller is changed. It retrieves the selected option
 * from the drive roller and updates the drive mode accordingly. The updated drive mode is then displayed
 * on the drive label.
 * 
 * @param e The event object associated with the drive roller.
 */
static void drive_update(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * tab1 = lv_event_get_current_target(e);
    lv_obj_t * drive_roller = lv_obj_get_child(tab1, -1);
    lv_obj_t * driveLabel = lv_obj_get_child(tab1, -2);

    if (code == LV_EVENT_VALUE_CHANGED) {
        std::string driveMode;
        char * opt = new char[18];
        lv_roller_get_selected_str(drive_roller, opt, 18);
        if(strcmp(opt, "Curvature Drive") == 0) {
            driveMode = Drivetrain::SwitchDrive(0);
        }
        else if(strcmp(opt, "Arcade Drive") == 0) {
            driveMode = Drivetrain::SwitchDrive(1);
        }
        else if(strcmp(opt, "Tank Drive") == 0) {
            driveMode = Drivetrain::SwitchDrive(2);
        }
        else {
            driveMode = "error";
        }
        lv_label_set_text_fmt(driveLabel, "Current drive mode: %s", driveMode.c_str());
    
    }
}

selector_screen::selector_screen() {}

/**
 * @brief Function to create and initialize the selector screen.
 * 
 * This function creates a tab view object and adds two tabs to it: "Autonomous select" and "Drive select".
 * It also adds event callbacks to the tabs for updating the UI.
 * The function creates labels, switches, and a dropdown list for selecting alliance
 * color, skills, and autonomous mode.
 * It also creates a label and a roller for selecting the current drive mode.
 */
void selector_screen::selector()
{
      /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 45);

    static lv_style_t header_style;
    lv_style_init(&header_style);
    lv_style_set_text_font(&header_style, &lv_font_montserrat_16);
    lv_obj_add_style(tabview, &header_style, 0);
    /*Add 2 tabs*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Autonomous select");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Drive select");

    

    /*
    * Both switches are "bubbled" to the tab view. This means that any event on 
    * the switches will be updated to the tab view.
    */
    lv_obj_add_event_cb(tab1, auton_ui_update, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(tab2, drive_update, LV_EVENT_VALUE_CHANGED, NULL);

    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_montserrat_18);

    lv_obj_t * label1 = lv_label_create(tab1);
    lv_obj_t * label2 = lv_label_create(tab1);
    lv_obj_t * autonName = lv_label_create(tab1);
    lv_label_set_text_fmt(label1, "Alliance Color:", 20);
    lv_label_set_text_fmt(label2, "Skills Auton:", 20);
    lv_label_set_text_fmt(autonName, "Current Auton:", 25);
    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 60, 25);
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 60, 0);
    lv_obj_align(autonName, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_style(label1, &label_style, 0);
    lv_obj_add_style(label2, &label_style, 0);
    lv_obj_add_style(autonName, &label_style, 0);

    // /*Create a normal drop down list*/



    /*Add alliance color switch*/
    lv_obj_t * matchSwitch = lv_switch_create(tab1);
    lv_obj_add_flag(matchSwitch, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_style_bg_color(matchSwitch, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
    lv_obj_set_size(matchSwitch, 50, 30);
    lv_obj_set_style_pad_all(matchSwitch, -5, LV_PART_KNOB);
    lv_obj_align(matchSwitch, LV_ALIGN_TOP_MID, 0, 20);

    /*Add skills switch*/
    lv_obj_t * skillSwitch = lv_switch_create(tab1);
    lv_obj_add_flag(skillSwitch, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_size(skillSwitch, 50, 30);
    lv_obj_set_style_pad_all(skillSwitch, -5, LV_PART_KNOB);
    lv_obj_align(skillSwitch, LV_ALIGN_CENTER, 0, 0);

    /*Create a drop down list for available */
    lv_obj_t * auton_dd = lv_dropdown_create(tab1);
    lv_obj_add_flag(auton_dd, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_dropdown_set_options(auton_dd, "Red Left\nRed Right");
    lv_obj_set_style_max_height(auton_dd, 50, LV_PART_MAIN);
    lv_obj_set_size(auton_dd, lv_pct(35), lv_pct(35));
    lv_obj_set_style_pad_top(auton_dd, 15, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(auton_dd, 15, LV_PART_MAIN);
    lv_obj_set_style_border_width(auton_dd, 4, 0);
    lv_obj_set_style_border_color(auton_dd, lv_color_hex(0xd22730), 0);
    lv_obj_align(auton_dd, LV_ALIGN_TOP_RIGHT, 0, 5);

    // Drive select tab
    lv_obj_t * driveName = lv_label_create(tab2);
    lv_label_set_text_fmt(driveName, "Current drive mode:", 25);
    lv_obj_align(driveName, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_style(driveName, &label_style, 0);

    // Style for the highlighted roller option
    static lv_style_t roller_style;
    lv_style_init(&roller_style);
    lv_style_set_bg_color(&roller_style, lv_color_hex(0xf97e2c));
    lv_style_set_text_font(&roller_style, &lv_font_montserrat_24);

    // Style for the non-highlighted roller options

    lv_obj_t * drive_roller = lv_roller_create(tab2);
    lv_obj_add_flag(drive_roller, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_roller_set_options(drive_roller, "Curvature Drive\nArcade Drive\nTank Drive", LV_ROLLER_MODE_INFINITE);
    // Changed when highlighted
    lv_obj_add_style(drive_roller, &roller_style, LV_PART_SELECTED);
    lv_roller_set_visible_row_count(drive_roller, 3);
    lv_obj_center(drive_roller);
    lv_obj_align(drive_roller, LV_ALIGN_TOP_MID, 0, 0);
    
}




