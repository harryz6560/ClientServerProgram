a2p1:
	gcc -o a2p1 a2p1.c -pthread
a2p2:
	gcc -o a2p2 a2p2.c
clean:
	rm -f a2p1 a2p2
tar:
	tar -cvf Zhao-a2.tar a2p1.c a2p2.c a2p2-ex1.dat Makefile testing.dat project_report.pdf fmt.man
