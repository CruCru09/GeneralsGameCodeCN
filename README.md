[![GitHub Release](https://img.shields.io/github/v/release/TheSuperHackers/GeneralsGameCode?include_prereleases&sort=date&display_name=tag&style=flat&label=Release)](https://github.com/TheSuperHackers/GeneralsGameCode/releases)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/TheSuperHackers/GeneralsGameCode/3)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/TheSuperHackers/GeneralsGameCode/1)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/TheSuperHackers/GeneralsGameCode/4)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/TheSuperHackers/GeneralsGameCode/5)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/TheSuperHackers/GeneralsGameCode/6)

[![GitHub issues by-label](https://img.shields.io/github/issues/TheSuperHackers/GeneralsGameCode/bug?style=flat&label=Bug%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/TheSuperHackers/GeneralsGameCode/issues?q=label%3ABug)
[![GitHub issues by-label](https://img.shields.io/github/issues/TheSuperHackers/GeneralsGameCode/enhancement?style=flat&label=Enhancement%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/TheSuperHackers/GeneralsGameCode/issues?q=label%3AEnhancement)
[![GitHub issues by-label](https://img.shields.io/github/issues/TheSuperHackers/GeneralsGameCode/major?style=flat&label=Major%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/TheSuperHackers/GeneralsGameCode/issues?q=label%3AMajor)
[![GitHub issues by-label](https://img.shields.io/github/issues/TheSuperHackers/GeneralsGameCode/critical?style=flat&label=Critical%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/TheSuperHackers/GeneralsGameCode/issues?q=label%3ACritical)
[![GitHub issues by-label](https://img.shields.io/github/issues/TheSuperHackers/GeneralsGameCode/blocker?style=flat&label=Blocker%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/TheSuperHackers/GeneralsGameCode/issues?q=label%3ABlocker)

# 欢迎来到将军游戏代码项目

GeneralsGameCode是一个社区驱动的项目，旨在修复和改进经典的RTS游戏，*命令&

征服：将军*及其扩展*零时*。这个存储库包含了这两款游戏的源代码

主要关注“零时”。

此外，还有一个用于修复和改进游戏数据和资产的补充项目存储库

INI脚本，GUI， AI，地图，模型，纹理，音频，本地化。你可以找到它
[here](https://github.com/TheSuperHackers/GeneralsGamePatch/) 并为之做出贡献。

## 项目概述

游戏最初是用Visual Studio 6和c++ 98开发的。我们已经更新了代码以与Visual兼容

Studio 2022和c++ 20。

该项目的初始目标是修复关键错误并实现改进，同时保持与

原来的*将军*版本1.08和*零时*版本1.04。一旦我们可以打破零售兼容性，更多的修复

功能将有可能实现。

## 当前重点和未来计划

以下是我们目前的重点和未来计划的概述

- **使代码库现代化**: 过渡到现代c++标准并重构旧代码。
- **关键Bug修复**: 修复破坏游戏的问题（如全屏崩溃）。
- **小错误修复**: 解决小错误（例如，UI问题，图形故障）。
- **跨平台的支持**: 增加对更多平台的支持（例如，Linux, macOS）。
- **引擎的改进**: 增强游戏引擎，提高性能和稳定性。
- **客户端功能**: 增强游戏的客户端功能，如改进的重播查看器和UI更新。
- **多人的改进**: 实现了一个新的游戏服务器和升级的配对大厅。
- **工具的改进**: 开发新的或改进现有的建模和游戏开发工具。
- **社区驱动的改进**: 一旦社区发展壮大，我们计划加入更多的功能，更新，和根据玩家反馈进行调整。

## 运行游戏

要运行*将军*或*零时*使用这个项目，你需要有原来的*命令与征服：将军和零时* 游戏安装。最简单的方法是通过*命令与征服的终极集合*
在 [Steam](https://store.steampowered.com/bundle/39394). 一旦游戏准备好了，下载最新版本的
项目从 [GitHub Releases](https://github.com/TheSuperHackers/GeneralsGameCode/releases), 提取必要的
文件，并按照 [Wiki](https://github.com/TheSuperHackers/GeneralsGameCode/wiki).


## 加入社区

您可以在我们的网站上聊天和讨论项目的发展 [Discord channel](https://www.community-outpost.com/discord) 要获取最新更新，请报告bug，并为项目做出贡献！

## 自己创造游戏

我们为使用Visual Studio 6 （VS6）和Visual Studio 2022构建项目提供支持。详细构建
说明，请查看 [Wiki](https://github.com/TheSuperHackers/GeneralsGameCode/wiki/build_guides)，这也包括使用Docker、CLion构建的指南，以及支持其他版本的分支的链接。

### 依赖关系管理

存储库使用vcpkg清单 (`vcpkg.json`) 还有一个锁文件 (`vcpkg-lock.json`). 添加或升级时

依赖关系, `vcpkg install --x-manifest-root . --triplet <triplet>` 与 `VCPKG_FEATURE_FLAGS=versions` 因此,Lockfile获取新版本，并在更改中包含更新后的Lockfile。GitHub Actions使用这些端口
通过 `VCPKG_BINARY_SOURCES=clear;files,<workspace>/vcpkg-bincache,readwrite` (搭配一个 `actions/cache` 条目该文件夹)因此，第一次CI构建将使用缓存，后续构建将使用预构建的二进制文件，而不是

基于一切。

## 贡献

欢迎对项目的贡献！如果你对贡献感兴趣，你需要有c++的知识。加入

开发者在Discord上聊天以获取更多关于如何开始的信息。请务必阅读我们的
[Contributing Guidelines](CONTRIBUTING.md) 在提交拉取请求之前。你也可以退出
the [Wiki](https://github.com/TheSuperHackers/GeneralsGameCode/wiki) 有关更详细的文档。


## 许可和法律免责声明

EA没有认可也不支持这个产品。所有商标均为其各自所有者的财产。

本项目在 [GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.html)，这样你就可以
在本许可证的条款下自由地修改和分发源代码。请参阅 [LICENSE.md](LICENSE.md) 获取详细信息。
