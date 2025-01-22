# BinaryClock

Este proyecto implementa un reloj binario utilizando un **Arduino Nano** y un **módulo RTC DS3231**. Muestra la hora en formato binario utilizando LEDs conectados al microcontrolador y permite ajustar la hora con botones.

## Características
- Usa un **Arduino Nano** (Clon con chip CH340)
- Utiliza un **módulo RTC DS3231** para mantener la hora
- Representa la hora, los minutos y los segundos en **binario** con LEDs
- Ajuste manual de hora y minutos con botones
- Indicador de errores y estado mediante el **LED interno**

## Hardware Utilizado
- **Arduino Nano (clon con chip CH340)**
- **Módulo RTC DS3231**
- **DollaTek Expansion Prototype Shield**
- **Resistencias de 220 Ohm**
- **Transistores NPN 2N2222**
- **Botones con LED para 6.3V (5V)**

### Pines de Conexión
- **LEDs de segundos:** D2 - D7
- **LEDs de minutos:** A0 - A5
- **LEDs de horas:** D8 - D12
- **Botón de ajuste de horas:** D0
- **Botón de ajuste de minutos:** D1
- **LED interno de estado:** D13

## Instalación y Uso
1. **Instalar el driver CH340** si usas un clon de Arduino Nano
2. En el IDE de Arduino, seleccionar el procesador **"ATmega328P (Old Bootloader)"**
3. Cargar el código **BinaryClock.ino** al Arduino
4. Conectar los LEDs y botones según la configuración de pines

## Funcionamiento
- **Ajuste de Hora:** Presionar el botón de horas para incrementar la hora
- **Ajuste de Minutos:** Presionar el botón de minutos para incrementar los minutos
- **Visualización en LEDs:**
  - Se muestra la hora, minutos y segundos en binario con los LEDs
- **Indicador de Errores:**
  - Si hay error en el RTC, el LED interno parpadea continuamente
  - Si el RTC ha perdido alimentación, el LED interno parpadea rápido

## Licencia
Este proyecto es de código abierto y puedes modificarlo y distribuirlo libremente.

## Note for English speakers
If you need to translate this content into English, you can use a **LLM (Large Language Model)** to do it easily.

---
*Autor: Nahúm Manuel Martín Vegas*

