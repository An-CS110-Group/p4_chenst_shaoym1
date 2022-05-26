.globl drawGnd
.type drawGnd, @function
drawGnd:
















# void drawGnd() {
#     LCD_Fill(0, 65, 159, 65, BLACK);
#     LCD_Fill(0, 70, 159, 70, BLACK);
#     for (int i = 0; i < 160; ++i) {
#         if (ground[i][1]) LCD_DrawPoint(i, 65, WHITE60);
#         if (ground[i][0]) LCD_DrawPoint(i, 70, WHITE40);
#     }
# }