project "HttpVisualizer"
    language "C++"
    cppdialect "C++17"
    flags "FatalWarnings"

    defines { 
        "_CRT_SECURE_NO_WARNINGS",
        "CURL_STATICLIB" 
    }

    -- gcc* clang* msc*
    filter "toolset:msc*"
        warnings "High" -- High
        externalwarnings "Default" -- Default
        buildoptions { "/sdl" }

    filter { "toolset:gcc* or toolset:clang*" }
        enablewarnings {
            "cast-align",
            "cast-qual",
            "ctor-dtor-privacy",
            "disabled-optimization",
            "format=2",
            "init-self",
            "missing-declarations",
            "missing-include-dirs",
            "old-style-cast",
            "overloaded-virtual",
            "redundant-decls",
            "shadow",
            "sign-conversion",
            "sign-promo",
            "strict-overflow=5",
            "switch-default",
            "undef",
            "uninitialized",
            "unreachable-code",
            "unused",
            "alloca",
            "conversion",
            "deprecated",
            "format-security",
            "null-dereference",
            "stack-protector",
            "vla",
            "shift-overflow"
        }

    filter "toolset:gcc*"
        warnings "Extra"
        externalwarnings "Off"
        linkgroups "on" -- activate position independent linking
        enablewarnings {
            "noexcept",
            "strict-null-sentinel",
            "array-bounds=2",
            "duplicated-branches",
            "duplicated-cond",
            "logical-op",
            "arith-conversion",
            "stringop-overflow=4",
            "implicit-fallthrough=3",
            "trampolines"
        }

    filter "toolset:clang*"
        warnings "Extra"
        externalwarnings "Everything"
        enablewarnings {
            "array-bounds",
            "long-long",
            "implicit-fallthrough", 
        }
    filter {}

    files {
        "**.cpp",
        "**.h"
    }

    includedirs {
        RaylibDir .. "/src",
        RaylibDir .. "/include",
        DepDir,
        "D:/Dev/HttpVisualizer/Dependencies/curl-7.86.0/builds/libcurl-vc22-x64-debug-static-ipv6-sspi-schannel/include"
    }

    externalincludedirs {
        RaylibDir .. "/src",
        RaylibDir .. "/include",
        DepDir
    }

    links {
        "raylib",
        "Winmm",
        "ws2_32",
        "crypt32",
        "Wldap32",
        "Normaliz"
    }

    
    filter { "configurations:Debug" }
        kind "ConsoleApp"
        floatingpoint "default"
        libdirs "D:/Dev/HttpVisualizer/Dependencies/curl-7.86.0/builds/libcurl-vc22-x64-debug-static-ipv6-sspi-schannel/lib"
        links "libcurl_a_debug"

    filter { "configurations:Release" }
        --kind "WindowedApp"
        kind "ConsoleApp"
        entrypoint "mainCRTStartup"
        floatingpoint "fast"
        libdirs "D:/Dev/HttpVisualizer/Dependencies/curl-7.86.0/builds/libcurl-vc22-x64-release-static-ipv6-sspi-schannel/lib"
        links "libcurl_a"