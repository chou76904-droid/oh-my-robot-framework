set_project("oh-my-robot")
set_xmakever("3.0.7")
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = os.projectdir()})

includes("oh-my-robot")

target("robot_project")
    set_kind("binary")
    set_filename("robot_project.elf")
    add_deps("tar_oh_my_robot")
    set_policy("check.auto_ignore_flags", false)
    add_rules("oh_my_robot.context", "oh_my_robot.board_assets", "oh_my_robot.image_convert")
    add_files("oh-my-robot/samples/pal/serial_crc/main.c")	-- 示例文件
target_end()