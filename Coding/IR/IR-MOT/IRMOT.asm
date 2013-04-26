;------------------------------------------
.EQU _MOTBIT0=4
.EQU _MOTBIT1=5
.EQU _MOTBIT2=6
.EQU _MOTBIT3=7
.EQU _MOTBIT4=0
.EQU _MOTBIT5=1
.EQU _MOTBIT6=2
.EQU _MOTBIT7=3
;------------------------------------------
L00000:
JMP     L00028       	;Jump
;------------------------------------------
L00002:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00004:   
RETI                     ;Interrupt return
L00005:   NOP                      ;No operation
L00006:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00008:   
RETI                     ;Interrupt return
NOP                      ;No operation
;------------------------------------------
L0000A:   
JMP     L00159       	;Jump
;------------------------------------------
L0000C:   
RETI                     ;Interrupt return
NOP                      ;No operation
L0000E:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00010:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00012:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00014:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00016:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00018:   
RETI                     ;Interrupt return
L00019:   
NOP                      ;No operation
L0001A:   
RETI                     ;Interrupt return
NOP                      ;No operation
L0001C:   
RETI                     ;Interrupt return
NOP                      ;No operation
L0001E:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00020:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00022:   
RETI                     ;Interrupt return
L00023:   
NOP                      ;No operation
L00024:   
RETI                     ;Interrupt return
NOP                      ;No operation
L00026:   
RETI                     ;Interrupt return
NOP                      ;No operation
;------------------------------------------
L00028:   
LDI     R24,0x1F         ;Load immediate
L00029:   
OUT     0x21,R24         ;Out to I/O location
L0002A:   
LDI     R24,0x17         ;Load immediate
L0002B:   
OUT     0x21,R24         ;Out to I/O location
L0002C:   
LDI     R24,0x5F         ;Load immediate
L0002D:   
OUT     0x3D,R24         ;Out to I/O location
L0002E:   
LDI     R28,0x40         ;Load immediate
L0002F:   
LDI     R30,0x38         ;Load immediate
L00030:   
MOV     R4,R30           ;Copy register
L00031:   
LDI     R24,0x08         ;Load immediate
L00032:   
OUT     0x3E,R24         ;Out to I/O location
L00033:   
LDI     R29,0x08         ;Load immediate
L00034:   
LDI     R31,0x08         ;Load immediate
L00035:   
MOV     R5,R31           ;Copy register
L00036:   
LDI     R30,0xFE         ;Load immediate
L00037:   
LDI     R31,0x07         ;Load immediate
L00038:   
LDI     R26,0x60         ;Load immediate
L00039:   
LDI     R27,0x00         ;Load immediate
L0003A:   
CLR     R24              ;Clear Register
L0003B:   
ST      X+,R24           ;Store indirect and postincrement
L0003C:   
SBIW    R30,0x01         ;Subtract immediate from word
L0003D:   
BRNE    PC-0x02          ;Branch if not equal
L0003E:   
CLR     R6               ;Clear Register
L0003F:   
LDI     R24,0xF0         ;Load immediate
L00040:   
OUT     0x1A,R24         ;Out to I/O location
L00041:   
LDI     R24,0xF9         ;Load immediate
L00042:   
OUT     0x17,R24         ;Out to I/O location
L00043:   
SER     R24              ;Set Register
L00044:   
OUT     0x14,R24         ;Out to I/O location
L00045:   
LDI     R24,0xFD         ;Load immediate
L00046:   
OUT     0x11,R24         ;Out to I/O location
L00047:   
LDI     R24,0xA1         ;Load immediate
L00048:   
OUT     0x2F,R24         ;Out to I/O location
L00049:   
LDI     R24,0x04         ;Load immediate
L0004A:   
OUT     0x2E,R24         ;Out to I/O location
L0004B:   
SEI                      ;Global Interrupt Enable
L0004C:   
SER     R24              ;Set Register
L0004D:   
LDI     R25,0x00         ;Load immediate
L0004E:   
OUT     0x29,R25         ;Out to I/O location
L0004F:   
OUT     0x28,R24         ;Out to I/O location
L00050:   
SER     R24              ;Set Register
L00051:   
LDI     R25,0x00         ;Load immediate
L00052:   
OUT     0x2B,R25         ;Out to I/O location
L00053:   
OUT     0x2A,R24         ;Out to I/O location
L00054:   
LDI     R24,0x00         ;Load immediate
L00055:   
STS     0x0061,R24       ;Store direct to data space
L00057:   
SBI     0x12,0           ;Set bit in I/O register
L00058:   
LDS     R16,0x0061       ;Load direct from data space
L0005A:   
CPI     R16,0x20         ;Compare with immediate
L0005B:   
BREQ    PC+0x03          ;Branch if equal
L0005C:   
JMP     L00069       	;Jump

