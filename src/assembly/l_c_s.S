# # DO NOT REMOVE THIS LINE WHEN SUBMITTING
# .import input.S

.data

# Input string 1 (consisting of numbers)
# DO NOT MODIFY THIS VARIABLE
.globl str1
str1:
	.word 0 1 2 3 4


# Input string 2 (consisting of numbers)
# DO NOT MODIFY THIS VARIABLE
.globl str2
str2:
	.word 2 3 4 5

# Length of string 1
# DO NOT MODIFY THIS VARIABLE
.globl len1
len1:
	.word 5

# Length of string 2
# DO NOT MODIFY THIS VARIABLE
.globl len2
len2:
	.word 4


# .........................................
# .text  # code starts here

.globl l_c_s
.type l_c_s, @function
l_c_s:
    la a2 str1#load address
    la a3 str2#load address
    lw a4 len1#load address
    lw a5 len2#load address
    addi sp sp -12#load address
    sw ra 8(sp)#load address
    sw a2 4(sp)#l#load address
    sw a3 0(sp)


    jal func
    lw a3 0 sp#load adress
    lw a2 4 sp
    lw ra 8 sp
    addi sp sp 12

    jal Print


    li a0 10
    ecall
Print:
    mv a1 t3
    addi a0, x0, 1
	ecall # Print Result
    jr ra

func:
    add a0 x0 x0
    addi t0 x0 -1#to initialize i
    add t1 x0 x0#to initialize j
    add t2 x0 x0#to initialize num
    add t3 x0 x0#to initialize max

loop1_pre:
    addi t0 t0 1
   
loop1:
    beq t0 a4 exit # i<strlen() continue
    li t1 0
loop2:

    bge t1 a5 loop1_pre
    add t4 x0 t0 #start1=i;
    add t5 x0 t1 #int start2=j;
while_loop3:
    bge t4 a4 label1
    bge t5 a5 label1

    slli t6 t4 2 #t6 be the offset to str1
    add a2 a2 t6
    lw s1 0(a2) #be the current position_number we fetch
    sub a2 a2 t6

    slli s0 t5 2 #similar
    add a3 a3 s0 
    lw s2 0(a3) 
    sub a3 a3 s0

    bne s2 s1 label1
    addi t2 t2 1
    addi t4 t4 1
    addi t5 t5 1

    j while_loop3



    

label1: bge t3 t2 label2#if(num > max)
        add t3 x0 t2
      


label2:
        add t2 x0 x0
        addi t1 t1 1
        j loop2


# ...................... 
label3:#just ignore it never run to this region
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
# ...................... 
label4:#just ignore it never run to this region
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

# ...................... 
label5:#just ignore it never run to this region
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



exit:
    jr ra

