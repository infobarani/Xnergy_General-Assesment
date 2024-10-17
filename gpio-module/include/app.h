#ifndef APP_H
#define APP_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool state;
    bool active_high;
    uint32_t pin;
    uint32_t interval_ms;
    uint32_t last_toggle_time;
} led_t;

void led_init(void);
void push_button_init(void);
void led_app(void);
void push_button_app(void);
void toggle_green_led(void);
void change_red_blink_interval(void);
int set_push_button(PUSH_BUTTON push_button, void (*callback_func)(void));
void push_button_active_high_conf(int32_t button, bool active_high);
int set_led(LED led_number, uint32_t interval_ms);
bool led_get_status(int32_t index);

#endif 