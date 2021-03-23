cmake_minimum_required(VERSION 3.17)
project(MazeRunner)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(spdlog REQUIRED)

configure_file(BuildConfig.h.in BuildConfig.h)

include_directories(PUBLIC
        ${PROJECT_BINARY_DIR}
        /usr/local/include
        include
        vendor
        /usr/local/Cellar/glew/2.2.0_1/include
        vendor/imgui
        )
link_libraries(
        OpenGL::GL
        glfw
        spdlog::spdlog
        /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib
)

set(VENDOR_FILES
        vendor/imgui/imconfig.h
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui.h
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_internal.h
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h
        vendor/imgui/imstb_truetype.h

        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_glfw.h
        vendor/imgui/backends/imgui_impl_opengl3.cpp
        vendor/imgui/backends/imgui_impl_opengl3.h)

set(INCLUDE_FILES
        src/engine/Log.cpp include/engine/Log.h
        src/engine/Application.cpp include/engine/Application.h
        include/engine/GLImport.h
        src/engine/model/Model.cpp include/engine/model/Model.h
        src/engine/model/Shader.cpp include/engine/model/Shader.h
        src/engine/scene/Camera.cpp include/engine/scene/Camera.h
        src/engine/Utility.cpp include/engine/Utility.h
        include/engine/scene/Gui.h src/engine/scene/Gui.cpp
        src/engine/scene/Scene.cpp include/engine/scene/Scene.h
        include/engine/event/Event.h
        src/engine/event/KeyEvent.cpp include/engine/event/KeyEvent.h
        include/engine/event/IEvent.h src/engine/event/IEvent.cpp
        src/engine/event/ScrollEvent.cpp include/engine/event/ScrollEvent.h
        src/engine/event/MouseEvent.cpp include/engine/event/MouseEvent.h)

set(APPLICATION_FILES
        src/MazeGenerator.cpp include/MazeGenerator.h
        src/Cell.cpp include/Cell.h
        src/PlayerCamera.cpp include/PlayerCamera.h
        src/MazeRunner.cpp include/MazeRunner.h
        src/OpeningGui.cpp include/OpeningGui.h
        src/EscGui.cpp include/EscGui.h
        src/MainScene.cpp include/MainScene.h
        BuildConfig.h.in)

add_executable(MazeRunner ${INCLUDE_FILES} ${APPLICATION_FILES} ${VENDOR_FILES})