{
    "targets": [
        {
            "target_name": "gpio",
            "sources": [ "gpio.cpp", "./led-blaster/led-blaster-pre.cpp", "./led-blaster/fade.cpp", "./led-blaster/file.cpp", "./led-blaster/init.cpp", "./led-blaster/led.cpp", "./led-blaster/modes.cpp" ],
            "libraries": [ " -lpigpio" ]
        }
    ]
}
