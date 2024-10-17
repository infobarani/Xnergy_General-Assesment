#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

// LED configurations
typedef enum {
    GREEN,
    RED,
    LED_MAX
} LED;

typedef enum {
    PB_1,  // toggle Green led
    PB_2,  // change RED led blink interval
    PB_MAX
} PUSH_BUTTON;

typedef enum {
    PORT_0,  
    PORT_1,
    PORT_2,
    PORT_3,
    PORT_MAX
} GPIO;

typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK
} LED_STATE;

typedef enum {
    TRIGGER_LEVEL,
    TRIGGER_EDGE
} TRIGGER_MODE;

typedef struct {
    LED_STATE state;
    bool active_high;
    uint32_t blink_interval;  // in ms
    uint32_t last_toggle;
    bool current_level;
} LED_Config;

typedef struct {
    bool active_high;
    TRIGGER_MODE trigger_mode;
    void (*callback_func)(void);
    bool last_state;
    uint32_t last_debounce;
    bool is_pressed;
} PB_Config;

// Function prototypes
void read_gpio_pin(int pin, int value);
bool get_gpio_pin(int pin);
void gpio_init(void);
uint32_t get_current_time_ms(void);
void set_gpio_pin(int pin, bool value);

#endif // GPIO_H