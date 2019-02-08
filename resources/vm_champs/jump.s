.name		"Jumper"
.comment	"Jolly"

#ld		116, r16
#sti		r1, %:live, %1
#ld		%1879310724, r3
#ld		%65540, r1
#ld		60, r4
#ld		59, r5
#ld		58, r6
#ld		57, r7
#ld		56, r8
#ld		55, r9
#ld		54, r10
#ld		53, r11
#ld		52, r12
#ld		51, r13
#ld		50, r14
#ld		49, r15

#loop:		add		r1, r3, r3
#st		r4, 388
#st		r3, -4
#and		r3, %1048576, r16
#zjmp	%:loop

#live:		live	%1
#ld		%0, r3
#ld		%0, r2
#zjmp	%353

#ld		1, r16
#ld		19, r15
#live	%19
#zjmp		%430


#l2:		ld 388, r3
#		ld 4, r5
#		sti r1, %:live, %1
#		ld 1, r1

#loop:		add	r1, r3, r3
#			st r4, 388
#			st r3, -4
#			st r3, 0
#			zjmp	%:loop

#live:	live %19
#		ld 19, r16
#		st r3, 388
#		st r5, 388
#		zjmp %:loop

		ld		116, r16
		sti		r1, %:live, %1
		ld		%1879310724, r3
		ld		%65540, r1
		ld		54, r4
		ld		53, r5
		ld		52, r6
		ld		51, r7
		ld		50, r8
		ld		49, r9
		ld		48, r10
		ld		47, r11
		ld		46, r12
		ld		45, r13
		ld		44, r14
		ld		43, r15
loop:	add		r1, r3, r3
		st		r4, 388
		st		r3, -4
		and		r3, %1048576, r16
		zjmp	%:loop
live:	live	%19
		ld		%1879310724, r3
		ld		%0, r2
		zjmp	%353
