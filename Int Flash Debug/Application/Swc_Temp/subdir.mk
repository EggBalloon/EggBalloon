################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Application/Swc_Temp/Temp.c" \

C_SRCS += \
../Application/Swc_Temp/Temp.c \

OBJS += \
./Application/Swc_Temp/Temp.o \

C_DEPS += \
./Application/Swc_Temp/Temp.d \

OBJS_QUOTED += \
"./Application/Swc_Temp/Temp.o" \

C_DEPS_QUOTED += \
"./Application/Swc_Temp/Temp.d" \

OBJS_OS_FORMAT += \
./Application/Swc_Temp/Temp.o \


# Each subdirectory must supply rules for building sources it contributes
Application/Swc_Temp/Temp.o: ../Application/Swc_Temp/Temp.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Application/Swc_Temp/Temp.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Application/Swc_Temp/Temp.o"
	@echo 'Finished building: $<'
	@echo ' '


