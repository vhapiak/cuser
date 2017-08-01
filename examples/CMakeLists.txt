function(add_example name source)
    add_executable(${name} ${source})
    target_link_libraries(${name}
        PRIVATE ${CUSER}
        PRIVATE nlohmann_json
        )
endfunction(add_example)

add_example(serialize_enum_static serializeEnumStatic.cpp)
add_example(serialize_enum_dynamic serializeEnumDynamic.cpp)
