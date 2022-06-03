.section .text
.globl sign
.type sign, @function
sign:
	# return (t>0) ? 1 : (t==0)? 0 : -1;

	blt zero, a0, greater_than  # if t > 0, return 1
	beq zero, a0, equal		    # if t == 0 , return 0
	li a0, -1					# else return -1
	j exit

	greater_than:
	li a0, 1
	j exit

	equal:
	li a0, 0
	j exit

	exit:
	ret

unlesslabel:
	addi sp, sp, -52
	sw ra, 0(sp) 
	# save ra reg
    sw s0, 4(sp)
    #store s0
    sw s1, 8(sp)
    #store s1
    sw s2, 12(sp)
    #store s2
    sw s3, 16(sp)
    #store s3
    sw s4, 20(sp)
    #store s4
    sw s5, 24(sp)
    #store s5
    sw s6, 28(sp)
    #store s6
    sw s7, 32(sp)
    #store s6
    sw s8, 36(sp)
    #store s6
    sw s9, 40(sp)
    #store s9
    sw s10, 44(sp)
    #store s6
    sw s11,48(sp)
    #store s11
	call Inp_init 
	# Inp_init();
	call Adc_init 
	# Adc_init();
	call Lcd_Init 
	# Lcd_Init();

	
	lw ra, 0(sp) 
	# save ra reg
    lw s0, 4(sp)
    #store s0
    lw s1, 8(sp)
    #store s1
    lw s2, 12(sp)
    #store s2
    lw s3, 16(sp)
    #store s3
    lw s4, 20(sp)
    #store s4
    lw s5, 24(sp)
    #store s5
    lw s6, 28(sp)
    #store s6
    lw s7, 32(sp)
    #store s6
    lw s8, 36(sp)
    #store s6
    lw s9, 40(sp)
    #store s9
    lw s10, 44(sp)
    #store s6
    lw s11,48(sp)
    #store s11
    addi sp, sp, 52
	ret 
	# return
