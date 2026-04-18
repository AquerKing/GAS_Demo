# GAS_Demo

基于 **虚幻引擎 5.7** 的 **Gameplay Ability System（GAS）** 学习与演示项目，展示常见 GAS 搭建方式：玩家能力组件放在 **PlayerState**、敌人能力组件放在 **Character**，以及 Enhanced Input、Gameplay Tag、属性复制与简单近战检测等。

---

## 环境要求

| 项目 | 说明 |
|------|------|
| 引擎 | **Unreal Engine 5.7**（与 `GAS_Demo.uproject` 中 `EngineAssociation` 一致） |
| 平台 | Windows（当前仓库以 Win 开发为主） |

启用插件（见 `GAS_Demo.uproject`）：

- **GameplayAbilities**（GAS 核心）
- **ModelingToolsEditorMode**（仅编辑器目标）

---

## 快速开始

1. 双击 `GAS_Demo.uproject` 用对应版本引擎打开工程。  
2. 首次打开若提示模块需编译，选择 **是** 生成项目文件并编译 `GAS_Demo` 模块。  
3. 默认地图与游戏模式（见 `Config/DefaultEngine.ini`）：
   - **启动地图**：`/Game/GAS_Demo/Maps/Abattoir/Abattoir`
   - **全局默认 GameMode**：`BP_DemoGameMode`（`Content/GAS_Demo/Game/`）

> 仓库中的 `Binaries`、`Intermediate`、`Saved`、`DerivedDataCache` 等目录通常不应提交版本库；克隆后需在本地重新生成/编译。

---

## 功能概览

- **玩家**：第三人称移动与镜头；通过 **Enhanced Input** 绑定移动、视角、跳跃与主/副/第三技能槽位；技能通过 **Gameplay Tag**（如 `GDTags.GDAbilities.Primary`）激活。  
- **能力系统组件（ASC）**：
  - 玩家：`UGD_AbilitySystemComponent` 挂在 **`AGD_PlayerState`** 上，复制模式为 **Mixed**，便于持久化与常见多人范例。  
  - 敌人：`UGD_AbilitySystemComponent` 挂在 **`AGD_EnemyCharacter`** 上，复制模式为 **Minimal**。  
- **属性集 `UGD_AttributeSet`**：生命/最大生命、法力/最大法力；支持复制与 `OnRep_` 通知；首次由 GameplayEffect 初始化后会广播 `OnAttributesInitialized`。  
- **自定义 ASC**：在授予能力时根据 Asset Tag 是否匹配 **`ActivateOnGiven`** 自动尝试激活能力；并提供按类设置/增加能力等级的蓝图可调用接口。  
- **主技能 `UGD_Primary`（C++）**：在角色前方做球形 **Overlap** 检测命中 Pawn，并向命中目标发送 **`HitReact`** 类型的 Gameplay Event，驱动敌人受击表现（具体动画与 GA 在内容侧配置）。  
- **受击 `UGD_HitReact`**：提供受击方向相关向量缓存，配合 **`UGD_BlueprintLibrary`** 中的受击方位枚举，便于蒙太奇或动画蓝图分支。  
- **UI**：`UGD_WidgetComponent` 在 ASC 初始化后，按 **属性映射表** 将 `UGD_AttributeWidget` 等控件绑定到 GAS 属性变化。

内容资源主要位于 `Content/GAS_Demo/`（角色蓝图、GA/GE、输入、UI、`Abattoir` 关卡等），并包含 **Paragon** 示例角色资源目录（如 `ParagonBoris`、`ParagonMinions`）用于展示或绑定。

---

## 技术要点

### 1. ASC 归属与 `InitAbilityActorInfo`

- **玩家**：`UAbilitySystemComponent` 与 `UAttributeSet` 创建在 **`AGD_PlayerState`**。在 `AGD_PlayerCharacter::PossessedBy`（服务端有权限时）与 `OnRep_PlayerState`（客户端收到复制后的 PlayerState）中调用  
  `InitAbilityActorInfo(GetPlayerState(), this)`，  
  使 **OwnerActor** 为 PlayerState、**AvatarActor** 为实际角色，符合「数据随 PlayerState 持久、表现随 Pawn」的常见多人写法。
- **敌人**：ASC 与 AttributeSet 挂在 **`AGD_EnemyCharacter`**，`BeginPlay` 中执行  
  `InitAbilityActorInfo(this, this)`，  
  敌人为 AI/非玩家时无需 PlayerState，Owner 与 Avatar 同为该 Character 即可。

### 2. 网络复制策略

- 玩家 ASC：`SetReplicationMode(Mixed)`，兼顾 GameplayEffect 与预测相关需求在演示工程中的典型默认。
- 敌人 ASC：`Minimal`，减少非玩家实体上的 GE 复制开销，适合大量 AI 的简化策略（具体是否满足你的玩法需自行评估）。

### 3. 能力授予与「授予即激活」

- `UGD_AbilitySystemComponent` 重写 **`OnGiveAbility`** 与 **`OnRep_ActivateAbilities`**，在客户端收到可复制能力列表后同样走一遍逻辑，避免仅服务端激活、客户端不同步的问题。
- 若某 `UGameplayAbility` 的 **Asset Tags** 含原生 Tag **`GDTags.GDAbilities.ActivateOnGiven`**（精确匹配），则对该 Spec 调用 **`TryActivateAbility`**，用于被动、持续型或受击反应等「发到身上就要跑」的能力。

