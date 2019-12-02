################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Bluetooth_Nmr.lss \

FLASH_IMAGE += \
Bluetooth_Nmr.hex \

EEPROM_IMAGE += \
Bluetooth_Nmr.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Bluetooth_Nmr.elf secondary-outputs

# Tool invocations
Bluetooth_Nmr.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Bluetooth_Nmr.map -mmcu=atmega32 -o "Bluetooth_Nmr.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Bluetooth_Nmr.lss: Bluetooth_Nmr.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Bluetooth_Nmr.elf  >"Bluetooth_Nmr.lss"
	@echo 'Finished building: $@'
	@echo ' '

Bluetooth_Nmr.hex: Bluetooth_Nmr.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Bluetooth_Nmr.elf  "Bluetooth_Nmr.hex"
	@echo 'Finished building: $@'
	@echo ' '

Bluetooth_Nmr.eep: Bluetooth_Nmr.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Bluetooth_Nmr.elf  "Bluetooth_Nmr.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Bluetooth_Nmr.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Bluetooth_Nmr.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) Bluetooth_Nmr.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
