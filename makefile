.PHONY : win clean
win :
	cl /W4 /EHsc /I\src src\*.cpp /link /out:build\program.exe
	nmake clean
	
clean :
	del *.obj
	del *.o