L0005E:   
CBI     0x15,_MOTBIT0           ;Clear bit in I/O register
L0005F:   
CBI     0x15,_MOTBIT2           ;Clear bit in I/O register
L00060:   
SBI     0x15,_MOTBIT1           ;Set bit in I/O register
L00061:   
SBI     0x15,_MOTBIT3           ;Set bit in I/O register
L00062:   
CBI     0x1B,4           ;Clear bit in I/O register
L00063:   
LDI     R24,0x03         ;Load immediate
L00064:   
LDI     R25,0x00         ;Load immediate
L00065:   
CALL    L00175       	;Call subroutine
L00067:   
JMP     L0013F       	;Jump

L00069:   
LDS     R16,0x0061       ;Load direct from data space
L0006B:   
CPI     R16,0x21         ;Compare with immediate
L0006C:   
BREQ    PC+0x03          ;Branch if equal
L0006D:   
JMP     L0007A       	;Jump

L0006F:   
CBI     0x15,_MOTBIT1           ;Clear bit in I/O register
L00070:   
CBI     0x15,_MOTBIT3           ;Clear bit in I/O register
L00071:   
SBI     0x15,_MOTBIT0           ;Set bit in I/O register
L00072:   
SBI     0x15,_MOTBIT2           ;Set bit in I/O register
L00073:   
CBI     0x1B,4           ;Clear bit in I/O register
L00074:   
LDI     R24,0x03         ;Load immediate
L00075:   
LDI     R25,0x00         ;Load immediate
L00076:   
CALL    L00175       	;Call subroutine
L00078:   
JMP     L0013F       	;Jump

L0007A:   
LDS     R16,0x0061       ;Load direct from data space
L0007C:   
CPI     R16,0x11         ;Compare with immediate
L0007D:   
BREQ    PC+0x03          ;Branch if equal
L0007E:   
JMP     L0008B       	;Jump

L00080:   
CBI     0x15,_MOTBIT1           ;Clear bit in I/O register
L00081:   
SBI     0x15,_MOTBIT3           ;Set bit in I/O register
L00082:   
SBI     0x15,_MOTBIT0           ;Set bit in I/O register
L00083:   
CBI     0x15,_MOTBIT2           ;Clear bit in I/O register
L00084:   
CBI     0x1B,4           ;Clear bit in I/O register
L00085:   
LDI     R24,0x03         ;Load immediate
L00086:   
LDI     R25,0x00         ;Load immediate
L00087:   
CALL    L00175       	;Call subroutine
L00089:   
JMP     L0013F       	;Jump

L0008B:   
LDS     R16,0x0061       ;Load direct from data space
L0008D:   
CPI     R16,0x10         ;Compare with immediate
L0008E:   
BREQ    PC+0x03          ;Branch if equal
L0008F:   
JMP     L0009C       	;Jump

L00091:   
SBI     0x15,_MOTBIT1           ;Set bit in I/O register
L00092:   
CBI     0x15,_MOTBIT3           ;Clear bit in I/O register
L00093:   
CBI     0x15,_MOTBIT0           ;Clear bit in I/O register
L00094:   
SBI     0x15,_MOTBIT2           ;Set bit in I/O register
L00095:   
CBI     0x1B,4           ;Clear bit in I/O register
L00096:   
LDI     R24,0x03         ;Load immediate
L00097:   
LDI     R25,0x00         ;Load immediate
L00098:   
CALL    L00175       	;Call subroutine
L0009A:   
JMP     L0013F       	;Jump

