project "Engine"
    kind "StaticLib"
    location "./Build/Projects/"
    targetdir "./Bin/"
    files {
        "../Engine/Code/**.h",
        "../Engine/Code/**.cpp",
        "../Engine/Code/**.inl",
    }
    excludes {
        "../Engine/Code/Object/**",
        "../Engine/Code/External/**",
        "../Engine/Code/Hash/**",
    }
        
 
