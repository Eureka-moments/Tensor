{
    files = {
        "src/main.cpp"
    },
    depfiles_gcc = "main.o: src/main.cpp src/tensor.h\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-DNDEBUG"
        }
    }
}