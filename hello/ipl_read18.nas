
		ORG		0x7c00			


		JMP		entry
		DB		0x90
		DB		"HELLOIPL"		
		DW		512				
		DB		1			
		DW		1			
		DB		2			
		DW		224			
		DW		2880		
		DB		0xf0		
		DW		9			
		DW		18			
		DW		2			
		DD		0			
		DD		2880		
		DB		0,0,0x29	
		DD		0xffffffff	
		DB		"HELLO-OS   "
		DB		"FAT12   "	
		RESB	18			


entry:
		MOV		AX,0			
		MOV		SS,AX
		MOV		SP,0x7c00

		MOV		DS,AX
		MOV		CX,AX
		MOV		AX,0x0820		; 初始化目标内存地址
		MOV		ES,AX
		MOV		CL,1			; 扇区1
read:
		ADD		CL,1			; 一开始直接加一个扇区 让读从2号扇区开始
		CMP		CL,18			; 比较下当前要读的扇区是否已经读到了18号
		JE		readfinish		; 如果读到了18号扇区，则跳转到读取结束
		MOV		CH,0			; 柱面0
		MOV		DH,0			; 磁头0
		;MOV	CL,2

beginmove:
		MOV		AH,0x02			; 读盘
		MOV		AL,1			; 读一个扇区
		MOV		BX,0			; 内存子地址初始化为0 目标写入点：ES:BX => 0x0820:0x0000
		MOV 	DL,0x00
		JMP		changeES
endmove:
		INT		0x13
		JC		error
		JMP		read
changeES:
		MOV		AX,ES
		ADD		AX,0x020
		MOV		ES,AX
		MOV		AH,0x02
		MOV		AL,1
		CMP		CL,18
		JE		readfinish
		JMP		endmove;

readfinish:
		MOV		SI,msg
		JMP		putloop
error:
		MOV		SI,msg
		MOV		AL,[SI]
		ADD		SI,1			
		CMP		AL,0
		JE		entry	
		MOV		AH,0x0e			
		MOV		BX,15			
		INT		0x10			
		JMP		putloop

putloop:
		MOV		AL,[SI]
		ADD		SI,1			
		CMP		AL,0
		;JE		rep	
		JE		fin	
		MOV		AH,0x0e			
		MOV		BX,15			
		INT		0x10			
		JMP		putloop
rep:
		ADD		CX,1
		CMP		CX,5
		JE		fin
		MOV 	SI,msg
		JMP		putloop
fin:
		HLT						
		JMP		fin				

msg:
		DB		0x0a, 0x0a		
		DB		"error!"
		DB		0x0a			
		DB		0

		RESB	0x7dfe-$		

		DB		0x55, 0xaa

