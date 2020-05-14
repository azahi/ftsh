TARGET := sh

TGT_LDFLAGS := -L$(TARGET_DIR)
TGT_LDLIBS  := -lft
TGT_PREREQS := libft.a

ifdef DEBUG_ASAN
    DEBUG       := 1
    TGT_CFLAGS  += -fsanitize=address -fsanitize-address-use-after-scope
    TGT_LDFLAGS += -fsanitize=address
endif

ifdef DEBUG_UBSAN
    DEBUG       := 1
    TGT_CFLAGS  += -fsanitize=undefined
    TGT_LDFLAGS += -fsanitize=undefined
endif

ifdef DEBUG
    TGT_CFLAGS  += -O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls
else
    TGT_CFLAGS  += -O2
endif

SRC_INCDIRS := ./libft/include

SUBMAKEFILES := \
	./libft/_.mk \
	./src/_.mk
