//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture {
private:
    cv::Mat image_data;

public:
    Texture(const std::string &name) {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width  = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v) {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        // std::cout << "u" << u_img << " v" << v_img << std::endl;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    // 插值算法
    Eigen::Vector3f getColorBilinear(float u, float v) {
        // 这里开始就帮你做了uv变换了，不需要考虑什么x,y
        auto u_img = u * width;
        auto v_img = (1 - v) * height;

        auto umin = (int) u_img;
        auto vmin = (int) v_img;
        // 这里很想(int)(u_img + 1) 不知道效率如何
        auto umax = std::min((float) width, ceil(u_img));
        auto vmax = std::min((float) height, ceil(v_img));

        auto u01 = image_data.at<cv::Vec3b>(vmin, umin);
        auto u11 = image_data.at<cv::Vec3b>(vmin, umax);
        auto u00 = image_data.at<cv::Vec3b>(vmax, umin);
        auto u10 = image_data.at<cv::Vec3b>(vmax, umax);

        auto s = u_img - umin;
        // 注意opencv 坐标都是反着的😅
        auto t = vmax - v_img;

        auto u1 = u01 + s * (u11 - u01);
        auto u0 = u00 + s * (u10 - u00);
        auto p  = u0 + t * (u1 - u0);

        return Eigen::Vector3f(p[0], p[1], p[2]);
    }
};

#endif//RASTERIZER_TEXTURE_H
