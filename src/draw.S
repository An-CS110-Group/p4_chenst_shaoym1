.data
    hs: .string "Hello, world!"

.section .text
.globl draw
.type draw, @function

draw:
    li a0, 20;
    li a1, 20;
    li a2, 15;
    li a3, 0x01F;
    jal LCD_DrawCircle

    li a0, 40;
    li a1, 0;
    li a2, 60;
    li a3, 20;
    li a4, 0xFFF;
    jal LCD_DrawRectangle;

	la t0, hs;
    li a0, 20;
    li a1, 40;
    mv a2, t0;
    li a3, 0x300;
    jal LCD_ShowString;