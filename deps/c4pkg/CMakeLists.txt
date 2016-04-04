add_library  (c4pkg
    src/c4pkg_install.c
    src/c4pkg_package.c
    src/c4pkg_parser.c
  )

target_link_libraries (c4pkg
    cJSON c4pkg_zip c4pkg_utils
  )
