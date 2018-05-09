add_library( blur_sof
             SHARED
             blur_sof.cpp )

target_link_libraries( blur_sof
                       jnigraphics
                       ${log-lib} )
