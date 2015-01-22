CC		= gcc
CXX		= g++
CXXFLAGS	= -g -std=c++11 -Wall
TARGET	= calculator

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

.PHONY: run
run: $(TARGET)
	@python3 runtests.py

.PHONY: diff
diff: $(TARGET)
	python3 runtests.py | diff - output.txt

.PHONY: clean
clean:
	rm -f *.o *~ $(TARGET)
	rm -rf *.dSYM
