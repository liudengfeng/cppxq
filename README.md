# cppxq

利用`cpp`提速中国象棋扩展包


## 前提条件
- 在虚拟机或容器实例上安装vcpkg包管理器
- 安装目录为`~/src/`
- 在vcpkg中安装外部包 `./vcpkg install fmt gtest pybind11`


## install 

```bash
pip install --upgrade setuptools
git clone https://github.com/liudengfeng/cppxq.git
# With the setup.py file included in this example, 
# the pip install command will invoke CMake and build the pybind11 module as specified in CMakeLists.txt.
pip install ./cppxq

# test 
pip install pytest pytest-html
```