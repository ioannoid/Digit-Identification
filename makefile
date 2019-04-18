.PHONY : win mac clean
win :
	cl /W4 /EHsc /I\src src\*.cpp /link /out:build\program.exe
	nmake clean

mac :
	g++ src/*.cpp -o build/GBEmulator.out
	make clean

clean :
	del *.obj
	del *.o