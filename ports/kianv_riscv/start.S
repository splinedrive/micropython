.section .init
.global main

lui sp, %hi(__stacktop);
addi sp, sp, %lo(__stacktop);

	/* call main */
	call main
  ebreak;
loop:
        j loop
.balign 4

