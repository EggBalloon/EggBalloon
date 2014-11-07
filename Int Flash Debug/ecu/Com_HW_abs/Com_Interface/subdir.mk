################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../ecu/Com_HW_abs/Com_Interface/Com_Interface.c" \

C_SRCS += \
../ecu/Com_HW_abs/Com_Interface/Com_Interface.c \

OBJS += \
./ecu/Com_HW_abs/Com_Interface/Com_Interface.o \

C_DEPS += \
./ecu/Com_HW_abs/Com_Interface/Com_Interface.d \

OBJS_QUOTED += \
"./ecu/Com_HW_abs/Com_Interface/Com_Interface.o" \

C_DEPS_QUOTED += \
"./ecu/Com_HW_abs/Com_Interface/Com_Interface.d" \

OBJS_OS_FORMAT += \
./ecu/Com_HW_abs/Com_Interface/Com_Interface.o \


# Each subdirectory must supply rules for building sources it contributes
ecu/Com_HW_abs/Com_Interface/Com_Interface.o: ../ecu/Com_HW_abs/Com_Interface/Com_Interface.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"ecu/Com_HW_abs/Com_Interface/Com_Interface.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"ecu/Com_HW_abs/Com_Interface/Com_Interface.o"
	@echo 'Finished building: $<'
	@echo ' '


