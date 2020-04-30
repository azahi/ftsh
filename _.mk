TARGET := sh

TGT_LDFLAGS := -L$(TARGET_DIR)
TGT_LDLIBS  := -lft
TGT_PREREQS := libft.a

SRC_INCDIRS := ./libft/include

SUBMAKEFILES := \
	./libft/main.mk \
	./src/_.mk
