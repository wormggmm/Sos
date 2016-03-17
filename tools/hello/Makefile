# TOOLSPATH=../tools/z_tools/
# _TOOLSPATH=..\tools\z_tools\
# NASK=$(TOOLSPATH)nask.exe
# EDIMG=$(TOOLSPATH)edimg.exe
# MAKE=$(TOOLSPATH)make.exe

TOOLSPATH = ../z_tools/
INCPATH  = $(TOOLSPATH)haribote/
# 这里一定要再最后用双斜杠，否则会判断为换行 这里是windows批处理的命令问题，有些命令后必须跟正斜杠才能正确执行
_TOOLSPATH = ..\z_tools\\
MAKE     = $(TOOLSPATH)make.exe
NASK     = $(TOOLSPATH)nask.exe
EDIMG    = $(TOOLSPATH)edimg.exe
IMGTOL   = $(TOOLSPATH)imgtol.com
CC1      = $(TOOLSPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLSPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLSPATH)obj2bim.exe
BIM2HRB  = $(TOOLSPATH)bim2hrb.exe
RULEFILE = $(TOOLSPATH)haribote/haribote.rul
COPY     = copy
DEL      = del



ipl10.bin:ipl10.nas Makefile
	$(NASK)  ipl10.nas ipl10.bin ipl10.lst


asmhead.bin: asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

bootpack.gas: bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.nas: bootpack.gas Makefile
	$(GAS2NASK) bootpack.gas bootpack.nas

bootpack.obj: bootpack.nas Makefile
	$(NASK) bootpack.nas bootpack.obj bootpack.lst

naskfunc.obj: naskfunc.nas Makefile
	$(NASK) naskfunc.nas naskfunc.obj naskfunc.lst

bootpack.bim: bootpack.obj naskfunc.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj naskfunc.obj
# 3MB+64KB=3136KB

bootpack.hrb: bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

haribote.sys: asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb haribote.sys

haribote.img: ipl10.bin haribote.sys Makefile
	$(EDIMG)   imgin:$(TOOLSPATH)fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		imgout:haribote.img

asm:
	$(MAKE) -r ipl10.bin

img:
	$(MAKE) -r haribote.img

run:
	$(MAKE) img
	$(COPY) haribote.img $(_TOOLSPATH)qemu\fdimage0.bin
	$(MAKE) -C $(TOOLSPATH)qemu

clean:
		-$(DEL) *.bin
	-$(DEL) *.lst
	-$(DEL) *.gas
	-$(DEL) *.obj
	-$(DEL) bootpack.nas
	-$(DEL) bootpack.map
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.hrb
	-$(DEL) haribote.sys