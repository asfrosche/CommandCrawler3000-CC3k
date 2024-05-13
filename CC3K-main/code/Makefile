CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = board.o character.o strategy.o dragon.o enemy.o main.o piece.o race.o treasure.o potion.o enemies/dwarf.o enemies/elf.o enemies/halfling.o enemies/human.o enemies/merchant.o enemies/orc.o items/ba.o items/bd.o items/dragonHoard.o items/merchantHoard.o items/normalPile.o items/ph.o items/rh.o items/smallPile.o items/wa.o items/wd.o races/drow.o races/goblin.o races/shade.o races/troll.o races/vampire.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
