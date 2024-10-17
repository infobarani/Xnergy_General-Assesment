#include "gpio.h"
#include "app.h"
#include <stdio.h>

#define DEBOUNCE_TIME_MS        50
#define DEFAULT_BLINK_INTERVAL  50

static PB_Config pb_configs[PB_MAX];
static led_t leds[LED_MAX];

void led_init(void){
    // Initialize LEDs
    for (int i = 0; i < LED_MAX; i++) {
        leds[i].state = LED_OFF;
        leds[i].active_high = false;
        leds[i].interval_ms = 0;
        leds[i].last_toggle_time = 0;
        leds[i].pin = PB_MAX + i; // Assume allocating pins after push button pins
    }
}

void push_button_init(void){
    // Initialize Push Buttons
    for (int i = 0; i < PB_MAX; i++) {
        pb_configs[i].active_high = true;
        pb_configs[i].trigger_mode = TRIGGER_LEVEL;
        pb_configs[i].callback_func = NULL;
        pb_configs[i].last_state = false;
        pb_configs[i].is_pressed = false;
        pb_configs[i].last_debounce = 0;
    }
}

// Configure push button active high/low state
void push_button_active_high_conf(int32_t button, bool active_high){
    pb_configs[button].active_high = active_high;
}

// Set the LED state with blink interval
int set_led(LED led_number, uint32_t interval_ms) {
    leds[led_number].interval_ms = interval_ms;
    leds[led_number].last_toggle_time = get_current_time_ms();
    return 0;
}

// Callback for toggle button (PB_1)
void toggle_green_led(void) {
    if (leds[GREEN].interval_ms == 0) {
        leds[GREEN].state = !leds[GREEN].state;
        printf("\t\t-> Green LED is %s\n", leds[GREEN].state ? "ON" : "OFF");
    }
}

// Callback for blinking interval change button (PB_2)
void change_red_blink_interval(void) {
    static uint32_t intervals[] = {500, 1000, 2000};
    static int index = 0;

    index = (index + 1) % 3;
    set_led(RED, intervals[index]);
    printf("\t\t-> Red LED blink interval set to %d ms\n", intervals[index]);
}

bool led_get_status(int32_t index)
{
    return leds[index].state;
}

// LED application logic (non-blocking)
void led_app(void) {
    uint32_t current_time = get_current_time_ms();

    for (int i = 0; i < LED_MAX; i++) {
        if (leds[i].interval_ms > 0 && (current_time - leds[i].last_toggle_time) >= leds[i].interval_ms) {
            leds[i].state = !leds[i].state;  // Toggle the LED
            leds[i].last_toggle_time = current_time;
        }

        // Sync logical LED states to port output via GPIO driver
        bool port_value = leds[i].active_high ? leds[i].state : !leds[i].state;
        set_gpio_pin(leds[i].pin, port_value);
    }
}

int set_push_button(PUSH_BUTTON push_button, void (*callback_func)(void)) {
    if (push_button >= PB_MAX || callback_func == NULL) {
        return -1;
    }

    pb_configs[push_button].callback_func = callback_func;
    return 0;
}

void push_button_app(void) {
    uint32_t current_time = get_current_time_ms();

    for (int i = 0; i < PB_MAX; i++) {
        bool current_state = get_gpio_pin(i);
        bool triggered = false;

        if (current_state != pb_configs[i].last_state){
           if ((current_time - pb_configs[i].last_debounce) >= DEBOUNCE_TIME_MS){
                if (pb_configs[i].trigger_mode == TRIGGER_LEVEL){
                    triggered = (current_state == pb_configs[i].active_high);
                }
                else{
                    if (!pb_configs[i].is_pressed && 
                        (current_state == pb_configs[i].active_high) && 
                        (current_state != pb_configs[i].last_state)) {
                        triggered = true;
                        pb_configs[i].is_pressed = true;
                    } else if (current_state != pb_configs[i].active_high) {
                        pb_configs[i].is_pressed = false;
                    }
                }
                pb_configs[i].last_state = current_state;                
                pb_configs[i].last_debounce = current_time;
           }
        }
        else{
            pb_configs[i].last_debounce = current_time;
        }

        // Execute callback if triggered
        if (triggered && pb_configs[i].callback_func != NULL) {
            pb_configs[i].callback_func();
            printf("\t<- Push Button %d callback called!\n", i);
        }
    }
}
