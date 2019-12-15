//Реализация фрактала Множество Мандельброта
// Библиотеки CUDA и OpenCV
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#define HEIGHT 512 // Кратность block_size.y
#define WIDTH 512 // Кратность block_size.x
#define MAX_ITER 10000

// Функция множества Мандельброта
void mandelbrotGPU(uchar*);
__global__ void calc(char* image_buffer);


#define cudaAssertSuccess(ans)\
{ _cudaAssertSuccess((ans), __FILE__, __LINE__); }

// Функция Assert’а
inline void _cudaAssertSuccess(cudaError_t code, char *file, int line) {
    if (code != cudaSuccess) {
        fprintf(stderr,"_cudaAssertSuccess: %s %s %d\n", cudaGetErrorString(code), file, line);
        exit(code);
    }
}

int main(int argc, char** argv) {
    // Рендеринг множества
    cv::Mat image_output = cv::Mat(WIDTH, HEIGHT, CV_8UC1);
    // image* image_output = cvCreateImage(cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U,1);
    mandelbrotGPU(image_output.data);
    cv::namedWindow("GPU", 256);
    cv::imshow("GPU", image_output);
    cv::waitKey();
}

// Работа GPU с множеством Мандельброта
void mandelbrotGPU(uchar* image_buffer) {
    char* d_image_buffer;
    cudaAssertSuccess(cudaMalloc(&d_image_buffer, WIDTH * HEIGHT));
    dim3 block_size(16, 16);
    dim3 grid_size(WIDTH / block_size.x, HEIGHT / block_size.y);
    calc<<<grid_size, block_size>>>(d_image_buffer);
    cudaAssertSuccess(cudaPeekAtLastError());
    cudaAssertSuccess(cudaDeviceSynchronize());
    cudaAssertSuccess(cudaMemcpy(image_buffer, d_image_buffer, HEIGHT * WIDTH,
    cudaMemcpyDeviceToHost));
    cudaAssertSuccess(cudaFree(d_image_buffer));
}

__global__ void calc(char* image_buffer) {
    int row = blockIdx.y * blockDim.y + threadIdx.y; // WIDTH
    int col = blockIdx.x * blockDim.x + threadIdx.x; // HEIGHT
    int idx = row * WIDTH + col;
    if(col >= WIDTH || row >= HEIGHT) 
        return;
    float x0 = ((float)col / WIDTH) * 3.5f - 2.5f;
    float y0 = ((float)row / HEIGHT) * 3.5f - 1.75f;
    float x = 0.0f;
    float y = 0.0f;
    int iter = 0;
    float xtemp;
    // Основная часть построения множества Мандельброта
    while((x * x + y * y <= 4.0f) && (iter < MAX_ITER)) {
        xtemp = x * x - y * y + x0;
        y = 2.0f * x * y + y0;
        x = xtemp;
        iter++;
    }

    // Цвет рендеринга
    int color = iter * 5;
    if (color >= 256) color = 0;
    image_buffer[idx] = color;
}