L0009C:   
LDS     R16,0x0061       ;Load direct from data space
L0009E:   
CPI     R16,0x0E         ;Compare with immediate
L0009F:   
BREQ    PC+0x03          ;Branch if equal
L000A0:   
JMP     L000A7       	;Jump

L000A2:   
CBI     0x15,_MOTBIT4           ;Clear bit in I/O register
L000A3:   
SBI     0x15,_MOTBIT5           ;Set bit in I/O register
L000A4:   
CBI     0x1B,4           ;Clear bit in I/O register
L000A5:   
JMP     L0013F       	;Jump

L000A7:   
LDS     R16,0x0061       ;Load direct from data space
L000A9:   
CPI     R16,0x29         ;Compare with immediate
L000AA:   
BREQ    PC+0x03          ;Branch if equal
L000AB:   
JMP     L000B2       	;Jump
L000AD:   
CBI     0x15,_MOTBIT5           ;Clear bit in I/O register
L000AE:   
SBI     0x15,_MOTBIT4           ;Set bit in I/O register
L000AF:   
CBI     0x1B,4           ;Clear bit in I/O register
L000B0:   
JMP     L0013F       	;Jump

L000B2:   
LDS     R16,0x0061       ;Load direct from data space
L000B4:   
CPI     R16,0x1E         ;Compare with immediate
L000B5:   
BREQ    PC+0x03          ;Branch if equal
L000B6:   
JMP     L000BD       	;Jump

L000B8:   
CBI     0x15,_MOTBIT7           ;Clear bit in I/O register
L000B9:   
SBI     0x15,_MOTBIT6           ;Set bit in I/O register
L000BA:   
CBI     0x1B,4           ;Clear bit in I/O register
L000BB:   
JMP     L0013F       	;Jump

L000BD:   
LDS     R16,0x0061       ;Load direct from data space
L000BF:   
CPI     R16,0x38         ;Compare with immediate
L000C0:   
BREQ    PC+0x03          ;Branch if equal
L000C1:   
JMP     L000C8       	;Jump

L000C3:   
CBI     0x15,_MOTBIT6           ;Clear bit in I/O register
L000C4:   
SBI     0x15,_MOTBIT7           ;Set bit in I/O register
L000C5:   
CBI     0x1B,4           ;Clear bit in I/O register
L000C6:   
JMP     L0013F       	;Jump

L000C8:   
LDS     R16,0x0061       ;Load direct from data space
L000CA:   
CPI     R16,0x01         ;Compare with immediate
L000CB:   
BREQ    PC+0x03          ;Branch if equal
L000CC:   
JMP     L000D9       	;Jump

L000CE:   
LDI     R24,0x64         ;Load immediate
L000CF:   
LDI     R25,0x00         ;Load immediate
L000D0:   
OUT     0x29,R25         ;Out to I/O location
L000D1:   
OUT     0x28,R24         ;Out to I/O location
L000D2:   
LDI     R24,0x64         ;Load immediate
L000D3:   
LDI     R25,0x00         ;Load immediate
L000D4:   
OUT     0x2B,R25         ;Out to I/O location
L000D5:   
OUT     0x2A,R24         ;Out to I/O location
L000D6:   
CBI     0x1B,4           ;Clear bit in I/O register
L000D7:   
JMP     L0013F       	;Jump

L000D9:   
LDS     R16,0x0061       ;Load direct from data space
L000DB:   
CPI     R16,0x02         ;Compare with immediate
L000DC:   
BREQ    PC+0x03          ;Branch if equal
L000DD:   
JMP     L000EA       	;Jump

L000DF:   
LDI     R24,0xAF         ;Load immediate
L000E0:   
LDI     R25,0x00         ;Load immediate
L000E1:   
OUT     0x29,R25         ;Out to I/O location
L000E2:   
OUT     0x28,R24         ;Out to I/O location
L000E3:   
LDI     R24,0xAF         ;Load immediate
L000E4:   
LDI     R25,0x00         ;Load immediate
L000E5:   
OUT     0x2B,R25         ;Out to I/O location
L000E6:   
OUT     0x2A,R24         ;Out to I/O location
L000E7:   
CBI     0x1B,4           ;Clear bit in I/O register
L000E8:   
JMP     L0013F       	;Jump

