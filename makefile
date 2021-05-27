flag = -pedantic-errors -std=c++11

game_status.o: game_status.cpp game_status.h structure.h
	g++ $(flag) -g -c $<

interface.o: interface.cpp interface.h structure.h
	g++ $(flag) -g -c $<

survival.o: survival.cpp survival.h structure.h
	g++ $(flag) -g -c $<

explore.o: explore.cpp explore.h structure.h interface.h
	g++ $(flag) -g -c $<

battle.o: battle.cpp battle.h structure.h interface.h explore.h
	g++ $(flag) -g -c $<

story.o: story.cpp story.h structure.h
	g++ $(flag) -g -c $<

main.o: main.cpp game_status.h interface.h survival.h explore.h structure.h
	g++ $(flag) -g -c $<

game: main.o game_status.o interface.o survival.o explore.o battle.o story.o
	g++ $(flag) -g $^ -o $@

clean:
	rm -rf *.o

.PHONY: clean
