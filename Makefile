FILE = main
ARGS = 
FLAGS = -lglut -lGLU -lGL -Wall -Wextra
HEADERS = libs/menu.cpp libs/drawings.cpp

all:
	g++ $(FILE).cpp -o app $(FLAGS) $(HEADERS)

run:
	./app $(ARGS)

.PHONY: clean
clean:
	rm -f app
