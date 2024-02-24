FROM debian:bookworm

RUN apt-get update && apt-get install -y g++-12 cmake ninja-build git libeigen3-dev libprotobuf-dev protobuf-compiler libboost-system-dev libboost-program-options-dev


WORKDIR /usr/src/myapp
RUN --mount=type=bind,source=code,target=/source set -ex && cmake -G"Ninja" -DCMAKE_CXX_COMPILER=g++-12 /source/
