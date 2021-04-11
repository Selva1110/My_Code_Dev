CC= arm-none-eabi-gcc
MACH= cortex-m0plus
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0 -D__SAMD21G17D__ -DDEBUG -I"../Lib" -I"../Lib/CMSIS/Include"
DEB_CFLAGS= -save-temps=obj -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0 -D__SAMD21G17D__ -DDEBUG -I"../Lib" -I"../Lib/CMSIS/Include"
OBJS= Build/startup_samd21.o Build/system_samd21.o Build/main.o 
LINKER_SCRIPTS= ../Device_Startup/samd21g17d_flash.ld ../Device_Startup/samd21g17d_sram.ld
DEB_OBJS= Temps/startup_samd21.o Temps/system_samd21.o Temps/main.o



Build/startup_samd21.o: ../Device_Startup/startup_samd21.c
	$(CC) $(CFLAGS) -o $@ $^

Build/system_samd21.o: ../Device_Startup/system_samd21.c
	$(CC) $(CFLAGS) -o $@ $^

Build/main.o: .././main.c
	$(CC) $(CFLAGS) -o $@ $^
	
Temps/startup_samd21.o: ../Device_Startup/startup_samd21.c
	$(CC) $(DEB_CFLAGS) -o $@ $^

Temps/system_samd21.o: ../Device_Startup/system_samd21.c
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
	$(CC) -o Debug_Build.elf $(DEB_OBJS) -mthumb -Wl,-Map="Debug_Build.map" -L"..\\Device_Startup" -mcpu=cortex-m0plus -Tsamd21g17d_flash.ld

Build.elf: $(OBJS) $(LINKER_SCRIPTS)
	$(CC) -o Build.elf $(OBJS) -mthumb -Wl,-Map="Build.map" -L"..\\Device_Startup" -mcpu=cortex-m0plus -Tsamd21g17d_flash.ld