TARGET = p08_grammar
OBJS = Grammar.o GrammarMain.o myAlphabet.o tools.o
FLAGS = -Wall -Wextra

$(TARGET) : $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o : %.cc
	g++ -c $(FLAGS) $< -o $@

.PHONY : clean 
clean:
	rm -f *.o *.out $(TARGET)