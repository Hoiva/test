include "EC2Common.thrift"

service EC2QTService {
    //����ס�����������͹�������Ϣ
    oneway void onLoginChange(string userID, string userName),
    oneway void onLogoutChange(string userID),
}