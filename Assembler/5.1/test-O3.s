	.file	"test.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	test
	.type	test, @function
test:
.LFB60:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	push	edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	mov	edx, 1
	push	esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	sub	esp, 24
	.cfi_def_cfa_offset 44
	mov	DWORD PTR m.3178, 0
	mov	ebx, DWORD PTR [esp+44]
	test	ebx, ebx
	mov	DWORD PTR curr.3173, ebx
	mov	eax, ebx
	jne	.L51
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L29:
	mov	edx, ecx
.L51:
	mov	eax, DWORD PTR [eax]
	lea	ecx, [edx+1]
	test	eax, eax
	jne	.L29
	mov	DWORD PTR curr.3173, 0
	mov	DWORD PTR m.3178, edx
.L5:
	mov	esi, DWORD PTR ptr2.3175
	mov	ebp, DWORD PTR i.3180
	xor	ecx, ecx
	mov	eax, DWORD PTR ptr4.3177
	mov	edx, DWORD PTR ptr3.3176
	mov	DWORD PTR temp.3172, ebx
	mov	DWORD PTR n.3179, 1
	mov	DWORD PTR [esp], esi
	mov	esi, DWORD PTR m.3178
	mov	DWORD PTR [esp+12], ebp
	mov	BYTE PTR [esp+8], 0
	mov	ebp, ecx
	mov	DWORD PTR [esp+4], 1
	mov	DWORD PTR [esp+20], edx
	mov	edi, eax
	mov	DWORD PTR [esp+16], esi
	xor	esi, esi
.L3:
	test	ebx, ebx
	mov	eax, OFFSET FLAT:temp.3172
	je	.L6
	mov	esi, DWORD PTR [esp+4]
	mov	ecx, eax
	mov	edi, ebx
	sub	esi, 1
	mov	DWORD PTR [esp+8], esi
	.p2align 4,,10
	.p2align 3
.L22:
	mov	edx, DWORD PTR [esp+4]
	test	edx, edx
	je	.L31
	mov	esi, edi
	xor	edx, edx
	mov	ebx, DWORD PTR [esp+8]
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L8:
	add	edx, 1
	test	esi, esi
	je	.L63
.L11:
	cmp	ebx, edx
	mov	esi, DWORD PTR [esi]
	jne	.L8
	test	esi, esi
	je	.L64
	mov	ebx, 1
	mov	DWORD PTR [esp], ecx
	mov	edx, esi
	mov	ebp, DWORD PTR [esp+4]
	mov	ecx, ebx
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L66:
	test	edx, edx
	lea	ebx, [ecx+1]
	je	.L65
	mov	ecx, ebx
.L14:
	cmp	ebp, ecx
	mov	edx, DWORD PTR [edx]
	jne	.L66
	cmp	esi, edi
	mov	DWORD PTR [esp+12], ecx
	mov	ecx, DWORD PTR [esp]
	je	.L34
	mov	ebp, esi
	cmp	ebp, edx
	je	.L10
	.p2align 4,,10
	.p2align 3
.L15:
	mov	ebx, ebp
	mov	eax, edi
	mov	DWORD PTR [esp], edx
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L68:
	mov	DWORD PTR [ecx], eax
	mov	ecx, eax
	mov	eax, DWORD PTR [eax]
	mov	ebx, ebp
	cmp	eax, esi
	je	.L35
.L69:
	cmp	ebx, DWORD PTR [esp]
	mov	ebp, ebx
	mov	edi, eax
	je	.L67
.L18:
	mov	edx, DWORD PTR [ebx+4]
	cmp	DWORD PTR [eax+4], edx
	jl	.L68
	mov	eax, edi
	mov	DWORD PTR [ecx], ebx
	mov	ecx, ebx
	cmp	eax, esi
	mov	ebx, DWORD PTR [ebx]
	jne	.L69
.L35:
	mov	edx, DWORD PTR [esp]
	mov	ebp, ecx
.L7:
	mov	edi, edx
	mov	eax, ecx
	mov	ecx, ebx
	cmp	ecx, edi
	mov	DWORD PTR [esp], esi
	mov	edx, ebx
	jne	.L21
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L38:
	mov	ecx, edx
.L21:
	mov	DWORD PTR [ebp+0], ecx
	mov	edx, DWORD PTR [ecx]
	mov	ebp, ecx
	cmp	edx, edi
	jne	.L38
	mov	eax, ecx
