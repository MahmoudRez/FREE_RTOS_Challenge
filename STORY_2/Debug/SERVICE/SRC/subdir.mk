################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERVICE/SRC/croutine.c \
../SERVICE/SRC/event_groups.c \
../SERVICE/SRC/heap_1.c \
../SERVICE/SRC/list.c \
../SERVICE/SRC/port.c \
../SERVICE/SRC/queue.c \
../SERVICE/SRC/stream_buffer.c \
../SERVICE/SRC/tasks.c \
../SERVICE/SRC/timers.c 

OBJS += \
./SERVICE/SRC/croutine.o \
./SERVICE/SRC/event_groups.o \
./SERVICE/SRC/heap_1.o \
./SERVICE/SRC/list.o \
./SERVICE/SRC/port.o \
./SERVICE/SRC/queue.o \
./SERVICE/SRC/stream_buffer.o \
./SERVICE/SRC/tasks.o \
./SERVICE/SRC/timers.o 

C_DEPS += \
./SERVICE/SRC/croutine.d \
./SERVICE/SRC/event_groups.d \
./SERVICE/SRC/heap_1.d \
./SERVICE/SRC/list.d \
./SERVICE/SRC/port.d \
./SERVICE/SRC/queue.d \
./SERVICE/SRC/stream_buffer.d \
./SERVICE/SRC/tasks.d \
./SERVICE/SRC/timers.d 


# Each subdirectory must supply rules for building sources it contributes
SERVICE/SRC/%.o: ../SERVICE/SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Embedded\Workspace\RTOS_Sprint2\ECUAL\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\APP\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\MCAL\INC" -I"E:\Embedded\Workspace\RTOS_Sprint2\SERVICE\INC" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


