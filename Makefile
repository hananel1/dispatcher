GENERATED_COUNTER_FILES = $(addsuffix .txt, $(addprefix counter, $(shell seq -f "%02g" 0 99)))

all: hw2

hw2: hw2.c
	gcc -pthread -g -Wall hw2.c -o hw2

clean:
	rm -f hw2 $(GENERATED_COUNTER_FILES)
