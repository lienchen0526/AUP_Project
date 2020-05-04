main:
	g++ -o libi.so -shared -fPIC libi.c -ldl -fno-builtin
	g++ -o sandbox sandbox.c
test:
	gcc sample.c -o sample1
	gcc sample.c -o sample2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
sandbox:
	g++ -o sandbox sandbox.c
runtest:
	g++ -o libi.so -shared -fPIC libi.c -ldl
	gcc sample.c -o sample1
	gcc sample.c -o sample2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
	LD_PRELOAD=./libi.so ./sample1
	LD_PRELOAD=./libi.so ./sample2

showsym:
	gcc -o sample -g testcase.c
	nm -D sample
clean:
	rm libi.so
	rm sample1
	rm sample2
	rm sandbox
