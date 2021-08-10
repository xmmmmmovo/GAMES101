CXX = clang++

.PHONY: all build run

build:
	$(CXX) $(name).cpp -std=c++11 -o build/$(name) -O3

run: build
	build/$(name)