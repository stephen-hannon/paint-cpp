
CMP = g++ -std=c++11
CLASS = paint
MAIN = paintmain
EXEC = paint

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o gfx3.o -lX11 -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o 

clean:
	# rm *.o
	rm $(EXEC)

