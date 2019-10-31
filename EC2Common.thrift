struct RetInfo {
    1: i32 errCode,
    2: string errStr
}

//心跳相关信息
struct HardwareInfo {
    1: double cpuTemprature,
    2: i64 deviceRunTime
}

struct AlarmInfo {
    1: string alarmID,
    2: string alarmEvent,
    3: string alarmLevel,
    4: i64 alarmRunTime,
    5: string alarmContent
}

struct SoftwareObj {
    1: string moduleName,
    2: list<AlarmInfo> alarmList
}


//界面相关消息
enum LayoutTypeEnum {
    LayoutTypeOneSplit = 0,
    LayoutTypeFourSplit = 1,
    LayoutTypeCustomSplit = 2
}

enum MenuDirectionType {
    MenuDirectionTop = 0,
    MenuDirectionBottom = 1
}

enum UdiskStateType {
    UdiskStateTypeNone = 0,
    UdiskStateTypeConnect = 1,
    UdiskStateTypeDisconnect = 2
}

enum SignalListSortType {
    SignalListSortByType = 0,
    SignalListSortByName = 1,
    SignalListSortByRate = 2,
}

enum SignalListType {
    SignalListTypeAll,
    SignalListTypeEC2000,
    SignalListTypeProcessor,
    SignalListTypeFibreOptical,
    SignalListTypeStreamMedia
}

struct EC2ResolutionInfo {
    1: i32 width,
    2: i32 height
}

//这里提供的信息只是针对登录用户对应的某一个位置上发送盒的，并不能获取全部信息
struct UserCfgOSDInfo {
    1: double menuOpacity,
    2: i32 volume,
    3: LayoutTypeEnum layoutType,
    4: EC2ResolutionInfo resInfo,
    5: MenuDirectionType menuDirection
}

struct SignalOSDInfo {
    1: string signalID,
    2: string signalName,
    3: i32 mainType,
    4: i32 subType
}

struct PreviewOSDInfo {
    1: string signalID,
    2: i32 previewChn,
}

struct SignalWndObj {
    1: i32 x,
    2: i32 y,
    3: i32 w,
    4: i32 h,
    5: i32 clipX,
    6: i32 clipY,
    7: i32 clipW,
    8: i32 clipH,
    9: optional i32 wndID,//当打开信号窗口时，qt不负责维护窗口句柄，不填。
    10: SignalOSDInfo signal
}

struct ModelCubeOSDObj {
    1: i32 x,
    2: i32 y,
    3: LayoutTypeEnum layoutType,
    4: list<SignalWndObj> signalList
}

struct ModelOSDInfo {
    1: string modelID,
    2: string modelName,
    3: list<ModelCubeOSDObj> model
}

struct WallOSDInfo {
    1: string wallID,
    2: string wallName
}

//接收盒网络相关消息
struct LoginInfo {
    1: string layoutID,
    2: string userName,
    3: string password
}

struct LoginRetInfo {
    1: RetInfo ret,
    2: string userID
}

struct LogoutInfo {
    1: string userID
}

struct LoginUserInfo {
    1: string userID,
    2: string userName
}

struct ReciverLayoutObj {
    1: string devID,
    2: string chnID,
    3: string name,
    4: bool isMain,
    5: i32 startX,
    6: i32 startY
}

struct LayoutInfo {
    1: i32 syncCode,
    2: string layoutID,
    3: string layoutName,
    4: list<ReciverLayoutObj> reciverList
}

struct LayoutRetInfo {
    1: RetInfo ret,
    2: LayoutInfo layoutInfo
}

struct OpenSignalWndInfo {
    1: i32 syncCode,
    2: string openSignalWndStr
}
struct OpenSignalWndRetInfo {
    1: RetInfo ret,
    2: TempModelInfo tmpModelInfo
}

struct ModelInfo {
    1: string modelID,
    2: string modelName,
    3: string modelContent
}

struct ModelListInfo {
    1: i32 syncCode,
    2: list<ModelInfo> modelList
}

struct ModelRetInfo {
    1: RetInfo ret,
    2: ModelListInfo modelList
}

struct UserConfigInfo {
    1: i32 syncCode,
    2: string configStr
}

struct UserConfigRetInfo {
    1: RetInfo ret,
    2: UserConfigInfo userInfo
}


struct UserSignalInfo {
    1: i32 syncCode,
    2: string signalListStr
}

struct UserSignalRetInfo {
    1: RetInfo ret,
    2: UserSignalInfo signalInfo
}

struct OnlineUserObj {
    1: string userID,
    2: string userName,
    3: string layoutID,
    4: string layoutName,
    5: string ec2Name
}

struct OnlineUserInfo {
    1: i32 syncCode,
    2: list<OnlineUserObj> userList
}

struct OnlineUserRetInfo {
    1: RetInfo ret,
    2: OnlineUserInfo onlineUserInfo
}

struct UserWallObj {
    1: string wallID,
    2: string wallName,
    3: i32 row,
    4: i32 column,
    5: i32 unitW,
    6: i32 unitH,
    7: i32 totalW,
    8: i32 totalH,
    9: string keyID,
    10: i32 startX,
    11: i32 startY,
    12: i32 endX,
    13: i32 endY
}

struct UserWallInfo {
    1: i32 wallSyncCode,
    2: i32 userScreenSyncCode,
    3: list<UserWallObj> wallList
}

struct UserWallRetInfo {
    1: RetInfo ret,
    2: UserWallInfo userWallInfo
}