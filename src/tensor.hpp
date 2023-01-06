#include <cstddef>
#include <cstdlib>
#ifndef TENSOR_DIMENSIONS
#define TENSOR_DIMENSIONS 20
#endif

template <typename T> auto memsize(size_t n) { return n * sizeof(T); }

template <typename T, typename... Args> auto memsize(size_t n, Args... args) {
  return n * (sizeof(T *) + memsize<T>(args...));
}
template <typename T> auto memsize(size_t *arr_mems, size_t argn) {
  size_t size = 0;
  for (size_t i = 0; i < argn - 1; i++)
    size += arr_mems[i] * sizeof(void *);
  size += arr_mems[argn - 1] * sizeof(T);
  return size;
}
auto memsize(size_t *arr_mems, size_t argn) {
  size_t size = 0;
  for (size_t i = 0; i < argn; i++)
    size += arr_mems[i];
  return size;
}

void get_args(size_t *arr, size_t *arr_pro, size_t argn, size_t n) {
  arr[argn - 1] = n;
  arr_pro[argn - 1] = arr_pro[argn - 2] * n;
}

template <typename... Args>
void get_args(size_t *arr, size_t *arr_pro, size_t argn, size_t n,
              Args... args) {
  size_t tmp = argn - sizeof...(args) - 1;
  arr[tmp] = n;
  arr_pro[tmp] = (tmp != 0) ? (arr_pro[tmp - 1] * n) : n;
  get_args(arr, arr_pro, argn, args...);
}

template <typename T, typename U>
void embed(size_t *ptr, size_t *arr_args, size_t *arr_mems, size_t argn,
           int level = 0) {
  // pointer是将被赋值的指针列表
  U **pointer = (U **)ptr;
  //提供赋值指针，指向未被赋值的下一级指针空间
  U *pointer_next = (U *)(pointer + arr_mems[level]);
  //这是目前最优赋值循环，后两种开销更大
  size_t tmp = arr_args[level + 1];
  for (int i = 0; i < arr_mems[level]; i++) {
    pointer[i] = pointer_next;
    pointer_next += tmp;
  }
  // //加设中间值将乘法变为加法
  // size_t tmp_pace = arr_args[level + 1];
  // size_t index = tmp_pace;
  // //按照第level+1级的划分长度提取指针进行链接
  // for (int i = 0; i < arr_mems[level]; i++) {
  //   pointer[i] = pointer_next + index;
  //   index+=tmp_pace;
  // }

  // for (int i = 0; i < arr_mems[level]; i++) {
  //   pointer[i] = pointer_next + i*arr_args[level+1];
  // }
  //递归进入下一层

  pointer += arr_mems[level];
  level++;
  //如果下一层不是数据层，只是指针层（区别为泛型T的字节宽度可能与指针不同）需要分别处理
  //  if (level < argn - 2)
  //   embed<T, U>(ptr, arr_args, arr_mems, argn, level);
  // else if (level == argn - 2) //下一层为数据层
  //   embed<T, T>(ptr, arr_args, arr_mems, argn, level);
  if (level < argn - 2)
    embed<T, U>((size_t *)pointer, arr_args, arr_mems, argn, level);
  else if (level == argn - 2) //下一层为数据层
    embed<T, T>((size_t *)pointer, arr_args, arr_mems, argn, level);
}

template <typename T, typename... Args> void *tensor(Args... args) {
  //提取参数信息
  int argn = sizeof...(args);
  //若为一维向量则不需要链接指针
  if (argn == 1)
    return (size_t *)malloc(memsize<T>(args...));

  //参数列表
  size_t arr_args[TENSOR_DIMENSIONS] = {0};
  //参数乘积（每一级指针层或者数据层的内存大小），为后链接做准备
  size_t arr_mems[TENSOR_DIMENSIONS] = {0};

  get_args(arr_args, arr_mems, argn, args...);

  //总内存长度
  size_t *ptr = (size_t *)malloc(memsize<T>(args...));

  //链接嵌入指针（size_t与指针字节长度相同所以选择它）
  embed<T, size_t>(ptr, arr_args, arr_mems, argn);
  return ptr;
}
template <typename TENSOR_TYPE> void *tensor(size_t *arr_args, size_t argn) {
  if (argn == 1)
    return (size_t *)malloc(arr_args[0]);

  size_t *arr_mems = (size_t *)malloc(argn * sizeof(size_t));

  arr_mems[0] = arr_args[0];
  for (size_t i = 1; i < argn; i++)
    arr_mems[i] = arr_mems[i - 1] * arr_args[i];
  size_t *ptr = (size_t *)malloc(memsize<TENSOR_TYPE>(arr_mems, argn));

  embed<TENSOR_TYPE, size_t>(ptr, arr_args, arr_mems, argn);
  return ptr;
}
