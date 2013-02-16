CXXFLAGS += -I/usr/X11/include
LDFLAGS += -L/usr/X11/lib

SRC = main.cpp loadtex.cpp
main.exe : $(SRC:.cpp=.o)
	$(CXX) $(LDFLAGS) -lglut -lGLU -lGL -o main.exe $(SRC:.cpp=.o)

SOL = main_solution.cpp loadtex.cpp
sol : main_solution.exe
main_solution.exe : $(SOL:.cpp=.o)
	$(CXX) $(LDFLAGS) -lglut -lGLU -lGL -o main_solution.exe $(SOL:.cpp=.o)

clean:
	-\rm *.o *.exe

loadtex.o: loadtex.cpp loadtex.h bitmap.h
main.o: main.cpp float3.h loadtex.h
main_solution.o: main_solution.cpp float3.h loadtex.h
