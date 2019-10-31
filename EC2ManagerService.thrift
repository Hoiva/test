include "EC2Common.thrift"


service EC2ManagerService {
    void ping(),
    bool isMainReciver(),
    bool isLogin(),
    
    EC2Common.RetInfo loginAction(string userName, string password),
    EC2Common.RetInfo logoutAction(),


    //用户配置相关
    void setMenuOpacity(double menuOpacity),
    double getMenuOpacity(),
    void setVolume(i32 volume),
    i32 getVolume(),
    void setLayoutType(EC2Common.LayoutTypeEnum layoutType),
    EC2Common.LayoutTypeEnum getLayoutType(),
    void setResolution(EC2Common.EC2ResolutionInfo resInfo),
    EC2Common.EC2ResolutionInfo getResolution(), 
    void setMenuDirection(EC2Common.MenuDirectionType direction),
    EC2Common.MenuDirectionType getMenuDirection(),
    void setUserCfgInfo(EC2Common.UserCfgOSDInfo userInfo),
    EC2Common.UserCfgOSDInfo getUserCfgInfo(),

    //U盘
    void setUDiskState(EC2Common.UdiskStateType udiskState),
    EC2Common.UdiskStateType getUdiskState(),

    //信号源
    list<EC2Common.SignalOSDInfo> getSignalList(EC2Common.SignalListType listType = EC2Common.SignalListType.SignalListTypeAll, EC2Common.SignalListSortType sortType = EC2Common.SignalListSortType.SignalListSortByName),
    list<EC2Common.SignalOSDInfo> searchSignalList(string keyword),
    list<EC2Common.PreviewOSDInfo> requestPreview(list<string> previewList),
    void closePreview(i32 previewChn),
    void closeAllPreview(),
    //打开信号操作，等待主服务推送消息才真正开窗
    void openSignalWndAction(EC2Common.ModelSignalOSDObj signal),
    //关闭信号
    void closeSignalWnd(i32 hwnd),
    void closeAllSignalWnd(),
    //设置置顶
    void setSignalWndTopmost(i32 hwnd),
    //移动窗口
    void moveSignalWnd(EC2Common.ModelSignalOSDObj signal),

    //获取当前所有信号，信号源排列方式按照从下层到上层排列
    EC2Common.ModelCubeOSDObj getCurrentSignals(),

    //预案
    list<EC2Common.ModelOSDInfo> getModelList(),
    string createModel(string modelName),
    void deleteModel(string modelID),
    void renameModel(string modelID, string modelName),
    void executeModel(string modelID),

    list<EC2Common.WallOSDInfo> getWallList(),
    list<EC2Common.LoginUserInfo> getLoginUserList(),
    //协作(四分屏/一分屏问题，暂时需要确定需要那些参数实现)
    void executePush2Wall(string wallID),
    void executePush2User(string userID),


    //TODO 提供网络适配层推送消息的更新数据接口
    void loginUserChanged(EC2Common.LoginUserInfo loginUser),
    void logoutUserChanged(EC2Common.LogoutInfo logoutUser),
    //当需要开窗指令时，实际下发的是该指令，接受盒判断当前下发的窗口，判断位移/开窗/关窗操作。
    void openWndListChanged(EC2Common.OpenSignalWndInfo openWndInfo),
    void userModelChanged(EC2Common.ModelListInfo modelList),
    void userConfigChanged(EC2Common.UserConfigInfo userConfigInfo),
    void devLayoutChanged(EC2Common.LayoutInfo layoutInfo)


}