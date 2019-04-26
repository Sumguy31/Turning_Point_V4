#include "main.h"

lv_obj_t *label;
lv_obj_t *lab;

static lv_obj_t * s;
int autonNumber = 0;
static  lv_res_t btn_rel_action(lv_obj_t * btn);
static  lv_res_t ddlist_action(lv_obj_t * ddlist);
static std::string autons[] = {"None","RedFront","Redback","BlueFront","BlueBack"};
  lv_theme_t * th = lv_theme_alien_init(210, NULL);

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

static  lv_res_t btn_rel_action(lv_obj_t * btn)
{
  int x = lv_obj_get_free_num(btn);
    autonNumber = x;
    std::string text = ("Autons " + autons[(int)autonNumber]);
    const char* c = text.c_str();
    lv_label_set_text(lab, c);
    lv_obj_set_x(lab, 50);

    return LV_RES_OK;
}

static  lv_res_t ddlist_action(lv_obj_t * ddlist)
{

  return LV_RES_OK;
}

void chooseAuton(){
  lv_theme_set_current(th);
  s = lv_page_create(NULL, NULL);
  lv_scr_load(s);

  lab = lv_label_create(s, NULL);

  std::string text = ("Autons " + autons[(int)autonNumber]);
  const char* c = text.c_str();
  lv_label_set_text(lab, c);
  lv_obj_set_x(lab, 10);

  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  label = lv_label_create(btn1,NULL);
  lv_label_set_text(label, "RedFront");
  lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_obj_set_height(btn1, 50);

  lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);
  label = lv_label_create(btn2, NULL);
  lv_label_set_text(label, "RedBack");
  lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), btn1);
  label = lv_label_create(btn3, NULL);
  lv_label_set_text(label, "BlueFront");
  lv_obj_align(btn3, btn1, LV_ALIGN_OUT_RIGHT_MID, 50, 0);

  lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), btn2);
  label = lv_label_create(btn4, NULL);
  lv_label_set_text(label, "BlueBack");
  lv_obj_align(btn4, btn2, LV_ALIGN_OUT_RIGHT_MID, 50, 0);

  lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), NULL);
  label = lv_label_create(btn5,NULL);
  lv_label_set_text(label, "NONE");
  lv_obj_align(btn5, btn3, LV_ALIGN_OUT_RIGHT_MID, 50, 20);//originally 40
  lv_obj_set_height(btn5, 50);
  lv_obj_set_width(btn5, 50);

  lv_obj_t * btn6 = lv_btn_create(lv_scr_act(), NULL);
  label = lv_label_create(btn6, NULL);
  lv_label_set_text(label, "Park");
  lv_obj_align(btn6, btn4, LV_ALIGN_OUT_RIGHT_MID, 50, 20);
  lv_obj_set_height(btn6, 50);
  lv_obj_set_width(btn6, 50);

  static lv_style_t style_rel;
  lv_style_copy(&style_rel, &lv_style_pretty);
  style_rel.body.main_color = LV_COLOR_RED;
  style_rel.body.grad_color = LV_COLOR_MARRON;
  style_rel.body.border.color = LV_COLOR_BLACK;
  style_rel.body.shadow.color = LV_COLOR_RED;
  style_rel.body.shadow.width = 0;

    lv_btn_set_style(btn1, LV_BTN_STYLE_REL, &style_rel);
    lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &style_rel);

  static lv_style_t style_pr;

  lv_style_copy(&style_pr,  &lv_style_pretty);
  style_pr.body.main_color = LV_COLOR_NAVY;
  style_pr.body.grad_color = LV_COLOR_AQUA;
  style_pr.body.border.color = LV_COLOR_BLACK;
  style_pr.body.shadow.color = LV_COLOR_AQUA;
  style_pr.body.shadow.width = 0;

  static lv_style_t style_ded;

  lv_style_copy(&style_ded,  &lv_style_pretty);
  style_ded.body.main_color = LV_COLOR_WHITE;
  style_ded.body.grad_color = LV_COLOR_GRAY;
  style_ded.body.border.color = LV_COLOR_BLACK;
  style_ded.body.shadow.color = LV_COLOR_BLACK;
  style_ded.body.shadow.width = 0;
        /*Copy a built-in style as a starting point*/

  lv_btn_set_style(btn3, LV_BTN_STYLE_REL, &style_pr);
  lv_btn_set_style(btn4, LV_BTN_STYLE_REL, &style_pr);
  lv_btn_set_style(btn5, LV_BTN_STYLE_REL, &style_ded);
  lv_btn_set_style(btn6, LV_BTN_STYLE_REL, &style_ded);


  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_rel_action);
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_rel_action);
  lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_rel_action);
  lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_rel_action);
  lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn_rel_action);
  lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn_rel_action);

   lv_obj_set_free_num(btn1, 1);
   lv_obj_set_free_num(btn2, 2);
   lv_obj_set_free_num(btn3, 3);
   lv_obj_set_free_num(btn4, 4);
   lv_obj_set_free_num(btn5, 0);
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	yaw.reset();
	pitch.reset();
	//pros::lcd::initialize();
	void lvgl_init(void);
	pros::delay(1000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	chooseAuton();
}
