FROM ubuntu:latest
USER root
WORKDIR /download/

RUN apt-get update
RUN apt-get install wget git make g++ libssl-dev -y

WORKDIR /usr/include/
RUN wget https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.bz2
RUN tar -xvf boost_1_70_0.tar.bz2
WORKDIR boost_1_70_0
RUN /bin/sh bootstrap.sh
RUN ./b2
WORKDIR /usr/include
RUN cp -r boost_1_70_0/boost/ .

RUN git clone https://github.com/nlohmann/json.git
RUN mv json/include/nlohmann/ /usr/include/
RUN rm -rf json

WORKDIR /bot/
COPY . .
RUN ls /usr/include/boost/
WORKDIR Release
RUN make
WORKDIR /bot/
CMD ["Release/trading", "train"]