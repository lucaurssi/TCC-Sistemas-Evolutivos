FILE = test2
ARGS = 
FLAGS = -Wall -Wextra

all:
	g++ -c -o app.o $(FILE).cpp -I"C:\Users\lucau\Downloads\TCC-Sistemas-Evolutivos\freeglut\include"
	g++ -o app.exe app.o -L"C:\Users\lucau\Downloads\TCC-Sistemas-Evolutivos\freeglut\lib\x64" -lfreeglut -lopengl32 -Wl,--subsystem,windows

run:
	./app $(ARGS)

.PHONY: clean
clean:
	rm -f app