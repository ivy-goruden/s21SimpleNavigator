CXX := gcc
CXXFLAGS := -Wall -Wextra -Werror -std=c++20
LDLIBS := -lgtest -lgtest_main -pthread
CPP_FLAGS = -lstdc++ -lm
TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(TEST_SRCS:.cpp=.o)
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := main_test.out
GCOVFLAGS := -O0 -fprofile-arcs -ftest-coverage -std=c++20
SANITIZE_FLAG = -fsanitize=address

# gcc -Wall -Wextra -Werror -std=c++20 -c src/*.cpp
# ar rcs s21_containers.a *.o
# gcc -Wall -Wextra -Werror -std=c++20 test_lib.cpp -L. -l:s21_containers.a -o test_lib.out


test_lib: s21_containers.a
	$(CXX) $(CXXFLAGS) test/test_lib.cpp -o test/test_lib.out $(CPP_FLAGS) -L. -l:s21_containers.a

s21_containers.a: $(OBJS)
	ar rcs s21_containers.a $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDLIBS) $(CPP_FLAGS)
	
tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDLIBS) $(CPP_FLAGS)

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $(TARGET) $(LDLIBS) $(CPP_FLAGS)

sanitize: clean $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(SANITIZE_FLAG) tests/main_test.cpp -o ./sanitize.out $(LDLIBS) $(CPP_FLAGS)
	./sanitize.out

valgrind: clean test
	valgrind --leak-check=yes --tool=memcheck -q ./$(TARGET)

gcov_report: clean
	$(CXX) $(GCOVFLAGS) $(TEST_SRCS) -o ./gcov_report $(LDLIBS) $(CPP_FLAGS)
	./gcov_report
	lcov --ignore-errors mismatch,unsupported,inconsistent,format --rc geninfo_unexecuted_blocks=1 -c -d . -o ./coverage.info
	lcov -r coverage.info '/usr/*' '**/tests/*' -o coverage.info
	genhtml --ignore-errors category -o ./report ./coverage.info
	xdg-open ./report/index.html

all: clean test
	./$(TARGET)

cf-check:
	@find . -type f -name "*.[ch]" -exec clang-format -i {} \;
	@find . -type f -name "*.cpp" -exec clang-format -i {} \;
	@find . -type f -name "*.hpp" -exec clang-format -i {} \;
	
clean:
	rm -f ../src/**/*.[ao] ./*.[ao] ./*.out ./*.gch
	rm -f ./gcov_report* ./coverage.info
	rm -rf report
