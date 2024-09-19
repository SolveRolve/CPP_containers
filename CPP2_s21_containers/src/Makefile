ifndef VERBOSE
.SILENT:
endif
OS := $(shell uname)
CC =  --coverage -Wall -Werror -Wextra -lstdc++ -std=c++17
FLAGS = -lgtest -ftest-coverage -fprofile-arcs

ifeq ($(OS),Darwin)
	OPEN_CMD = open
else
	FLAGS += -lm -lrt 
	OPEN_CMD = xdg-open
endif

all: clean test gcov_report

test: test_list test_queue test_stack test_vector test_tree test_set test_map test_multiset test_array
	./test_array
	./test_queue
	./test_list
	./test_stack
	./test_vector
	./test_tree
	./test_set
	./test_map
	./test_multiset

s21_map.a:
	g++ $(CC) -c Map/s21_map.cc
	ar -crs s21_map.a s21_map.o
	clear

s21_array.a:
	g++ $(CC) -c Array/s21_array.cc
	ar -crs s21_array.a s21_array.o
	clear


tree_rb.a:
	g++ $(CC) -c Tree_rb/tree_rb.cc
	ar -crs tree_rb.a tree_rb.o
	clear

s21_stack.a:
	g++ $(CC) -c Stack/s21_stack.cc
	ar -crs s21_stack.a s21_stack.o
	clear

s21_queue.a:
	g++ $(CC) -c Queue/s21_queue.cc
	ar -crs s21_queue.a s21_queue.o
	clear

s21_list.a:
	g++ $(CC) -c List/s21_list.cc
	ar -crs s21_list.a s21_list.o
	clear

s21_vector.a:
	g++ $(CC) -c Vector/s21_vector.cc
	ar -crs s21_vector.a s21_vector.o
	clear

s21_multiset.a:
	g++ $(CC) -c Multiset/s21_multiset.cc
	ar -crs s21_multiset.a s21_multiset.o
	clear

s21_set.a:
	g++ $(CC) -c Set/s21_set.cc
	ar -crs s21_set.a s21_set.o
	clear

test_multiset: clean s21_multiset.a
	g++ $(CC) Multiset/test_multiset.cc s21_multiset.a $(FLAGS) -o test_multiset
	clear

test_array: clean s21_array.a
	g++ $(CC) Array/test_array.cc s21_array.a $(FLAGS) -o test_array
	clear


test_map: clean s21_map.a
	g++ $(CC) Map/test_map.cc s21_map.a $(FLAGS) -o test_map
	clear

test_tree: clean tree_rb.a
	g++ $(CC) Tree_rb/test_tree.cc tree_rb.a $(FLAGS) -o test_tree
	clear
	

test_list: clean s21_list.a
	g++ $(CC) List/test_list.cc s21_list.a $(FLAGS) -o test_list
	clear

test_stack: clean s21_stack.a
	g++ $(CC) Stack/test_stack.cc s21_stack.a $(FLAGS) -o test_stack
	clear

test_queue: clean s21_queue.a
	g++ $(CC) Queue/test_queue.cc s21_queue.a $(FLAGS) -o test_queue
	clear

test_vector: clean s21_vector.a
	g++ $(CC) Vector/test_vector.cc s21_vector.a $(FLAGS) -o test_vector
	clear
	
test_set: clean s21_set.a
	g++ $(CC) Set/test_set.cc s21_set.a $(FLAGS) -o test_set
	clear
	
gcov_report: clean test
	lcov -t "./test_array ./test_multiset ./test_tree ./test_map ./test_list ./test_stack ./test_queue ./test_vector ./test_set"  -o report.info --no-external --ignore-errors inconsistent,format,usage  -c -d .
	genhtml -o report report.info 
	$(OPEN_CMD) ./report/index.html
	clear
	rm -rf *.gcno *gcda *.gco

clean:
	rm -rf *.o *.a test_list test_queue test_stack test_vector test_tree test_set test_map test_multiset test_array
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	clang-format -style=Google -i **/*.h **/*.cc
	clear