L000EA:   
LDS     R16,0x0061       ;Load direct from data space
L000EC:   
CPI     R16,0x03         ;Compare with immediate
L000ED:   
BREQ    PC+0x03          ;Branch if equal
L000EE:   
JMP     L000FB       	;Jump

L000F0:   
SER     R24              ;Set Register
L000F1:   
LDI     R25,0x00         ;Load immediate
L000F2:   
OUT     0x29,R25         ;Out to I/O location
L000F3:   
OUT     0x28,R24         ;Out to I/O location
L000F4:   
SER     R24              ;Set Register
L000F5:   
LDI     R25,0x00         ;Load immediate
L000F6:   
OUT     0x2B,R25         ;Out to I/O location
L000F7:   
OUT     0x2A,R24         ;Out to I/O location
L000F8:   
CBI     0x1B,4           ;Clear bit in I/O register
L000F9:   
JMP     L0013F       	;Jump

L000FB:   
LDS     R16,0x0061       ;Load direct from data space
L000FD:   
CPI     R16,0x09         ;Compare with immediate
L000FE:   
BREQ    PC+0x03          ;Branch if equal
L000FF:   
JMP     L00136       	;Jump

L00101:   
CBI     0x12,0           ;Clear bit in I/O register
L00102:   
SER     R24              ;Set Register
L00103:   
LDI     R25,0x00         ;Load immediate
L00104:   
OUT     0x29,R25         ;Out to I/O location
L00105:   
OUT     0x28,R24         ;Out to I/O location
L00106:   
SER     R24              ;Set Register
L00107:   
LDI     R25,0x00         ;Load immediate
L00108:   
OUT     0x2B,R25         ;Out to I/O location
L00109:   
OUT     0x2A,R24         ;Out to I/O location
L0010A:   
CLR     R16              ;Clear Register
L0010B:   
CLR     R27              ;Clear Register
L0010C:   
LDI     R26,0x30         ;Load immediate
L0010D:   
LD      R24,X            ;Load indirect
L0010E:   
BST     R24,1            ;Bit store from register to T
L0010F:   
BRTC    PC+0x02          ;Branch if T flag cleared
L00110:   
LDI     R16,0x01         ;Load immediate
L00111:   
LDI     R20,0x00         ;Load immediate
L00112:   
CP      R16,R20          ;Compare
L00113:   
BREQ    PC+0x03          ;Branch if equal
L00114:   
JMP     L0012D       	;Jump

L00116:   
CBI     0x15,_MOTBIT1           ;Clear bit in I/O register
L00117:   
SBI     0x15,_MOTBIT0           ;Set bit in I/O register
L00118:   
CBI     0x15,_MOTBIT3           ;Clear bit in I/O register
L00119:   
SBI     0x15,_MOTBIT2           ;Set bit in I/O register
L0011A:   
LDI     R30,0x01         ;Load immediate
L0011B:   
LDI     R31,0x00         ;Load immediate
L0011C:   
CALL    L00166       	;Call subroutine
L0011E:   
CBI     0x15,_MOTBIT1           ;Clear bit in I/O register
L0011F:   
SBI     0x15,_MOTBIT3           ;Set bit in I/O register
L00120:   
SBI     0x15,_MOTBIT0           ;Set bit in I/O register
L00121:   
CBI     0x15,_MOTBIT2           ;Clear bit in I/O register
L00122:   
SER     R24              ;Set Register
L00123:   
LDI     R25,0x00         ;Load immediate
L00124:   
CALL    L00175       	;Call subroutine
L00126:   
SER     R24              ;Set Register
L00127:   
LDI     R25,0x00         ;Load immediate
L00128:   
CALL    L00175       	;Call subroutine
L0012A:   
SBI     0x1B,5           ;Set bit in I/O register
L0012B:   
JMP     L00132       	;Jump

