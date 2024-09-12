type(ML620909)
model large
romwindow 0, 08fffH
extrn   code: _main
extrn   code: _custom_break
public  $$start_up
_$$SP	EQU	0F000h

dw	_$$SP
dw	$$start_up
dw	_BRK
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT
dw	_INT

_BRK:
	b _custom_break
	mov	psw,	#3
	brk

_INT:
	rti

_060EC:
	PUSH LR
	MOV ER2, ER0
	TB 0F00AH.1
	BNE _$L074
_$L00A:
	DI
	MOV ER0, #01H
	ST ER0, 0F024H
	MOV ER0, #00H
	ST ER0, 0F022H
	ST ER2, 0F020H
	MOV R0, #01H
	ST R0, 0F025H
	MOV R0, #00H
	ST R0, 0F014H
	ST R0, 0F015H
	MOV R2, #50H
	MOV R3, #0A0H
	ST R2, 0F008H
	ST R3, 0F008H
	MOV R0, #02H
	ST R0, 0F009H
	NOP
	NOP
_$L044:
	L R0, 0F042H
	BNE _$L072
_$L04A:
	MOV ER0, #0FH
	ST ER0, 0F024H
	MOV ER0, #00H
	ST ER0, 0F022H
	MOV R0, #9EH
	MOV R1, #07H
	ST ER0, 0F020H
	MOV R0, #01H
	ST R0, 0F025H
	MOV R0, #00H
	ST R0, 0F014H
	ST R0, 0F015H
	EI
_$L072:
	POP PC
_$L074:
	RB 0F00AH.1
	BAL _$L00A

$$start_up:
	MOV R0, #00H
	ST R0, 0F000H
	B _2F060

_2F060:
	L R0, 0F058H
	MOV R4, R0
	BL _3DEDE
	MOV R0, #40H
	MOV R1, #06H
	BL _060EC
	MOV R0, #81H
	ST R0, 0F00AH
	MOV R0, #04H
	ST R0, 0F030H
	MOV R0, #03H
	ST R0, 0F033H
	MOV R0, #06H
	ST R0, 0F034H
	MOV R0, #17H
	ST R0, 0F035H
	MOV R0, #08H
	ST R0, 0F036H
	MOV R0, #00H
	ST R0, 0F039H
	MOV R0, #55H
	ST R0, 0F031H
	BL _entry


_3DEDE:
	PUSH LR
	MOV R0, #31H
	ST R0, 0F00AH
	MOV R0, #0F7H
	ST R0, 0F028H
	MOV R0, #32H
_$L010:
	ADD R0, #-1H
	CMP R0, #00H
	BNE _$L010
	MOV R0, #22H
	ST R0, 0F010H
	MOV R0, #00H
	ST R0, 0F011H
	ST R0, 0F012H
	MOV R0, #01H
	ST R0, 0F018H
	MOV R0, #00H
	ST R0, 0F058H
	MOV R0, #00H
	ST R0, 0F042H
	MOV R0, #07H
	ST R0, 0F03DH
	MOV R0, #0C8H
	MOV R1, #00H
_$L02E:
	BL _060EC
	MOV R0, #04H
	ST R0, 0F030H
	MOV R0, #07H
	ST R0, 0F033H
	MOV R0, #06H
	ST R0, 0F034H
	MOV R0, #17H
	ST R0, 0F035H
	MOV R0, #08H
	ST R0, 0F036H
	MOV R0, #00H
	ST R0, 0F039H
	MOV R0, #57H
	ST R0, 0F031H
	MOV R0, #12H
	ST R0, 0F032H
	MOV R0, #00H
	ST R0, 0F220H
	MOV R0, #7FH
	ST R0, 0F221H
	MOV R0, #00H
	ST R0, 0F222H
	MOV R0, #7FH
	ST R0, 0F223H
	MOV R0, #00H
	ST R0, 0F224H
	ST R0, 0F225H
	MOV R0, #00H
	ST R0, 0F048H
	ST R0, 0F049H
	MOV R0, #07H
	ST R0, 0F04AH
	MOV R0, #00H
	ST R0, 0F04BH
	MOV R0, #07H
	ST R0, 0F04CH
	MOV R0, #00H
	ST R0, 0F04EH
	MOV R0, #00H
	ST R0, 0F041H
	MOV R0, #80H
	ST R0, 0F044H
	MOV R0, #0FFH
	ST R0, 0F045H
	MOV R2, #00H
	ST R2, 0F046H
	POP PC

delay:
	tb	00h:0f00ah.1
	beq	_$L27
	rb	00h:0f00ah.1
