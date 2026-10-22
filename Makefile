CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRCS     = main.cpp utils.cpp storage.cpp candidate.cpp voter.cpp voting.cpp results.cpp
OBJS     = $(SRCS:.cpp=.o)
TARGET   = voting
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:

	rm -f $(OBJS) $(TARGET)
