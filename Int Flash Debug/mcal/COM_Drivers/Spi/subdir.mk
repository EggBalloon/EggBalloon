################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../mcal/COM_Drivers/Spi/SpiB.c" \

C_SRCS += \
../mcal/COM_Drivers/Spi/SpiB.c \

OBJS += \
./mcal/COM_Drivers/Spi/SpiB.o \

C_DEPS += \
./mcal/COM_Drivers/Spi/SpiB.d \

OBJS_QUOTED += \
"./mcal/COM_Drivers/Spi/SpiB.o" \

C_DEPS_QUOTED += \
"./mcal/COM_Drivers/Spi/SpiB.d" \

OBJS_OS_FORMAT += \
./mcal/COM_Drivers/Spi/SpiB.o \


# Each subdirectory must supply rules for building sources it contributes
mcal/COM_Drivers/Spi/SpiB.o: ../mcal/COM_Drivers/Spi/SpiB.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"mcal/COM_Drivers/Spi/SpiB.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"mcal/COM_Drivers/Spi/SpiB.o"
	@echo 'Finished building: $<'
	@echo ' '


