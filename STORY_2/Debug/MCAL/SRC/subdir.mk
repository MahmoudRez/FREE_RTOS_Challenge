################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SRC/DIO.c \
../MCAL/SRC/DIO_conf.c 

OBJS += \
./MCAL/SRC/DIO.o \
./MCAL/SRC/DIO_conf.o 

C_DEPS += \
./MCAL/SRC/DIO.d \
./MCAL/SRC/DIO_conf.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SRC/%.o: ../MCAL/SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Embedded\Workspace\RTOS_Sprint2\ECUAL\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\APP\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\MCAL\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\SERVICE\INC" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


