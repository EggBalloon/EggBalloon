################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Complex_Drivers/Sci/Sci.c" \

C_SRCS += \
../Complex_Drivers/Sci/Sci.c \

OBJS += \
./Complex_Drivers/Sci/Sci.o \

C_DEPS += \
./Complex_Drivers/Sci/Sci.d \

OBJS_QUOTED += \
"./Complex_Drivers/Sci/Sci.o" \

C_DEPS_QUOTED += \
"./Complex_Drivers/Sci/Sci.d" \

OBJS_OS_FORMAT += \
./Complex_Drivers/Sci/Sci.o \


# Each subdirectory must supply rules for building sources it contributes
Complex_Drivers/Sci/Sci.o: ../Complex_Drivers/Sci/Sci.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Complex_Drivers/Sci/Sci.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Complex_Drivers/Sci/Sci.o"
	@echo 'Finished building: $<'
	@echo ' '


