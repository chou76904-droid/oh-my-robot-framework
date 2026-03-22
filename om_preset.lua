local preset = {
  board = {name = "rm-c-board"},
  os = {name = "freertos"},

  -- 默认工具链，第一次建议 gnu-rm
  toolchain_default = {
    name = "armclang", -- armclang
  },

  -- 这里是你本机工具链路径（通常必须修改）
  toolchain_presets = {
    ["gnu-rm"] = {
      sdk = "D:/tool/arm-gnu-toolchain-15.2.rel1-mingw-w64-i686-arm-none-eabi", -- 请改成你本机路径
      bin = "D:/tool/arm-gnu-toolchain-15.2.rel1-mingw-w64-i686-arm-none-eabi/bin", -- 请改成你本机路径
    },
    ["armclang"] = {
      sdk = "D:/Program Files/Program tools/keil_v5/ARM/ARMCLANG", -- 选用 armclang 时请改
      bin = "D:/Program Files/Program tools/keil_v5/ARM/ARMCLANG/bin", -- 选用 armclang 时请改
      flags = {
        common = {"--target=arm-arm-none-eabi", "-Wno-unused-command-line-argument"},
        cflags = {"-Wno-unused-command-line-argument"},
        cxflags = {"-Wno-unused-command-line-argument"},
        asflags = {"-Wno-unused-command-line-argument"},
        ldflags = {"--target=arm-arm-none-eabi", "-Wno-unused-command-line-argument"},
      }
    },
  },

  -- 烧录器预设：当前仅支持 jlink
  flash = {
    jlink = {
      device = "STM32F407",
      interface = "swd",
      speed = 4000,
      program = "C:/Program Files/SEGGER/JLink_V916a/JLink.exe", -- 找不到 JLink 时请改
      target = "robot_project",
      firmware = nil,
      prefer_hex = true,
      reset = true,
      run = true,
      native_output = false,
    },
  },
}

function get_preset()
  return preset
end