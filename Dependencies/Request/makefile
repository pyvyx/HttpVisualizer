LIB=request
HEADER=Request

ifeq ($(OS),Windows_NT)
	TARGET1=x86_64-pc-windows-msvc
	TARGET2=x86_64-pc-windows-gnu
	TARGET3=i686-pc-windows-msvc
	TARGET4=i686-pc-windows-gnu
	LIBFOLDER=Lib\windows
else
	TARGET=x86_64-unknown-linux-gnu
	LIBFOLDER=Lib/linux
endif

.PHONY: all build header move create clean

all: build header move

ifeq ($(OS),Windows_NT)
build:
	cargo build --release --target=$(TARGET1)
	cargo build --release --target=$(TARGET2)
	cargo build --release --target=$(TARGET3)
	cargo build --release --target=$(TARGET4)

move: create
	move /y target\$(TARGET1)\release\$(LIB).lib $(LIBFOLDER)/x64/$(LIB).lib
	move /y target\$(TARGET2)\release\lib$(LIB).a $(LIBFOLDER)/x64/lib$(LIB).a
	move /y target\$(TARGET3)\release\$(LIB).lib $(LIBFOLDER)/x86/$(LIB).lib
	move /y target\$(TARGET4)\release\lib$(LIB).a $(LIBFOLDER)/x86/lib$(LIB).a

create:
	if exist $(LIBFOLDER) rmdir /s /q $(LIBFOLDER)
	mkdir $(LIBFOLDER)\x64
	mkdir $(LIBFOLDER)\x86

clean:
	if exist $(LIBFOLDER) rmdir /s /q $(LIBFOLDER)
else
build:
	cargo build --release --target=$(TARGET)

move: create
	mv target/$(TARGET)/release/lib$(LIB).a $(LIBFOLDER)/x64/lib$(LIB).a

create:
	rm -f -r $(LIBFOLDER)
	mkdir -p $(LIBFOLDER)/x64

clean:
	rm -f -r $(LIBFOLDER)
endif

header:
	cbindgen --config cbindgen.toml --output include/$(HEADER).h
