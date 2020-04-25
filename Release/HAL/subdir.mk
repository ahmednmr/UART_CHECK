################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EF_7Segment.c \
../HAL/EF_E2PROM_24C16.c \
../HAL/EF_E2PROM_24C64.c \
../HAL/EF_Keypad.c \
../HAL/EF_LCD.c 

OBJS += \
./HAL/EF_7Segment.o \
./HAL/EF_E2PROM_24C16.o \
./HAL/EF_E2PROM_24C64.o \
./HAL/EF_Keypad.o \
./HAL/EF_LCD.o 

C_DEPS += \
./HAL/EF_7Segment.d \
./HAL/EF_E2PROM_24C16.d \
./HAL/EF_E2PROM_24C64.d \
./HAL/EF_Keypad.d \
./HAL/EF_LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


