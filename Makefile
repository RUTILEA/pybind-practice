all: build test

pybind_opencv: pybind11_opencv/ndarray_converter.cpp
	g++ -fPIC -c -o pybind_opencv.o pybind11_opencv/ndarray_converter.cpp `pkg-config --cflags --libs opencv4` `python3 -m pybind11 --includes` 

build: pybind_opencv mod.cpp
	g++ -shared -std=c++17 -fPIC `python3 -m pybind11 --includes` mod.cpp pybind_opencv.o -o mod`python3-config --extension-suffix` `pkg-config --cflags --libs opencv4`

test: main.py
	@python3 main.py

clean:
	@rm ./*.so
