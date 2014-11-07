################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../services/OS/Os.c" \

C_SRCS += \
../services/OS/Os.c \

OBJS += \
./services/OS/Os.o \

C_DEPS += \
./services/OS/Os.d \

OBJS_QUOTED += \
"./services/OS/Os.o" \

C_DEPS_QUOTED += \
"./services/OS/Os.d" \

OBJS_OS_FORMAT += \
./services/OS/Os.o \


# Each subdirectory must supply rules for building sources it contributes
services/OS/Os.o: ../services/OS/Os.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"services/OS/Os.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"services/OS/Os.o"
	@echo 'Finished building: $<'
	@echo ' '


