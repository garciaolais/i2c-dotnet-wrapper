CC = gcc # C compiler
CFLAGS = -fPIC -lm # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = i2c-dotnet.so # target lib

SRCS = i2c-dotnet.c # source files
OBJS = $(SRCS:.c=.o)

all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	        $(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	        $(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)


.PHONY: clean
clean:
		${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
