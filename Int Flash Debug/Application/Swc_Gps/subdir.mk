################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Application/Swc_Gps/Gps.c" \

C_SRCS += \
../Application/Swc_Gps/Gps.c \

OBJS += \
./Application/Swc_Gps/Gps.o \

C_DEPS += \
./Application/Swc_Gps/Gps.d \

OBJS_QUOTED += \
"./Application/Swc_Gps/Gps.o" \

C_DEPS_QUOTED += \
"./Application/Swc_Gps/Gps.d" \

OBJS_OS_FORMAT += \
./Application/Swc_Gps/Gps.o \


# Each subdirectory must supply rules for building sources it contributes
Application/Swc_Gps/Gps.o: ../Application/Swc_Gps/Gps.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Application/Swc_Gps/Gps.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Application/Swc_Gps/Gps.o"
	@echo 'Finished building: $<'
	@echo ' '


