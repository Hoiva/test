include "EC2Common.thrift"

service EC2QTService {
    //接收住服务主动推送过来的消息
    oneway void onLoginChange(string userID, string userName),
    oneway void onLogoutChange(string userID),
}