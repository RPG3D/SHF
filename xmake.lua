

add_rules("mode.release", "mode.debug")

target("jxqy2")

    set_kind("binary")

    set_symbols("debug")

    add_files("src/Component/*.cpp")
    add_files("src/Element/*.cpp")
    add_files("src/Engine/*.cpp")
    add_files("src/File/*.cpp")
    add_files("src/Image/*.cpp")

    add_files("src/libconvert/*.cpp")
    add_files("3rd/minilzo/*.c")
    remove_files("3rd/minilzo/testmini.c")

    add_files("3rd/lua/*.c")


    add_files("src/Weather/*.cpp")
    add_files("src/Game/**.cpp")
    
    add_files("src/main.cpp")

    plat = get_config("plat") or os.host()
    plat2 = plat:replace("windows", "win")
    arch = get_config("arch") or os.arch()

    add_includedirs("3rd/fmod/" .. plat2 .. "/inc")
    add_includedirs("3rd/SDL2/" .. plat2 .. "/include")
    add_includedirs("3rd/SDL2_image/" .. plat2 .. "/include")
    add_includedirs("3rd/SDL2_ttf/" .. plat2 .. "/include")
    add_includedirs("3rd/ffmpeg/" .. plat2 .. "/include")

    add_linkdirs('3rd/fmod/' .. plat2 .. '/lib/' .. arch)
    add_linkdirs('3rd/SDL2/' .. plat2 .. '/lib/' .. arch)
    add_linkdirs('3rd/SDL2_image/' .. plat2 .. '/lib/' .. arch)
    add_linkdirs('3rd/SDL2_ttf/' .. plat2 .. '/lib/' .. arch)
    add_linkdirs('3rd/ffmpeg/' .. plat2 .. '/lib/' .. arch)

    add_links("fmod_vc", "fmodL_vc")
    add_links("SDL2", "SDL2main", "SDL2_image", "SDL2_ttf")
    add_links("avcodec", "avdevice", "avfilter", "avformat", "avutil", "swresample", "swscale")
    
    after_build(function (target)
        plat = get_config("plat") or os.host()
        plat2 = plat:replace("windows", "win")
        arch = get_config("arch") or os.arch()

        DestBinDir = "$(buildir)/" .. plat .. "/" .. arch .. '/' .. get_config("mode")

        os.cp("3rd/fmod/" .. plat2 .. "/lib/" .. arch .. "/*.dll", DestBinDir)
        os.cp("3rd/SDL2/" .. plat2 .. "/lib/" .. arch .. "/*.dll", DestBinDir)
        os.cp("3rd/SDL2_image/" .. plat2 .. "/lib/" .. arch .. "/*.dll", DestBinDir)
        os.cp("3rd/SDL2_ttf/" .. plat2 .. "/lib/" .. arch .. "/*.dll", DestBinDir)
        os.cp("3rd/ffmpeg/" .. plat2 .. "/lib/" .. arch .. "/bin/*.dll", DestBinDir)

    end)

