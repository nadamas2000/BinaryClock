/**
 * @file BinaryClock.ino
 * @brief Implementación de un reloj binario utilizando un Arduino Nano y un módulo RTC DS3231.
 * 
 * Este programa muestra la hora en formato binario utilizando LEDs conectados a un Arduino Nano.
 * También permite el ajuste de la hora mediante botones y utiliza el LED interno para indicar errores del RTC.
 *
 * Hardware utilizado:
 * - Módulo RUIZHI - Módulo Board con Chip CH340 (Arduino Nano Clon)
 * - DollaTek Expansion Prototype Shield
 * - Módulo RTC DS3231
 * - Resistencias 220 Ohm.
 * - Transistores NPN 2N2222
 * - Botones con led para 6.3V (5V).
 *
 * Para usar el Clon de Arduino Nano es necesario instalar el driver CH340 y usar el procesador "ATmega328P (Old Bootloader)"
 * 
 * @author Nahúm Manuel Martín Vegas
 * @date 2015-01-22
 */

#include <Wire.h>
#include <RTClib.h>  // Librería para el DS3231

RTC_DS3231 rtc;  // Crear objeto RTC

// Pines para LEDs que mostrarán los segundos en binario (D2-D7)
const int secondPins[] = {2, 3, 4, 5, 6, 7};

// Pines para LEDs que mostrarán los minutos en binario (A0-A5)
const int minutePins[] = {A0, A1, A2, A3, A6, A7};

// Pines para LEDs que mostrarán las horas en binario (D8-D12)
const int hourPins[] = {8, 9, 10, 11, 12};

// Botones para ajuste de hora y minutos
const int buttonHour = 0;
const int buttonMinute = 1;

// LED interno del Arduino Nano
const int ledInternal = 13;

void setup() {
    Wire.begin();  // Iniciar I2C

    // Configurar pines de segundos como salida
    for (int pin : secondPins) pinMode(pin, OUTPUT);

    // Configurar pines de minutos como salida
    for (int pin : minutePins) pinMode(pin, OUTPUT);

    // Configurar pines de horas como salida
    for (int pin : hourPins) pinMode(pin, OUTPUT);

    // Configurar LED interno como salida
    pinMode(ledInternal, OUTPUT);

    // Configurar botones como entrada con pull-up interno
    pinMode(buttonHour, INPUT_PULLUP);
    pinMode(buttonMinute, INPUT_PULLUP);

    // Iniciar el RTC
    if (!rtc.begin()) {
        // Indicar error con el LED interno
        while (1) {
            digitalWrite(ledInternal, HIGH);
            delay(500);
            digitalWrite(ledInternal, LOW);
            delay(500);
        }
    }

    if (rtc.lostPower()) {
        // Indicar pérdida de alimentación con parpadeo rápido
        for (int i = 0; i < 10; i++) {
            digitalWrite(ledInternal, HIGH);
            delay(100);
            digitalWrite(ledInternal, LOW);
            delay(100);
        }
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Configura la hora del sistema
    }
}

void loop() {
    DateTime now = rtc.now();  // Obtener la hora actual del DS3231
    int hours = now.hour();
    int minutes = now.minute();

    // Ajuste de hora y minutos con botones
    if (digitalRead(buttonHour) == LOW) {
        hours = (hours + 1) % 24;
        rtc.adjust(DateTime(now.year(), now.month(), now.day(), hours, minutes, 0));
        digitalWrite(ledInternal, HIGH);
        delay(500); // Evita rebotes
        digitalWrite(ledInternal, LOW);
    }

    if (digitalRead(buttonMinute) == LOW) {
        minutes = (minutes + 1) % 60;
        rtc.adjust(DateTime(now.year(), now.month(), now.day(), hours, minutes, 0));
        digitalWrite(ledInternal, HIGH);
        delay(500); // Evita rebotes
        digitalWrite(ledInternal, LOW);
    }

    // Mostrar los segundos en binario en los LEDs D2-D7
    int seconds = now.second();
    for (int i = 0; i < 6; i++) {
        digitalWrite(secondPins[i], (seconds >> i) & 1);
    }

    // Mostrar los minutos en binario en los LEDs A0-A5
    for (int i = 0; i < 6; i++) {
        digitalWrite(minutePins[i], (minutes >> i) & 1);
    }

    // Mostrar las horas en binario en los LEDs D8-D12
    for (int i = 0; i < 5; i++) {
        digitalWrite(hourPins[i], (hours >> i) & 1);
    }

    delay(250);  // Refresco rápido para los LEDs binarios
}
