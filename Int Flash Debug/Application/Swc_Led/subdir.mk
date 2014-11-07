################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Application/Swc_Led/Led.c" \

C_SRCS += \
../Application/Swc_Led/Led.c \

OBJS += \
./Application/Swc_Led/Led.o \

C_DEPS += \
./Application/Swc_Led/Led.d \

OBJS_QUOTED += \
"./Application/Swc_Led/Led.o" \

C_DEPS_QUOTED += \
"./Application/Swc_Led/Led.d" \

OBJS_OS_FORMAT += \
./Application/Swc_Led/Led.o \


# Each subdirectory must supply rules for building sources it contributes
Application/Swc_Led/Led.o: ../Application/Swc_Led/Led.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Application/Swc_Led/Led.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Application/Swc_Led/Led.o"
	@echo 'Finished building: $<'
	@echo ' '


