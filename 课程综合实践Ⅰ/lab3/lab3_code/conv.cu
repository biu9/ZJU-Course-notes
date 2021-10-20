#include <cuda.h>

#include <iomanip>
#include <iostream>
#include <random>

const int kSize = 5000;
const int kKernelSize = 13;  // odd

#define InitRandom()                         \
  std::random_device r;                      \
  std::default_random_engine generator(r()); \
  std::uniform_real_distribution<float> distribution(0, 1e3);

void Generate(float *const a, float *const w) {
#pragma omp parallel for num_threads(8)
  for (int i = 0; i < kSize; ++i) {
    InitRandom();
    const int j_upperbound = (i + 1) * kSize; 
    for (int j = i * kSize; j < j_upperbound; ++j)
      a[j] = distribution(generator);
  }
  {
    InitRandom();
    for (int i = 0; i < kKernelSize * kKernelSize; ++i)
      w[i] = distribution(generator);
  }
}

__global__
void Conv_GPU(const float *const a, const float *const w, float *const b) {
#pragma omp parallel for num_threads(8)
  //for (int i = 0; i < kSize; ++i) {
    //for (int j = 0; j < kSize; ++j) {
      int index_i = blockIdx.x * blockDim.x + threadIdx.x;
      int index_j = blockIdx.y * blockDim.y + threadIdx.y;
//      int shared_index = threadIdx.y + threadIdx.x * 16;

int gridStride = blockDim.x * gridDim.x;

__shared__ float b_temp[256];

for(int i = index_i;i<kSize;i+=gridStride){
for(int j = index_j;j<kSize;j+=gridStride){
  if(i < kSize && j < kSize){
    b[i * kSize + j] = 0;
    int x = i - kKernelSize / 2;
    int y = j - kKernelSize / 2;

    for (int k = 0; k < kKernelSize; ++k) {
      for (int l = 0; l < kKernelSize; ++l) {
        if (!(x < 0 || x >= kSize || y < 0 || y >= kSize)){
        b_temp[threadIdx.x*16 + threadIdx.y] += a[x * kSize + y] * w[k * kKernelSize + l];
//            __syncthreads();
//            b[i * kSize + j] = b_temp[index_i * 64 + index_j];
//              b_temp[i * kSize + j] += a[x * kSize + y] * w[k * kKernelSize + l];
//              b[i * kSize + j] += a[x * kSize + y] * w[k * kKernelSize + l];
//            b[i * kSize + j] = b_temp[(blockIdx.x * blockDim.x + threadIdx.x)*32+blockIdx.y * blockDim.y + threadIdx.y];
        }
        y++;
      }
      x++;
      y -= kKernelSize;
    }
//        __syncthreads();
   b[i * kSize + j] = b_temp[threadIdx.x*16 + threadIdx.y];
   b_temp[threadIdx.x*16 + threadIdx.y] = 0;
//       __syncthreads();
  }
}
}
}

void Conv(const float *const a, const float *const w, float *const b) {
  #pragma omp parallel for num_threads(8)
    for (int i = 0; i < kSize; ++i) {
      for (int j = 0; j < kSize; ++j) {
        float conv = 0;
        int x = i - kKernelSize / 2, y = j - kKernelSize / 2;
        for (int k = 0; k < kKernelSize; ++k) {
          for (int l = 0; l < kKernelSize; ++l) {
            if (!(x < 0 || x >= kSize || y < 0 || y >= kSize))
              conv += a[x * kSize + y] * w[k * kKernelSize + l];
            y++;
          }
          x++;
          y -= kKernelSize;
        }
        b[i * kSize + j] = conv;
      }
    }
  }

void Check(const float *const a, const float *const w, float *const b) {
  auto b_std = new float[kSize * kSize];
  Conv(a, w, b_std);
  for (int i = 0; i < kSize * kSize; ++i) {
    if (abs(b[i] / b_std[i] - 1) > 1e-3 || isnanf(b[i]) || isinff(b[i])) {
      std::cout << "\x1b[31m"
                   "Wrong Answer"
                   "\x1b[0m"
                   " at "
                << i << std::endl;
      std::cout << "expected " << b_std[i] << " but found " << b[i]
                << std::endl;
      delete[] b_std;
      return;
    }
}
std::cout << "\x1b[32m"
             "Correct"
             "\x1b[0m"
          << std::endl;

delete[] b_std;
}

