.name		"P.O.D."
.comment	"2007"


			sti		r1, %:loop, %1
			sti		r1, %:live, %1
			and		r1, %0, r1
loop:		live	%19
			fork	%6
			zjmp	%:loop
live:		live	%19
			zjmp	%:live
