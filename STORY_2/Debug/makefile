################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SERVICE/SRC/subdir.mk
-include MCAL/SRC/subdir.mk
-include ECUAL/SRC/subdir.mk
-include APP/SRC/subdir.mk
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
RTOS_Sprint2.lss \

FLASH_IMAGE += \
RTOS_Sprint2.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: RTOS_Sprint2.elf secondary-outputs

# Tool invocations
RTOS_Sprint2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RTOS_Sprint2.map -mmcu=atmega32 -o "RTOS_Sprint2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RTOS_Sprint2.lss: RTOS_Sprint2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RTOS_Sprint2.elf  >"RTOS_Sprint2.lss"
	@echo 'Finished building: $@'
	@echo ' '

RTOS_Sprint2.hex: RTOS_Sprint2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RTOS_Sprint2.elf  "RTOS_Sprint2.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RTOS_Sprint2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 RTOS_Sprint2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RTOS_Sprint2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
