	.file	"cs261labw3"
	.text
.globl main
	.type	main, @function
main:
movq %rsp, %rbp
addq $-56, %rsp
# stack and strings concept
        movabsq $8263709752659164337, %rax
        movq    %rax, 48(%rsp)
        movabsq $0xabcdef0000632520, %rax
        movq    %rax, 40(%rsp)
        movabsq $0x6425206425206425, %rax
        movq    %rax, 32(%rsp)
        movabsq $0x213f62, %rax
        movq    %rax, 24(%rsp)
        movabsq $0x616c626d6f422072, %rax
        movq    %rax, 16(%rsp)
        movabsq $0x6f66207964616572, %rax
        movq    %rax, 8(%rsp)
        movabsq $0x20756f7920657241, %rax
        movq    %rax, (%rsp)

# understanding types and data movement
movabsq $0xabcdef1234567890, %rax
movq %rax, %rcx
movb $0x5c, %al
movl $0x5c, %eax
movsbq %cl, %rax
movzbq %cl, %rax

#address calculations and destination
movq $7,%rcx
leaq 0x20(, %rcx, 4), %rdx
addq 0x20(%rsp, %rcx, 2), %rax
movl (%rsp, %rdx), %eax

#logical and arithmetic shifts
movabsq $0x9012345678abcdef, %rbx
movq %rbx, %rax
shrq $56, %rbx
sarq $56, %rax

addq $56, %rsp
ret
	.size	main, .-main
	.ident	"GCC: () 4.1.2 20080704 (Red Hat 4.1.2-51)"
	.section	.note.GNU-stack,"",@progbits
