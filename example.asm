__R65A__
.org $0600
; 6502 test program - 100 lines
Start:  LDX #$00
InitLoop: LDA #$00
STA $0200,X
INX
CPX #$10
BNE InitLoop
; set up values in zero page
LDA #$05
STA $10    ; ValueA at $10
LDA #$07
STA $11    ; ValueB at $11
JSR AddAB
STA $12    ; Result at $12
; save result to $00 for inspection
LDA $12
STA $00
; compare result with 12
LDA $12
CMP #$0C
BEQ EqualLabel
BNE NotEqual
EqualLabel:
LDA #$01
STA $13
JMP AfterCompare
NotEqual:
LDA #$00
STA $13
AfterCompare:
; countdown using Y
LDY #$05
DecLoop: DEY
BNE DecLoop
; set flags example
LDA #$FF
STA $14
CLC
ADC #$01
STA $15
; loop to copy memory
LDX #$00
CopyLoop: LDA $0200,X
STA $0300,X
INX
CPX #$10
BNE CopyLoop
; subroutine: Add values in zero page $10 and $11, return in A
AddAB:
LDA $10
CLC
ADC $11
RTS
; subroutine: Multiply ValueA by two (shift left)
MulByTwo:
LDA $10
ASL
STA $10
RTS
; Stack push/pop example
LDA #$AA
PHA
LDA #$55
PHA
PLA
STA $20
PLA
STA $21
; Indirect jump example (uses vector at $FFFC)
JMP ($FFFC)
; Using indexed addressing to read data table
LDX #$04
LDA $0200,X
STA $40
; Bit test and branching
BIT $40
BMI NegativeBranch
BPL PositiveBranch
NegativeBranch:
LDA #$80
STA $41
JMP PostBit
PositiveBranch:
LDA #$00
STA $41
PostBit:
; simple decrement loop using Counter at $22
LDA #$03
STA $22
LoopA:
LDA $22
BEQ DoneA
SEC
SBC #$01
STA $22
JMP LoopA
DoneA:
BRK
; end of program - zero page vars: $10 ValueA, $11 ValueB, $12 Result, $13 compare flag, $14 temp, $15 temp2
