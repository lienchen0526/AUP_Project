main:
	g++ -o libi.so -shared -fPIC libi.c -ldl
test:
	g++ -o sample testcase.c
runtest:
	g++ -o libi.so -shared -fPIC libi.c -ldl
	g++ -o sample testcase.c
	LD_PRELOAD=./libi.so ./sample

showsym:
	gcc -o sample testcase.c
	nm -D sample
clean:
	rm libi.so
	rm sample