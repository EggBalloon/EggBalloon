################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Application/Swc_Sd/Sd.c" \

C_SRCS += \
../Application/Swc_Sd/Sd.c \

OBJS += \
./Application/Swc_Sd/Sd.o \

C_DEPS += \
./Application/Swc_Sd/Sd.d \

OBJS_QUOTED += \
"./Application/Swc_Sd/Sd.o" \

C_DEPS_QUOTED += \
"./Application/Swc_Sd/Sd.d" \

OBJS_OS_FORMAT += \
./Application/Swc_Sd/Sd.o \


# Each subdirectory must supply rules for building sources it contributes
Application/Swc_Sd/Sd.o: ../Application/Swc_Sd/Sd.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Application/Swc_Sd/Sd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Application/Swc_Sd/Sd.o"
	@echo 'Finished building: $<'
	@echo ' '


