SH_NAME    ?= sh
SH_VERSION ?= 0.0.0

TARGET  := $(SH_NAME)

TGT_CFLAGS  := -DSH_NAME=\"$(SH_NAME)\" -DSH_VERSION=\"$(SH_VERSION)\"
TGT_LDFLAGS := -L$(TARGET_DIR)
TGT_LDLIBS  := -lft
TGT_PREREQS := libft.a

ifdef DEBUG_ASAN
    DEBUG       := 1
    TGT_CFLAGS  += -fsanitize=address -fsanitize-address-use-after-scope
    TGT_LDFLAGS += -fsanitize=address
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
