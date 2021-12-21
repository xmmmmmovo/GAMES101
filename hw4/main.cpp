#include <chrono>
#include <functional>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

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
        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;

        // 插值
        // 这里不像hw2里面那样全屏绘制所以插值方法不一样
        auto l = std::floor(point.x);
        // opencv 上下颠倒
        auto top = std::floor(point.y);

        // 刚好在中间就啥都不用管
        if (point.x == l + 0.5 && point.y == top + 0.5) { continue; }

        // 判断横纵覆盖方向
        int hd = point.x - l < 0.5f ? -1 : 1;
        int vd = point.y - top < 0.5f ? -1 : 1;

        // 相对原点
        auto p0 = cv::Point2f(l + 0.5f, top + 0.5f);

        // 周围三个像素: 自己所在像素，以point为中心覆盖的三个像素
        std::vector<cv::Point2f> aroundp = {
                cv::Point2f(p0.x + hd * 1.0f, p0.y),
                cv::Point2f(p0.x, p0.y + vd * 1.0f),
                cv::Point2f(p0.x + hd * 1.0f, p0.y + vd * 1.0f)};

        // 算离原点距离
        auto pd           = p0 - point;
        auto p2p0distance = sqrt(pd.x * pd.x + pd.y * pd.y);

        for (auto &ap : aroundp) {
            auto tmpp         = ap - point;
            auto ap2pdistance = sqrt(tmpp.x * tmpp.x + tmpp.y * tmpp.y);
            // 用了简单的比例关系 可能不需要光强类似的公式
            auto percent = p2p0distance / ap2pdistance;

            // 这里直接用引用 就不用再取浪费性能了
            cv::Vec3b &c = window.at<cv::Vec3b>(ap.y, ap.x);
            if (c[2] != 0) {
                c[2] = (c[2] + 255 * percent) / 2;
            } else {
                c[2] = 255 * percent;
            }
        }
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
