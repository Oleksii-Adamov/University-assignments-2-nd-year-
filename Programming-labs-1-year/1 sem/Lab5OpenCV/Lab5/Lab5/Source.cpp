/*
Знайти і підключити до проекту сторонню бібліотеку для роботи з зображеннями. 
Зчитати деяке зображення та: повернути його на 90 градусів за годинниковою стрілкою і зберегти; знайти середнє значення кольору всіх пікселів зображення.

Використовую бібліотеку https://sourceforge.net/projects/opencvlibrary/files/opencv-win/
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
int main()
{
    std::string input;
    std::cout << "Enter image path\n";
    std::cin >> input;
    int dot = input.find('.');
    std::string extension = input.substr(dot,input.size()-dot);
    cv::Mat src = cv::imread(input);
    if (src.empty()) { std::cout << "Error loading image" << std::endl; return 0; }
    cv::Mat dst;
    cv::rotate(src, dst, cv::ROTATE_90_CLOCKWISE);
    double blue = 0, green = 0, red = 0;
    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            cv::Vec3b color = dst.at<cv::Vec3b>(i, j);
            blue += color.val[0];
            green += color.val[1];
            red += color.val[2];
        }
    }
    double number_of_pixels = dst.total();
    blue /= number_of_pixels;
    green /= number_of_pixels;
    red /= number_of_pixels;
    std::cout << "Avarage colour is: " << "blue:" << blue << " green: " << green << " red: " << red << "\n";
    cv::Scalar avarage = cv::mean(dst);
    std::cout << "Avarage colour is " << "blue:" << avarage[0] << " green: " << avarage[1] << " red: " << avarage[2] << "\n";
    cv::imwrite("Result" + extension, dst);
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    return 0;
}
// D:\\Images/symbols.jpg
// D:\\Images/Waterfall.jpg
// D:\\Images/index.jpg