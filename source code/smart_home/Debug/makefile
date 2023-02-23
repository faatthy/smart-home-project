################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMER1/subdir.mk
-include MCAL/TIMER0/subdir.mk
-include MCAL/IIC/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/TEMP_SENSOR/subdir.mk
-include HAL/SERVO_MOTOR/subdir.mk
-include HAL/RELAY/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/HC05/subdir.mk
-include HAL/EEPROM/subdir.mk
-include HAL/DIMMER_LAMP/subdir.mk
-include HAL/DC_MOTOR/subdir.mk
-include HAL/BUZZER/subdir.mk
-include HAL/BUTTON/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
smart_home.lss \

FLASH_IMAGE += \
smart_home.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: smart_home.elf secondary-outputs

# Tool invocations
smart_home.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,smart_home.map -mmcu=atmega32 -o "smart_home.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

smart_home.lss: smart_home.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S smart_home.elf  >"smart_home.lss"
	@echo 'Finished building: $@'
	@echo ' '

smart_home.hex: smart_home.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex smart_home.elf  "smart_home.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: smart_home.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 smart_home.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) smart_home.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
