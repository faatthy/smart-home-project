################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/TEMP_SENSOR/TEMP_SENSOR_prog.c 

OBJS += \
./HAL/TEMP_SENSOR/TEMP_SENSOR_prog.o 

C_DEPS += \
./HAL/TEMP_SENSOR/TEMP_SENSOR_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/TEMP_SENSOR/%.o: ../HAL/TEMP_SENSOR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


