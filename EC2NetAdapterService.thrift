include "EC2Common.thrift"

struct ENCAttribute {
    1: string chnID,
    2: string encType,
    3: string IP
}

struct DECAttribute {
    1: string chnID
}

// ���豸����Ϊ���ͺ�ʱ��ֻ��encAttrList��Ϊ���պ�ʱ��ֻ��decAttrList
struct OnlineMsg {
    1: string devIP,
    2: string deviceType,
    3: string softwareVersion,
    4: string hardwareVersion,
    5: list<ENCAttribute> encAttrList,
    6: list<DECAttribute> decAttrList
}

struct OnlineRetMsg {
    1: EC2Common.RetInfo ret,
    2: string devID;
}

struct HeartbeatMsg {
    1: EC2Common.HardwareInfo hardwareInfo,
    2: list<EC2Common.SoftwareObj> softwareInfo
}

service EC2NetAdapterService {
    //�����豸��Ϣ�����豸����ģ�����
    OnlineRetMsg sendOnlineMsg(OnlineMsg onlineMsg),
    EC2Common.RetInfo sendHeartbeatMsg(HeartbeatMsg heartbeatMsg),

    //����ҵ����Ϣ
    EC2Common.LoginRetInfo sendLoginMsg(EC2Common.LoginInfo loginInfo),
    EC2Common.RetInfo sendLogoutMsg(string userID),

    //����������Ϣ����get��set��
    EC2Common.LayoutRetInfo getLayoutInfo(string devID),

    EC2Common.OpenSignalWndRetInfo getOpenWndList(string userID),
    // EC2Common.RetInfo setTmpModel(string userID, string tmpModel),
    EC2Common.RetInfo openSignalWnd(EC2Common.SignalWndObj signalWnd),
    EC2Common.RetInfo closeSignalWnd(string userID, i32 wndID),
    EC2Common.RetInfo moveSignalWnd(),
    
    EC2Common.ModelRetInfo getModel(string userID, list<string> modelIDList),
    EC2Common.RetInfo setModel(string userID, EC2Common.ModelInfo model),

    EC2Common.UserConfigRetInfo getUserConfig(string userID),
    EC2Common.RetInfo setUserConfig(string userID, EC2Common.UserConfigInfo userCfg),

    EC2Common.UserSignalRetInfo getUserSignal(string userID),

    EC2Common.OnlineUserRetInfo getUserOnlineInfo(string userID),

    EC2Common.UserWallRetInfo getUserWallInfo(string userID)
}