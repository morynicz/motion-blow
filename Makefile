PROJECT=motion-blow

all: build run

build:
	sudo docker buildx build -t ${PROJECT} --build-context code=`pwd`/code .

run:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -it ${PROJECT}

startssh:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -p 2222:22 -it ${PROJECT} /usr/sbin/sshd -D

test:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -it ${PROJECT} ninja run_tests

format:
	clang-format-15 -i `find code -type f \( -iname *.hpp -o -iname *.cpp \)`

.PHONY: all build run
