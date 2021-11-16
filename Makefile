SCHEDULING_POLICIES_SRC_DIR = scheduling_policies/src
SCHEDULING_POLICIES_BUILD_DIR = scheduling_policies/build

output: build/*.o
	gcc build/*.o -o build/output
	


scheduling_policies_executables: scheduling_policies/build/*.o
	@for f in $(shell ls -1 *.o ${SCHEDULING_POLICIES_BUILD_DIR} | sed 's/\.[a-z]*//g'); do gcc ${SCHEDULING_POLICIES_BUILD_DIR}/$${f}.o -o ${SCHEDULING_POLICIES_BUILD_DIR}/$${f} ; done

scheduling_policies.o: scheduling_policies/src/*.c
	@for f in $(shell ls -1 *.c ${SCHEDULING_POLICIES_SRC_DIR} | sed 's/\.[a-z]*//g'); do gcc -c ${SCHEDULING_POLICIES_SRC_DIR}/$${f}.c -o ${SCHEDULING_POLICIES_BUILD_DIR}/$${f}.o ; done

main.o: main.c
	gcc -c main.c -o build/main.o

scheduler.o: scheduler.c
	gcc -c scheduler.c -o build/scheduler.o

file_manager.o: file_manager.c
	gcc -c file_manager.c -o build/file_manager.o


