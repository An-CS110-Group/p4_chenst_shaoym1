.globl drawGnd
.type drawGnd, @function
drawGnd:



# 	addi sp, sp, -4
# 	sw ra, 0(sp)

# 	jal LCD_Fill


# 	jal LCD_Fill



# 	j exit
# 	exit:
# 	lw ra, 0(sp)
# 	addi sp, sp, 4
# 	ret


# void drawGnd() {
#     LCD_Fill(0, 65, 159, 65, BLACK);
#     LCD_Fill(0, 70, 159, 70, BLACK);
#     for (int i = 0; i < 160; ++i) {
#         if (ground[i][1]) LCD_DrawPoint(i, 65, WHITE60);
#         if (ground[i][0]) LCD_DrawPoint(i, 70, WHITE40);
#     }
# }


