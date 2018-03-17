## this Makefile is for generate distribution of hashtable
CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS__hash_djb2_1 = -O0
CFLAGS__hash_djb2_2  = -O0

EXEC = phonebook_hash_djb2_1 phonebook_hash_jdbm

GIT_HOOKS := .git/hooks/applied
.PHONY: all
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

SRCS_common = main.c

phonebook_hash_djb2_1: $(SRCS_common) phonebook_hash_djb2_1.c phonebook_hash_djb2_1.h
	$(CC) $(CFLAGS_common) $(CFLAGS__hash_djb2_1) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_hash_jdbm: $(SRCS_common) phonebook_hash_jdbm.c phonebook_hash_jdbm.h
	$(CC) $(CFLAGS_common) $(CFLAGS__hash_djb2_2) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c
		
		
run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_hash_jdbm && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	rm -f ./*.txt
	perf stat --repeat 1 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_hash_djb2_1
	perf stat --repeat 1 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_hash_jdbm

plot: cache-test
	gnuplot scripts/distribution_djb2.gp
	gnuplot scripts/distribution_jdbm.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate hash1.txt hash2.txt output.txt distribution_djb2.png distribution_jdbm.png