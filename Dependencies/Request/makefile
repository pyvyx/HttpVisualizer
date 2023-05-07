LIB=request
HEADER=Request

ifeq ($(OS),Windows_NT)
	TARGET1=x86_64-pc-windows-msvc
	TARGET2=x86_64-pc-windows-gnu
	TARGET3=i686-pc-windows-msvc
	TARGET4=i686-pc-windows-gnu
else
	TARGET1=x86_64-unknown-linux-gnu
	TARGET2=i686-unknown-linux-gnu
	TARGET3=
	TARGET4=
endif

.PHONY: all build header move create

all: build header move

build:
	cargo build --release --target=$(TARGET1)
	cargo build --release --target=$(TARGET2)
	cargo build --release --target=$(TARGET3)
	cargo build --release --target=$(TARGET4)

header:
	cbindgen --config cbindgen.toml --output include/$(HEADER).h

ifeq ($(OS),Windows_NT)
move: create
	move /y target\$(TARGET1)\release\$(LIB).lib BIN/windows/x64/$(LIB).lib
	move /y target\$(TARGET2)\release\lib$(LIB).a BIN/windows/x64/lib$(LIB).a
	move /y target\$(TARGET3)\release\$(LIB).lib BIN/windows/x86/$(LIB).lib
	move /y target\$(TARGET4)\release\lib$(LIB).a BIN/windows/x86/lib$(LIB).a
else
move: create
	mv target/$(TARGET1)/release/$(LIB).lib BIN/$(TARGET1)/$(LIB).lib
	mv target/$(TARGET2)/release/lib$(LIB).a BIN/$(TARGET2)/lib$(LIB).a
endif

ifeq ($(OS),Windows_NT)
create:
	if exist BIN rmdir /s /q BIN
	mkdir BIN\windows\x64
	mkdir BIN\windows\x86
else
create:
	rm -f BIN
	mkdir -p BIN\linux\x64
	mkdir -p BIN\linux\x86
endif