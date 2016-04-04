add_library  (c4pkg_zip
    src/zipfile.c
    src/centraldir.c
    src/c4pkg_zip.c
  )

target_link_libraries (c4pkg_zip
    z c4pkg_utils
  )
