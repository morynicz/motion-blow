CFLAGS = -std=gnu99
CXXFLAGS = -std=c++14

all: mot cclient cserver motionBlow

mot: main.c
	gcc main.c ${CFLAGS} -lwiringPi -o mot 

cclient: src/chat_client.cpp
	g++ src/chat_client.cpp ${CXXFLAGS} -Iinclude -lpthread -lboost_system -o cclient

cserver: src/chat_server.cpp
	g++ src/chat_server.cpp ${CXXFLAGS} -Iinclude -lpthread -lboost_system -o cserver

motionBlow: src/blow.cpp
	g++ src/blow.cpp ${CXXFLAGS} -lRTIMULib -lpthread -lboost_system -o motionBlow
