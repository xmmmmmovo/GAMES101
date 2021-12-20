#include <chrono>
#include <functional>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

// 4xMSAA(2 * 2)
float msaa[4][2] = {{0.25, 0.25}, {0.25, 0.75}, {0.75, 0.25}, {0.75, 0.75}};

void mouse_handler(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) {
        std::cout << "Left button of the mouse is clicked - position (" << x
                  << ", " << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) {
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = std::pow(1 - t, 3) * p_0 +
                     3 * t * std::pow(1 - t, 2) * p_1 +
                     3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points,
                             float                           t) {
    if (control_points.size() == 1) return control_points[0];
    std::vector<cv::Point2f> p;
    for (int i = 0; i < control_points.size() - 1; i++) {
        // 大概不需要move吧......
        p.emplace_back(control_points[i] +
                       ((control_points[i + 1] - control_points[i]) * t));
    }
    return recursive_bezier(p, t);
}

void msaa_bezier(const std::vector<cv::Point2f> &control_points,
                 cv::Mat                        &window) {
    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = recursive_bezier(control_points, t);
        int cnt = 0;
        // 4xmsaa
        for (int i = 0; i < 4; i++) {
            
        }
        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) {
    // recursive Bezier algorithm.
    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = recursive_bezier(control_points, t);
        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

std::function<void(const std::vector<cv::Point2f> &, cv::Mat &)>
        bezierFunciton = bezier;

int main(int argc, const char **argv) {
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    if (argc >= 1) {
        if (argc == 2 && std::string(argv[1]) == "msaa") {
            std::cout << "using msaa" << std::endl;
            bezierFunciton = msaa_bezier;
        } else if (argc == 2 && std::string(argv[1]) == "naive") {
            std::cout << "using naive" << std::endl;
            bezierFunciton = naive_bezier;
        }
    }

    int key = -1;
    while (key != 27) {
        for (auto &point : control_points) {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 4) {
            bezierFunciton(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

    return 0;
}
