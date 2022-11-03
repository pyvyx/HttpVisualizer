project "HttpVisualizer"
    language "C++"
    cppdialect "C++17"
    --flags "FatalWarnings"

    defines { 
        "_CRT_SECURE_NO_WARNINGS",
        "CURL_STATICLIB" 
    }

    CurlDir = cwd .. "/Dependencies/curl-7.86.0"
    CurlBinDir = CurlDir .. "/Binaries"
    filter { "system:windows", "platforms:x64" }
        libdirs { CurlBinDir .. "/windows/x64" }
--
    filter { "system:windows", "platforms:x86" }
        libdirs { CurlBinDir .. "/windows/x86" }

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
        CurlDir .. "/include"
    }

    externalincludedirs {
        RaylibDir .. "/src",
        RaylibDir .. "/include",
        CurlDir .. "/include"
    }

    links "raylib"

    filter "system:windows"
        links {
            "Winmm",
            "ws2_32",
            "crypt32",
            "Wldap32",
            "Normaliz",
            "Advapi32",
            "user32",
            "gdi32",
            "shell32"
        }

    filter { "configurations:Debug" }
        kind "ConsoleApp"
        floatingpoint "default"
        links "libcurl_a_debug"

    filter { "configurations:Release" }
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
        floatingpoint "fast"
        links "libcurl_a"