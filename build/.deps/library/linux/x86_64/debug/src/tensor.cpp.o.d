{
    files = {
        "src/tensor.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64"
        }
    },
    depfiles_gcc = "tensor.o: src/tensor.cpp src/tensor.hpp\
"
}