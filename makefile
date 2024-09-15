CPPFLAGS = -lSDL2
TARGET = game

default:
	g++ -o $(TARGET) main.cpp $(CPPFLAGS)

clear:
	rm $(TARGET)

run:
	./$(TARGET)