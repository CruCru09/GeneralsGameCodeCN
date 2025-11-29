# How to contribute as a developer

To contribute, fork this repository to create your own copy that you can clone locally and push back to. You can use your fork to create pull requests for your code to be merged into this repository.

## Code guidelines

### Scope of code changes

Code edits only touch the lines of code that serve the intended goal of the change. Big refactors should not be combined with logical changes, because these can become very difficult to review. If a change requires a refactor, create a commit for the refactor before (or after) creating a commit for the change. A Pull Request can contain multiple commits and can be merged with **Rebase and Merge** if these commits are meant to be preserved on the main branch. Otherwise, method of merging will be **Squash and Merge**.

### Style of code changes

Code edits should fit the nearby code in ways that the code style reads consistent, unless the original code style is bad. The original game code uses c++98, or a deviation thereof, and is simple to read. Prefer not to use newer language features unless required to implement the desired change. Prefer to use newer language features when they are considerably more robust or make the code easier to understand or maintain.

### Language style guide

*Work in progress. Needs a maintainer. Can be built upon existing Code guidelines, such as the "Google C++ Style Guide".*

### Precedence of code changes

Changes to Zero Hour take precedence over Generals, if applicable. When the changed code is not shared by both titles, then the change needs to be created for Zero Hour first, and then recreated for Generals. The implementation of a change for both titles needs to be identical or as close as possible. Preferably the Generals replica of a change comes with the same Pull Request. The Generals replica can be created after the Zero Hour code review has finished.


## Change documentation

User facing changes need to be documented in code, Pull Requests and change logs. All documentation ideally is written in the present tense, and not the past.

Good:

> Fixes particle effect of USA Missile Defender

Bad:

> Fixed particle effect of USA Missile Defender

When a text refers to a faction unit, structure, upgrade or similar, then the unit should be worded without any abbrevations and should be prefixed with the faction name. Valid faction names are USA, China, GLA, Boss, Civilian. Subfaction names can be appended too, for example GLA Stealth.

Good:

> Fixes particle effect of USA Missile Defender

Bad:

> Fixes particle effect of MD


### Code documentation

User facing changes need to be accompanied by comment(s) where the change is made. Maintenance related changes, such as compilation fixes, typically do not need commenting, unless the next reader can benefit from a special explanation. The comment can be put at the begin of the changed file, class, function or block. It must be clear from the change description what has changed.

The expected comment format is

```
// TheSuperHackers @keyword author DD/MM/YYYY A meaningful description for this change.
```

The `TheSuperHackers` word and `@keyword` are mandatory. `author` and date can be omitted when preferred.

| Keyword          | Use-case                                                    |
|------------------|-------------------------------------------------------------|
| @bugfix          | Fixes a bug                                                 |
| @fix             | Fixes something, but is not a user facing bug               |
| @build           | Addresses a compile warning or error                        |
| @feature         | Adds something new                                          |
| @performance     | Improves performance                                        |
| @refactor        | Moves or rewrites code, but does not change the behaviour   |
| @tweak           | Changes values or settings                                  |
| @info            | Writes useful information for the next reader               |
| @todo            | Adds a note for something left to do if really necessary    |

Block comment sample

```
    // TheSuperHackers @bugfix JAJames 17/03/2025 Fix uninitialized memory access and add more Windows versions.
    memset(&os_info,0,sizeof(os_info));
```

Optionally, the pull request number can be appended to the comment. This can only be done after the pull request has been created.

```
// TheSuperHackers @bugfix JAJames 17/03/2025 Fix uninitialized memory access and add more Windows versions. (#123)
```

### Pull request documentation

The title of a new Pull Request, and/or commit(s) within, begins with a [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/) tag. The tag is followed by a concise and descriptive sentence about the change and/or commit, beginning with an upper case letter and ending without a dot. The sentence ideally begins with a word that describes the action that the change takes, for example `fix *this*`, `change *that*`, `add *those*`, `refactor *thing*`.

