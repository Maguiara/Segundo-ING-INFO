TARGET = p02Strings
OBJS = alphabet.o language.o mystring.o tools.o main.o
FLAGS = -Wall -Wextra 

$(TARGET) : $(OBJS)
	g++ $(FLAGS) $(OBJS) -o $(TARGET)

%.o : %.cc
	g++ -c $(FLAGS)  $< -o $@

.PHONY : clean
clean :
	rm -f *.o $(TARGET)