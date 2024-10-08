TARGET = p04Regex
OBJS = CodeAnalyzer_practica.o CodeAnalyzer_main.o tools.o variableHandler.o loopsHandler.o commentHandler.o structHandler.o
FLAGS = -Wall -Wextra 

$(TARGET) : $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o : %.cc
	g++ -c $(FLAGS)  $< -o $@

.PHONY : clean
clean :
	rm -f *.o $(TARGET)