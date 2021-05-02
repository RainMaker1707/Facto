.PHONY: build lunch_tests help delbuild
.SILENT:
.DEFAULT_GOAL = build

#VAR
FLAGS_BUILD =
FILEIN =
FILEOUT =
THREADNBR =

# ====================================================Help============================================================
# code found here : https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html

help:
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-20s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

# ====================================================================================================================


build: fact build_test## Build the entire project

test: build_test
	echo "Running tests"
	./test -v
	rm test
	echo "SUCCESS"


fact: main.c ## Build the file Main
	gcc main.c -o fact ./ListTool.c ./FileTool.c ./Primes.c ./ArrayTool.c -lpthread -lm -std=c99
	echo "Build main : SUCCESS"

fact2: main2.c ## Build the file Main
	gcc main2.c -o fact2 ./ListTool.c ./FileTool.c ./Primes2.c ./ArrayTool.c -lpthread -lm -std=c99
	echo "Build main2 : SUCCESS"

build_test: TestFunctions.c ## Build the tests file
	gcc TestFunctions.c -o test ./ListTool.c ./FileTool.c ./Primes.c ./ArrayTool.c -lpthread -lm -lcunit -std=c99
	echo "Build tests : SUCCESS"

globaltest: TestGlobal.c
	echo "Building and running Global Tests"
	gcc TestGlobal.c -o testg -lpthread -lm -lcunit -std=c99
	./testg
	echo "Tests finished"

fast_run:
	./fact -N 4 Ressources/test/in_test.txt fastOut.txt
	echo "Fast run finished"

fast_run2:
	./fact2 -N 4 Ressources/test/in_test.txt fastOut2.txt
	echo "Fast run finished"

run: ## Run the main with the arguments pattern "-N X" where X is a threads number between 1 and X FILEIN are FILE OUT are explicit
	./fact $(THREADNBR) $(FILEIN) $(FILEOUT) -std=c99

clean:  ## DELETE all files build
	touch fact fact2 test fastOut.txt fastOut2.txt
	rm fact fact2 test fastOut.txt fastOut2.txt
	echo "Delete successfully"

#Tests
launch_test:
	valgrind --xml=yes --xml-file="valgrind.xml" --leak-check=full ./test
	cppcheck --enable=all --inconclusive --xml --xml-version=2 --suppress=missingIncludeSystem TestFunctions.c 2> cppcheck.xml
	echo "CPP Check SUCCESS"