L0012D:   
SBI     0x15,_MOTBIT1           ;Set bit in I/O register
L0012E:   
CBI     0x15,_MOTBIT0           ;Clear bit in I/O register
L0012F:   
SBI     0x15,_MOTBIT3           ;Set bit in I/O register
L00130:   
CBI     0x15,_MOTBIT2           ;Clear bit in I/O register
L00131:   
CBI     0x1B,5           ;Clear bit in I/O register
L00132:   
JMP     L0010A       	;Jump

L00134:   
JMP     L0013F       	;Jump

L00136:   
CBI     0x15,_MOTBIT5           ;Clear bit in I/O register
L00137:   
CBI     0x15,_MOTBIT7           ;Clear bit in I/O register
L00138:   
CBI     0x15,_MOTBIT4           ;Clear bit in I/O register
L00139:   
CBI     0x15,_MOTBIT6           ;Clear bit in I/O register
L0013A:   
CBI     0x15,_MOTBIT1           ;Clear bit in I/O register
L0013B:   
CBI     0x15,_MOTBIT0           ;Clear bit in I/O register
L0013C:   
CBI     0x15,_MOTBIT3           ;Clear bit in I/O register
L0013D:   
CBI     0x15,_MOTBIT2           ;Clear bit in I/O register
L0013E:   
SBI     0x1B,4           ;Set bit in I/O register
L0013F:   
LDI     R24,0x00         ;Load immediate
L00140:   
STS     0x0061,R24       ;Store direct to data space
L00142:   
CALL    L00184       	;Call subroutine
L00144:   
LDI     R26,0x60         ;Load immediate
L00145:   
LDI     R27,0x00         ;Load immediate
L00146:   
ST      X,R18            ;Store indirect
L00147:   
LDI     R26,0x61         ;Load immediate
L00148:   
LDI     R27,0x00         ;Load immediate
L00149:   
ST      X,R17            ;Store indirect
L0014A:   
LDS     R16,0x0060       ;Load direct from data space
L0014C:   
CPI     R16,0x00         ;Compare with immediate
L0014D:   
BREQ    PC+0x03          ;Branch if equal
L0014E:   
JMP     L00155       	;Jump

L00150:   
LDI     R26,0x61         ;Load immediate
L00151:   
LDI     R27,0x00         ;Load immediate
L00152:   
LD      R24,X            ;Load indirect
L00153:   
ANDI    R24,0x7F         ;Logical AND with immediate
L00154:   
ST      X,R24            ;Store indirect
L00155:   
JMP     L00058       	;Jump

L00157:   
CLI                      ;Global Interrupt Disable
L00158:   
RJMP    PC-0x0000        ;Relative jump

L00159:   
PUSH    R24              ;Push register on stack
L0015A:   
PUSH    R25              ;Push register on stack
L0015B:   
IN      R24,0x3F         ;In from I/O location
L0015C:   
INC     R19              ;Increment
L0015D:   
INC     R21              ;Increment
L0015E:   
BRNE    PC+0x02          ;Branch if not equal
L0015F:   
INC     R20              ;Increment
L00160:   
LDI     R25,0xC1         ;Load immediate
L00161:   
OUT     0x24,R25         ;Out to I/O location
L00162:   
POP     R25              ;Pop register from stack
L00163:   
OUT     0x3F,R24         ;Out to I/O location
L00164:   
POP     R24              ;Pop register from stack
L00165:   
RETI                     ;Interrupt return

L00166:   
LDI     R24,0xE8         ;Load immediate
L00167:   
LDI     R25,0x03         ;Load immediate
L00168:   
RCALL   PC+0x000D        ;Relative call subroutine
L00169:   
SBIW    R30,0x01         ;Subtract immediate from word
L0016A:   
BRNE    PC-0x04          ;Branch if not equal
L0016B:   
RET                      ;Subroutine return

L0016C:   
SBIW    R30,0x01         ;Subtract immediate from word
L0016D:   
BRNE    PC-0x01          ;Branch if not equal
L0016E:   
RET                      ;Subroutine return

L0016F:   
SET                      ;Set T in SREG
L00170:   
BLD     R6,2             ;Bit load from T to register
L00171:   
RET                      ;Subroutine return

L00172:   
CLT                      ;Clear T in SREG
L00173:   
BLD     R6,2             ;Bit load from T to register
L00174:   
RET                      ;Subroutine return

