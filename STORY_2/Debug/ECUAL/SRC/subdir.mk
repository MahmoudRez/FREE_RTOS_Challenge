################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/SRC/INFO_LCD.c \
../ECUAL/SRC/LED.c 

OBJS += \
./ECUAL/SRC/INFO_LCD.o \
./ECUAL/SRC/LED.o 

C_DEPS += \
./ECUAL/SRC/INFO_LCD.d \
./ECUAL/SRC/LED.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/SRC/%.o: ../ECUAL/SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Embedded\Workspace\RTOS_Sprint2\ECUAL\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\APP\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\MCAL\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\SERVICE\INC" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


