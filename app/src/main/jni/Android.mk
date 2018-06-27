#
# Copyright 2009 Cedric Priscal
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License. 
#

LOCAL_PATH := $(call my-dir)

########################### bitmapblur ###########################

include $(CLEAR_VARS)

TARGET_PLATFORM := android-14
LOCAL_MODULE    := bitmapblur
LOCAL_SRC_FILES := bitmap_blur.cpp
LOCAL_LDLIBS    += -llog -ljnigraphics -latomic

include $(BUILD_SHARED_LIBRARY)

########################### blur_sof ###########################

include $(CLEAR_VARS)

TARGET_PLATFORM := android-14
LOCAL_MODULE    := blur_sof
LOCAL_SRC_FILES := blur_sof.cpp
LOCAL_LDLIBS    += -llog -ljnigraphics -latomic

include $(BUILD_SHARED_LIBRARY)

########################### native-lib ###########################

include $(CLEAR_VARS)

TARGET_PLATFORM := android-14
LOCAL_MODULE    := native-lib
LOCAL_SRC_FILES := native-lib.cpp
LOCAL_LDLIBS    += -llog -latomic

include $(BUILD_SHARED_LIBRARY)

########################### stringutils ###########################

include $(CLEAR_VARS)

TARGET_PLATFORM := android-14
LOCAL_MODULE    := stringutils
LOCAL_SRC_FILES := stringutils.cpp
LOCAL_LDLIBS    += -llog -latomic

include $(BUILD_SHARED_LIBRARY)

########################### openssl ###########################

# 引用libcrypto.a
include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto
LOCAL_SRC_FILES := openssl/$(TARGET_ARCH_ABI)/lib/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

# 引用libssl.a
include $(CLEAR_VARS)
LOCAL_MODULE := libssl
LOCAL_SRC_FILES := openssl/$(TARGET_ARCH_ABI)/lib/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := mycrypto
LOCAL_SRC_FILES := crypto/crypto.cpp \
                   crypto/base64.cpp \
                   crypto/rsa.cpp \
                   crypto/aes.cpp \
                   crypto/digest.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/openssl/$(TARGET_ARCH_ABI)/include
TARGET_PLATFORM := android-14
# 静态库依赖
LOCAL_STATIC_LIBRARIES  := libssl libcrypto
LOCAL_LDLIBS += -latomic -lz -llog
include $(BUILD_SHARED_LIBRARY)