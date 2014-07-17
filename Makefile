all:
	g++ main.cpp -o snake_game -lGL -lglut
	
clean:
	rm snake_game