void Output(const float *const a, const float *const w, const float *const b) {
for (int i = 0; i < kSize; ++i) {
  for (int j = 0; j < kSize; ++j)
    std::cout << std::setw(2) << a[i * kSize + j] << ' ';
  std::cout << std::endl;
}

for (int i = 0; i < kKernelSize; ++i) {
  for (int j = 0; j < kKernelSize; ++j)
    std::cout << std::setw(2) << w[i * kKernelSize + j] << ' ';
  std::cout << std::endl;
}

for (int i = 0; i < kSize; ++i) {
  for (int j = 0; j < kSize; ++j)
    std::cout << std::setw(2) << b[i * kSize + j] << ' ';
  std::cout << std::endl;
}
}

int main() {
    auto a = new float[kSize * kSize];
    auto w = new float[kKernelSize * kKernelSize];
    auto b = new float[kSize * kSize];
  
    float *a_cuda;
    float *b_cuda;
    float *w_cuda;
  
  //  auto a_cuda = new float[kSize * kSize];
  //  auto w_cuda = new float[kKernelSize * kKernelSize];
  //  auto b_cuda = new float[kSize * kSize];
  
    size_t size = kSize * kSize * sizeof (float);
    size_t size_w = kKernelSize * kKernelSize * sizeof (float);
  
    cudaMalloc((void**)&a_cuda,size);
    cudaMalloc((void**)&b_cuda,size);
    cudaMalloc((void**)&w_cuda,size_w);
  //  cudaMallocManaged (&a, size);//===========================
  //  cudaMallocManaged (&b, size);//===========================
  //  cudaMallocManaged (&w, size_w);//=========================
  
    Generate(a, w);
  
    cudaEvent_t start_e, stop_e;
    cudaEventCreate(&start_e);
    cudaEventCreate(&stop_e);
  
    cudaEventRecord(start_e);
  
    dim3 threads_per_block (8, 8, 1); // A 16 x 16 block threads==========================
    dim3 number_of_blocks (256, 256, 1);//=============================
  
    cudaMemcpy(a_cuda,a,size,cudaMemcpyHostToDevice);
  //  cudaMemcpy((void*)b_cuda,(void*)b,size,cudaMemcpyHostToDevice);
    cudaMemcpy(w_cuda,w,size_w,cudaMemcpyHostToDevice);
  
      cudaStream_t stream;//------------------------------------------------------
      cudaStreamCreate(&stream);//-------------------------------------------------
  
    Conv_GPU <<<number_of_blocks,threads_per_block,0,stream>>> (a_cuda, w_cuda, b_cuda);//================================
  
      cudaStreamDestroy(stream);//-------------------------------------------------
  
  //  cudaMemcpy((void*)a,(void*)a_cuda,size,cudaMemcpyDeviceToHost);
    cudaMemcpy(b,b_cuda,size,cudaMemcpyDeviceToHost);
  //  cudaMemcpy((void*)w,(void*)w_cuda,size_w,cudaMemcpyDeviceToHost);
  
    cudaDeviceSynchronize();
  
    cudaEventRecord(stop_e);
    cudaEventSynchronize(stop_e);
  
    Check(a, w, b);
  
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start_e, stop_e);
    std::cout << milliseconds << " milliseconds" << std::endl;
    cudaEventDestroy(start_e);
    cudaEventDestroy(stop_e);
  
    cudaFree(a_cuda);
    cudaFree(b_cuda);
    cudaFree(w_cuda);
  
  //  cudaFree(a); //============================
  //  cudaFree(b);//=============================
  //  cudaFree(w);//=============================
  
    // Output(a, w, b);
  
    delete[] a;
    delete[] w;
    delete[] b;
    return 0;
  }
  
 