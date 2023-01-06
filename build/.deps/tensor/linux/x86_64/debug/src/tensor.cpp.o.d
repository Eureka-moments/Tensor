{
    depfiles_gcc = "tensor.o: src/tensor.cpp src/tensor.h\
",
    files = {
        "src/tensor.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0"
        }
    }
}