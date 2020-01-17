# Install BCC

## Build BCC from source - Ubuntu  

To build the toolchain from source, one needs:

* LLVM 3.7.1 or newer, compiled with BPF support (default=on)  
* Clang, built from the same tree as LLVM  
* cmake (>=3.1), gcc (>=4.7), flex, bison  
* LuaJIT, if you want Lua support  

### Install build dependencies
```
# Trusty (14.04 LTS) and older
VER=trusty
echo "deb http://llvm.org/apt/$VER/ llvm-toolchain-$VER-3.7 main
deb-src http://llvm.org/apt/$VER/ llvm-toolchain-$VER-3.7 main" | \
  sudo tee /etc/apt/sources.list.d/llvm.list
wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
sudo apt-get update

# For Bionic (18.04 LTS)
sudo apt-get -y install bison build-essential cmake flex git libedit-dev \
  libllvm6.0 llvm-6.0-dev libclang-6.0-dev python zlib1g-dev libelf-dev

# For Eon (19.10)
sudo apt install -y bison build-essential cmake flex git libedit-dev \
  libllvm7 llvm-7-dev libclang-7-dev python zlib1g-dev libelf-dev

# For other versions
sudo apt-get -y install bison build-essential cmake flex git libedit-dev \
  libllvm3.7 llvm-3.7-dev libclang-3.7-dev python zlib1g-dev libelf-dev

# For Lua support
sudo apt-get -y install luajit luajit-5.1-dev
```

### Install and compile BCC
```
git clone https://github.com/iovisor/bcc.git
mkdir bcc/build; cd bcc/build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```

# Install bpftrace

## Linux Kernel Requirements

It is recommended that you are running a Linux 4.9 kernel or higher. Some tools may work on older kernels, but these old kernels are no longer tested. To explain this requirement, these are the kernel versions where major features were added:

- 4.1 - kprobes
- 4.3 - uprobes
- 4.6 - stack traces, count and hist builtins (use PERCPU maps for accuracy and efficiency)
- 4.7 - tracepoints
- 4.9 - timers/profiling

Minor improvements have been added in later kernels, so newer than 4.9 is preferred.

Your kernel also needs to be built with the following options:

```
CONFIG_BPF=y
CONFIG_BPF_SYSCALL=y
CONFIG_BPF_JIT=y
CONFIG_HAVE_EBPF_JIT=y
CONFIG_BPF_EVENTS=y
CONFIG_FTRACE_SYSCALLS=y
```

## Ubuntu

Due to the kernel requirements Ubuntu 18.04 or newer is highly recommended.

### 18.04 and 18.10

The versions of `bcc` currently available in Ubuntu 18.04 (Bionic) and 18.10
(Cosmic) do not have all the requirements for building `bpftrace` so building
`bcc` first is required. The instructions for building `bcc` can be found
[here](https://github.com/iovisor/bcc/blob/master/INSTALL.md#install-and-compile-bcc).
The build dependencies listed below are also required for `bcc` so install those first.

Make sure `bcc` works by testing some of the shipped tools before proceeding. It
might be required to `ldconfig` to update the linker.

### 19.04 and newer

The version of `bcc` available in Ubuntu 19.04 (Disco) is new enough so
compilation is not required, install with:

```
sudo apt-get install -y libbpfcc-dev
```

### Building `bpftrace`

```
sudo apt-get update
sudo apt-get install -y bison cmake flex g++ git libelf-dev zlib1g-dev libfl-dev systemtap-sdt-dev binutils-dev
sudo apt-get install -y llvm-7-dev llvm-7-runtime libclang-7-dev clang-7
git clone https://github.com/iovisor/bpftrace
mkdir bpftrace/build; cd bpftrace/build;
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
make install
```

The bpftrace binary will be in installed in /usr/local/bin/bpftrace, and tools
in /usr/local/share/bpftrace/tools. You can change the install location using an
argument to cmake, where the default is `-DCMAKE_INSTALL_PREFIX=/usr/local`.

# For other OS, check.
1. [Installing BCC](https://github.com/iovisor/bcc/blob/master/INSTALL.md)  
2. [bpftrace Install](https://raw.githubusercontent.com/iovisor/bpftrace/master/INSTALL.md)  
