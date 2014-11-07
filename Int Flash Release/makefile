################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 1
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Source/subdir.mk
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
$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int\ Flash\ Release/mfs_sdcard.elf \

EXECUTABLES_QUOTED += \
"$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int Flash Release/mfs_sdcard.elf" \

EXECUTABLES_OS_FORMAT += \
$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int Flash Release/mfs_sdcard.elf \


# All Target
all: warning-messages explicit-dependencies $(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int\ Flash\ Release/mfs_sdcard.elf secondary-outputs

# Tool invocations
$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int\ Flash\ Release/mfs_sdcard.elf: $(OBJS) $(USER_OBJS) $(BSP)/intflash.ld
	@echo 'Building target: $@'
	@echo 'Executing target #2 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" @"mfs_sdcard.args" -o"$(SDCARD)/build/cw10gcc/mfs_sdcard_frdmk64f/Int Flash Release/mfs_sdcard.elf"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d"  $(ProjDirPath)/Int Flash Release/mfs_sdcard.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: $(BSP)/intflash.ld 

warning-messages: 

