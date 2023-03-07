# xqcpp
Chinese chess game(xiangqi) 

- [x] for WSL2
- [x] use vcpkg for acquiring and managing libraries


## install 

```bash
pip install --upgrade setuptools
git clone https://github.com/liudengfeng/xqcpp.git
# With the setup.py file included in this example, 
# the pip install command will invoke CMake and build the pybind11 module as specified in CMakeLists.txt.
pip install ./xqcpp

# test 
pip install pytest pytest-html
```