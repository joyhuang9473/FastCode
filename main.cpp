#include <iostream>
#include <stdio.h>

inline bool is_a_ge_zero_and_a_lt_b(int a, int b) {
    return static_cast<unsigned>(a) < static_cast<unsigned>(b);
}

template <typename Dtype>
void im2col_cpu(const Dtype* data_im, const int channels,
                const int height, const int width, const int kernel_h, const int kernel_w,
                const int pad_h, const int pad_w,
                const int stride_h, const int stride_w,
                const int dilation_h, const int dilation_w,
                Dtype* data_col) {
    const int output_h = (height + 2 * pad_h -
                          (dilation_h * (kernel_h - 1) + 1)) / stride_h + 1;
    const int output_w = (width + 2 * pad_w -
                          (dilation_w * (kernel_w - 1) + 1)) / stride_w + 1;
    const int channel_size = height * width;
    for (int channel = channels; channel--; data_im += channel_size) {
        for (int kernel_row = 0; kernel_row < kernel_h; kernel_row++) {
            for (int kernel_col = 0; kernel_col < kernel_w; kernel_col++) {
                int input_row = -pad_h + kernel_row * dilation_h;
                for (int output_rows = output_h; output_rows; output_rows--) {
                    if (!is_a_ge_zero_and_a_lt_b(input_row, height)) {
                        for (int output_cols = output_w; output_cols; output_cols--) {
                            *(data_col++) = 0;
                        }
                    } else {
                        int input_col = -pad_w + kernel_col * dilation_w;
                        for (int output_col = output_w; output_col; output_col--) {
                            if (is_a_ge_zero_and_a_lt_b(input_col, width)) {
                                *(data_col++) = data_im[input_row * width + input_col];
                            } else {
                                *(data_col++) = 0;
                            }
                            input_col += stride_w;
                        }
                    }
                    input_row += stride_h;
                }
            }
        }
    }
}
/*
 * kernel for 3-D convolution process, the number of kernel decides next chanel size
 * size is kernel_h, kernel_w, kernel_b(channels of input)
 * FMADD(1)
 * simd[A[1], A[1], A[1], A[1]]
 * simd[B1[1], B2[1], B3[1], B4[1]]
 *
 */
double* kernel(int height, int width, int channel,double* input, int kernel_h, int kernel_w, double* kernel, int stride_h, int stride_w, int pad_h,  int pad_w){
    const int output_h = (height + 2 * pad_h -( (kernel_h - 1) + 1)) / stride_h + 1;
    const int output_w = (width + 2 * pad_w -((kernel_w - 1) + 1)) / stride_w + 1;
    int size = height*width;
    for(int i = 0; i < channel*size; i += size){
        input[i];
    }
    printf("output h is %d ,output w is %d", output_h,output_w);
    double *c = new double[output_h*output_w];
    for(int i = 0; i < width+pad_w-kernel_w; i += stride_w){
        for(int j = 0; j < height+pad_h-kernel_h; j += stride_h){

        }
    }

    return c;
}
int main() {
//    double data_im[] = {7,91,9,164,
//                        87,221,66,13,
//                        29,34,1,81,
//                        4,87,72,45};
//
//    int channel = 1;
//    int height = 4;
//    int weight = 4;
//    int kernel_h = 2;
//    int kernel_w = 2;
//    int pad_h = 0;
//    int pad_w = 0;
//    int stride_h = 2;
//    int stride_w = 2;
//    int dilation_h = 1;
//    int dilation_w = 1;
//
//    double output[16];
//
//    im2col_cpu(data_im,channel,height,weight,kernel_h,kernel_w,pad_h,pad_w,stride_h,stride_w,dilation_h,dilation_w,output);
//
//    printf("%f", output[0]);
    double* a = new double (16);
    double *b = new double (4);
    kernel(4,4,64,a,2,2,b,2,2,1,1);
    return 0;
}