_$L27 :
	di
	st	er0,	00h:0f020h
	mov	er0,	#0
	st	er0,	00h:0f022h
	mov	r0,	#01h
	mov	r1,	#01h
	st	er0,	00h:0f024h
	mov	er0,	#0
	st	er0,	00h:0f014h
	mov	r0,	#050h
	st	r0,	00h:0f008h
	mov	r0,	#0a0h
	st	r0,	00h:0f008h
	mov	r0,	#02h
	st	r0,	00h:0f009h
	nop
	nop
	ei
	rt

_entry:
	mov r0, #01h
	st r0, 0F018h
	b _main
	mov	r0,	#06h
	st	r0,	00h:0f034h
	mov	r0,	#08h
	st	r0,	00h:0f036h
main_loop:
    mov    r13,    #01h ;starting segment to read from
    mov    r10,    #00h ;starting address to read from ill have to change this to the address right after the code
    mov	   r11,    #00h ;
loop_n:
    bl    decomp        ;decompress the image to image buffer
    push    er10         ;save address after decomp (next frame data)
    push    r13         ;save segment after decomp (segment to read data from)

	l    r0,    0F037h  ;load state of f037 (lcd buffer select)
    xor    r0,    #04h  ;toggle f037 buffer select
    st    r0,    0F037h ;store back into f037

    mov    r2,    #00h  ;buff 1
    mov    r3,    #90h  ;
    mov    r0,    #00h  ;not invert

    bl    FastRender_LCD;render the frame buffer to the screen (light gray)

    l    r0,    0F037h  ;load state of f037 (lcd buffer select)
    xor    r0,    #04h  ;toggle f037 buffer select
    st    r0,    0F037h ;store back into f037

    mov    r2,    #00h  ;buff 2
    mov    r3,    #96h  ;

    bl    FastRender_LCD;render the frame buffer to the screen (dark gray)

    mov    r0,    #35h  ;delay 055A ticks
    mov    r1,    #0Ch  ;
    bl    delay         ;
    ;brk

    pop    r13          ;restore segment to read from
    pop    er10          ;restore address to read from
    bal    loop_n       ;loop

decomp:
    mov    r3,    #90h
    mov    r2,    #00h
    push    er10
    mov    er6,    #00h
main_d:
    l    er0,    r13:[er10]
    add    er10,    #02h
    addc    r13,    #00h
    cmp    r13,    #09h
    beq    skib
    bal    cont
skib:
	mov    r13,    #01h
cont:
    mov    r4,    #00h
loop_d:
    st    r1,    [er2]
    add    er2,    #01h
    add    er6,    #01h
    cmp    r7,    #0Ch
    beq    return
    add    r4,    #01h
    cmp    r0,    r4
    bne    loop_d
    bal    main_d
return:
    rt


FastRender_LCD:
    push    qr8            ; 4
    push    xr4            ; 2

    mov    r4,    #00h        ; 1
    mov    r5,    #0F8h        ; 1    ; ER4 = VRAM

    lea    [er2]            ; 1    ; destination goes to EA
    mov    r3,    #0FFh    ; 1    ; 64 rows * 4 * 8 bytes in VRAM
    mov    r6,    #37h
    mov    r7,    #0F0h
loop:
    mov    r8,    #03h   ; 1
    and    r8,    r3        ; 1    ; test lower 2 bits of counter
    bc    zf,    skip        ; 3/1    ; skip last 8 bytes for each row of VRAM

    l    qr8,    [ea+]    ; 5
;    cmp    r0,    #01h
;    beq    is_one
;    bal    is_not_one
;is_one:
;	xor    r8,    #0FFh
;	xor    r9,    #0FFh
;	xor    r10,    #0FFh
;	xor    r11,    #0FFh
;	xor    r12,    #0FFh
;	xor    r13,    #0FFh
;	xor    r14,    #0FFh
;	xor    r15,    #0FFh
;is_not_one:
    st    er8,    [er4]        ; 1
    add    er4,    #02h        ; 1
    st    er10,    [er4]        ; 1
    add    er4,    #02h        ; 1
    st    er12,    [er4]        ; 1
    add    er4,    #02h        ; 1
    st    er14,    [er4]        ; 1
    add    er4,    #02h        ; 1

    add    r3,    #0FFh        ; 1
    bc    nz,    loop        ; 3
    pop    xr4            ; 2
    pop    qr8            ; 4

    rt                ; 2
skip:
    add    er4,    #08h        ; 1
    add    r3,    #0FFh        ; 1
    bc    al,    loop        ; 3
