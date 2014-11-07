################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../mcal/IO_drivers/Pwm/Pwm.c" \

C_SRCS += \
../mcal/IO_drivers/Pwm/Pwm.c \

OBJS += \
./mcal/IO_drivers/Pwm/Pwm.o \

C_DEPS += \
./mcal/IO_drivers/Pwm/Pwm.d \

OBJS_QUOTED += \
"./mcal/IO_drivers/Pwm/Pwm.o" \

C_DEPS_QUOTED += \
"./mcal/IO_drivers/Pwm/Pwm.d" \

OBJS_OS_FORMAT += \
./mcal/IO_drivers/Pwm/Pwm.o \


# Each subdirectory must supply rules for building sources it contributes
mcal/IO_drivers/Pwm/Pwm.o: ../mcal/IO_drivers/Pwm/Pwm.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"mcal/IO_drivers/Pwm/Pwm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"mcal/IO_drivers/Pwm/Pwm.o"
	@echo 'Finished building: $<'
	@echo ' '


