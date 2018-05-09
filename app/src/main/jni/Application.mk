# http://crash.163.com/#news/!newsId=24

APP_ABI := armeabi
APP_PLATFORM := android-14
APP_OPTIM := release
APP_STL := c++_static
# APP_STL := gnustl_static

APP_THIN_ARCHIVE := true
APP_CPPFLAGS := -std=c++11 -fpic -fexceptions -frtti
APP_GNUSTL_FORCE_CPP_FEATURES := pic exceptions rtti