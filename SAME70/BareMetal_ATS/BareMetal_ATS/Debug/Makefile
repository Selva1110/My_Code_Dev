################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Device_Startup/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Device_Startup/startup_same70q21.c \
../Device_Startup/system_same70q21.c \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Device_Startup/startup_same70q21.o \
Device_Startup/system_same70q21.o \
main.o

OBJS_AS_ARGS +=  \
Device_Startup/startup_same70q21.o \
Device_Startup/system_same70q21.o \
main.o

C_DEPS +=  \
Device_Startup/startup_same70q21.d \
Device_Startup/system_same70q21.d \
main.d

C_DEPS_AS_ARGS +=  \
Device_Startup/startup_same70q21.d \
Device_Startup/system_same70q21.d \
main.d

OUTPUT_FILE_PATH +=BareMetal_ATS.elf

OUTPUT_FILE_PATH_AS_ARGS +=BareMetal_ATS.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+=  \
../Device_Startup/same70q21_flash.ld \
../Device_Startup/same70q21_sram.ld


# AVR32/GNU C Compiler
Device_Startup/startup_same70q21.o: ../Device_Startup/startup_same70q21.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAME70Q21__ -DDEBUG  -I"A:\Atmel Studio\7.0\Packs\atmel\SAME70_DFP\2.4.166\same70a\include" -I"A:\Atmel Studio\7.0\Packs\ARM\CMSIS\5.3.0\CMSIS\Include"  -O1 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m7 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Device_Startup/system_same70q21.o: ../Device_Startup/system_same70q21.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAME70Q21__ -DDEBUG  -I"A:\Atmel Studio\7.0\Packs\atmel\SAME70_DFP\2.4.166\same70a\include" -I"A:\Atmel Studio\7.0\Packs\ARM\CMSIS\5.3.0\CMSIS\Include"  -O1 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m7 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAME70Q21__ -DDEBUG  -I"A:\Atmel Studio\7.0\Packs\atmel\SAME70_DFP\2.4.166\same70a\include" -I"A:\Atmel Studio\7.0\Packs\ARM\CMSIS\5.3.0\CMSIS\Include"  -O1 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m7 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker : 6.3.1
	$(QUOTE)A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mthumb -Wl,-Map="BareMetal_ATS.map" -Wl,--start-group -lm  -Wl,--end-group -L"..\\Device_Startup"  -Wl,--gc-sections -mcpu=cortex-m7 -Tsame70q21_flash.ld  
	@echo Finished building target: $@
	"A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O binary "BareMetal_ATS.elf" "BareMetal_ATS.bin"
	"A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "BareMetal_ATS.elf" "BareMetal_ATS.hex"
	"A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "BareMetal_ATS.elf" "BareMetal_ATS.eep" || exit 0
	"A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objdump.exe" -h -S "BareMetal_ATS.elf" > "BareMetal_ATS.lss"
	"A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "BareMetal_ATS.elf" "BareMetal_ATS.srec"
	"A:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-size.exe" "BareMetal_ATS.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "BareMetal_ATS.elf" "BareMetal_ATS.a" "BareMetal_ATS.hex" "BareMetal_ATS.bin" "BareMetal_ATS.lss" "BareMetal_ATS.eep" "BareMetal_ATS.map" "BareMetal_ATS.srec"
	