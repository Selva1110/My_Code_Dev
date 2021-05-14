CC= arm-none-eabi-gcc
MACH= cortex-m7
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0 -D__SAME70Q21__ -DDEBUG -I"../Lib" -I"../Lib/CMSIS/Include"
DEB_CFLAGS= -save-temps=obj -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0 -D__SAME70Q21__ -DDEBUG -I"../Lib" -I"../Lib/CMSIS/Include"
OBJS= Build/startup_same70q21.o Build/main.o 
LINKER_SCRIPTS= ../Device_Startup/same70q21_flash.ld ../Device_Startup/same70q21_sram.ld
DEB_OBJS= Temps/startup_same70q21.o Temps/main.o



Build/startup_same70q21.o: ../Device_Startup/startup_same70q21.c
	$(CC) $(CFLAGS) -o $@ $^

Build/main.o: .././main.c
	$(CC) $(CFLAGS) -o $@ $^
	
Temps/startup_same70q21.o: ../Device_Startup/startup_same70q21.c
	$(CC) $(DEB_CFLAGS) -o $@ $^

Temps/main.o: .././main.c
	$(CC) $(DEB_CFLAGS) -o $@ $^
	
make_Temps:
	$(shell mkdir -p Temps)
	
make_Build:
	$(shell mkdir -p Build)
	
clean:  
	rm -rf *.elf *.map ./Build ./Temps
	
all: make_Build Build.elf
	
debug: make_Temps Debug_Build.elf

Debug_Build.elf: $(DEB_OBJS) $(LINKER_SCRIPTS)
	$(CC) -o Debug_Build.elf $(DEB_OBJS) -mthumb -Wl,-Map="Debug_Build.map" -L"..\\Device_Startup" -mcpu=cortex-m7 -Tsame70q21_flash.ld

Build.elf: $(OBJS) $(LINKER_SCRIPTS)
	$(CC) -o Build.elf $(OBJS) -mthumb -Wl,-Map="Build.map" -L"..\\Device_Startup" -mcpu=cortex-m7 -Tsame70q21_flash.ld