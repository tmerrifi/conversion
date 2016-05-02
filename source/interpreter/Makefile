

kwi: interpret.c bar.c
	gcc -std=c99 -O0 -g -I../udis86 -I. -L../udis86/libudis86/.libs/ -ludis86 -Wall $< -o $@

run: kwi
	LD_LIBRARY_PATH=../udis86/libudis86/.libs/ ./kwi

copy:
	cp ../decoder/bar.c .


clean:
	rm -f kwi
