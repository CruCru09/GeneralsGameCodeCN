# Test Replays

The GeneralsReplays folder contains replays and the required maps that are tested in CI to ensure that the game is retail compatible.

You can also test with these replays locally:
- Copy the replays into a subfolder in your `%USERPROFILE%/Documents/Command and Conquer Generals Zero Hour Data/Replays` folder.
- Copy the maps into `%USERPROFILE%/Documents/Command and Conquer Generals Zero Hour Data/Maps`
- Start the test with this: (copy into a .bat file next to your executable)
```
START /B /W generalszh.exe -jobs 4 -headless -replay subfolder/*.rep > replay_check.log
echo %errorlevel%
PAUSE
```
It will run the game in the background and check that each replay is compatible. You need to use a VC6 build with optimizations and RTS_BUILD_OPTION_DEBUG = OFF, otherwise the game won't be compatible.

------------------

# 测试回放

generalsreplay文件夹包含重播和在CI中测试的所需地图，以确保游戏与零售兼容。

你也可以在本地使用以下回放进行测试：

- 复制重播到子文件夹在你的 `%USERPROFILE%/Documents/Command and Conquer Generals Zero Hour Data/Replays` 文件夹中。

- 将地图复制到 `%USERPROFILE%/Documents/Command and Conquer Generals Zero Hour Data/Maps`

- 这样开始测试：（复制到可执行文件旁边的.bat文件中）
```
START /B /W generalszh.exe -jobs 4 -headless -replay subfolder/*.rep > replay_check.log
echo %errorlevel%
PAUSE
```
它将在后台运行游戏，并检查每个重播是否兼容。你需要使用VC6构建优化和RTS_BUILD_OPTION_DEBUG = OFF，否则游戏将不兼容。