L00175:   
PUSH    R30              ;Push register on stack
L00176:   
PUSH    R31              ;Push register on stack
L00177:   
CLR     R30              ;Clear Register
L00178:   
OR      R30,R24          ;Logical OR
L00179:   
OR      R30,R25          ;Logical OR
L0017A:   
BREQ    PC+0x07          ;Branch if equal
L0017B:   
LDI     R30,0xFA         ;Load immediate
L0017C:   
LDI     R31,0x00         ;Load immediate
L0017D:   
SBIW    R30,0x01         ;Subtract immediate from word
L0017E:   
BRNE    PC-0x01          ;Branch if not equal
L0017F:   
SBIW    R24,0x01         ;Subtract immediate from word
L00180:   
BRNE    PC-0x05          ;Branch if not equal
L00181:   
POP     R31              ;Pop register from stack
L00182:   
POP     R30              ;Pop register from stack
L00183:   
RET                      ;Subroutine return

L00184:   
PUSH    R16              ;Push register on stack
L00185:   
PUSH    R19              ;Push register on stack
L00186:   
PUSH    R20              ;Push register on stack
L00187:   
PUSH    R21              ;Push register on stack
L00188:   
PUSH    R2               ;Push register on stack
L00189:   
PUSH    R3               ;Push register on stack
L0018A:   
PUSH    R24              ;Push register on stack
L0018B:   
PUSH    R25              ;Push register on stack
L0018C:   
IN      R24,0x3F         ;In from I/O location
L0018D:   
PUSH    R24              ;Push register on stack
L0018E:   
IN      R24,0x25         ;In from I/O location
L0018F:   
PUSH    R24              ;Push register on stack
L00190:   
ORI     R24,0x01         ;No Pre Scalling in TCCR2
L00191:   
OUT     0x25,R24         ;Out to I/O location
L00192:   
IN      R24,0x39         ;In from I/O location
L00193:   
PUSH    R24              ;Push register on stack
L00194:   
ORI     R24,0x40         ;Timer2 OVFL Enable bit High
L00195:   
OUT     0x39,R24         ;Out to I/O location
L00196:   
LDI     R24,0xC1         ;Load immediate
L00197:   
OUT     0x24,R24         ;C! count in TimerCounter2
L00198:   
CLR     R21              ;Clear Register
L00199:   
CLR     R20              ;Clear Register
L0019A:   
CLR     R19              ;Clear Register
L0019B:   
CPI     R20,0x08         ;Compare with immediate
L0019C:   
BRCS    PC+0x02          ;Branch if carry set
L0019D:   
RJMP    PC+0x0048        ;Relative jump

L0019E:   
CPI     R19,0x37         ;Compare with immediate
L0019F:   
BRGE    PC+0x05          ;Branch if greater or equal, signed
L001A0:   
SBIS    0x19,0           ;Skip if bit in I/O register set
L001A1:   
RJMP    PC-0x0007        ;Relative jump

L001A2:   
RJMP    PC-0x0007        ;Relative jump

L001A3:   
RJMP    PC+0x0042        ;Relative jump

L001A4:   
CPI     R20,0x08         ;Compare with immediate
L001A5:   
BRGE    PC-0x02          ;Branch if greater or equal, signed
L001A6:   
SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001A7:   
RJMP    PC-0x0003        ;Relative jump

L001A8:   
CLR     R19              ;Clear Register
L001A9:   
CPI     R19,0x22         ;Compare with immediate
L001AA:   
BRGE    PC+0x3B          ;Branch if greater or equal, signed
L001AB:   
SBIS    0x19,0           ;Skip if bit in I/O register set
L001AC:   
RJMP    PC-0x0003        ;Relative jump

