#define BUTTONS_ADDR 56//0x38
#define BUTTONS_SDA 1
#define BUTTONS_SCL 3

void Init_buttons();
void bt_softl_down();
void bt_softr_down();
void bt_left_down();
void bt_right_down();
void bt_up_down();
void bt_down_down();
void bt_ok_down();
void bt_softl_up();
void bt_softr_up();
void bt_left_up();
void bt_right_up();
void bt_up_up();
void bt_down_up();
void bt_ok_up();
void readbuttons();