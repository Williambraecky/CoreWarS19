.name		"Jumper"
.comment	"Jolly"

			sti		r1, %:live, %1
live:		live	%19
			ld		116, r16
			ld		%1879310724, r3
			ld		%388, r3
			ld		%4, r1
			ld		35, r4
			ld		34, r5
			ld		33, r6
			ld		32, r7
			ld		31, r8
			ld		30, r9
			ld		29, r10
loop:		add		r1, r3, r3
			st		r4, 388
			st		r3, -4
			and		r3, %1048576, r16
			zjmp	%:loop
			ld		%0, r2
			zjmp	%353
