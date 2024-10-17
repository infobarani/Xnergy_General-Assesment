#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "app.h"

static bool pin_status[PORT_MAX];
struct timeval reference_time;

// Dummy function to simulate GPIO read
void read_gpio_pin(int pin, int value) {
    pin_status[pin] = (value == 1);
}

// Get latched status of GPIO without IO access
bool get_gpio_pin(int pin){
    return pin_status[pin];
}

// Set the value to given GPIO port
void set_gpio_pin(int pin, bool value){
    pin_status[pin] = value;

    //Set the port IO in MCU code
}

// Emulate MCU systick using gettimeofday difference from refrence time at the start of code
static uint32_t get_time_diff_ms(struct timeval *t1, struct timeval *t2) {
    return (t2->tv_sec - t1->tv_sec) * 1000 + 
           (t2->tv_usec - t1->tv_usec) / 1000;
}

uint32_t get_current_time_ms(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return get_time_diff_ms(&reference_time, &current_time);
}

// In real MCU code need to hanlde port initializations
void gpio_init(void) {
    gettimeofday(&reference_time, NULL);
}
