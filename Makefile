APPLICATION_NAME = tbp
SOURCE_FOLDER = src/
MAIN_FILE = main.cpp
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system


build: main.o
	g++ $(SOURCE_FOLDER)/$(MAIN_FILE) -o $(APPLICATION_NAME) $(SFML_FLAGS)

main.o:
	g++ -c $(SOURCE_FOLDER)/$(MAIN_FILE) -o $(APPLICATION_NAME).o

clean:
	rm -rf $(APPLICATION_NAME).o $(APPLICATION_NAME)
