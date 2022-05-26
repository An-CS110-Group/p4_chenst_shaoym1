.globl Inp_init
.type Inp_init, @function
Inp_init:
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
    #into the funtion
	addi sp, sp, -4
	sw ra, 0(sp) 
	# save ra
	li a0, 1073809408 
	# GPIOA
	li a1, 0x04 
	# GPIO_MODE_IN_FLOATING
	li a2, 0x03 
	# GPIO_OSPEED_50MHZ
	li a3, 256 
	# GPIO_PIN_8
	call gpio_init 
	# gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	
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
	# return back



    # void Inp_init(void) { gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8); }