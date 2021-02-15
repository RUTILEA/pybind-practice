all: build test

build: mod.cpp
	g++ -shared -std=c++17 -fPIC `python3 -m pybind11 --includes` mod.cpp -o mod`python3-config --extension-suffix` `pkg-config --cflags --libs opencv4`

test: main.py
	@python3 main.py

clean:
	rm ./*.so
