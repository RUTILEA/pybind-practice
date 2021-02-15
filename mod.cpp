#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/core.hpp>
#include "pybind11_opencv/ndarray_converter.h"

namespace py = pybind11;

int add(int a, int b) {
    return a + b;
}

cv::Mat make_array(void) {
    cv::Mat frame = (cv::Mat_<double>(3,3) << 1,2,3,4,5,6,7,8,9);
    return frame;
}


PYBIND11_MODULE(mod, m) {
    NDArrayConverter::init_numpy();
    m.doc() = "description of sample module";
    m.def("add", &add, "A function which adds two numbers");

    m.def("make_array", &make_array, "make a new array range 1 to 9");
}


