################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(SDCARD)/demo.c" \

C_SRCS += \
$(SDCARD)/demo.c \

OBJS += \
./Source/demo.o \

C_DEPS += \
./Source/demo.d \

OBJS_QUOTED += \
"./Source/demo.o" \

C_DEPS_QUOTED += \
"./Source/demo.d" \

OBJS_OS_FORMAT += \
./Source/demo.o \


# Each subdirectory must supply rules for building sources it contributes
Source/demo.o: $(SDCARD)/demo.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Source/demo.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Source/demo.o"
	@echo 'Finished building: $<'
	@echo ' '


