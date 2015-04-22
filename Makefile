TARGET = libfirebird.a
OBJDIR = build

OBJS = $(OBJDIR)/lcd.o $(OBJDIR)/timer.o $(OBJDIR)/motor.o $(OBJDIR)/sensor.o $(OBJDIR)/xbee.o

SRC = lcd.c timer.c motor.c sensor.c xbee.c

$(OBJDIR)/%.o : %.c
	avr-gcc -mmcu=atmega2560 -O0 -DF_CPU=14745600 -c $< -o $@
	
all: $(OBJS)
	avr-ar rcs $(TARGET) $(OBJS)

clean:
	rm $(OBJS)
