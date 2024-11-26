TARGET = docserver
OBJS = docserver.o tools.o SafeFD.o SafeMap.o
FLAGS = -std=c++23 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -fsanitize=address,undefined,leak 

$(TARGET) : $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o : %.cc
	g++ -c $(FLAGS) $< -o $@

.PHONY : clean 
clean:
	rm -f *.o *.out $(TARGET)