cmake_minimum_required(VERSION 3.11.4)      # 设置最低版本要求

# 定义项目名称和版本
project(pi-3b-c LANGUAGES C VERSION 1.0)

# 编译信息打印控制
set(CMAKE_VERBOSE_MAKEFILE OFF)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/platform/include ${PROJECT_SOURCE_DIR}/app/include)

# 添加库，指定其源文件
add_library(plat_common ${PROJECT_SOURCE_DIR}/platform/common/plat_common.c)

# 创建可执行文件目标
add_executable(main ${PROJECT_SOURCE_DIR}/main.c)

# 添加全局编译器标志
add_compile_options(-pedantic -Wall -Wextra-g)

# 链接库到可执行文件，依赖放在后面
target_link_libraries(main plat_common pthread)