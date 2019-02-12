	.file	"test.c"
	.intel_syntax noprefix
	.text
	.globl	test
	.type	test, @function
test:
.LFB2:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	mov	DWORD PTR m.2632, 0
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR curr.2627, eax
	jmp	.L2
.L3:
	mov	eax, DWORD PTR curr.2627
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR curr.2627, eax
	mov	eax, DWORD PTR m.2632
	add	eax, 1
	mov	DWORD PTR m.2632, eax
.L2:
	mov	eax, DWORD PTR curr.2627
	test	eax, eax
	jne	.L3
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR temp.2626, eax
	mov	DWORD PTR n.2633, 1
.L23:
	mov	DWORD PTR curr.2627, OFFSET FLAT:temp.2626
	mov	eax, DWORD PTR temp.2626
	mov	DWORD PTR ptr1.2628, eax
	jmp	.L4
.L20:
	mov	eax, DWORD PTR ptr1.2628
	mov	DWORD PTR ptr2.2629, eax
	mov	DWORD PTR i.2634, 0
	jmp	.L5
.L7:
	mov	eax, DWORD PTR i.2634
	add	eax, 1
	mov	DWORD PTR i.2634, eax
	mov	eax, DWORD PTR ptr2.2629
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR ptr2.2629, eax
.L5:
	mov	edx, DWORD PTR i.2634
	mov	eax, DWORD PTR n.2633
	cmp	edx, eax
	jnb	.L6
	mov	eax, DWORD PTR ptr2.2629
	test	eax, eax
	jne	.L7
.L6:
	mov	eax, DWORD PTR ptr2.2629
	mov	DWORD PTR ptr4.2631, eax
	mov	DWORD PTR i.2634, 0
	jmp	.L8
.L10:
	mov	eax, DWORD PTR i.2634
	add	eax, 1
	mov	DWORD PTR i.2634, eax
	mov	eax, DWORD PTR ptr4.2631
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR ptr4.2631, eax
.L8:
	mov	edx, DWORD PTR i.2634
	mov	eax, DWORD PTR n.2633
	cmp	edx, eax
	jnb	.L9
	mov	eax, DWORD PTR ptr4.2631
	test	eax, eax
	jne	.L10
.L9:
	mov	eax, DWORD PTR ptr2.2629
	mov	DWORD PTR ptr3.2630, eax
	jmp	.L11
.L15:
	mov	eax, DWORD PTR ptr1.2628
	mov	edx, DWORD PTR [eax+4]
	mov	eax, DWORD PTR ptr3.2630
	mov	eax, DWORD PTR [eax+4]
	cmp	edx, eax
	jge	.L12
	mov	eax, DWORD PTR curr.2627
	mov	edx, DWORD PTR ptr1.2628
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR ptr1.2628
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR ptr1.2628, eax
	jmp	.L13
.L12:
	mov	eax, DWORD PTR curr.2627
	mov	edx, DWORD PTR ptr3.2630
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR ptr3.2630
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR ptr3.2630, eax
.L13:
	mov	eax, DWORD PTR curr.2627
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR curr.2627, eax
.L11:
	mov	edx, DWORD PTR ptr1.2628
	mov	eax, DWORD PTR ptr2.2629
	cmp	edx, eax
	je	.L16
	mov	edx, DWORD PTR ptr3.2630
	mov	eax, DWORD PTR ptr4.2631
	cmp	edx, eax
	jne	.L15
	jmp	.L16
.L17:
	mov	eax, DWORD PTR curr.2627
	mov	edx, DWORD PTR ptr1.2628
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR ptr1.2628
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR ptr1.2628, eax
	mov	eax, DWORD PTR curr.2627
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR curr.2627, eax
.L16:
	mov	edx, DWORD PTR ptr1.2628
	mov	eax, DWORD PTR ptr2.2629
	cmp	edx, eax
	jne	.L17
	jmp	.L18
.L19:
	mov	eax, DWORD PTR curr.2627
	mov	edx, DWORD PTR ptr3.2630
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR ptr3.2630
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR ptr3.2630, eax
	mov	eax, DWORD PTR curr.2627
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR curr.2627, eax
.L18:
	mov	edx, DWORD PTR ptr3.2630
	mov	eax, DWORD PTR ptr4.2631
	cmp	edx, eax
	jne	.L19
	mov	eax, DWORD PTR curr.2627
	mov	DWORD PTR [eax], 0
	mov	eax, DWORD PTR ptr4.2631
	mov	DWORD PTR ptr1.2628, eax
.L4:
	mov	eax, DWORD PTR ptr1.2628
	test	eax, eax
	jne	.L20
	mov	eax, DWORD PTR n.2633
	add	eax, eax
	mov	DWORD PTR n.2633, eax
	mov	edx, DWORD PTR n.2633
	mov	eax, DWORD PTR m.2632
	cmp	edx, eax
	jnb	.L26
	jmp	.L23
.L26:
	nop
	mov	eax, DWORD PTR temp.2626
	mov	DWORD PTR [ebp+8], eax
	mov	eax, DWORD PTR [ebp+8]
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	test, .-test
	.local	m.2632
	.comm	m.2632,4,4
	.local	curr.2627
	.comm	curr.2627,4,4
	.local	temp.2626
	.comm	temp.2626,8,4
	.local	n.2633
	.comm	n.2633,4,4
	.local	ptr1.2628
	.comm	ptr1.2628,4,4
	.local	ptr2.2629
	.comm	ptr2.2629,4,4
	.local	i.2634
	.comm	i.2634,4,4
	.local	ptr4.2631
	.comm	ptr4.2631,4,4
	.local	ptr3.2630
	.comm	ptr3.2630,4,4
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~14.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits
