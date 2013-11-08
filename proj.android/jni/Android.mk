LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp
  
LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/google/protobuf/descriptor.cc \
../../Classes/google/protobuf/descriptor.pb.cc \
../../Classes/google/protobuf/descriptor_database.cc \
../../Classes/google/protobuf/dynamic_message.cc \
../../Classes/google/protobuf/extension_set.cc \
../../Classes/google/protobuf/extension_set_heavy.cc \
../../Classes/google/protobuf/generated_message_reflection.cc \
../../Classes/google/protobuf/generated_message_util.cc \
../../Classes/google/protobuf/io/coded_stream.cc \
../../Classes/google/protobuf/io/gzip_stream.cc \
../../Classes/google/protobuf/io/printer.cc \
../../Classes/google/protobuf/io/tokenizer.cc \
../../Classes/google/protobuf/io/zero_copy_stream.cc \
../../Classes/google/protobuf/io/zero_copy_stream_impl.cc \
../../Classes/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../../Classes/google/protobuf/message.cc \
../../Classes/google/protobuf/message_lite.cc \
../../Classes/google/protobuf/reflection_ops.cc \
../../Classes/google/protobuf/repeated_field.cc \
../../Classes/google/protobuf/service.cc \
../../Classes/google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
../../Classes/google/protobuf/stubs/atomicops_internals_x86_msvc.cc \
../../Classes/google/protobuf/stubs/common.cc \
../../Classes/google/protobuf/stubs/once.cc \
../../Classes/google/protobuf/stubs/stringprintf.cc \
../../Classes/google/protobuf/stubs/structurally_valid.cc \
../../Classes/google/protobuf/stubs/strutil.cc \
../../Classes/google/protobuf/stubs/substitute.cc \
../../Classes/google/protobuf/text_format.cc \
../../Classes/google/protobuf/unknown_field_set.cc \
../../Classes/google/protobuf/wire_format.cc \
../../Classes/google/protobuf/wire_format_lite.cc \
../../Classes/AppDelegate.cpp \
../../Classes/HelloWorldScene.cpp \
../../Classes/ZLL/ArenaLayer.cpp \
../../Classes/ZLL/ArenaMediator.cpp \
../../Classes/ZLL/ArenaNode.cpp \
../../Classes/ZLL/ArenaPopLayer.cpp \
../../Classes/ZLL/CfgManager.cpp \
../../Classes/ZLL/CMyContact.cpp \
../../Classes/ZLL/CMyMenu.cpp \
../../Classes/ZLL/FightLayer.cpp \
../../Classes/ZLL/FightMediator.cpp \
../../Classes/ZLL/FightNode.cpp \
../../Classes/ZLL/GLES-Render.cpp \
../../Classes/ZLL/IniParser.cpp \
../../Classes/ZLL/LanguageManager.cpp \
../../Classes/ZLL/PVELayer.cpp \
../../Classes/ZLL/PVEMediator.cpp \
../../Classes/ZLL/PVENode.cpp \
../../Classes/ZLL/PVEPopLayer.cpp \
../../Classes/ZLL/ScrollViewModel.cpp \
../../Classes/ZLL/ToolsFun.cpp \
../../Classes/ZMQ/AlertDialog.cpp \
../../Classes/ZMQ/ChatMediator.cpp \
../../Classes/ZMQ/ClubMediator.cpp \
../../Classes/ZMQ/DlgLogin.cpp \
../../Classes/ZMQ/Facade.cpp \
../../Classes/ZMQ/FriendMediator.cpp \
../../Classes/ZMQ/GameLoading.cpp \
../../Classes/ZMQ/GameLogo.cpp \
../../Classes/ZMQ/layerManager.cpp \
../../Classes/ZMQ/MailMediator.cpp \
../../Classes/ZMQ/MessageCenter.cpp \
../../Classes/ZMQ/PacksackMediator.cpp \
../../Classes/ZMQ/RichangMediator.cpp \
../../Classes/ZMQ/SceneCover.cpp \
../../Classes/ZMQ/SceneString.cpp \
../../Classes/ZMQ/ShiwusuoMediator.cpp \
../../Classes/ZMQ/ShopMediator.cpp \
../../Classes/ZMQ/SoulMediator.cpp \
../../Classes/ZMQ/TaskMediator.cpp \
../../Classes/ZMQ/TiejiangpuMediator.cpp \
../../Classes/ZMQ/UIScrollViewP.cpp \
../../Classes/ZMQ/VipMediator.cpp \
../../Classes/ZMQ/ZhujueMediator.cpp \
../../Classes/ZXL/SportMediator.cpp \
../../Classes/ZXL/tools/CPSocket.cpp \
../../Classes/ZXL/tools/Datagram.cpp \
../../Classes/ZXL/tools/DataPackageManager.cpp \
../../Classes/ZXL/tools/GameNetworkDelegate.cpp \
../../Classes/ZXL/widgets/EditBoxTest.cpp \
../../Classes/proto_files/Land.pb.cc \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../Classes/google \
$(LOCAL_PATH)/../../Classes/google/protobuf \
$(LOCAL_PATH)/../../Classes/google/protobuf/io \
$(LOCAL_PATH)/../../Classes/google/protobuf/stubs \
$(LOCAL_PATH)/../../Classes/google/protobuf/testing \
$(LOCAL_PATH)/../../Classes/proto_files \
$(LOCAL_PATH)/../../Classes/ZLL \
$(LOCAL_PATH)/../../Classes/ZMQ \
$(LOCAL_PATH)/../../Classes/ZXL \
$(LOCAL_PATH)/../../Classes/ZXL/tools \
$(LOCAL_PATH)/../../Classes/ZXL/widgets \
 
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, e:\dev\cocos2d-x-2.2)\
$(call import-add-path, e:\dev\cocos2d-x-2.2\cocos2dx\platform\third_party\android\prebuilt)\
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
