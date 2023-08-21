FROM ubuntu:20.04

RUN useradd -ms /bin/bash compiler

RUN apt-get update && apt-get install -y build-essential

ENV LANG en_US.utf8

MKDIR ~/workspace

USER compiler
WORKDIR /home/compiler

COPY . ~/
WORKDIR ~/


