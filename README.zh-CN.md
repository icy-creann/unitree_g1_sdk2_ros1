# unitree_sdk2
Unitree 机器人 SDK 版本 2。

### 预构建环境
* 操作系统  (Ubuntu 20.04 LTS)
* CPU  (aarch64 和 x86_64)
* 编译器  (gcc 版本 9.4.0)

### 环境配置

在构建或运行 SDK 之前，请确保已安装以下依赖：

- CMake（版本 3.10 或更高）
- GCC（版本 9.4.0）
- Make

在 Ubuntu 20.04 上，你可以使用以下命令安装所需的软件包：

```bash
apt-get update
apt-get install -y cmake g++ build-essential libyaml-cpp-dev libeigen3-dev libboost-all-dev libspdlog-dev libfmt-dev
```

### 构建示例

要构建本仓库中的示例：

```bash
mkdir build
cd build
cmake ..
make
```

### 安装

要使用 SDK 构建你自己的应用程序，可以将 `unitree_sdk2` 安装到系统目录：

```bash
mkdir build
cd build
cmake ..
sudo make install
```

或者将 `unitree_sdk2` 安装到指定目录：

```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/unitree_robotics
sudo make install
```

注意：如果你将库安装到 `/opt/unitree_robotics` 以外的位置，需要确保该路径已添加到 `${CMAKE_PREFIX_PATH}`，以便 CMake 能通过 `find_package()` 找到它。

### 说明
更多参考信息，请访问 [Unitree 文档中心](https://support.unitree.com/home/zh/developer)。
