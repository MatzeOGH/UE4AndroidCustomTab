// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTabFunctionLibrary.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"

#endif

void UCustomTabFunctionLibrary::OpenCustomTab(const FString& Url)
{
    if (Url.IsEmpty()) return;
    
#if PLATFORM_ANDROID
    if(JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
    {
        static jmethodID AndroidThunkJava_CustomTab = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_OpenNativeTab", "(Ljava/lang/String;)V", false);
        if(AndroidThunkJava_CustomTab == 0)
        {
            UE_LOG(LogAndroid, Error, TEXT("Method not found"));
            return;
        }
        jstring UrlArg = Env->NewStringUTF(TCHAR_TO_UTF8(*Url));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_CustomTab, UrlArg);
        Env->DeleteLocalRef(UrlArg);
        if(Env->ExceptionCheck())
        {
            Env->ExceptionDescribe();
            Env->ExceptionClear();
            UE_LOG(LogAndroid, Warning, TEXT("Exception encountered calling AndroidThunkJava_CustomTab."));
        }
    }
#else
    FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
#endif
}
