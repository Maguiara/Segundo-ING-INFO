TARGET = p06_automata_simulator
OBJS = tools.o p06_automata_simulator.o State.o AlphabetDani.o Automaton.o 
FLAGS = -Wall -Wextra

$(TARGET) : $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o : %.cc
	g++ -c $(FLAGS) $< -o $@

.PHONY : clean 
clean:
	rm -f *.o *.out $(TARGET)