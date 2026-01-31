add_library(baybayin-core INTERFACE)
target_include_directories(baybayin-core
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(baybayin-core INTERFACE
        baybayin-core/norm.h
        baybayin-core/tl.h
)