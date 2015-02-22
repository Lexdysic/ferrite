project "Ferrite"
    kind "StaticLib"
    location "./Build/Projects/"
    targetdir "./Bin/"
    files {
        "./Code/**.h",
        "./Code/**.cpp",
        "./Code/**.inl",
    }
    excludes {
        "./Code/External/**",
        "./Code/External/bx/tools/**",
        "./Code/External/bx/3rdparty/**",
        --"./Code/External/bgfx/examples/**",
        --"./Code/External/bgfx/tools/**",
        --"./Code/External/bgfx/3rdparty/**",
    }
    --includedirs {
    --    "./Code/External/bx/**",
    --    "./Code/External/bgfx/**",
    --}
    vpaths {
        ["*"] = { "./Code/**" },
    }