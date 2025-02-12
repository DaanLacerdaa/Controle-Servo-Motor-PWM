#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 22
#define LED_RED_PIN 12

int servo_slice;
int led_slice;

void setup_pwm() {
    printf("Inicializando PWM...\n");
    
    // Configurar o pino do servo para PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_clkdiv(servo_slice, 125.0f); // Ajusta para 50Hz
    pwm_set_wrap(servo_slice, 2500); // Corrigido para 50Hz com clkdiv de 125
    pwm_set_enabled(servo_slice, true);
    printf("Servo configurado no slice %d\n", servo_slice);
    
    // Configurar o LED para PWM
    gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);
    led_slice = pwm_gpio_to_slice_num(LED_RED_PIN);
    pwm_set_wrap(led_slice, 255); // PWM de 8 bits para controle de brilho
    pwm_set_enabled(led_slice, true);
    printf("LED configurado no slice %d\n", led_slice);
}

void set_servo_position(int angle) {
    int pulse_width = 500 + (angle * (2400 - 500)) / 180; // Ajustado corretamente
    pwm_set_gpio_level(SERVO_PIN, pulse_width);
}

void update_led(int angle) {
    int brightness = (angle * 255) / 180; // Mapeia 0°-180° para 0-255
    pwm_set_gpio_level(LED_RED_PIN, brightness);
}

int main() {
    stdio_init_all();
    setup_pwm();
    
    printf("Iniciando movimentação do servo e controle do LED...\n");
    
    while (true) {
        // Posição máxima (180 graus)
        printf("Movendo para 180 graus\n");
        set_servo_position(180);
        update_led(180);
        sleep_ms(5000);

        // Posição intermediária (90 graus)
        printf("Movendo para 90 graus\n");
        set_servo_position(90);
        update_led(90);
        sleep_ms(5000);

        // Posição mínima (0 graus)
        printf("Movendo para 0 graus\n");
        set_servo_position(0);
        update_led(0);
        sleep_ms(5000);

        // Movimentação suave de 0 a 180 graus e de volta
        printf("Iniciando varredura suave de 0° a 180°...\n");
        for (int angle = 0; angle <= 180; angle += 5) {
            set_servo_position(angle);
            update_led(angle);
            sleep_ms(20); 
        }
        for (int angle = 180; angle >= 0; angle -= 5) {
            set_servo_position(angle);
            update_led(angle);
            sleep_ms(20);
        }
    }
}
