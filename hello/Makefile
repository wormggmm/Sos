# TOOLSPATH=../tools/z_tools/
# _TOOLSPATH=..\tools\z_tools\
# NASK=$(TOOLSPATH)nask.exe
# EDIMG=$(TOOLSPATH)edimg.exe
# MAKE=$(TOOLSPATH)make.exe

TOOLSPATH = ../tools/z_tools/
# 这里一定要再最后用双斜杠，否则会判断为换行 这里是windows批处理的命令问题，有些命令后必须跟正斜杠才能正确执行
_TOOLSPATH = ..\tools\z_tools\\
MAKE     = $(TOOLSPATH)make.exe
NASK     = $(TOOLSPATH)nask.exe
EDIMG    = $(TOOLSPATH)edimg.exe
IMGTOL   = $(TOOLSPATH)imgtol.com
COPY     = copy
DEL      = del


ipl.bin:ipl.nas Makefile
	$(NASK)  ipl.nas ipl.bin ipl.lst


helloos.img: ipl.bin Makefile
	$(EDIMG) imgin:$(TOOLSPATH)fdimg0at.tek \
	wbinimg src:ipl.bin len:512 from:0 to:0 imgout:helloos.img

asm:
	$(MAKE) -r ipl.bin

img:
	$(MAKE) -r helloos.img

run:
	$(MAKE) img
	$(COPY) helloos.img $(_TOOLSPATH)qemu\fdimage0.bin
	$(MAKE) -C $(TOOLSPATH)qemu

clean:
	$(DEL) *.bin *.lst *.img