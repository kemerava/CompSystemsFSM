all: main test_machine

clean:
	rm ./main

main:
	gcc -g -o main main.c
	@echo "Finished compiling main"
	@echo "---------------------------------\n"

test_machine: test_general_definition test_no_files_passed \
test_empty_definitions_file test_empty_inputs_file \
test_invalid_transitions_file_name test_invalid_inputs_file_name \
test_invalid_definitions test_invalid_inputs \
test_more_than_50_definitions test_more_than_250_inputs \
test_non_existing_edge test_debug_option_wrong
	@echo "Tests finished"



test_general_definition: main
	@echo "Stating general test. Success expected"
	./main ./transitions.txt ./inputs.txt
	@echo "General test finished"
	@echo "---------------------------------\n"

test_no_files_passed: main
	@echo "Stating test for number of parameters. Error expected"
	./main
	@echo "Test for number of parameters finished"
	@echo "---------------------------------\n"

test_invalid_transitions_file_name: main
	@echo "Stating test for invalid transitions file name. Error expected"
	./main ./transition.txt ./inputs.txt
	@echo "Test for invalid transitions file name finished"
	@echo "---------------------------------\n"

test_invalid_inputs_file_name: main
	@echo "Stating test for invalid inputs file name. Error expected"
	./main ./transitions.txt ./inpu.txt
	@echo "Test for invalid inputs file name finished"
	@echo "---------------------------------\n"

test_empty_definitions_file: main
	@echo "Stating test for empty definition. Error expected"
	./main ./transitions_empty.txt ./inputs.txt
	@echo "Test for empty definition finished"
	@echo "---------------------------------\n"

test_empty_inputs_file: main
	@echo "Stating test for empty finputs. Error expected"
	./main ./transitions.txt ./inputs_empty.xtx
	@echo "Test for empty finputs finished"
	@echo "---------------------------------\n"

test_invalid_definitions: main
	@echo "Stating test for invalid definition. Error expected"
	./main ./invalid_transitions.txt ./inputs.txt
	@echo "Test for invalid definition finished"
	@echo "---------------------------------\n"

test_invalid_inputs: main
	@echo "Stating test for invalid inputs. Error expected"
	./main ./transitions.txt ./invalid_inputs.txt
	@echo "Test for invalid inputs finished"
	@echo "---------------------------------\n"

test_more_than_50_definitions: main
	@echo "Stating test for more than 50 definitions. Success expected"
	./main ./transitions_over_50.txt ./inputs.txt
	@echo "Test for more than 50 definitions finished"
	@echo "---------------------------------\n"

test_more_than_250_inputs: main
	@echo "Stating test for more than 250 iputs. Success expected"
	./main ./transitions.txt ./inputs_over_250.txt
	@echo "Test for more than 250 iputs finished"
	@echo "---------------------------------\n"

test_non_existing_edge: main
	@echo "Stating test for nonexisting edge. Error expected"
	./main ./transitions_for_edges_test.txt ./inputs_for_edges_test.txt
	@echo "Test for nonexisting edge finished"
	@echo "---------------------------------\n"

test_debug_option_wrong: main
	@echo "Stating test for wrong debug option. Error expected"
	./main -t ./transitions.txt ./inputs.txt
	@echo "Test for wrong debug option finished"
	@echo "---------------------------------\n"



