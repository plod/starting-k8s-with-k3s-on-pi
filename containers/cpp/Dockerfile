FROM ubuntu:eoan AS builder

RUN apt-get update && \
    apt-get upgrade -y && \
     DEBIAN_FRONTEND=noninteractive apt-get install -y clang cmake python3 python3-pip git

RUN  pip3 install conan

WORKDIR /root

COPY CMakeLists.txt .
COPY src src

RUN mkdir build && cd build && cmake --configure -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

FROM ubuntu:eoan

COPY --from=builder /root/build/bin/hello-world-cpp /http-server

CMD /hello-world-cpp