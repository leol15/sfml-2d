

CPP=g++ -Wall -g

INCLUDE=-IC:/MinGW/mylib/sfml/include/ -LC:/MinGW/mylib/sfml/lib/

LIB=\
	-lsfml-graphics \
	-lsfml-audio \
	-lsfml-main \
	-lsfml-network \
	-lsfml-window \
	-lsfml-system

HEADERS=RollBug.h World2D.h Critter.h Utils.h

OBJS=RollBug.o World2D.o Utils.o

default: main

world: objs Utils.h
	$(CPP) $(OBJS) $(INCLUDE) $(LIB) -o $@
	./$@

main: main.cpp objs Utils.h
	$(CPP) $< *.o -o $@ $(INCLUDE) $(LIB)
	./$@

%.o: %.cpp %.h Utils.h
	$(CPP) -c $< $(INCLUDE)


objs: $(OBJS)

clean:
	rm -f main.exe
	rm -f *.o

.PHONY: main
