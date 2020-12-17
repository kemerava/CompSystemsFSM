all: main test_machine

clean:
	rm ./main

main:
	gcc -g -o main main.c
	@echo "Finished compiling main"

test_machine: test_general_definition test_no_files_passed


test_general_definition: main
	./main ./transitions.txt ./inputs.txt
	@echo "General test finished"

test_no_files_passed: main
	./main
	@echo "Test for number of parameters finished"





