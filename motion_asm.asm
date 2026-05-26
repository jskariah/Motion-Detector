
		; include c declarations
		.cdecls "motion.h"

        .text

					.ref motion_sensor
_motion_sensor 		.field motion_sensor


		.global ReadMotionSensorASM
		.asmfunc
ReadMotionSensorASM
		PUSH 	{LR}						; 	save link addr

		LDR		r0, _motion_sensor			;	load the motion sensor base address into r0
		LDR		r1, [r0, #4]				; 	load the lowest byte of the raw_input
		CMP		r1, #0						; 	compare the second word of motion_sensor to 0
		BNE		newInput					; 	branch to newInput iff r1>0; otherwise no new input (r0=0)
		MOV		r0, #0						;	... r0 = 0 (0=false, i.e. no new input)
		B		exit						;	jump over newInput to return.
newInput
		MOV		r0, #1						;	... r0 = 1 (1=true, i.e. new input)
exit
		;MOV		r0, #0
		POP		{PC}						; 	return to linked addr with r0 = 0 or 1
		.endasmfunc