Allowed (extended) commit title types are:
```
bugfix:
build:
chore:
ci:
docs:
fix:
feat:
perf:
refactor:
style:
test:
tweak:
unify:
```

For the optional scope behind the type pick a suitable word that describes the overall area that the change touches.

Good:
```
bugfix(system): fix uninitialized memory access in Get_OS_Info
```

Bad:
```
Minimal changes for successful build.
```

If the Pull Request is meant to be merged with rebase, then a note for **Merge with Rebase** should be added to the top of the text body, to help identify the correct merge action when it is ready for merge. All commits of the Pull Request need to be properly named and need the number of the Pull Request added as a suffix in parentheses. Example: **(#333)**. All commits need to be able to compile on their own without dependencies in newer commits of the same Pull Request. Prefer to create changes for **Squash and Merge**, as this will simplify things.

The text body begins with links to related issue report(s) and/or Pull Request(s) if applicable.

To write a link use the following format:

```
* Fixes #222
* Closes #333
* Relates to #555
* Follow up for #666
```

Links are commonly used for

* closing a related issue report or task when this pull request is merged
* closing another pull request when this pull request is merged

Some keywords are interpreted by GitHub. Read about it [here](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue).

The text body continues with a description of the change in appropriate detail. This serves to educate reviewers and visitors to get a good understanding of the change without the need to study and understand the associated changed files. If the change is controversial or affects gameplay in a considerable way, then a rationale text needs to be appended. The rationale explains why the given change makes sense.


### Pull request merging rules

Please be mindful when merging changes. There are pitfalls in regards to the commit title consistency.

When attempting to **Squash and Merge** a Pull Request that contains a single commit, then GitHub will default generate a commit title from that single commit. Typically this is undesired, when the new commit title is meant to be kept in sync with the Pull Request title rather than the Pull Request commit title. The generated commit title may need to be adjusted before merging the Pull Request.

When attempting to **Squash and Merge** a Pull Request that contains multiple commits, the GitHub will default generate a commit title from the Pull Request title. Additionally it will generate a commit description from the multiple commits that are part of the Pull Request. The generated commit description generally needs to be cleared before merging the Pull Request to keep the commit title clean.

When attempting to **Rebase and Merge** a Pull Request, then all commits will transfer with the same names to the main branch. Verify that all commit titles are properly crafted, with tags where applicable, trailing Pull Request numbers in parentheses and no unnecessary commit descriptions (texts below the commit title).


### Change log documentation

*Work in progress.*

---

# 作为开发人员如何做出贡献

要做出贡献，可以fork这个存储库来创建您自己的副本，您可以在本地克隆并推送到该副本。您可以使用fork创建拉取请求，以便将代码合并到此存储库中。

## 代码指南

### 代码更改的范围

代码编辑只涉及服务于预期更改目标的代码行。大型重构不应该与逻辑变更结合在一起，因为这些变更会变得非常难以审查。如果变更需要重构，那么在为变更创建提交之前（或之后）为重构创建一个提交。一个Pull Request可以包含多个提交，如果这些提交被保留在主分支上，可以用**Rebase和Merge**合并。否则，合并的方法将是 **Squash and Merge**.

### 代码更改的风格

代码编辑应该以代码风格一致的方式适应附近的代码，除非原始代码风格不好。最初的游戏代码使用c++98或其偏差，并且易于阅读。除非需要实现所需的更改，否则最好不要使用较新的语言特性。倾向于使用较新的语言特性，当它们相当健壮或使代码更容易理解或维护时。

### 语言风格指南

*工作正在进行中。需要一个维修工。可以建立在现有的代码指导方针上，例如"Google C++ Style Guide".*

### 代码更改的优先级

如果适用，零点时刻的改变优先于将军。当修改后的代码不能被两款游戏共享时，就需要先为《Zero Hour》创建修改，然后再为《Generals》重新创建修改。这两款游戏的改变执行必须相同或尽可能接近。最好的将军副本的变化带来了相同的拉请求。将军副本可以在零时代码审查完成后创建。

## 改变文档

面向用户的更改需要记录在代码、Pull Requests和更改日志中。理想情况下，所有文档都是用现在时，而不是过去时。

Good:

> 修正了美国导弹防御者的粒子效果

Bad:

> 修正了美国导弹防御者的粒子效果

当一个文本指的是一个阵营单位、结构、升级或类似的东西时，那么这个单位的措辞应该没有任何缩写，并且应该以阵营名称作为前缀。有效的派系名称是美国，中国，GLA, Boss，平民。子派系名称也可以添加，例如GLA Stealth。

Good:

> 修正了美国导弹防御者的粒子效果

Bad:

> 修正了MD的粒子效果


### 代码文档

面向用户的更改需要在进行更改的地方附有注释。与维护相关的更改，例如编译修复，通常不需要注释，除非下一个读者可以从特殊的解释中受益。注释可以放在已更改的文件、类、函数或块的开头。必须从变更描述中清楚地看到发生了哪些更改。

预期的注释格式是

```
// TheSuperHackers @作者关键字 DD/MM/YYYY 对该更改的有意义的描述.
```

这 `TheSuperHackers` 词和 `@keyword` 是强制性的。 `author` 如果需要，可以省略date。

| 关键字          | 用例                                                         |
|------------------|-------------------------------------------------------------|
| @bugfix          | 修复了一个bug                                               |
| @fix             | 修复了一些东西，但不是面向用户的错误                        |
| @build           | 处理编译警告或错误                                          |
| @feature         | 增加了一些新的东西                                          |
| @performance     | 提高了性能                                                  |
| @refactor        | 移动或重写代码，但不改变行为                                |
| @tweak           | 更改值或设置                                                |
| @info            | 为下一个阅读器写入有用的信息                                |
| @todo            | 如果真的有必要，还可以添加一个备注                          |

块注释示例

```
    // TheSuperHackers @bugfix JAJames 17/03/2025修复未初始化的内存访问并添加更多Windows版本。
    memset(&os_info,0,sizeof(os_info));
```

还可以选择将pull请求号附加到注释中。这只能在创建拉取请求之后完成。

```
// TheSuperHackers @bugfix JAJames 17/03/2025 Fix uninitialized memory access and add more Windows versions. (#123)
```

### 拉取请求文档

一个新的Pull Request的标题，和/或commit(s)在其中，以一个开头 [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/) 标签。标签后面是一个关于更改和/或提交的简明描述性句子，以大写字母开头，结尾没有点。例如，句子最好以一个描述改变所采取的行动的词开头 `fix *this*`, `change *that*`, `add *those*`, `refactor *thing*`.

允许的（扩展的）提交标题类型是:
```
bugfix: 错误修复
build: 构建
chore: 杂务
ci:
docs: 文档
fix: 修复
feat: 壮举
perf: 性能
refactor: 重构
style: 风格
test: 测试
tweak: 调整
unify: 统一
```

对于类型后面的可选范围，选择一个描述更改所涉及的整体区域的合适单词。

Good:
```
bugfix(system): 修复Get_OS_Info中未初始化的内存访问
```

Bad:
```
成功构建所需的最小更改。
```

如果Pull Request是要与rebase合并，那么应该在文本主体的顶部添加**Merge with rebase **的注释，以帮助识别正确的合并操作，当它准备合并时。Pull Request的所有提交都需要正确命名，并且需要在括号中添加Pull Request的编号作为后缀。例如:* * * *(# 333)。所有提交都需要能够自己编译，而不需要依赖于同一个Pull Request的新提交。我更倾向于为**Squash和Merge**创建更改，因为这将简化事情。

正文以相关问题报告和/或拉取请求（如果适用）的链接开始。

要编写链接，请使用以下格式:

```
* Fixes #222
* Closes #333
* Relates to #555
* Follow up for #666
```

链接通常用于

* 在合并此拉取请求时关闭相关的问题报告或任务
* 当合并这个拉取请求时关闭另一个拉取请求

一些关键字由GitHub解释。读一读 [here](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue).

正文继续以适当的细节描述更改。这可以帮助审阅者和访问者更好地理解变更，而不需要研究和理解相关的变更文件。如果改变是有争议的，或者对游戏玩法有很大的影响，那么就需要添加一个基本的文本。基本原理解释了为什么给定的更改是有意义的。

### 拉取请求合并规则

合并更改时请注意。在提交标题一致性方面存在陷阱。

当尝试**压缩和合并**包含单个提交的Pull Request时，GitHub将默认从该单个提交生成一个提交标题。当新的提交标题与Pull Request标题保持同步而不是与Pull Request提交标题保持同步时，这通常是不希望看到的。生成的提交标题可能需要在合并Pull Request之前进行调整。

当尝试**压缩和合并**包含多个提交的拉请求时，GitHub将默认从拉请求标题生成一个提交标题。此外，它将从作为Pull Request一部分的多个提交生成一个提交描述。生成的提交描述通常需要在合并Pull Request之前清除，以保持提交标题干净。

当尝试Rebase和Merge一个Pull Request时，所有的提交都会以相同的名字转移到主分支。确认所有的提交标题都是正确制作的，在适当的地方加上标签，在括号后面加上Pull Request号，没有不必要的提交描述（提交标题下面的文本）。


### 更改日志文档

*工作正在进行中。*

---

# Regarding the contributions of GeneralsGameCodeCN

# 关于GeneralsGameCodeCN贡献

We still give priority to using the format already compiled by the community and add dual languages based on this to assist Chinese developers.

我们依然优先使用社区已经编好的格式，并为此为基础添加双语言，辅助中文开发者。

The key objective of this project is to analyze the source code and file content. Chinese will be given priority as the build language. To assist other builders, English will be used as notes and identifiers, and annotations and documentation will be written in both languages

此项目重要目的是分析源码及文件内容，将优先使用中文作为构建语言，为辅助其他构建者，英文将作为备注和标识，作为双语言写注释和文档。

If you don't know how to use Chinese, you can use a translator to add Chinese at the end according to our format

如果你不会使用中文，可以利用翻译机按照我们的格式在后方添加中文。

### 关于MD文档 - About the document

In the project, apart from the self-statement file, the upper part of the document is in English and the lower part is in Chinese. This is our common document format

项目中除了自述文件，文档中上方为英文，文档的下方则为中文，这是我们通用的文档格式。

<br>

文档格式例 - Document format example:
```
1. 同步格式 - Synchronous format

# [English Title]

# [中文标题 - Chinese Title]

The content of the document is the same. First, write a Chinese note at the top, and then a Chinese note at the bottom.
If the title is too large or too long and affects reading, please divide it into two bilingual titles according to the format.
Otherwise, if it is just a subtitle, you can add a - symbol after the language of the subtitle as the next language note

文档内容同理，上方优先写一个中文，下方则是中文备注，如果是标题太大太长影响阅读，那么请分为两个双语标题按照格式，反之只是小标题语言的后面可以加上 - 符号 后面作为后一个语言备注

2. 分语言格式 - By language format

这是最为推荐的一种格式，编者按照自己的习惯，写完一篇md文档，在后面用 ---分隔线 为另一篇语言备注。

This is the most recommended format. The editor, according to their own habits, finishes writing an md document and uses a -- delimiter line at the end to mark another language note.

```

### 格式示例 - Format example

```
源码注释 - Source Code comment:

//Function function explanation[English] - 函数功能解释[Chinese]

```


