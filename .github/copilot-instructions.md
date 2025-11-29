# AI Coding Agent Instructions

## Project Overview

This is the **GeneralsGameCode** project - a community-driven effort to fix and improve the classic RTS games *Command & Conquer: Generals* and *Zero Hour*. The codebase has been modernized from Visual Studio 6/C++98 to Visual Studio 2022/C++20 while maintaining retail compatibility.

## Architecture

### Dual Game Structure
- **Generals/**: Original C&C Generals (v1.08) codebase
- **GeneralsMD/**: Zero Hour expansion (v1.04) codebase - **primary focus**
- **Core/**: Shared game engine and libraries used by both games

### Key Components
- **Core/GameEngine/**: Base game engine with GameClient/GameLogic separation
- **Core/Libraries/**: Internal libraries including WWVegas graphics framework
- **Core/GameEngineDevice/**: Platform-specific rendering (DirectX 8)
- **Core/Tools/**: Development tools (W3DView, texture compression, etc.)
- **Dependencies/**: External dependencies (MaxSDK for VC6, utilities)

## Build System

### CMake Presets (Critical)
- **vc6**: Visual Studio 6 compatible build (retail compatibility required)
- **win32**: Modern Visual Studio 2022 build
- **vc6-debug/vc6-profile**: Debug/profiling variants
- Use `cmake --preset <preset-name>` followed by `cmake --build build/<preset>`

### Build Commands
```bash
# Configure with specific preset
cmake --preset vc6

# Build (from project root)
cmake --build build/vc6

# Build with tools and extras
cmake --build build/vc6 --target <game>_tools <game>_extras
```

### Retail Compatibility
- VC6 builds are required for replay compatibility testing
- Debug builds break retail compatibility
- Use RTS_BUILD_OPTION_DEBUG=OFF for compatibility testing

## Development Workflow

### Code Change Documentation
**Every user-facing change requires TheSuperHackers comment format:**
```cpp
// TheSuperHackers @keyword author DD/MM/YYYY Description
```

Common keywords: `@bugfix`, `@feature`, `@performance`, `@refactor`, `@tweak`, `@build`

### Pull Request Guidelines
- Title format: `type: Description starting with action verb`
- Types: `bugfix:`, `feat:`, `fix:`, `refactor:`, `perf:`, `build:`
- Zero Hour changes take precedence over Generals
- Changes must be identical between both games when applicable

### Code Style
- Maintain consistency with surrounding legacy code
- Prefer C++98 style unless modern features add significant value
- No big refactors mixed with logical changes
- Use present tense in documentation ("Fixes" not "Fixed")

## Testing

### Replay Compatibility Testing
Located in `GeneralsReplays/` - critical for ensuring retail compatibility:
```bash
generalszh.exe -jobs 4 -headless -replay subfolder/*.rep
```
- Requires VC6 optimized build with RTS_BUILD_OPTION_DEBUG=OFF
- Copies replays to `%USERPROFILE%/Documents/Command and Conquer Generals Zero Hour Data/Replays`
- CI automatically tests GeneralsMD builds against known replays

### Build Validation
- CI tests multiple presets: vc6, vc6-profile, vc6-debug, win32 variants
- Path-based change detection triggers relevant builds
- Tools and extras are built with `+t+e` flags

## Common Patterns

### Memory Management
- Manual memory management (delete/delete[]) - this is legacy C++98 code
- STLPort for VC6 compatibility (see `cmake/stlport.cmake`)

### Game Engine Separation
- **GameLogic**: Game state, rules, simulation
- **GameClient**: Rendering, UI, platform-specific code
- Clean separation maintained for potential future networking

### Module Structure
```
Core/
├── GameEngine/Include/Common/     # Shared interfaces
├── GameEngine/Include/GameLogic/  # Game simulation
├── GameEngine/Include/GameClient/ # Rendering/UI
├── Libraries/Include/rts/         # RTS-specific utilities
└── Libraries/Source/WWVegas/      # Graphics framework
```

## External Dependencies

### Required for Building
- **VC6 builds**: Requires MSVC 6.0 toolchain (automated in CI via itsmattkc/MSVC600)
- **Modern builds**: Visual Studio 2022, Ninja generator
- **vcpkg** (optional): zlib, ffmpeg for enhanced builds

### Platform-Specific
- **Windows**: DirectX 8, Miles Sound System, Bink Video
- **Registry detection**: Automatic game install path detection from EA registry keys

## Tools and Utilities

### Development Scripts (`scripts/cpp/`)
- `fixInludesCase.sh`: Fix include case sensitivity
- `refactor_*.py`: Code refactoring utilities
- `remove_trailing_whitespace.py`: Code cleanup

### Build Tools
- W3DView: 3D model viewer
- TextureCompress: Asset optimization
- MapCacheBuilder: Map preprocessing

## Key Files to Understand
- `CMakePresets.json`: All build configurations
- `cmake/config-build.cmake`: Build options and feature flags
- `Core/GameEngine/Include/`: Core engine interfaces
- `**/Code/Main/WinMain.cpp`: Application entry points
- `GeneralsReplays/`: Compatibility test data

---

# AI编码代理说明

## 项目概述

这是**GeneralsGameCode**项目——由社区驱动的努力，以修复和改进经典RTS游戏** Command & Conquer: Generals* *和** Zero Hour* *。代码库已经从Visual Studio 6/ c++ 98现代化到Visual Studio 2022/ c++ 20，同时保持零售兼容性。

## 体系结构

### 双重游戏结构
- **Generals/**:原始C&C将军（v1.08）代码库
- **GeneralsMD/**: 零时扩展（v1.04）代码库- **主要焦点**
- **Core/**: 两个游戏共享的游戏引擎和库

### 关键部件
- **Core/GameEngine/**: 基本游戏引擎与GameClient/GameLogic分离
- **Core/Libraries/**: 内部库包括WWVegas图形框架
- **Core/GameEngineDevice/**: 特定平台渲染（DirectX 8）
- **Core/Tools/**: 开发工具（W3DView，纹理压缩等）
- **Dependencies/**: 外部依赖（VC6的MaxSDK，实用程序）

## 构建系统

### CMake Presets (Critical)
- **vc6**: Visual Studio 6兼容构建（需要零售兼容性）
- **win32**: 现代Visual Studio 2022版本
- **vc6-debug/vc6-profile**: 调试/分析
- Use `cmake --preset <preset-name>` followed by `cmake --build build/<preset>`

### 构建命令
```bash
# Configure with specific preset
cmake --preset vc6

