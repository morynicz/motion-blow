PROJECT=motion-blow

all: build run

build:
	sudo docker buildx build -t ${PROJECT} --build-context code=`pwd`/code .

run:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -it ${PROJECT}

test:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -it ${PROJECT} ninja run_tests

format:
	clang-format-15 -i code/src/* code/include/*/*

.PHONY: all build run
