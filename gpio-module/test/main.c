#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpio.h"
#include "app.h"

void log_app(void)
{
    char input0, input1, green_led, red_led;
    input0 = get_gpio_pin(PB_1)?'^':'_';   // _ indicates LOW and ^ indicates HIGH state
    input1 = get_gpio_pin(PB_2)?'^':'_';
    green_led = led_get_status(GREEN)?'O':'X';  // O indicates ON and X indicates OFF state
    red_led = led_get_status(RED)?'O':'X';

    printf("T:%4d I:%c%c G:%c R:%c\n", get_current_time_ms(), input0, input1, green_led, red_led);
}

bool input_app(FILE *file)
{
    int pin0, pin1;

    if(fscanf(file, "%d %d", &pin0, &pin1) != 2)
    {
        printf("\nEnd of simulated inputs\n");
        return false;
    }
    else
    {
        read_gpio_pin(0, pin0);
        read_gpio_pin(1, pin1);
    }

    return true;
}

int main(void) {

    const char *filename = "test/inputs.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        exit(1);  // Exit program with error
    }

    // Initialize GPIO, LED, Push_button
    gpio_init();
    led_init();
    push_button_init();

    // Configure LEDs and buttons
    set_led(GREEN, 0);
    set_led(RED, 500);  // Start with 1s blink interval
    set_push_button(PB_1, toggle_green_led);
    set_push_button(PB_2, change_red_blink_interval);
    // push_button_active_high_conf(PB_1, false);

    printf("GPIO Test Application\n");

    while (1) {
        if(!input_app(file))
        {
            break;
        }
        led_app();
        push_button_app();
        log_app();
        usleep(10000);  // 10ms delay to prevent Laptop hogging
    }

    fclose(file); 
    return 0;
}