{
    files = {
        "src/tensor.cpp"
    },
    depfiles_gcc = "tensor.o: src/tensor.cpp src/tensor.h\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64"
        }
    }
}