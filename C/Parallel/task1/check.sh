#!./roundup

gcc   -O2 -o int int.c -lm
mpicc -O2 -o tint tint.c -lm

it_check_N10P1() {
	test `./int 10` "=" `mpirun -np 1 ./tint 10`
}

it_check_N10P2() {
	test `./int 10` "=" `mpirun -np 2 ./tint 10`
}

it_check_N10P3() {
	test `./int 10` "=" `mpirun -np 3 ./tint 10`
}

it_check_N10P7() {
	test `./int 10` "=" `mpirun -np 7 ./tint 10`
}

it_check_N10P9() {
	test `./int 10` "=" `mpirun -np 9 ./tint 10`
}

it_check_N100P2() {
	test `./int 100` "=" `mpirun -np 2 ./tint 100`
}

it_check_N100P7() {
	test `./int 100` "=" `mpirun -np 7 ./tint 100`
}