L001AD:   
MOV     R25,R19          ;Copy register
L001AE:   
CLR     R19              ;Clear Register
L001AF:   
CLR     R17              ;Clear Register
L001B0:   
CLR     R18              ;Clear Register
L001B1:   
CPI     R25,0x11         ;Compare with immediate
L001B2:   
BRCS    PC+0x03          ;Branch if carry set
L001B3:   
LSR     R25              ;Logical shift right
L001B4:   
LDI     R17,0x01         ;Load immediate
L001B5:   
MOV     R2,R25           ;Copy register
L001B6:   
LSR     R2               ;Logical shift right
L001B7:   
MOV     R3,R2            ;Copy register
L001B8:   
ADD     R2,R25           ;Add without carry
L001B9:   
LSL     R25              ;Logical Shift Left
L001BA:   
ADD     R3,R25           ;Add without carry
L001BB:   
CPI     R17,0x01         ;Compare with immediate
L001BC:   
BREQ    PC+0x05          ;Branch if equal
L001BD:   
CP      R19,R2           ;Compare
L001BE:   
BRGE    PC+0x27          ;Branch if greater or equal, signed
L001BF:   
SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001C0:   
RJMP    PC-0x0003        ;Relative jump

L001C1:   
CLR     R19              ;Clear Register
L001C2:   
LDI     R16,0x0C         ;Load immediate
L001C3:   
CP      R19,R2           ;Compare
L001C4:   
BRCS    PC-0x01          ;Branch if carry set
L001C5:   
SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001C6:   
RJMP    PC+0x000A        ;Relative jump

L001C7:   
CLC                      ;Clear Carry
L001C8:   
ROL     R17              ;Rotate Left Through Carry
L001C9:   
ROL     R18              ;Rotate Left Through Carry
L001CA:   
CP      R19,R3           ;Compare
L001CB:   
BRGE    PC+0x1A          ;Branch if greater or equal, signed
L001CC:   
SBIS    0x19,0           ;Skip if bit in I/O register set
L001CD:   
RJMP    PC-0x0003        ;Relative jump

L001CE:   
CLR     R19              ;Clear Register
L001CF:   
RJMP    PC+0x0009        ;Relative jump

L001D0:   
SEC                      ;Set Carry
L001D1:   
ROL     R17              ;Rotate Left Through Carry
L001D2:   
ROL     R18              ;Rotate Left Through Carry
L001D3:   
CP      R19,R3           ;Compare
L001D4:   
BRGE    PC+0x11          ;Branch if greater or equal, signed
L001D5:   
SBIC    0x19,0           ;Skip if bit in I/O register cleared
L001D6:   
RJMP    PC-0x0003        ;Relative jump

L001D7:   
CLR     R19              ;Clear Register
L001D8:   
DEC     R16              ;Decrement
L001D9:   
BRNE    PC-0x16          ;Branch if not equal
L001DA:   
MOV     R25,R17          ;Copy register
L001DB:   
ROL     R25              ;Rotate Left Through Carry
L001DC:   
ROL     R18              ;Rotate Left Through Carry
L001DD:   
ROL     R25              ;Rotate Left Through Carry
L001DE:   
ROL     R18              ;Rotate Left Through Carry
L001DF:   
BST     R18,5            ;Bit store from register to T
L001E0:   
BLD     R17,7            ;Bit load from T to register
L001E1:   
BST     R18,6            ;Bit store from register to T
L001E2:   
BLD     R17,6            ;Bit load from T to register
L001E3:   
ANDI    R18,0x1F         ;Logical AND with immediate
L001E4:   
RJMP    PC+0x0003        ;Relative jump

L001E5:   
SER     R17              ;Set Register
L001E6:   
SER     R18              ;Set Register
L001E7:   
POP     R24              ;Pop register from stack
L001E8:   
OUT     0x39,R24         ;Out to I/O location
L001E9:   
POP     R24              ;Pop register from stack
L001EA:   
OUT     0x25,R24         ;Out to I/O location
L001EB:   
POP     R24              ;Pop register from stack
L001EC:   
OUT     0x3F,R24         ;Out to I/O location
L001ED:   
POP     R25              ;Pop register from stack
L001EE:   
POP     R24              ;Pop register from stack
L001EF:   
POP     R3               ;Pop register from stack
L001F0:   
POP     R2               ;Pop register from stack
L001F1:   
POP     R21              ;Pop register from stack
L001F2:   
POP     R20              ;Pop register from stack
L001F3:   
POP     R19              ;Pop register from stack
L001F4:   
POP     R16              ;Pop register from stack
L001F5:   
RET                      ;Subroutine return

