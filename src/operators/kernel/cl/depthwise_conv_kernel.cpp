/* Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#ifdef DEPTHWISECONV_OP

#include "operators/kernel/depthwise_conv_kernel.h"
#include "operators/kernel/central-arm-func/depthwise_conv_arm_func.h"

namespace paddle_mobile {
namespace operators {

template <>
bool DepthwiseConvKernel<GPU_CL, float>::Init(ConvParam<GPU_CL> *param) {
  DLOG << " depthwise conv kernel init begin ";
  PADDLE_MOBILE_ENFORCE(
          param->Filter()->dims()[2] == param->Filter()->dims()[3] &&
          param->Paddings()[0] == param->Paddings()[1],
          "need equal");
  int offset = static_cast<int>(param->Filter()->dims()[2]) / 2 -
               static_cast<int>(param->Paddings()[1]);
  param->SetOffset(offset);
  this->cl_helper_.AddKernel("depth_conv_3x3", "conv_add_bn_relu_kernel.cl");
  DLOG << " depthwise conv kernel init end ";
  return true;
}

template <>
void DepthwiseConvKernel<GPU_CL, float>::Compute(const ConvParam<GPU_CL> &param) {
  auto kernel = this->cl_helper_.KernelAt(0);
  auto default_work_size = this->cl_helper_.DefaultWorkSize(*param.Output());
  int c_block = default_work_size[0];
  int w = default_work_size[1];
  int nh = default_work_size[2];
  auto input = param.Input()->GetCLImage();
  auto filter = param.Filter()->GetCLImage();
  auto output = param.Output();
  int stride = param.Strides()[0];
  int offset = param.Offset();
  int input_c = param.Input()->CBlock();
  int dilation = param.Dilations()[0];
  int input_width = param.Input()->WidthOfOneBlock();
  int input_height = param.Input()->HeightOfOneBlock();
  int output_width = param.Output()->WidthOfOneBlock();
  int output_height = param.Output()->HeightOfOneBlock();

  clSetKernelArg(kernel, 0, sizeof(int), &c_block);
  clSetKernelArg(kernel, 1, sizeof(int), &w);
  clSetKernelArg(kernel, 2, sizeof(int), &nh);
  clSetKernelArg(kernel, 3, sizeof(cl_mem), &input);
  clSetKernelArg(kernel, 4, sizeof(cl_mem), &filter);
  clSetKernelArg(kernel, 5, sizeof(cl_mem), &output);
  clSetKernelArg(kernel, 6, sizeof(int), &stride);
  clSetKernelArg(kernel, 7, sizeof(int), &offset);
  clSetKernelArg(kernel, 8, sizeof(int), &input_c);
  clSetKernelArg(kernel, 9, sizeof(int), &dilation);
  clSetKernelArg(kernel, 10, sizeof(int), &input_width);
  clSetKernelArg(kernel, 11, sizeof(int), &input_height);
  clSetKernelArg(kernel, 12, sizeof(int), &output_width);
  clSetKernelArg(kernel, 13, sizeof(int), &output_height);

  clEnqueueNDRangeKernel(this->cl_helper_.CLCommandQueue(), kernel, 3, NULL,
                         default_work_size.data(), NULL, 0, NULL, NULL);
}

template class DepthwiseConvKernel<GPU_CL, float>;

}  // namespace operators
}  // namespace paddle_mobile

#endif