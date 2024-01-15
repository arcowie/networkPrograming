CC			= gcc
CFLAGS 		= -g
LDFLAGS		= -lm
OBJFILES	= driver.o ipAddressUtils.o
TARGET		= ipUtils

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm $(OBJFILES) $(TARGET)