add_library( bitmapblur
             SHARED
             bitmap_blur.cpp )

target_link_libraries( bitmapblur
                       jnigraphics
                       ${log-lib} )
