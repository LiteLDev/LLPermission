cmake_minimum_required(VERSION 3.24)

add_subdirectory(lib)

project(LLPermission)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES_DIR src/*.c src/*.cpp src/*.h)

add_library(LLPermission SHARED ${SRC_FILES_DIR})

target_link_libraries(LLPermission LiteLoader bds_api bds_var SymDBHelper)

target_compile_definitions(
        LLPermission PRIVATE
        NDEBUG NOMINMAX TEMPLATE_EXPORTS UNICODE WIN32_LEAN_AND_MEAN _AMD64_ _CRT_SECURE_NO_WARNINGS _UNICODE
        _USRDLL _WINDLL _WINDOWS PERMAPI_EXPORTS
)

target_compile_options(
        LLPermission PRIVATE
        /diagnostics:column /EHsc /FC /GL /MD /nologo /permissive- /sdl /utf-8 /Zc:inline /Zi
)

target_link_options(
        LLPermission PRIVATE
        /DEBUG /DLL /IGNORE:4199 /INCREMENTAL:NO /LTCG:INCREMENTAL /MANIFESTUAC:NO
        /MACHINE:X64 /NOLOGO /OPT:ICF /OPT:REF /SUBSYSTEM:CONSOLE /DELAYLOAD:bedrock_server.dll
)
