io.o : src/io.c
	gcc -c -Wall $<

game.o : src/game.c
	gcc -c -Wall $<

record.o : src/record.c
	gcc -c -Wall $<

main.o : src/main.c
	gcc -c -Wall $<

battleship : io.o game.o record.o main.o
	gcc $^ -o battleship

run : battleship
	./battleship

clean :
	rm -f *.o tfs
