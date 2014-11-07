################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../mcal/IO_drivers/Adc/AdcTemp.c" \

C_SRCS += \
../mcal/IO_drivers/Adc/AdcTemp.c \

OBJS += \
./mcal/IO_drivers/Adc/AdcTemp.o \

C_DEPS += \
./mcal/IO_drivers/Adc/AdcTemp.d \

OBJS_QUOTED += \
"./mcal/IO_drivers/Adc/AdcTemp.o" \

C_DEPS_QUOTED += \
"./mcal/IO_drivers/Adc/AdcTemp.d" \

OBJS_OS_FORMAT += \
./mcal/IO_drivers/Adc/AdcTemp.o \


# Each subdirectory must supply rules for building sources it contributes
mcal/IO_drivers/Adc/AdcTemp.o: ../mcal/IO_drivers/Adc/AdcTemp.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"mcal/IO_drivers/Adc/AdcTemp.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"mcal/IO_drivers/Adc/AdcTemp.o"
	@echo 'Finished building: $<'
	@echo ' '


