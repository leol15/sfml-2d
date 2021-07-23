
CPP=g++ -Wall -g

INCLUDE=-IC:/MinGW/mylib/sfml/include/ -LC:/MinGW/mylib/sfml/lib/

LIB=\
	-lsfml-graphics \
	-lsfml-audio \
	-lsfml-main \
	-lsfml-network \
	-lsfml-window \
	-lsfml-system

CRITTER_HEADERS=RollBug.h
UTIL_HEADERS=Utils.h vec2.h
HEADERS=World2D.h

OBJS=RollBug.o World2D.o Utils.o util/vec2.o

default: main

main: main.cpp objs
	$(CPP) $< out/*.o $(INCLUDE) $(LIB) -o $@
	./$@

objs: outDir \
	$(addprefix out/, $(CRITTER_HEADERS:.h=.o)) \
	$(addprefix out/, $(UTIL_HEADERS:.h=.o)) \
	$(addprefix out/, $(HEADERS:.h=.o))

outDir:
	@[ ! -d "./out" ] && mkdir "out/" || echo good!

out/%.o: critter/%.cpp critter/%.h
	@echo critter $*
	$(CPP) -c $< $(INCLUDE) -o $@

out/%.o: util/%.cpp util/%.h
	$(CPP) -c $< $(INCLUDE) -o $@

out/%.o: %.cpp %.h
	@echo default $*
	$(CPP) -c $< $(INCLUDE) -o $@

clean:
	rm -f main.exe
	rm -f *.o
	rm -f out/*.o

.PHONY: main

# %:
# 	@echo making $@

