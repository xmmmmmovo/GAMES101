#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <ctime>
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>


Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0],
            0, 1, 0, -eye_pos[1],
            0, 0, 1, -eye_pos[2],
            0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle) {
    Eigen::Matrix4f model  = Eigen::Matrix4f::Identity();
    float           radian = rotation_angle * M_PI / 180.0;

    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    auto cosa = cos(radian);
    auto sina = sin(radian);
    model << cosa, -sina, 0, 0,
            sina, cosa, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
    // Students will implement this function
    Eigen::Matrix4f projection2ortho = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f ortho            = Eigen::Matrix4f::Identity();
    auto            radian           = (eye_fov * M_PI / 180.0) / 2;

    // Create the projection matrix for the given parameters.
    // Then return it.
    auto top   = abs(zNear) * tan(radian);
    auto right = top * aspect_ratio;

    ortho << 1 / right, 0, 0, 0,
            0, 1 / top, 0, 0,
            0, 0, 2 / (zNear - zFar), -(zNear + zFar) / (zNear - zFar),
            0, 0, 0, 1;
    projection2ortho << zNear, 0, 0, 0,
            0, zNear, 0, 0,
            0, 0, zNear + zFar, -zNear * zFar,
            0, 0, 1, 0;

    return ortho * projection2ortho;
}

// 绕一个向量旋转
Eigen::Matrix4f get_rotation(Vector3f axis, float angle) {
    Eigen::Matrix3f model  = Eigen::Matrix3f::Identity();
    Eigen::Matrix3f N      = Eigen::Matrix3f::Identity();
    auto            radian = angle * M_PI / 180.0;
    N << 0, -axis[2], axis[1],
            axis[2], 0, -axis[0],
            -axis[1], axis[0], 0;
    model = cos(radian) * model + (1 - cos(radian)) * axis * axis.adjoint() + sin(radian) * N;
    return Affine3f(model).matrix();
}

int main(int argc, const char **argv) {
    float              angle        = 0;
    bool               command_line = false;
    auto               t            = std::time(nullptr);
    auto               tm           = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto        time_str = oss.str();
    std::string filename = "../output/" + time_str + ".png";

    if (argc >= 3) {
        command_line = true;
        angle        = std::stof(argv[2]);// -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key         = 0;
    int frame_count = 0;

    //测试用轴
    Eigen::Vector3f test_axis = {1, 0, 1};

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        // r.set_model(get_model_matrix(angle));
        r.set_model(get_rotation(test_axis, angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        } else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
