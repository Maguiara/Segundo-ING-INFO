TARGET = p06_automata
OBJS = tools.o AutomataMain.o Estados.o Alphabet.o Automata.o 
FLAGS = -Wall -Wextra

$(TARGET) : $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o : %.cc
	g++ -c $(FLAGS) $< -o $@

.PHONY : clean 
clean:
	rm -f *.o *.out $(TARGET)