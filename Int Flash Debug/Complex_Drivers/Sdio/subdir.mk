################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Complex_Drivers/Sdio/Sdio.c" \

C_SRCS += \
../Complex_Drivers/Sdio/Sdio.c \

OBJS += \
./Complex_Drivers/Sdio/Sdio.o \

C_DEPS += \
./Complex_Drivers/Sdio/Sdio.d \

OBJS_QUOTED += \
"./Complex_Drivers/Sdio/Sdio.o" \

C_DEPS_QUOTED += \
"./Complex_Drivers/Sdio/Sdio.d" \

OBJS_OS_FORMAT += \
./Complex_Drivers/Sdio/Sdio.o \


# Each subdirectory must supply rules for building sources it contributes
Complex_Drivers/Sdio/Sdio.o: ../Complex_Drivers/Sdio/Sdio.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Complex_Drivers/Sdio/Sdio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Complex_Drivers/Sdio/Sdio.o"
	@echo 'Finished building: $<'
	@echo ' '


