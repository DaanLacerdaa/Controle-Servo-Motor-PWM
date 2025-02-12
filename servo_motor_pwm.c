#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 22
#define LED_RED_PIN 12

#define PWM_FREQ 50
#define CLK_DIV 125.0f
#define PWM_WRAP (1000000 / PWM_FREQ) // Período de 20ms (50Hz)

#define PWM_MIN 500   // 0 graus (500µs)
#define PWM_MAX 2400  // 180 graus (2400µs)
#define PWM_MID ((PWM_MIN + PWM_MAX) / 2) // 90 graus

int servo_slice;
int led_slice;

void setup_pwm() {
    printf("Inicializando PWM...\n");
    
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_clkdiv(servo_slice, CLK_DIV);
    pwm_set_wrap(servo_slice, PWM_WRAP);
    pwm_set_enabled(servo_slice, true);
    
    gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);
    led_slice = pwm_gpio_to_slice_num(LED_RED_PIN);
    pwm_set_wrap(led_slice, 255);
    pwm_set_enabled(led_slice, true);
}

void set_servo_position(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    
    int pulse_width = PWM_MIN + ((PWM_MAX - PWM_MIN) * angle) / 180;
    pwm_set_gpio_level(SERVO_PIN, pulse_width);
}

void update_led(int angle) {
    int brightness = (angle * 255) / 180;
    pwm_set_gpio_level(LED_RED_PIN, brightness);
}

void smooth_sweep(int start_angle, int end_angle) {
    int step = (start_angle < end_angle) ? 1 : -1;
    
    for (int angle = start_angle; angle != end_angle + step; angle += step) {
        set_servo_position(angle);
        update_led(angle);
        
        int delay = 5 + (5 * (angle < 90 ? angle : 180 - angle)) / 90;
        sleep_ms(delay);
    }
}

int main() {
    stdio_init_all();
    setup_pwm();
    
    printf("Iniciando movimentação do servo e controle do LED...\n");
    
    while (true) {
        printf("Movendo para 180 graus\n");
        set_servo_position(180);
        update_led(180);
        sleep_ms(2000);

        printf("Movendo para 90 graus\n");
        set_servo_position(90);
        update_led(90);
        sleep_ms(2000);

        printf("Movendo para 0 graus\n");
        set_servo_position(0);
        update_led(0);
        sleep_ms(2000);

        printf("Iniciando varredura suave de 0° a 180°...\n");
        smooth_sweep(0, 180);
        smooth_sweep(180, 0);
    }
}
