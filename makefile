main:
	g++ -o libi.so -shared -fPIC libi.c -ldl -fno-builtin
	g++ -o sandbox sandbox.c
test:
	g++ -o sample testcase.c
sandbox:
	g++ -o sandbox sandbox.c
runtest:
	g++ -o libi.so -shared -fPIC libi.c -ldl
	g++ -o sample testcase.c
	LD_PRELOAD=./libi.so ./sample

showsym:
	gcc -o sample -g testcase.c
	nm -D sample
clean:
	rm libi.so
	rm sample
	rm sandbox
