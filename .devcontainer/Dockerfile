FROM ubuntu:bionic

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update \
    && apt install -y \
    build-essential \
    clang-10 libc++abi-dev libc++-dev clangd-10 \
    lldb \
    clang-format-10 clang-tidy-10 cppcheck uncrustify \
    make cmake git \
    manpages-dev \
    gdb lldb-10 valgrind \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-10 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-10 100 \
    && update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer /usr/bin/llvm-symbolizer-10 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-10 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-10 100 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-10 100 \
    # Clean up
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

COPY clang-tidy /root/.clang-tidy
COPY clang-format /root/.clang-format

ENV DEBIAN_FRONTEND=dialog
