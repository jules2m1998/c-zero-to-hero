	.file	"variables.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zca1p0_zcd1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	G_x
	.section	.sdata,"aw"
	.align	2
	.type	G_x, @object
	.size	G_x, 4
G_x:
	.word	10
	.globl	G_y
	.align	2
	.type	G_y, @object
	.size	G_y, 4
G_y:
	.word	12
	.globl	G_z
	.section	.sbss,"aw",@nobits
	.align	2
	.type	G_z, @object
	.size	G_z, 4
G_z:
	.zero	4
	.text
	.align	1
	.globl	f
	.type	f, @function
f:
	addi	sp,sp,-48 // Reserve 48 octets sur la stack
	sd	ra,40(sp) // sauvergade de l'adresse de retour sur les 8 dernier octets
	sd	s0,32(sp) // saugarde s0 dans la stack pour une restauration a la fin de l'execution de la fonction
	addi	s0,sp,48 // sauvergade le sommet de la pile, mais je sais pas vraiment pourquoi
	mv	a5,a0 // On transmet l'argument 1 dans a5, ici je me demande si c'est pas pour pouvoir definir la valeur de retour tout en concervant le premier argument de la fonction
	sd	a1,-48(s0) // on stocke le deuxieme argument au sommet de la stack, je sais pas pourquoi ?
	sw	a5,-36(s0) // puis on stocke le premier argument juste apres
	li	a5,5 // a a5 on attribut la valeur immediate 5
	sw	a5,-20(s0) // save 4 octets in the stack so from offset 16 to 20 but why not : sw a5, 32(s0) instead ?
	lw	a5,-36(s0) // lecture de la valeur de x
	sw	a5,-24(s0) // ecriture de la valeur de x dans offser [20, 24]
	ld	a5,-48(s0) // Lecture de l'adresse de retour dans a5
	lw	a5,0(a5) // puis lecture de la valeur a retourner, je sais pas pourquoi
	lw	a4,-24(s0) // puis lecture de x
	addw	a5,a4,a5 // addition sur 4 octets de x et la valeur de retour je sais pas pourquoi
	sw	a5,-24(s0) // t += *y ended and saved
	lw	a5,-24(s0) // Lecture de t dans a5
	mv	a4,a5 // sauvegarde de t dans a4
	lw	a5,-20(s0) // lecture de la valeur de c
	addw	a5,a4,a5 // operation : t + c
	sw	a5,-24(s0) // et t = t + c
	lui	a5,%hi(G_x) // load upper immediate de G_x dans a5
	lw	a5,%lo(G_x)(a5) // I don't understand this syntax
	lw	a4,-24(s0) // ecriture de t dans a4
	addw	a5,a4,a5 // t + G_x
	sw	a5,-24(s0) // t = t + G_x
	lw	a5,-24(s0) // lecture de t dans a5
	mv	a0,a5 // ecriture de t dans a0 pour le retour
	ld	ra,40(sp) // restaure du double d'adresse de retour
	ld	s0,32(sp) // restaure of s0
	addi	sp,sp,48 // restaure de la valeur de la stac
	jr	ra // jump to the return adress
	.size	f, .-f
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32 // reverve 32 octets sur la stack
	sd	ra,24(sp) // save return adresse to the stack offset [24, 32]
	sd	s0,16(sp) // save s0 to the stack
	addi	s0,sp,32 // save the original place of the stack
	li	a5,1 // put 1 in a0
	sw	a5,-20(s0) // x = 1
	li	a5,2 // load 2 into a5
	sw	a5,-28(s0) // y = 2
	addi	a4,s0,-28 // save adresse of y for the pointer into a4, that's cool to see un assembly
	lw	a5,-20(s0) // Load the value of x into a0 to define the first argument of f
	mv	a1,a4 // put address of y into a1 as the second arg
	mv	a0,a5 // Load the arg 0, the value of x
	call	f // call of f
	mv	a5,a0 // Load the return of f into a5
	sw	a5,-24(s0) // r = f(x, &y)
	lui	a5,%hi(G_y)
	lw	a4,-24(s0) // 
	sw	a4,%lo(G_y)(a5)
	lui	a5,%hi(G_x) // load upper of G_x
	lw	a5,%lo(G_x)(a5) // load from G_x into a5
	addiw	a5,a5,5 // G_x + 5
	sext.w	a4,a5 // a4 = a5
	lui	a5,%hi(G_y) // load upper of G_y
	sw	a4,%lo(G_y)(a5) // G_y = G_x + 5
	lw	a5,-24(s0) // store r into a5
	mv	a0,a5 // move r to a0 as returned
	ld	ra,24(sp) // restaure the return adresse
	ld	s0,16(sp) // restaure s0
	addi	sp,sp,32 // restaure sp to his initial value
	jr	ra // jump to return address
	.size	main, .-main // Define the size of main, even i don't know how is this a size
	.ident	"GCC: (g1b306039a) 15.1.0" // i dont get this one
	.section	.note.GNU-stack,"",@progbits // a custom section ?
