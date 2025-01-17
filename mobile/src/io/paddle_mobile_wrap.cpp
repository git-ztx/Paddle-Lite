/* Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "io/paddle_mobile_wrap.h"

#include "io/api_paddle_mobile.h"
#include "io/paddle_mobile.h"

namespace paddle_mobile {
namespace wrap {

#ifndef PADDLE_MOBILE_FPGA

// ddim class
int DDim::size() { return dims.size(); }

int64_t &DDim::operator[](int idx) {
  if (0 <= idx && idx < dims.size()) {
    return dims[idx];
  }
  int64_t non_exist = 0;
  return non_exist;
}

int64_t DDim::operator[](int idx) const {
  if (0 <= idx && idx < dims.size()) {
    return dims[idx];
  }
  return 0;
}

DDim make_ddim(const std::vector<int64_t> &dims) {
  DDim ddim;
  for (auto dim : dims) {
    ddim.dims.push_back(dim);
  }
  return ddim;
}

// tensor class
Tensor::Tensor(float *data, DDim ddim) {
  this->data_ = data;
  this->ddim_ = ddim;
}

template <typename T>
float *Tensor::data() const {
  return this->data_;
}

DDim Tensor::dims() const { return this->ddim_; }

// net class
template <typename Device>
void Net<Device>::SetThreadNum(int threads) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    engine->SetThreadNum(threads);
  }
}

template <typename Device>
PMStatus Net<Device>::Load(const std::string &dirname, const bool optimize,
                           const bool quantification, const int batch_size,
                           const bool lod_mode) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    paddle_mobile::PMStatus status =
        engine->Load(dirname, false, false, 1, true);
    return status == paddle_mobile::PMSuccess ? PMSuccess : PMUnKownError;
  }
  return PMUnKownError;
}

template <typename Device>
PMStatus Net<Device>::Load(const std::string &model_path,
                           const std::string &para_path, const bool optimize,
                           const bool quantification, const int batch_size,
                           const bool lod_mode) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    paddle_mobile::PMStatus status =
        engine->Load(model_path, para_path, false, false, 1, true);
    return status == paddle_mobile::PMSuccess ? PMSuccess : PMUnKownError;
  }
  return PMUnKownError;
}

template <typename Device>
bool Net<Device>::LoadCombinedMemory(size_t model_len, const uint8_t *model_buf,
                                     size_t combined_params_len,
                                     uint8_t *combined_params_buf,
                                     bool optimize, bool quantification,
                                     int batch_size, bool lod_mode) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    bool status =
        engine->LoadCombinedMemory(model_len, model_buf, combined_params_len,
                                   combined_params_buf, false, false, 1, true);
    return status;
  }
  return false;
}

template <typename Device>
PMStatus Net<Device>::Predict(const Tensor &input) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    auto input_data = input.data<float>();
    auto input_dims = input.dims();
    std::vector<int64_t> input_dims_as_vector = input_dims.dims;
    paddle_mobile::framework::Tensor input_inner(
        input_data, paddle_mobile::framework::make_ddim(input_dims_as_vector));
    paddle_mobile::PMStatus status = engine->Predict(input_inner);
    return status == paddle_mobile::PMSuccess ? PMSuccess : PMUnKownError;
  }
  return PMUnKownError;
}

template <typename Device>
std::vector<float> Net<Device>::Predict(const std::vector<float> &input,
                                        const std::vector<int64_t> &dims) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    auto result = engine->Predict(input, dims);
    return result;
  }
  return std::vector<float>();
}

template <typename Device>
PMStatus Net<Device>::Predict() {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    paddle_mobile::PMStatus status = engine->Predict();
    return status == paddle_mobile::PMSuccess ? PMSuccess : PMUnKownError;
  }
  return PMUnKownError;
}

template <typename Device>
void Net<Device>::Feed(const std::string &var_name, const Tensor &input) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    auto input_data = input.data<float>();
    auto input_dims = input.dims();
    std::vector<int64_t> input_dims_as_vector = input_dims.dims;
    paddle_mobile::framework::Tensor input_inner(
        input_data, paddle_mobile::framework::make_ddim(input_dims_as_vector));
    engine->Feed(var_name, input_inner);
  }
}

template <typename Device>
std::shared_ptr<Tensor> Net<Device>::Fetch(const std::string &var_name) {
  auto engine =
      (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
  if (engine != nullptr) {
    auto output_inner = engine->Fetch(var_name);
    auto ddim_inner = output_inner->dims();
    std::vector<int64_t> ddim_as_vector;
    for (int i = 0; i < ddim_inner.size(); i++) {
      ddim_as_vector.push_back(ddim_inner[i]);
    }
    auto ddim = make_ddim(ddim_as_vector);
    auto output_data = output_inner->data<float>();
    std::shared_ptr<Tensor> ptr(new Tensor(output_data, ddim));
    return ptr;
  }
  return nullptr;
}

template <typename Device>
Net<Device>::Net() {
  if (this->engine_ == nullptr) {
    PaddleMobileConfigInternal config;
    this->engine_ = new paddle_mobile::PaddleMobile<paddle_mobile::CPU>(config);
  }
}

template <typename Device>
Net<Device>::~Net() {
  if (this->engine_ != nullptr) {
    auto engine =
        (paddle_mobile::PaddleMobile<paddle_mobile::CPU> *)this->engine_;
    delete engine;
    this->engine_ = nullptr;
  }
}

template class Net<CPU>;
template float *Tensor::data<float>() const;

#endif

}  // namespace wrap
}  // namespace paddle_mobile
