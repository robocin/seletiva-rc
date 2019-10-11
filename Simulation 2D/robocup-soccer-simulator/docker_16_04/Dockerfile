#
# RoboCIn Soccer Simulator 2d
# Author: Heitor Rapela Medeiros
# This file need to be inside this repository, to copy all lib dependencies: https://github.com/robocin/simulation-2d
# Build command: docker build . -t "simulator2d:core"
# Run command: docker run -it --rm -e DISPLAY=${DISPLAY} -e QT_X11_NO_MITSHM=1 -v /tmp/.X11-unix:/tmp/.X11-unix --name=server --net mynet simulator2d:core
#


# Pull base image.
FROM ubuntu:16.04

# Install.
RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y build-essential && \
  apt-get install -y software-properties-common && \
  apt-get install -y byobu curl git htop man unzip vim wget python-pip libqt4-dev libxt-dev iputils-ping && \
  rm -rf /var/lib/apt/lists/*

# When was together, there was an error installing flex and bison
# So I changed to install separated
RUN apt-get update && apt-get install -y flex bison gcc make automake libtool libboost-all-dev libboost-dbg
RUN apt-get install -y libaudio-dev libpng-dev libxi-dev libglib2.0-dev libfontconfig-dev libxrender-dev 
RUN mkdir /simulation-2d
COPY . /root/simulation-2d

WORKDIR /root/simulation-2d/rcssserver
RUN ./bootstrap
RUN ./configure 
RUN make
RUN make install

WORKDIR /root/simulation-2d/rcssmonitor
RUN ./bootstrap
RUN ./configure 
RUN make
RUN make install

WORKDIR /root/simulation-2d/rcsslogplayer
RUN ./bootstrap
RUN ./configure 
RUN make
RUN make install


WORKDIR /root/simulation-2d/rcssserver/libs
COPY ./libs/* /usr/lib/

RUN apt-get install -qqy x11-apps
ENV DISPLAY :0
CMD xeyes


# Set environment variables.
ENV HOME /root

# Define working directory.
WORKDIR /root

# Define default command.
CMD ["bash"]