################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../ecu/IO_HW_abs/IO_Interface/IO_Interface.c" \

C_SRCS += \
../ecu/IO_HW_abs/IO_Interface/IO_Interface.c \

OBJS += \
./ecu/IO_HW_abs/IO_Interface/IO_Interface.o \

C_DEPS += \
./ecu/IO_HW_abs/IO_Interface/IO_Interface.d \

OBJS_QUOTED += \
"./ecu/IO_HW_abs/IO_Interface/IO_Interface.o" \

C_DEPS_QUOTED += \
"./ecu/IO_HW_abs/IO_Interface/IO_Interface.d" \

OBJS_OS_FORMAT += \
./ecu/IO_HW_abs/IO_Interface/IO_Interface.o \


# Each subdirectory must supply rules for building sources it contributes
ecu/IO_HW_abs/IO_Interface/IO_Interface.o: ../ecu/IO_HW_abs/IO_Interface/IO_Interface.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"ecu/IO_HW_abs/IO_Interface/IO_Interface.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"ecu/IO_HW_abs/IO_Interface/IO_Interface.o"
	@echo 'Finished building: $<'
	@echo ' '