# Build (from project root)
cmake --build build/vc6

# Build with tools and extras
cmake --build build/vc6 --target <game>_tools <game>_extras
```

### Retail Compatibility
- VC6 builds are required for replay compatibility testing
- Debug builds break retail compatibility
- Use RTS_BUILD_OPTION_DEBUG=OFF for compatibility testing

## Development Workflow

### Code Change Documentation
**Every user-facing change requires TheSuperHackers comment format:**
```cpp
// TheSuperHackers @keyword author DD/MM/YYYY Description
```

Common keywords: `@bugfix`, `@feature`, `@performance`, `@refactor`, `@tweak`, `@build`

### Pull Request Guidelines
- Title format: `type: Description starting with action verb`
- Types: `bugfix:`, `feat:`, `fix:`, `refactor:`, `perf:`, `build:`
- Zero Hour changes take precedence over Generals
- Changes must be identical between both games when applicable

### Code Style
- Maintain consistency with surrounding legacy code
- Prefer C++98 style unless modern features add significant value
- No big refactors mixed with logical changes
- Use present tense in documentation ("Fixes" not "Fixed")

## Testing

### Replay Compatibility Testing
Located in `GeneralsReplays/` - critical for ensuring retail compatibility:
```bash
generalszh.exe -jobs 4 -headless -replay subfolder/*.rep
```
- Requires VC6 optimized build with RTS_BUILD_OPTION_DEBUG=OFF
- Copies replays to `%USERPROFILE%/Documents/Command and Conquer Generals Zero Hour Data/Replays`
- CI automatically tests GeneralsMD builds against known replays

### Build Validation
- CI tests multiple presets: vc6, vc6-profile, vc6-debug, win32 variants
- Path-based change detection triggers relevant builds
- Tools and extras are built with `+t+e` flags

## Common Patterns

### Memory Management
- Manual memory management (delete/delete[]) - this is legacy C++98 code
- STLPort for VC6 compatibility (see `cmake/stlport.cmake`)

### Game Engine Separation
- **GameLogic**: Game state, rules, simulation
- **GameClient**: Rendering, UI, platform-specific code
- Clean separation maintained for potential future networking

### 模块结构
```
Core/
├── GameEngine/Include/Common/     # 共同的接口
├── GameEngine/Include/GameLogic/  # 游戏模拟
├── GameEngine/Include/GameClient/ # 渲染UI
├── Libraries/Include/rts/         # RTS专用工具
└── Libraries/Source/WWVegas/      # 图形框架
```

## External Dependencies

### Required for Building
- **VC6 builds**: Requires MSVC 6.0 toolchain (automated in CI via itsmattkc/MSVC600)
- **Modern builds**: Visual Studio 2022, Ninja generator
- **vcpkg** (optional): zlib, ffmpeg for enhanced builds

### Platform-Specific
- **Windows**: DirectX 8, Miles Sound System, Bink Video
- **Registry detection**: Automatic game install path detection from EA registry keys

## Tools and Utilities

### Development Scripts (`scripts/cpp/`)
- `fixInludesCase.sh`: Fix include case sensitivity
- `refactor_*.py`: Code refactoring utilities
- `remove_trailing_whitespace.py`: Code cleanup

### Build Tools
- W3DView: 3D model viewer
- TextureCompress: Asset optimization
- MapCacheBuilder: Map preprocessing

## Key Files to Understand
- `CMakePresets.json`: All build configurations
- `cmake/config-build.cmake`: Build options and feature flags
- `Core/GameEngine/Include/`: Core engine interfaces
- `**/Code/Main/WinMain.cpp`: Application entry points
- `GeneralsReplays/`: Compatibility test data
