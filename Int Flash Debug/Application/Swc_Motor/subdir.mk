################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Application/Swc_Motor/Motor.c" \

C_SRCS += \
../Application/Swc_Motor/Motor.c \

OBJS += \
./Application/Swc_Motor/Motor.o \

C_DEPS += \
./Application/Swc_Motor/Motor.d \

OBJS_QUOTED += \
"./Application/Swc_Motor/Motor.o" \

C_DEPS_QUOTED += \
"./Application/Swc_Motor/Motor.d" \

OBJS_OS_FORMAT += \
./Application/Swc_Motor/Motor.o \


# Each subdirectory must supply rules for building sources it contributes
Application/Swc_Motor/Motor.o: ../Application/Swc_Motor/Motor.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Application/Swc_Motor/Motor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Application/Swc_Motor/Motor.o"
	@echo 'Finished building: $<'
	@echo ' '


