all : clean main

clean: 
	rm -f  *.o

main: mySnake.o   

	g++ -o mySnake  mySnake.cpp
mySnake.o: mySnake.cpp Screen.o
	g++ -c mySnake.cpp Screen.o
Screen.o: Screen.cpp LivingArea.cpp Snake.cpp
	g++ -c Screen.o Screen.cpp LivingArea.cpp  

snakeNodeTest.o : snakeNodeTest.cpp 
	g++ -c snakeNodeTest.cpp 

dlinkedList.o : dlinkedList.h
	g++ -c dlinkedList.h
