add_executable(codegen_fa_lang)
init_target(codegen_fa_lang "(codegen)")

get_filename_component(src_loc ../.. REALPATH)

nice_target_sources(codegen_fa_lang ${src_loc}
PRIVATE
    codegen/fa_lang/generator.cpp
    codegen/fa_lang/generator.h
    codegen/fa_lang/main.cpp
    codegen/fa_lang/options.cpp
    codegen/fa_lang/options.h
    codegen/fa_lang/parsed_file.cpp
    codegen/fa_lang/parsed_file.h
)

target_include_directories(codegen_fa_lang
PUBLIC
    ${src_loc}
)

target_link_libraries(codegen_fa_lang
PUBLIC
    desktop-app::codegen_common
    desktop-app::external_qt
)
