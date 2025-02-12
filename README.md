# Controle de Servomotor por PWM

## Descrição do Projeto

Este repositório armazena a implementação de uma aplicação prática do módulo PWM (Pulse Width Modulation) utilizando o microcontrolador RP2040 da placa BitDogLab e a ferramenta Pico SDK para simular o controle do ângulo de um servomotor. A simulação foi realizada no simulador de eletrônica online Wokwi.

### Autoria

**Autor:** Danilo Pereira Lacerda

### Vídeo da Simulação

O experimento pode ser conferido no seguinte link:
[Assistir ao Vídeo](https://www.youtu.be/000000000)

---

## Componentes Utilizados

1. **Microcontrolador:** BitDogLab/Raspberry Pi Pico W
2. **Servomotor:** Motor micro servo padrão - Wokwi
3. **Simulador:** Wokwi
4. **LED RGB:** GPIO 12 (para experiência com BitDogLab)

---

## Requisitos de Desenvolvimento

### 1) Configuração do PWM na GPIO 22 (20% da nota)

Definição da frequência de PWM para aproximadamente **50Hz** (período de **20ms**):

```c
const uint16_t WRAP_PERIOD = 65535;
const float PWM_DIVISER = 38.16;

void pwm_setup()
{
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO);
    pwm_set_clkdiv(slice, PWM_DIVISER);
    pwm_set_wrap(slice, WRAP_PERIOD);
    pwm_set_gpio_level(PWM_SERVO, 0);
    pwm_set_enabled(slice, true);
}
```

### 2) Posicionar o Servo a 180º (10% da nota)

Definição do ciclo ativo do PWM para **2.400µs** (12% Duty Cycle):

```c
set_duty_cycle(0.12); // 2.400µs → 180º
sleep_ms(5000);
```

### 3) Posicionar o Servo a 90º (10% da nota)

Definição do ciclo ativo do PWM para **1.470µs** (7.35% Duty Cycle):

```c
set_duty_cycle(0.0735); // 1.470µs → 90º
sleep_ms(5000);
```

### 4) Posicionar o Servo a 0º (10% da nota)

Definição do ciclo ativo do PWM para **500µs** (2.5% Duty Cycle):

```c
set_duty_cycle(0.025); // 500µs → 0º
sleep_ms(5000);
```

### 5) Movimento Suave Entre 0º e 180º (35% da nota)

Incremento de ciclo ativo de **±5µs** com atraso de ajuste de **10ms**:

```c
for (int i = 0; i < 380; i++) {  // De 0 a 180 graus
    set_duty_cycle(0.025 + i * 0.00025);
    sleep_ms(10);
}

for (int i = 0; i < 380; i++) {  // De 180 a 0 graus
    set_duty_cycle(0.12 - i * 0.00025);
    sleep_ms(10);
}
```

### 6) Experimento com LED RGB - GPIO 12 (15% da nota)

A atividade com BitDogLab consistiu em observar o comportamento do LED RGB com a variação do PWM. O LED acende e apaga em sincronia com o ciclo ativo do PWM.

---

## Configuração e Compilação

### 1) Clone o repositório

```bash
git clone https://github.com/DaanLacerdaa/controle-servo-motor-PWM.git
cd controle-servo-motor-PWM
```

### 2) Configure o ambiente

```bash
export PICO_SDK_PATH=</caminho/para/o/pico-sdk>
```

### 3) Crie e entre no diretório de build

```bash
mkdir build && cd build
```

### 4) Execute o CMake

```bash
cmake ..
```

### 5) Compile o projeto

```bash
make
```

### 6) Carregamento no Raspberry Pi Pico

Após a compilação, conecte o **Raspberry Pi Pico** no modo **BOOTSEL** e arraste o arquivo **.uf2** gerado para o dispositivo.

---

## Uso

1. **Execute o código no simulador Wokwi**.
2. O servomotor irá realizar os movimentos conforme as especificações descritas.
3. O LED RGB demonstrará o comportamento do PWM na GPIO 12.
4. Para modificar os tempos das ações, ajuste os parâmetros no código-fonte.

---
## 👨💻 Autor

| [<img src="https://avatars.githubusercontent.com/DaanLacerdaa" width=115><br><sub>Daan Lacerda</sub>](https://github.com/DaanLacerdaa) |
|
