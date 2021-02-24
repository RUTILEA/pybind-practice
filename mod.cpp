#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>
#include <thread>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//struct to hold data
struct Data {
    cv::Point pt;
    double maxv;
    int angle;
};


//rotate template images
cv:: Mat rotation(double ang) {
    cv::Mat input_img = cv::imread("./images/temp_2.png");
    float x = input_img.rows;
    float y = input_img.cols;
    cv::Point2f center = cv::Point2f(x / 2, y / 2);
    cv::Mat rotated_mat = cv::getRotationMatrix2D(center, ang, 1.0);

    double rot_x = input_img.rows * std::abs(std::cos(ang)) + input_img.cols * std::abs(std::sin(ang));
    double rot_y = input_img.rows * std::abs(std::sin(ang)) + input_img.cols * std::abs(std::cos(ang));

    cv::Mat output_img;
    output_img = cv::Mat::zeros(cv::Size(rot_x, rot_y), input_img.type());
    cv::warpAffine(input_img, output_img, rotated_mat, output_img.size());

    return output_img;
}


//template matching
void checker(int start, int finish, Data* data) {
    cv::Mat target_img = cv::imread("./images/group_young_world.png");
    cv::Mat result_img;
    cv::Mat max_result_img;
    double maxv;
    double store_maxv = 0;
    int store_ang;
    cv::Point store_pt;

    for(int i = start; i < finish; i++) {
        cv::Mat temp_img = rotation(double(i));

        cv::matchTemplate(target_img, temp_img, result_img, cv::TM_CCOEFF_NORMED);

        cv::Point max;

        cv::minMaxLoc(result_img, NULL, &maxv, NULL, &max);

        if (maxv > store_maxv) {
            store_maxv = maxv;
            max_result_img = result_img;
            store_ang = i;
            store_pt = max;
        }
    }

    data->angle = store_ang;
    data->maxv = store_maxv;
    data->pt = store_pt;
}

//exec by threads
void mod_4thd() {
    Data *data_pt[4];
    Data data[4];

    data_pt[0] = &data[0];
    data_pt[1] = &data[1];
    data_pt[2] = &data[2];
    data_pt[3] = &data[3];

    std::thread thd_1(checker, 0, 90, data_pt[0]);
    std::thread thd_2(checker, 90, 180, data_pt[1]);
    std::thread thd_3(checker, 180, 270, data_pt[2]);
    std::thread thd_4(checker, 270, 360, data_pt[3]);

    thd_1.join();
    thd_2.join();
    thd_3.join();
    thd_4.join();

    std::vector<double> a = {data_pt[0]->maxv, data_pt[1]->maxv, data_pt[2]->maxv, data_pt[3]->maxv};
    std::sort(a.begin(), a.end());

    if (a[3] == data_pt[0]->maxv) {
        std::cout << "angle:\t" << data_pt[0]->angle << std::endl;
        std::cout << "x:\t" << data_pt[0]->pt.x << "\n" << "y:\t" << data_pt[0]->pt.y << std::endl;
    } else if (a[3] == data_pt[1]->maxv) {
        std::cout << "angle:\t" << data_pt[1]->angle << std::endl;
        std::cout << "x:\t" << data_pt[1]->pt.x << "\n" << "y:\t" << data_pt[1]->pt.y << std::endl;
    } else if (a[3] == data_pt[2]->maxv) {
        std::cout << "angle:\t" << data_pt[2]->angle << std::endl;
        std::cout << "x:\t" << data_pt[2]->pt.x << "\n" << "y:\t" << data_pt[2]->pt.y << std::endl;
    } else if (a[3 == data_pt[3]->maxv]) {
        std::cout << "angle:\t" << data_pt[3]->angle << std::endl;
        std::cout << "x:\t" << data_pt[3]->pt.x << "\n" << "y:\t" << data_pt[3]->pt.y << std::endl;
    }
}

void mod_1thd() {
    Data data;
    Data* data_pt;

    data_pt = &data;

    checker(1, 360, data_pt);

    std::cout << "angle:\t" << data_pt->angle << std::endl;
    std::cout << "x:\t" << data_pt->pt.x << "\n" << "y:\t" << data_pt->pt.y << std::endl;
}

PYBIND11_PLUGIN(mod) {
    pybind11::module m("mod", "mod made by pybind11");
    m.def("mod_4thd", &mod_4thd);
    m.def("mod_1thd", &mod_1thd);

    return m.ptr();
}