.L20:
	test	edi, edi
	mov	DWORD PTR [ecx], 0
	jne	.L22
	mov	ebx, DWORD PTR temp.3172
	mov	DWORD PTR [esp+20], edx
	mov	ecx, 1
	mov	BYTE PTR [esp+8], 1
	mov	esi, 1
	mov	ebp, 1
.L6:
	sal	DWORD PTR [esp+4]
	mov	edx, DWORD PTR [esp+4]
	cmp	edx, DWORD PTR [esp+16]
	jb	.L3
	mov	DWORD PTR [esp+16], edi
	mov	edi, ecx
	mov	ecx, ebp
	test	cl, cl
	mov	edx, DWORD PTR [esp+20]
	mov	ebp, DWORD PTR [esp+12]
	jne	.L71
.L23:
	mov	DWORD PTR curr.3173, eax
	mov	eax, esi
	mov	DWORD PTR ptr1.3174, 0
	test	al, al
	jne	.L72
.L24:
	mov	eax, edi
	test	al, al
	je	.L25
	mov	eax, DWORD PTR [esp+16]
	mov	DWORD PTR ptr4.3177, eax
.L25:
	cmp	BYTE PTR [esp+8], 0
	je	.L26
	mov	DWORD PTR i.3180, ebp
.L26:
	mov	eax, DWORD PTR [esp+4]
	mov	DWORD PTR n.3179, eax
	add	esp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	mov	eax, ebx
	pop	ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	pop	esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	pop	edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.p2align 4,,10
	.p2align 3
.L63:
	.cfi_restore_state
	xor	ebp, ebp
	xor	edx, edx
	mov	DWORD PTR [esp+12], 0
	cmp	ebp, edx
	jne	.L15
.L10:
	mov	DWORD PTR [esp], esi
	mov	ebx, ecx
	mov	esi, edx
	mov	ecx, edx
	mov	eax, edi
.L74:
	mov	DWORD PTR [ebx], eax
	mov	edi, DWORD PTR [eax]
	mov	ebx, eax
	cmp	edi, esi
	jne	.L36
	mov	edi, edx
	mov	ebp, eax
	.p2align 4,,10
	.p2align 3
.L73:
	cmp	ecx, edi
	jne	.L21
.L70:
	mov	ecx, ebp
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L67:
	mov	edx, DWORD PTR [esp]
	mov	ebx, ecx
	mov	DWORD PTR [esp], esi
	mov	ecx, edx
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L36:
	mov	eax, edi
.L19:
	mov	DWORD PTR [ebx], eax
	mov	edi, DWORD PTR [eax]
	mov	ebx, eax
	cmp	edi, esi
	jne	.L36
	mov	edi, edx
	mov	ebp, eax
	jmp	.L73
	.p2align 4,,10
	.p2align 3
.L65:
	cmp	esi, edi
	mov	DWORD PTR [esp+12], ecx
	mov	ecx, DWORD PTR [esp]
	je	.L34
	mov	ebp, esi
	jmp	.L15
.L31:
	mov	DWORD PTR [esp+12], 0
	mov	esi, edi
	mov	edx, edi
	mov	ecx, eax
	mov	ebp, eax
	mov	ebx, edi
	jmp	.L7
.L64:
	xor	edx, edx
	mov	DWORD PTR [esp], esi
	mov	ebx, ecx
	mov	DWORD PTR [esp+12], 0
	mov	ecx, edx
	mov	esi, edx
	mov	eax, edi
	jmp	.L74
.L34:
	mov	ebp, ecx
	mov	ebx, esi
	mov	ecx, eax
	jmp	.L7
.L71:
	mov	DWORD PTR ptr3.3176, edx
	jmp	.L23
.L72:
	mov	eax, DWORD PTR [esp]
	mov	DWORD PTR ptr2.3175, eax
	jmp	.L24
	.cfi_endproc
.LFE60:
	.size	test, .-test
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.local	ptr3.3176
	.comm	ptr3.3176,4,4
	.local	ptr4.3177
	.comm	ptr4.3177,4,4
	.local	i.3180
	.comm	i.3180,4,4
	.local	ptr2.3175
	.comm	ptr2.3175,4,4
	.local	ptr1.3174
	.comm	ptr1.3174,4,4
	.local	n.3179
	.comm	n.3179,4,4
	.local	temp.3172
	.comm	temp.3172,8,4
	.local	curr.3173
	.comm	curr.3173,4,4
	.local	m.3178
	.comm	m.3178,4,4
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~14.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits
