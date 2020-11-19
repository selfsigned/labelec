NAME=main

F_CPU=16000000UL
UART_BAUDRATE=115200
MCU=atmega328p
# we want to override this if we have our own udev rule with a different name
PORT ?= /dev/ttyUSB0

CC = avr-gcc
SRC = main.c
CFLAGS ?= -std=c99 -Wall -ffunction-sections

# all : hex flash considered harmful (race condition with -j)
all:
	$(MAKE) hex
	$(MAKE) flash

$(NAME).bin: $(SRC)
	$(CC) $(CFLAGS) -I. -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DUART_BAUDRATE=$(UART_BAUDRATE) -o $(NAME).bin $(SRC)

$(NAME).hex: $(SRC)
	avr-size $(NAME).bin
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex

hex:
	$(MAKE) $(NAME).bin
	$(MAKE) $(NAME).hex

flash:
	avrdude -p $(MCU) -c arduino -P $(PORT) -b 115200  -D -U flash:w:main.hex:i

clean:
	$(RM) $(NAME).bin $(NAME).hex

screen:
	screen $(PORT) $(UART_BAUDRATE),cs8

.PHONY: all hex flash clean terminal
