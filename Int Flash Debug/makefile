################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 16
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include services/OS/subdir.mk
-include services/Com_Manager/subdir.mk
-include mcal/IO_drivers/Pwm/subdir.mk
-include mcal/IO_drivers/Dio/subdir.mk
-include mcal/IO_drivers/Adc/subdir.mk
-include mcal/COM_Drivers/Spi/subdir.mk
-include ecu/IO_HW_abs/IO_Interface/subdir.mk
-include ecu/Com_HW_abs/Com_Interface/subdir.mk
-include Source/subdir.mk
-include Complex_Drivers/Sdio/subdir.mk
-include Complex_Drivers/Sci/subdir.mk
-include Application/Swc_Temp/subdir.mk
-include Application/Swc_Sd/subdir.mk
-include Application/Swc_Motor/subdir.mk
-include Application/Swc_Led/subdir.mk
-include Application/Swc_Gps/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int\ Flash\ Debug/mfs_sdcard.elf \

EXECUTABLES_QUOTED += \
"$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int Flash Debug/mfs_sdcard.elf" \

EXECUTABLES_OS_FORMAT += \
$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int Flash Debug/mfs_sdcard.elf \


# All Target
all: warning-messages explicit-dependencies $(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int\ Flash\ Debug/mfs_sdcard.elf secondary-outputs

# Tool invocations
$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int\ Flash\ Debug/mfs_sdcard.elf: $(OBJS) $(USER_OBJS) $(BSP)/intflash.ld
	@echo 'Building target: $@'
	@echo 'Executing target #17 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" @"mfs_sdcard.args" -o"$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int Flash Debug/mfs_sdcard.elf"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*/*.o" "./*/*.o" "./*/*/*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*.d" "./*/*/*/*.d"  $(ProjDirPath)/Int Flash Debug/mfs_sdcard.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: $(BSP)/intflash.ld 

warning-messages: 

