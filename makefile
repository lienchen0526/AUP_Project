main:
	gcc -o libi.so -shared -fPIC libi.c -ldl
test:
	gcc -o sample testcase.c
runtest:
	LD_PRELOAD=./libi.so ./sample
clean:
	rm libi.so
	rm sample