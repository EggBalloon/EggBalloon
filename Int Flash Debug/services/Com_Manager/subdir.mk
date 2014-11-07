################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../services/Com_Manager/Com_manager.c" \

C_SRCS += \
../services/Com_Manager/Com_manager.c \

OBJS += \
./services/Com_Manager/Com_manager.o \

C_DEPS += \
./services/Com_Manager/Com_manager.d \

OBJS_QUOTED += \
"./services/Com_Manager/Com_manager.o" \

C_DEPS_QUOTED += \
"./services/Com_Manager/Com_manager.d" \

OBJS_OS_FORMAT += \
./services/Com_Manager/Com_manager.o \


# Each subdirectory must supply rules for building sources it contributes
services/Com_Manager/Com_manager.o: ../services/Com_Manager/Com_manager.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"services/Com_Manager/Com_manager.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"services/Com_Manager/Com_manager.o"
	@echo 'Finished building: $<'
	@echo ' '


