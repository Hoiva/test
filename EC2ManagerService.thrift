include "EC2Common.thrift"


service EC2ManagerService {
    void ping(),
    bool isMainReciver(),
    bool isLogin(),
    
    EC2Common.RetInfo loginAction(string userName, string password),
    EC2Common.RetInfo logoutAction(),


    //�û��������
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

    //U��
    void setUDiskState(EC2Common.UdiskStateType udiskState),
    EC2Common.UdiskStateType getUdiskState(),

    //�ź�Դ
    list<EC2Common.SignalOSDInfo> getSignalList(EC2Common.SignalListType listType = EC2Common.SignalListType.SignalListTypeAll, EC2Common.SignalListSortType sortType = EC2Common.SignalListSortType.SignalListSortByName),
    list<EC2Common.SignalOSDInfo> searchSignalList(string keyword),
    list<EC2Common.PreviewOSDInfo> requestPreview(list<string> previewList),
    void closePreview(i32 previewChn),
    void closeAllPreview(),
    //���źŲ������ȴ�������������Ϣ����������
    void openSignalWndAction(EC2Common.ModelSignalOSDObj signal),
    //�ر��ź�
    void closeSignalWnd(i32 hwnd),
    void closeAllSignalWnd(),
    //�����ö�
    void setSignalWndTopmost(i32 hwnd),
    //�ƶ�����
    void moveSignalWnd(EC2Common.ModelSignalOSDObj signal),

    //��ȡ��ǰ�����źţ��ź�Դ���з�ʽ���մ��²㵽�ϲ�����
    EC2Common.ModelCubeOSDObj getCurrentSignals(),

    //Ԥ��
    list<EC2Common.ModelOSDInfo> getModelList(),
    string createModel(string modelName),
    void deleteModel(string modelID),
    void renameModel(string modelID, string modelName),
    void executeModel(string modelID),

    list<EC2Common.WallOSDInfo> getWallList(),
    list<EC2Common.LoginUserInfo> getLoginUserList(),
    //Э��(�ķ���/һ�������⣬��ʱ��Ҫȷ����Ҫ��Щ����ʵ��)
    void executePush2Wall(string wallID),
    void executePush2User(string userID),


    //TODO �ṩ���������������Ϣ�ĸ������ݽӿ�
    void loginUserChanged(EC2Common.LoginUserInfo loginUser),
    void logoutUserChanged(EC2Common.LogoutInfo logoutUser),
    //����Ҫ����ָ��ʱ��ʵ���·����Ǹ�ָ����ܺ��жϵ�ǰ�·��Ĵ��ڣ��ж�λ��/����/�ش�������
    void openWndListChanged(EC2Common.OpenSignalWndInfo openWndInfo),
    void userModelChanged(EC2Common.ModelListInfo modelList),
    void userConfigChanged(EC2Common.UserConfigInfo userConfigInfo),
    void devLayoutChanged(EC2Common.LayoutInfo layoutInfo)


}