CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall -ffunction-sections -fdata-sections
CFLAGS += -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD
CFLAGS += -IStart -ILibrary -IUser -ISystem -IHardware

LDFLAGS = -mcpu=cortex-m3 -mthumb -Tstm32f103c8.ld
LDFLAGS += -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs

SRCS = \
	Start/core_cm3.c \
	Start/system_stm32f10x.c \
	Library/misc.c \
	Library/stm32f10x_adc.c \
	Library/stm32f10x_bkp.c \
	Library/stm32f10x_can.c \
	Library/stm32f10x_cec.c \
	Library/stm32f10x_crc.c \
	Library/stm32f10x_dac.c \
	Library/stm32f10x_dbgmcu.c \
	Library/stm32f10x_dma.c \
	Library/stm32f10x_exti.c \
	Library/stm32f10x_flash.c \
	Library/stm32f10x_fsmc.c \
	Library/stm32f10x_gpio.c \
	Library/stm32f10x_i2c.c \
	Library/stm32f10x_iwdg.c \
	Library/stm32f10x_pwr.c \
	Library/stm32f10x_rcc.c \
	Library/stm32f10x_rtc.c \
	Library/stm32f10x_sdio.c \
	Library/stm32f10x_spi.c \
	Library/stm32f10x_tim.c \
	Library/stm32f10x_usart.c \
	Library/stm32f10x_wwdg.c \
	System/Delay.c \
	Hardware/Key.c \
	Hardware/OLED.c \
	Hardware/OLED_Data.c \
	Hardware/DHT11.c \
	Hardware/bsp_bmp180.c \
	Hardware/adc.c \
	Hardware/Buzzer.c \
	User/main.c \
	User/stm32f10x_it.c

ASM_SRCS = Start/startup_stm32f103xb.s

OBJS = $(SRCS:.c=.o) $(ASM_SRCS:.s=.o)

TARGET = firmware

.PHONY: all clean

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex
