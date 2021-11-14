

output: build/*.o
	gcc build/*.o -o build/output
	
# Define objects for all sources
scheduling_policies_objs := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.c=.o))	
	

	
scheduling_policies.o: scheduling_policies/src/*.c
	gcc -c scheduling_policies/src/*.c && mv ./*.o build 

main.o: main.c
	gcc -c main.c -o build/main.o

scheduler.o: scheduler.c
	gcc -c scheduler.c -o build/scheduler.o

file_manager.o: file_manager.c
	gcc -c file_manager.c -o build/file_manager.o


