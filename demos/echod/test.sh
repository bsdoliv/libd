#!/bin/sh

while sleep .01; do echo GET / HTTP/1.1 | nc localhost 8080; done