### 4. 输入与能力绑定

- **`AGD_PlayerController`** 使用 **Enhanced Input**：向 Local Player 子系统添加多个 **Mapping Context**，将 Primary/Secondary/Tertiary 等 Action 回调到 **`ActivateAbility(FGameplayTag)`**。
- 实际激活通过 **`UAbilitySystemComponent::TryActivateAbilitiesByTag`**，与 GA 上配置的 **Ability Tags**（如 `Primary` / `Secondary` / `Tertiary`）对齐，实现「输入层只认 Tag、具体逻辑在 GA」。

### 5. 主技能命中与 Gameplay Event

- **`UGD_Primary::HitBoxOverlapTest`**：在角色前向偏移位置做 **球体 Overlap**，查询通道为 **`ECC_Visibility`**，并通过 **`CollisionResponse`** 仅对 **`ECC_Pawn`** 为 Block，其余忽略，从而筛出 Pawn。
- **`SendHitReactEventToActor`** 使用 **`UAbilitySystemBlueprintLibrary::SendGameplayEventToActor`**，事件 Tag 为 **`GDTags::Events::Enemy::HitReact`**，Payload 中带 **Instigator**，便于目标侧 GA（如 HitReact）做蒙太奇或 GameplayCue。

### 6. 属性集与 UI

- **`UGD_AttributeSet`** 使用 **`ATTRIBUTE_ACCESSORS`** 宏生成 GameplayAttribute 访问器；生命/法力等属性在 **`GetLifetimeReplicatedProps`** 中使用 **`COND_None` + `REPNOTIFY_Always`**，保证每次复制更新都能触发 UI 或 GameplayCue 依赖的 RepNotify。
- **`bAttributesInitialized`** 在 **`PostGameplayEffectExecute`** 中置位并广播，用于「初始 GE 执行完再绑 UI」等顺序控制。
- **`UGD_WidgetComponent`** 监听 **`AGD_CharacterBase::OnASCInitialized`**，在 ASC 与 AttributeSet 有效后按 **`AttributeMap`** 把 **`UGD_AttributeWidget`** 绑到对应 **`GameplayAttribute`** 的变化上。

### 7. 动画与专用服务器

- **`AGD_CharacterBase`** 将 SkeletalMesh 的 **`VisibilityBasedAnimTickOption`** 设为 **`AlwaysTickPoseAndRefreshBones`**，在无渲染的专用服务器上仍能刷新骨骼姿势，有利于根运动或依赖骨骼数据的受击/攻击判定。

### 8. 原生 Gameplay Tag

- Tag 在 **`GD_Tags.h`** 中以 **`UE_DECLARE_GAMEPLAY_TAG_EXTERN`** 声明，在 **`GD_Tags.cpp`** 中以 **`UE_DEFINE_GAMEPLAY_TAG_COMMENT`** 定义并附注释，便于 C++ 侧强类型引用、与编辑器 **Gameplay Tag 项目设置** 中的字典一致。

---

## 源码结构（`Source/GAS_Demo`）

| 路径 | 作用 |
|------|------|
| `Characters/` | `AGD_CharacterBase`（抽象基类：初始能力、属性初始化 GE）、`AGD_PlayerCharacter`、`AGD_EnemyCharacter` |
| `Player/` | `AGD_PlayerState`（玩家 ASC + AttributeSet）、`AGD_PlayerController`（Enhanced Input + 按 Tag 激活能力） |
| `AbilitySystem/` | `UGD_AbilitySystemComponent`、`UGD_AttributeSet` |
| `AbilitySystem/Abilities/` | `UGD_GameplayAbility` 基类；`Player/GD_Primary`；`Enemy/GD_HitReact` |
| `GameplayTags/GD_Tags.*` | 原生 Gameplay Tag 声明与定义（能力槽位、授予即激活、敌人受击事件等） |
| `UI/` | `UGD_WidgetComponent`、`UGD_AttributeWidget` |
| `Utils/GD_BlueprintLibrary.*` | 受击方向等蓝图工具函数 |

模块依赖见 `GAS_Demo.Build.cs`：`GameplayAbilities`、`GameplayTags`、`GameplayTasks`、`EnhancedInput`、`UMG` 等。

---

## 配置与扩展提示

- **初始属性**：在角色蓝图（或子类）中为 `AGD_CharacterBase` 配置 **`InitializedAttributesEffect`**（工程中已有 `GE_InitializeAttributes` 等资源可参考路径 `Content/GAS_Demo/AbilitySystem/GameplayEffects/`）。  
- **开局技能**：在同一处配置 **`StartupAbilities`** 数组。若某能力的 Asset Tag 包含 **`GDTags.GDAbilities.ActivateOnGiven`**，授予后会由 `UGD_AbilitySystemComponent` 自动 `TryActivate`。  
- **输入**：在 `AGD_PlayerController` 上指定 **Input Mapping Context** 与各 **Input Action**（`Content/GAS_Demo/Input/` 下已有相关资源目录）。

---

## 版权

工程设置中的版权信息为：**Copyright AquerKing**（见 `Config/DefaultGame.ini` 与部分源码文件头）。

若本 README 与引擎或插件行为存在出入，以你本机安装的 **UE 5.7** 官方文档为准。
